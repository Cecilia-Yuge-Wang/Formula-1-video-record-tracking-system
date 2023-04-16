g++ -g -o demo demo.cpp src/frameprocess.cpp -I src/include -I include/ncnn lib/libncnn.a `pkg-config --libs --cflags opencv` -fopenmp
