#pragma once
#include <iostream>
#include <ostream>

class Color
{
private:
	int red;
	int green;
	int blue;

public:
	Color() = delete;
	Color(int r, int g, int b);
	~Color();
	int getRed();
	int getGreen();
	int getBlue();
	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);
};

