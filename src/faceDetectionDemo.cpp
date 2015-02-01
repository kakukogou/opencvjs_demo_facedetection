#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/objdetect/detection_based_tracker.hpp>

//DetectionBasedTracker



namespace kaku {

/** Global variables */
static bool isInitialized = false;
cv::String const face_cascade_name = "lbpcascade_frontalface.xml";
cv::String const eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;

/**
 * @function detectAndDisplay
 */
static void detectAndDisplay(cv::Mat frame, double scaleFactor, int minWidth, int minHeight)
{
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;

    cv::cvtColor( frame, frame_gray, cv::COLOR_RGBA2GRAY );
    cv::equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    clock_t c = clock();
    face_cascade.detectMultiScale( frame_gray, faces, scaleFactor, 3, 0, cv::Size(minWidth, minHeight) );
    printf("detectMultiScale(): #faces = %u, %f ms\n", faces.size(), ((float)(clock() - c)*1000.0f/CLOCKS_PER_SEC));

    for( size_t i = 0; i < faces.size(); i++ )
    {
        // cv::Mat faceROI = frame_gray( faces[i] );
        // std::vector<cv::Rect> eyes;

        //-- In each face, detect eyes
        // eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );
        // if( eyes.size() == 2)
        // {
            //-- Draw the face
            cv::Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            cv::ellipse( frame, center, cv::Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, cv::Scalar( 255, 0, 0 ), 5, 8, 0 );

            // for( size_t j = 0; j < eyes.size(); j++ )
            // { //-- Draw the eyes
            //     cv::Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            //     int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            //     cv::circle( frame, eye_center, radius, cv::Scalar( 255, 0, 255 ), 3, 8, 0 );
            // }
        // }
    }

    //-- Show what you got
    //imshow( window_name, frame );
}

extern "C" {
extern int kaku_face_detection_demo(void const *array, int width, int height, double scaleFactor, int minWidth, int minHeight) {
	
	cv::Mat image(height, width, CV_8UC4, (unsigned char*)(array));

//	detectFeatures(image);

    //-- 1. Load the cascade
    if (!isInitialized) {
	    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
	    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };
	    isInitialized = true;
	}	    

	detectAndDisplay(image, scaleFactor, minWidth, minHeight);
	
	return 0;
}
}
}