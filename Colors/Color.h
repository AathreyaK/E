
#include <opencv2/opencv.hpp>

class RGBColor
{
private:
	float m_r;
	float m_g;
	float m_b;

public:
	RGBColor(cv::Vec3b CVColor);
	RGBColor(float r, float g, float b);
	~RGBColor();

	float getR();
	float getG();
	float getB();
	float * getRGB();
	cv::Vec3b getRGB_CV();

	void setR(float val);
	void setG(float val);
	void setB(float val);
	void setRGB(float r, float g, float b);

	float luminance();

};