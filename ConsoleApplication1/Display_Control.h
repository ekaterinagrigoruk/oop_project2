#pragma once
#include "Video_Player.h"
#include "Subtitles_Player.h"

class Display final 
{
private:
	VideoPlayer video;
	SubtitlesPlayer subs;
    int current_time = 0;
    bool is_paused = false;
    static void onButtonPressed(int event, int x, int y, int flags, void* userdata) {
        Display* display = static_cast<Display*>(userdata);
        if (event == cv::EVENT_LBUTTONDOWN) {
            if (x >= 50 && x <= 150 && y >= 50 && y <= 100) {
                if (display->is_paused) {
                    display->is_paused = false;
                }
                else {
                    display->is_paused = true;
                }
            }
            else if (x >= 200 && x <= 300 && y >= 50 && y <= 100) {
                display->video.forward(display->current_time);
            }
            else if (x >= 350 && x <= 450 && y >= 50 && y <= 100) {
                display->video.backward(display->current_time);
            }
        }
    }
public:
	Display(const VideoPlayer& video, const SubtitlesPlayer& subs) : video(video), subs(subs) {};
	void start() {
		cv::namedWindow("Display", cv::WINDOW_NORMAL);

        while (true) {
            if (!is_paused) {
                video.play("Display");
                subs.play(current_time);
                current_time += 30;
            }

            cv::Mat controls(150, 640, CV_8UC3, cv::Scalar(200, 200, 200));
            if (is_paused) {
                cv::rectangle(controls, cv::Rect(50, 50, 100, 50), cv::Scalar(100, 100, 100), -1);
                cv::putText(controls, "Play", cv::Point(60, 90), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
            }
            else {
                cv::rectangle(controls, cv::Rect(50, 50, 100, 50), cv::Scalar(100, 100, 100), -1);
                cv::putText(controls, "Pause", cv::Point(60, 90), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
            }
            cv::rectangle(controls, cv::Rect(200, 50, 100, 50), cv::Scalar(100, 100, 100), -1);
            cv::rectangle(controls, cv::Rect(350, 50, 100, 50), cv::Scalar(100, 100, 100), -1);
            cv::putText(controls, "+5s", cv::Point(210, 90), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
            cv::putText(controls, "-5s", cv::Point(370, 90), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);
            cv::imshow("Controls", controls);

            cv::setMouseCallback("Controls", onButtonPressed, this);

            char c = cv::waitKey(30);
            if (c == 27) {
                break;
            }
        }
        
	}
    
};