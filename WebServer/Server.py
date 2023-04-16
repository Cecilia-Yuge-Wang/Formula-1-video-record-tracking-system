import time
import cv2
import numpy as np
import subprocess
import re
from flask import Flask, render_template, Response
from PIL import ImageGrab

app = Flask(__name__)

# Function to get the geometry of the specific window by its name
def get_window_geometry(window_name):
    try:
        # Run the 'xwininfo' command and capture its output
        output = subprocess.check_output(['xwininfo', '-name', window_name])

        # Extract window coordinates and dimensions using regex
        x = int(re.search(b'Absolute upper-left X:  (\d+)', output).group(1))
        y = int(re.search(b'Absolute upper-left Y:  (\d+)', output).group(1))
        w = int(re.search(b'Width: (\d+)', output).group(1))
        h = int(re.search(b'Height: (\d+)', output).group(1))
        return x, y, w, h

    except subprocess.CalledProcessError:
        return 0, 0, 0, 0


# Generate function to stream frames from the window
def gen_frames():
    while True:
        # Get the window called 'Camera' 
        x, y, w, h = get_window_geometry('Camera')

        if (x, y, w, h) != (0, 0, 0, 0):
            # Capture the content of the window
            img = ImageGrab.grab(bbox=(x, y, x + w, y + h))
            img_np = np.array(img)

            # Convert image to the proper color space
            frame = cv2.cvtColor(img_np, cv2.COLOR_BGR2RGB)

            # Encode image as JPEG
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()

            # Yield frame as part of the streaming response
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
                   
        else:
            print("Camera window not found.")
            time.sleep(1)


# Route for the homepage
@app.route('/')
def index():
    return render_template('index.html')

# Route for the video feed
@app.route('/video_feed')
def video_feed():
    return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

