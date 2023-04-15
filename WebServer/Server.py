import time
import cv2
import numpy as np
import subprocess
import re
from flask import Flask, render_template, Response
from PIL import ImageGrab

app = Flask(__name__)


def get_window_geometry(window_name):
    try:
        output = subprocess.check_output(['xwininfo', '-name', window_name])
        x = int(re.search(b'Absolute upper-left X:  (\d+)', output).group(1))
        y = int(re.search(b'Absolute upper-left Y:  (\d+)', output).group(1))
        w = int(re.search(b'Width: (\d+)', output).group(1))
        h = int(re.search(b'Height: (\d+)', output).group(1))
        return x, y, w, h
    except subprocess.CalledProcessError:
        return 0, 0, 0, 0



def gen_frames():
    while True:
        x, y, w, h = get_window_geometry('Camera')
        if (x, y, w, h) != (0, 0, 0, 0):
            img = ImageGrab.grab(bbox=(x, y, x + w, y + h))
            img_np = np.array(img)
            frame = cv2.cvtColor(img_np, cv2.COLOR_BGR2RGB)
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
        else:
            print("Camera window not found.")
            time.sleep(1)


@app.route('/')
def index():
    return render_template('index.html')

@app.route('/video_feed')
def video_feed():
    return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

