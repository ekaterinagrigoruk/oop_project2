#pragma once
#include <string>

class Subtitle final {
private:
	std::string text;
	int startTime;
	int endTime;
public:
	Subtitle(std::string text_, int startTime_, int endTime_) : text(text_), startTime(startTime_), endTime(endTime_) {}
	const int get_startTime() const {
		return startTime;
	}
	const int get_endTime() const {
		return endTime;
	}
	const std::string get_text() const {
		return text;
	}
};