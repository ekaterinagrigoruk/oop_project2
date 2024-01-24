#pragma once
#include <opencv2/opencv.hpp>
#include <string>

class VideoExceptions : public std::exception {};

class VideoNotFoundExceptions : public VideoExceptions {
public:
	const char* what() const override {
		return "The file with video was not found";
	}
};

class VideoPlayer final {
private:

	cv::VideoCapture video;
	int max_count() {
		double fps = video.get(cv::CAP_PROP_FPS);
		double frameCount = video.get(cv::CAP_PROP_FRAME_COUNT);
		return frameCount / fps;
	}
public:
	VideoPlayer(const std::string& VideoPath) {
		video.open(VideoPath);
		if (!video.isOpened()) {
			throw VideoNotFoundExceptions();
		}
	}
	void play(const std::string& display) {
		cv::Mat current_frame;
		video.read(current_frame);
	    cv::imshow(display, current_frame);
	}
	void forward(int& time_ms) {
		video.set(cv::CAP_PROP_POS_FRAMES, video.get(cv::CAP_PROP_POS_FRAMES) + static_cast<double>(5 * 33));
		time_ms += 5 * 1000;
	}
	void backward(int& time_ms) {
		video.set(cv::CAP_PROP_POS_FRAMES, video.get(cv::CAP_PROP_POS_FRAMES) - static_cast < double>(5 * 33));
		if (time_ms - 5 * 1000 < 0) {
			time_ms = 0;
			return;
		}
		time_ms -= 5 * 1000;
	}
	~VideoPlayer() {
		video.release();
		cv::destroyAllWindows();
	}
};


