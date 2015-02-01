OPENCV_INSTALL_DIR=/Users/kakukogou/MyLib/opencv/release_asm/install
OBJDIR=./bin

all:facedetection

facedetection: ./bin/facedetection.bc 
	mkdir -p $(OBJDIR)
	emcc --bind \
	./bin/facedetection.bc \
	$(OPENCV_INSTALL_DIR)/lib/libopencv_core.so \
	$(OPENCV_INSTALL_DIR)/lib/libopencv_imgproc.so \
	$(OPENCV_INSTALL_DIR)/lib/libopencv_features2d.so \
	$(OPENCV_INSTALL_DIR)/lib/libopencv_video.so \
	$(OPENCV_INSTALL_DIR)/lib/libopencv_objdetect.so \
	-s EXPORTED_FUNCTIONS="['_kaku_face_detection_demo', '_kaku_feature_tracking_demo']" \
	-s TOTAL_MEMORY=46777216 \
	-O3 \
	-s PRECISE_F32=1 \
	--preload-file lbpcascade_frontalface.xml \
	--preload-file haarcascade_eye_tree_eyeglasses.xml \
	-o ./bin/facedetection.js

# --preload-file lbpcascade_frontalface.xml \
# --preload-file lbpcascade_profileface.xml \
# --preload-file lbpcascade_silverware.xml \
# --preload-file haarcascade_eye_tree_eyeglasses.xml \

./bin/facedetection.bc: ../src/faceDetectionDemo.cpp ../src/featureTrackingDemo.cpp
	mkdir -p $(OBJDIR)
	emcc \
	../src/faceDetectionDemo.cpp \
	../src/featureTrackingDemo.cpp \
	-I ../include \
	-I $(OPENCV_INSTALL_DIR)/include \
	-O3 \
	-s PRECISE_F32=1 \
	-o ./bin/facedetection.bc

clean:
	rm ./bin/*.bc ./bin/*.data ./bin/*js ./bin/*.mem

install:
	rsync -rupE ./bin/*.js ../Demo_FaceDetection_WebAPP_imageData/
	rsync -rupE ./bin/*.js.mem ../Demo_FaceDetection_WebAPP_imageData/
	rsync -rupE ./bin/*.data ../Demo_FaceDetection_WebAPP_imageData/
	rsync -rupE ./bin/*.js ../Demo_FaceDetection_WebAPP_imageBitmap/
	rsync -rupE ./bin/*.js.mem ../Demo_FaceDetection_WebAPP_imageBitmap/
	rsync -rupE ./bin/*.data ../Demo_FaceDetection_WebAPP_imageBitmap/