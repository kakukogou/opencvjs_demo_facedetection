# opencvjs_demo_facedetection

## Download and build opencv.js
[OpenCV.js installation guild](https://github.com/kakukogou/opencv/tree/opencvjs)

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
Open your Firefox and load *opencvjs_demo_facedetection/Demo_Segmentation_WebAPP/index.html*