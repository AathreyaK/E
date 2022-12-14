#include <iostream>
#include <stdint.h>

#include "Colors/Color.h"
#include "Colors/CVImageMods.h"

#define APP_ORIGINAL_WIN_WIDTH		600
#define APP_ORIGINAL_WIN_HEIGHT		800
#define FPS							20

typedef uint8_t						GRAY_PIXEL_T;
typedef	cv::Vec3b					COL_PIXEL_T;

cv::Mat applyTransformation(cv::Mat in)
{
	cv::Mat result;
	cv::Canny(in, result, 100, 100);
	return result;
}

int main()
{
    std::cout << "This is E." << std::endl;
	std::cout << "Note that E uses OpenCV version 4.3.0.\n" << std::endl;

	cv::namedWindow("E", cv::WINDOW_FREERATIO);

	cv::Mat frame;

	cv::VideoCapture vid(0);

	if (!vid.isOpened())
	{
		return -1;
	}

	while (vid.read(frame))
	{
		cv::imshow("E", applyTransformation(frame));

		if (cv::waitKey(1000 / FPS) >= 0)
			break;
	}

	return 0;
}