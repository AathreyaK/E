#include "Color.h"

RGBColor::RGBColor(cv::Vec3b CVColor)
{
	m_r = CVColor[2];
	m_g = CVColor[1];
	m_b = CVColor[0];
}

RGBColor::RGBColor(float r, float g, float b)
	: m_r(r), m_g(g), m_b(b)
{
}

RGBColor::~RGBColor()
{
}

float RGBColor::getR()
{
	return m_r;
}

float RGBColor::getG()
{
	return m_g;
}

float RGBColor::getB()
{
	return m_b;
}

float * RGBColor::getRGB()
{
	float * temp = new float[3];
	temp[0] = m_r;
	temp[1] = m_g;
	temp[2] = m_b;

	return temp;
}

cv::Vec3b RGBColor::getRGB_CV()
{
	return cv::Vec3b(m_b, m_g, m_r);
}

void RGBColor::setR(float val)
{
	m_r = val;
}

void RGBColor::setG(float val)
{
	m_g = val;
}

void RGBColor::setB(float val)
{
	m_b = val;
}

void RGBColor::setRGB(float r, float g, float b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}

float RGBColor::luminance()
{
	return sqrt(m_r*m_r*.241 +  m_g*m_g*.691 + m_b*m_b*.068);
}
