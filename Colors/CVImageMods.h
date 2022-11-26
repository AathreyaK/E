#pragma once

#include <opencv2/opencv.hpp>

// Color Modifications 
cv::Mat applyRGBFilter(cv::Mat original, bool r, bool g, bool b) // This method is much faster than actually doing it by hand.
{
	cv::Mat splitchannels[3];
	cv::split(original, splitchannels);
	if (!r)
		splitchannels[2] = cv::Mat::zeros(splitchannels[2].size(), CV_8UC1);
	if (!g)
		splitchannels[1] = cv::Mat::zeros(splitchannels[2].size(), CV_8UC1);
	if (!b)
		splitchannels[0] = cv::Mat::zeros(splitchannels[2].size(), CV_8UC1);
	cv::Mat output;

	cv::merge(splitchannels, 3, output);
	return output;
}

cv::Mat getChannel(cv::Mat original, short channel) // 0 for r, 1 for g, 2 for b
{
	cv::Mat splitchannels[3];
	cv::split(original, splitchannels);

	return splitchannels[2 - channel];
}

// DFT Related Modifications
void takeDFT(cv::Mat & source, cv::Mat & destination)
{
	cv::Mat originalC[2] = { source, cv::Mat::zeros(source.size(), CV_32F) };
	cv::Mat dftReady;

	cv::merge(originalC, 2, dftReady);
	dft(dftReady, destination, cv::DFT_COMPLEX_OUTPUT);
}

void recenterDFT(cv::Mat & source)
{
	int centerX = source.cols / 2;
	int centerY = source.rows / 2;

	cv::Mat q1(source, cv::Rect(0, 0, centerX, centerY));
	cv::Mat q2(source, cv::Rect(centerX, 0, centerX, centerY));
	cv::Mat q3(source, cv::Rect(0, centerY, centerX, centerY));
	cv::Mat q4(source, cv::Rect(centerX, centerY, centerX, centerY));

	cv::Mat swapMap;

	q1.copyTo(swapMap);
	q4.copyTo(q1);
	swapMap.copyTo(q4);

	q2.copyTo(swapMap);
	q3.copyTo(q2);
	swapMap.copyTo(q3);
}

void showDFT(cv::Mat & source)
{
	cv::Mat splitArray[2] = { cv::Mat::zeros(source.size(), CV_32F), cv::Mat::zeros(source.size(), CV_32F) };
	cv::split(source, splitArray);
	cv::Mat dftMag;
	magnitude(splitArray[0], splitArray[1], dftMag);
	dftMag += cv::Scalar::all(1);
	log(dftMag, dftMag);
	cv::normalize(dftMag, dftMag, 0, 1, cv::NORM_MINMAX);

	recenterDFT(dftMag);

	cv::imshow("DFT", dftMag);
	cv::waitKey();
}

void invertDFT(cv::Mat & source, cv::Mat & destination)
{
	cv::Mat inverse;

	dft(source, inverse, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);

	destination = inverse;
}

void createGaussian(cv::Size & size, cv::Mat & output, int uX, int uY, float sigmaX, float sigmaY, float amplitude = 1.0f)
{
	cv::Mat temp = cv::Mat(size, CV_32F);

	for (int r = 0; r < size.height; r++)
	{
		for (int c = 0; c < size.width; c++)
		{
			float x = ((c - uX)*((float)c - uX)) / (2.0f * sigmaX * sigmaX);
			float y = ((r - uY)*((float)r - uY)) / (2.0f * sigmaY * sigmaY);

			float value = amplitude * exp(-(x + y));

			temp.at<float>(r, c) = value;
		}
	}
	normalize(temp, temp, 0.0f, 1.0f, cv::NORM_MINMAX);
	output = temp;
}