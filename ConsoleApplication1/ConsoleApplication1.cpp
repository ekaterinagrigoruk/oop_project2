#include "Display_Control.h"


int main(int argc, char** argv)
{
	std::string videoPath = "C:\\Users\\userok\\OOP_FTI_TASKS\\ConsoleApplication1\\ConsoleApplication1\\example.mp4";
	std::string subtitlePath = "C:\\Users\\userok\\Desktop\\sub.srt";
	try {
		VideoPlayer player_v(videoPath);
		SubtitlesPlayer player_s(subtitlePath);
		Display D(player_v, player_s);
		D.start();
	}
	catch (SubtitlesExceptions& exc) {
		std::cerr << exc.what() << std::endl;
	}
	catch (VideoExceptions& exc) {
		std::cerr << exc.what() << std::endl;
	}
	return 0;
}
