#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include <string>
#include "SRT_List.h"

class SubtitlesExceptions : public std::exception {};

class SubtitlesNotFoundExceptions : public SubtitlesExceptions {
public:
	const char* what() const override {
		return "The file with subtitles was not found";
	}
};

class SubtitlesPlayer final {
private:
	SRTList list_sub;
public:
	SubtitlesPlayer(const std::string& SubtitlePath) {
		std::ifstream subtitles_file;
		subtitles_file.open(SubtitlePath);
		if (!subtitles_file.is_open()) {
			throw SubtitlesNotFoundExceptions();
		}
		list_sub.full_list(SubtitlePath);
		subtitles_file.close();
	}
	SubtitlesPlayer(const SubtitlesPlayer& other) = default;
	void play(const int& time_ms) {
		auto found_value = list_sub.find_sub(time_ms);
		cv::Mat subtitles(100, 640, CV_8UC3, cv::Scalar(255, 255, 255));
		if (found_value.has_value()){
			cv::putText(subtitles, found_value->get_text(), cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
		}
		else {
			cv::putText(subtitles, "", cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
		}
		cv::imshow("Subtitles", subtitles);
	}
};