#include <math.h>
#include <algorithm>
#include "frameprocess.h"
#include <thread>


//Parameter configuration of the model

const char** CNN::class_names = nullptr;

CNN::CNN()
{   
    printf("Creat frameprocess ...\n");
    //Number of output point
    numOutput = 2;
    
    //Number of Thread
    numThreads = 4;
    
    //anchor num
    numAnchor = 3;
    
    //Category number
    numCategory = 1;
   
    //NMS Thresh
    nmsThresh = 0.25;

    //Size of Model Input
    inputWidth = 352;
    inputHeight = 352;

    //Name of Model input point 
    inputName = "input.1";
    outputName1 = "794"; //22x22
    outputName2 = "796"; //11x11

    //Print initialization Information
    printf("numThreads:%d\n", numThreads);
    printf("inputWidth:%d inputHeight:%d\n", inputWidth, inputHeight);

    //anchor box w h
    std::vector<float> bias {98.65,138.84, 134.40,75.68, 155.02,213.15, 166.34,116.23, 223.98,139.03, 264.10,187.48};

    anchor.assign(bias.begin(), bias.end());
    
    class_names = new const char*[1];
    class_names[0] = "Ferrari";
    
}



//Load class names

void CNN::read_class_names(const char* filename) {
    std::vector<std::string> class_names_vec;
    std::string line;
    std::ifstream file(filename, std::ios::in);
    if (file.is_open()) {
        while (std::getline(file, line)) {
            class_names_vec.push_back(line);
        }
        file.close();
        // Convert vector of strings to array of char pointers
        class_names = new const char*[class_names_vec.size()];
        for (int i = 0; i < class_names_vec.size(); ++i) {
            class_names[i] = class_names_vec[i].c_str();
        }
    }
}





CNN::~CNN()
{
     delete[] class_names;
    printf("Destroy frameprocess...\n");
}

//ncnn model load
int CNN::loadModel(const char* paramPath, const char* binPath)
{
    printf("Ncnn mode init:\n%s\n%s\n", paramPath, binPath);

    net.load_param(paramPath);
    net.load_model(binPath);    

    printf("Ncnn model init sucess...\n");

    return 0;
}

float intersection_area(const TargetBox &a, const TargetBox &b)
{
    if (a.x1 > b.x2 || a.x2 < b.x1 || a.y1 > b.y2 || a.y2 < b.y1)
    {
        // no intersection
        return 0.f;
    }

    float inter_width = std::min(a.x2, b.x2) - std::max(a.x1, b.x1);
    float inter_height = std::min(a.y2, b.y2) - std::max(a.y1, b.y1);

    return inter_width * inter_height;
}

bool scoreSort(TargetBox a, TargetBox b) 
{ 
    return (a.score > b.score); 
}

//NMS Process
int CNN::nmsHandle(std::vector<TargetBox> &tmpBoxes, 
                             std::vector<TargetBox> &dstBoxes)
{
    std::vector<int> picked;
    
    sort(tmpBoxes.begin(), tmpBoxes.end(), scoreSort);

    for (int i = 0; i < tmpBoxes.size(); i++) {
        int keep = 1;
        for (int j = 0; j < picked.size(); j++) {
            //Intersections
            float inter_area = intersection_area(tmpBoxes[i], tmpBoxes[picked[j]]);
            //Union
            float union_area = tmpBoxes[i].area() + tmpBoxes[picked[j]].area() - inter_area;
            float IoU = inter_area / union_area;

            if(IoU > nmsThresh && tmpBoxes[i].cate == tmpBoxes[picked[j]].cate) {
                keep = 0;
                break;
            }
        }

        if (keep) {
            picked.push_back(i);
        }
    }
    
    for (int i = 0; i < picked.size(); i++) {
        dstBoxes.push_back(tmpBoxes[picked[i]]);
    }

    return 0;
}



//Score of category processing
int CNN::getCategory(const float *values, int index, int &category, float &score)
{
    float tmp = 0;
    float objScore  = values[4 * numAnchor + index];

    for (int i = 0; i < numCategory; i++) {
        float clsScore = values[4 * numAnchor + numAnchor + i];
        clsScore *= objScore;

        if(clsScore > tmp) {
            score = clsScore;
            category = i;

            tmp = clsScore;
        }
    }
    
    return 0;
}

//Post-processing of feature maps
int CNN::predHandle(const ncnn::Mat *out, std::vector<TargetBox> &dstBoxes, 
                              const float scaleW, const float scaleH, const float thresh)
{    //do result
    for (int i = 0; i < numOutput; i++) {   
        int stride;
        int outW, outH, outC;

        outH = out[i].c;
        outW = out[i].h;
        outC = out[i].w;

        assert(inputHeight / outH == inputWidth / outW);
        stride = inputHeight / outH;

        for (int h = 0; h < outH; h++) {
            const float* values = out[i].channel(h);

            for (int w = 0; w < outW; w++) {
                for (int b = 0; b < numAnchor; b++) {                    
                    //float objScore = values[4 * numAnchor + b];
                    TargetBox tmpBox;
                    int category = -1;
                    float score = -1;

                    getCategory(values, b, category, score);

                    if (score > thresh) {
                        float bcx, bcy, bw, bh;

                        bcx = ((values[b * 4 + 0] * 2. - 0.5) + w) * stride;
                        bcy = ((values[b * 4 + 1] * 2. - 0.5) + h) * stride;
                        bw = pow((values[b * 4 + 2] * 2.), 2) * anchor[(i * numAnchor * 2) + b * 2 + 0];
                        bh = pow((values[b * 4 + 3] * 2.), 2) * anchor[(i * numAnchor * 2) + b * 2 + 1];
                        
                        tmpBox.x1 = (bcx - 0.5 * bw) * scaleW;
                        tmpBox.y1 = (bcy - 0.5 * bh) * scaleH;
                        tmpBox.x2 = (bcx + 0.5 * bw) * scaleW;
                        tmpBox.y2 = (bcy + 0.5 * bh) * scaleH;
                        tmpBox.score = score;
                        tmpBox.cate = category;

                        dstBoxes.push_back(tmpBox);
                    }
                }
                values += outC;
            } 
        } 
    }
    return 0;
}

//Detection processing
int CNN::detection(const cv::Mat srcImg, std::vector<TargetBox> &dstBoxes, const float thresh)
{   
    dstBoxes.clear();

    float scaleW = (float)srcImg.cols / (float)inputWidth;
    float scaleH = (float)srcImg.rows / (float)inputHeight;
    
    //resize of input image data
    ncnn::Mat inputImg = ncnn::Mat::from_pixels_resize(srcImg.data, ncnn::Mat::PIXEL_BGR,\
                                                       srcImg.cols, srcImg.rows, inputWidth, inputHeight); 

    //Normalization of input image data
    const float mean_vals[3] = {0.f, 0.f, 0.f};
    const float norm_vals[3] = {1/255.f, 1/255.f, 1/255.f};
    inputImg.substract_mean_normalize(mean_vals, norm_vals);  

    //creat extractor
    ncnn::Extractor ex = net.create_extractor();
    ex.set_num_threads(numThreads);

    //set input tensor
    ex.input(inputName, inputImg);

    //forward
    ncnn::Mat out[2]; 
    ex.extract(outputName1, out[0]); //22x22
    ex.extract(outputName2, out[1]); //11x11

    std::vector<TargetBox> tmpBoxes;
    //Post-processing
    predHandle(out, tmpBoxes, scaleW, scaleH, thresh);

    //NMS
    nmsHandle(tmpBoxes, dstBoxes);
    
    return 0;
}



//veideo capture thread
void CNN::processThread(cv::VideoCapture& cap) {

    while (!g_quit) {
        cap >> srcImg;  // read image from webcamera
        if (srcImg.empty()) {
            std::cerr << "Failed to capture frame." << std::endl;
            break;
        }
    }
}

//Output the vedio and create a new window
void CNN::showThread(cv::Mat& img) {
    while (!g_quit) {
        cv::imshow("Camera", img);
        if (cv::waitKey(1) == 27) {
            break;
        }
    }
}


//Draw rectangle and print imformation in vedio

void CNN::rectangle(const cv::Mat cvImg, std::vector<TargetBox>& boxes/*, const char* class_names[]*/){
   
  
   
    for (int i = 0; i < boxes.size(); i++) {
        std::cout << boxes[i].x1 << " " << boxes[i].y1 << " " << boxes[i].x2 << " " << boxes[i].y2
            << " " << boxes[i].score << " " << boxes[i].cate << std::endl;

        char text[256];
        sprintf(text, "%s %.1f%%", class_names[boxes[i].cate], boxes[i].score * 100);

        int baseLine = 0;
        cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);

        int x = boxes[i].x1;
        int y = boxes[i].y1 - label_size.height - baseLine;
        if (y < 0)
            y = 0;
        if (x + label_size.width > cvImg.cols)
            x = cvImg.cols - label_size.width;

        cv::rectangle(cvImg, cv::Rect(cv::Point(x, y), cv::Size(label_size.width, label_size.height + baseLine)),
            cv::Scalar(255, 255, 255), -1);

        cv::putText(cvImg, text, cv::Point(x, y + label_size.height),
            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));

        cv::rectangle(cvImg, cv::Point(boxes[i].x1, boxes[i].y1),
            cv::Point(boxes[i].x2, boxes[i].y2), cv::Scalar(255, 255, 0), 2, 2, 0);


        cv::Point center((boxes[i].x2 - boxes[i].x1) / 2 + boxes[i].x1, (boxes[i].y2 - boxes[i].y1) / 2 + boxes[i].y1);
          cv::circle(cvImg, center, 5, cv::Scalar(0, 255, 0), -1);
        
	rx = static_cast<int>((boxes[i].x2 - boxes[i].x1) / 2 + boxes[i].x1);
	//std::cout<<"x1="<<rx;
	ry = static_cast<int>((boxes[i].y2 - boxes[i].y1) / 2 + boxes[i].y1);
    }
        //return rx, ry;

}








