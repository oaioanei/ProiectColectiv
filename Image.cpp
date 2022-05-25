#include "Image.h"
#include "exprtk.hpp"
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

Image::Image(int w, int h) : width(w), height(h) {}

Image::~Image() {}

void Image::generateBMP(int algorithm, const char* fileName, const char* location)
{
	std::string file;
	file.append(location);
	file.append("\\");
	file.append(fileName);
	file.append(".bmp");

	int widthInBytes = width * bytesPerPixel;
	unsigned char padding[3] = { 0, 0, 0 };
	int paddingSize = (4 - (widthInBytes) % 4) % 4;
	int stride = (widthInBytes)+paddingSize;

	std::ofstream fout(file, std::ios::binary);

	unsigned char* BMPHeader = createBMPHeader(height, stride);
	fout.write(reinterpret_cast<char*>(BMPHeader), BMPHeaderSize);

	unsigned char* DIBHeader = createDIBHeader(width, height);
	fout.write(reinterpret_cast<char*>(DIBHeader), DIBHeaderSize);

	switch (algorithm)
	{
	default:
		break;
	case 1:
		this->algorithm1();
		break;
	case 2:
		this->algorithm2();
		break;
	case 3:
		this->algorithm3();
		break;
	case 4:
		this->algorithm4();
		break;
	case 5:
		this->algorithm5();
		break;
	}

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++) {
			int blue = image[i * height + j].getBlue();
			int green = image[i * height + j].getGreen();
			int red = image[i * height + j].getRed();
			fout.write(reinterpret_cast<char*>(&blue), 1);
			fout.write(reinterpret_cast<char*>(&green), 1);
			fout.write(reinterpret_cast<char*>(&red), 1);
		}

	fout.close();
}

unsigned char* Image::createBMPHeader(int h, int stride)
{
	int fileSize = BMPHeaderSize + DIBHeaderSize + (h * stride);

	static unsigned char BMPHeader[] = {
		0,0,		//signature
		0,0,0,0,	//image file size in bytes
		0,0,0,0,	//reserved
		0,0,0,0,	//start of pixel array
	};

	BMPHeader[0] = (unsigned char)('B');
	BMPHeader[1] = (unsigned char)('M');
	BMPHeader[2] = (unsigned char)(fileSize);
	BMPHeader[3] = (unsigned char)(fileSize >> 8);
	BMPHeader[4] = (unsigned char)(fileSize >> 16);
	BMPHeader[5] = (unsigned char)(fileSize >> 24);
	BMPHeader[10] = (unsigned char)(BMPHeaderSize + DIBHeaderSize);

	return BMPHeader;
}

unsigned char* Image::createDIBHeader(int w, int h)
{
	static unsigned char DIBHeader[] = {
		0,0,0,0,	//header size
		0,0,0,0,	//image width
		0,0,0,0,	//image height
		0,0,		//number of color planes
		0,0,		//bits per pixel
		0,0,0,0,	//compression
		0,0,0,0,	//image size
		0,0,0,0,	//horizontal resolution
		0,0,0,0,	//vertical resolution
		0,0,0,0,	//colors in color table
		0,0,0,0,	//important color count
	};

	DIBHeader[0] = (unsigned char)(DIBHeaderSize);
	DIBHeader[4] = (unsigned char)(w);
	DIBHeader[5] = (unsigned char)(w >> 8);
	DIBHeader[6] = (unsigned char)(w >> 16);
	DIBHeader[7] = (unsigned char)(w >> 24);
	DIBHeader[8] = (unsigned char)(h);
	DIBHeader[9] = (unsigned char)(h >> 8);
	DIBHeader[10] = (unsigned char)(h >> 16);
	DIBHeader[11] = (unsigned char)(h >> 24);
	DIBHeader[12] = (unsigned char)(1);
	DIBHeader[14] = (unsigned char)(bytesPerPixel * 8);

	return DIBHeader;
}

void Image::algorithm1()
{
	double pi = 3.14159265359;
	image.clear();
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			uint8_t value;
			double a = i * (pi / 180);
			double b = j * (pi / 180);
			double c;
			c = 23 * sin(a + cos(b));
			value = static_cast<int>(c) % 16;
			Color color((unsigned char)value * 6, (unsigned char)value * 2, (unsigned char)value * 6);
			image.push_back(color);
		}
	
}

void Image::algorithm2()
{
	double pi = 3.14159265359;
	image.clear();
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			uint8_t value;
			double a = i * (pi / 180);
			double b = j * (pi / 180);
			double c;
			c = tan(a) * 10 * cos(b);
			value = static_cast<int>(c) % 16;
			Color color((unsigned char)value, (unsigned char)value * 12, (unsigned char)value);
			image.push_back(color);
		}
}

void Image::algorithm3()
{
	double pi = 3.14159265359;
	image.clear();
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			uint8_t value;
			double a = i * (pi / 180);
			double b = j * (pi / 180);
			double c;
			c = sin(a) / b * 1 / tan(a) * 100;
			value = static_cast<int>(c) % 51;
			Color color((unsigned char)value * 10, (unsigned char)value * 2, (unsigned char)value);
			image.push_back(color);
		}
}

void Image::algorithm4()
{
	double pi = 3.14159265359;
	image.clear();
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			uint8_t value;
			double a = i * (pi / 180);
			double b = j * (pi / 180);
			double c;
			c = sin(a + b) - cos(b * tan(a)) * 2;
			value = static_cast<int>(c) % 16;
			Color color((unsigned char)value * 100, (unsigned char)value * 100, (unsigned char)value);
			image.push_back(color);
		}
}

void Image::algorithm5()
{
	double pi = 3.14159265359;
	image.clear();
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			uint8_t value;
			double a = i * (pi / 180);
			double b = j * (pi / 180);
			double c;
			c = sin(a * sin(b)) / sin(b * sin(a));
			value = static_cast<int>(c) % 16;
			Color color((unsigned char)value * 29, (unsigned char)value * 100, (unsigned char)value * 100);
			image.push_back(color);
		}
}

void Image::insertAlg(std::string text)
{
	double pi = 3.14159265359;
	image.clear();

	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double>   expression_t;
	typedef exprtk::parser<double>       parser_t;

	const std::string expression_string = text;

	uint8_t value;
	double x;
	double y;
	double c;

	symbol_table_t symbol_table;
	symbol_table.add_variable("x", x);
	symbol_table.add_variable("y", y);
	symbol_table.add_constants();

	expression_t expression;
	expression.register_symbol_table(symbol_table);

	parser_t parser;
	parser.compile(expression_string, expression);

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) 
		{	
			x = i * (pi / 180);
			y = j * (pi / 180);
			c = expression.value();
			value = static_cast<int>(c) % 16;
			Color color((unsigned char)value * 29, (unsigned char)value * 100, (unsigned char)value * 100);
			image.push_back(color);
		}
	generateBMP(0, "customImage", "assets");
}
