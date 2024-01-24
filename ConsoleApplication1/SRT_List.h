#pragma once
#include <sstream>
#include <list>
#include "Subtitle.h"
#include "Subtitles_Player.h"

class SRTList final {
private:
	std::list<Subtitle> head{};
public:
	SRTList() = default;

	void full_list(const std::string& filename) {
		std::ifstream file(filename);

		std::string line;
		while (std::getline(file, line)) {
			int number;
			if (std::istringstream(line) >> number) {
				std::getline(file, line);

				int startTimeH, startTimeM, startTimeS, startTimeMs, endTimeH, endTimeM, endTimeS, endTimeMs;
				char arrow;
				std::istringstream iss(line);
				char colon;
				iss >> startTimeH >> colon >> startTimeM >> colon >> startTimeS >> colon >> startTimeMs >> arrow >> arrow >> arrow
					>> endTimeH >> colon >> endTimeM >> colon >> endTimeS >> colon >> endTimeMs;

				int startTime = startTimeH * 3600000 + startTimeM * 60000 + startTimeS * 1000 + startTimeMs;
				int endTime = endTimeH * 3600000 + endTimeM * 60000 + endTimeS * 1000 + endTimeMs;

				std::string subtitleText;
				std::getline(file, line);
				while (!file.eof() && !line.empty())
				{
					subtitleText += line + "\n";
					std::getline(file, line);
				}
				head.push_back(Subtitle(subtitleText, startTime, endTime));

			}
		}
	}

	const std::optional<Subtitle> find_sub(const int& time_ms) {
		auto current = head.begin();
		while (current != head.end()) {
			if (current->get_startTime() <= time_ms && current->get_endTime() >= time_ms) {
				return current.operator*();
			}
			++current;
		}
		return std::nullopt;
	}

	auto begin() const {
		return head.begin();
	}

	auto end() const {
		return head.end();
	}

	auto begin()  {
		return head.begin();
	}

	auto end()  {
		return head.end();
	}
};