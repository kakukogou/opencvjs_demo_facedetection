#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/video.hpp>

namespace kaku {

static bool isInitialized = false;
static cv::Mat prevFrame;
static cv::Mat prevPts;

extern "C" {
extern int kaku_feature_tracking_demo(void const *imageData, int width, int height) {

	// convert color
	cv::Mat frame_rgba(height, width, CV_8UC4, (unsigned char*)(imageData));
    cv::Mat frame_gray;
    cv::cvtColor(frame_rgba, frame_gray, cv::COLOR_RGBA2GRAY);

	if (!isInitialized) {
		
		// features2d::FeatureList features;
		
		// detect features
		cv::Mat pts;
		cv::goodFeaturesToTrack(frame_gray, pts, 100, 0.01, 0.0);
		prevFrame = frame_gray;
		prevPts = pts;
		isInitialized = true;

		// printf("first pts.size() = %d\n", pts.rows);
	}
	else {
		cv::Mat nextPts;
		cv::Mat status;
		int const winSize = 5;
		int const levels = 3;
		int const iters = 10;
		cv::calcOpticalFlowPyrLK(prevFrame, frame_gray, prevPts, nextPts, status, cv::noArray(),
								 cv::Size(winSize, winSize), levels - 1,
								 cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, iters, 0.01));

		// printf("prevPts.rows = %d\n", prevPts.rows);
		// printf("status.rows = %d\n", status.rows);
		for (int i = 0; i < prevPts.rows; ++i) {
			if (*status.ptr<unsigned char>(i) == 1) {
				float *pt = nextPts.ptr<float>(i);
				cv::circle(frame_rgba, cv::Point(*(pt+0), *(pt+1)), 5, cv::Scalar(255,255,0), -1);
			}
		}

		// printf("nextPts.size() = %d\n", nextPts.rows);
	}

	return 1;
}
}
}