#include "Color.h"

Color::Color(int r, int g, int b) : red(r), green(g), blue(b) {}

Color::~Color() {}

int Color::getRed()
{
	return red;
}

int Color::getGreen()
{
	return green;
}

int Color::getBlue()
{
	return blue;
}

void Color::setRed(int r)
{
	red = r;
}

void Color::setGreen(int g)
{
	green = g;
}

void Color::setBlue(int b)
{
	blue = b;
}
