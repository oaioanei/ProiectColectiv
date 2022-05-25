#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Image.h"

class AppWindow
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

public:
	AppWindow();
	~AppWindow();
	void renderFile(const char* fileName, int x, int y, int w, int h);
	SDL_Renderer* getRenderer();
	void mainMenu(Image image);
	void chooseAlgMenu(Image image);
	void insertFormulaMenu(Image image);
	void findBMPMenu(Image image);
};
