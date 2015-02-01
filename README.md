# opencvjs_demo_facedetection

## Download and build opencv.js
[OpenCV.js installation guide](https://github.com/kakukogou/opencv/tree/opencvjs)

## Compile

### Download this repository
<pre>
git clone https://github.com/kakukogou/opencvjs_demo_facedetection.git
cd opencvjs_demo_facedetection
cd emscripten_build
</pre>

### Set the installation folder of OpenCV.js
In **Makefile**, assign the **OPENCV_INSTALL_DIR** to your local path.
```
OPENCV_INSTALL_DIR=<your_opencvjs_local_repository>/release_asm/install
```

### Build
<pre>
make
make install
</pre>

### Run
Open your Firefox and load *opencvjs_demo_segmentation/Demo_FaceDetection_WebAPP_imageData/index.html*

* Demo_FaceDetection_WebAPP_imageBitmap is not supported by any released browser now. It is an experimental feature of Mozilla Firefox.