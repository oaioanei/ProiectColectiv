#include "AppWindow.h"
#include <iostream>

AppWindow::AppWindow()
{
	//create window
	SDL_Init(SDL_INIT_EVERYTHING);
	this->window = SDL_CreateWindow("ImageViewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640 + 320, 480, SDL_WINDOW_OPENGL);
	if (this->window == NULL)
		printf("Could not create window: %s\n", SDL_GetError());

	//create renderer
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
}

AppWindow::~AppWindow()
{
	/*SDL_DestroyWindow(this->window);
	SDL_Quit();*/
}

void AppWindow::renderFile(const char* fileName, int x, int y, int w, int h)
{
	SDL_Surface* loadingSurface;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	srcRect.x = 0;
	destRect.x = x;
	srcRect.y = 0;
	destRect.y = y;
	srcRect.w = destRect.w = w;
	srcRect.h = destRect.h = h;
	loadingSurface = IMG_Load(fileName);								//load file to surface
	texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);	//change from surface to texture
	SDL_FreeSurface(loadingSurface);									//free surface memory
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);						//place texture in renderer
	SDL_RenderPresent(renderer);										//show renderer
	//SDL_DestroyTexture(texture);										//free texture memory
}

SDL_Renderer* AppWindow::getRenderer()
{
	return renderer;
}

void AppWindow::mainMenu(Image image)
{
	SDL_Event event;
	bool quit = 0;

	SDL_SetRenderDrawColor(renderer, 83, 150, 201, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	renderFile("assets\\blue.bmp", 0, 0, 325, 480);

	renderFile("assets\\buton1.bmp", 20, 20, 280, 50);
	renderFile("assets\\buton2.bmp", 20, 90, 280, 50);
	renderFile("assets\\buton3.bmp", 20, 160, 280, 50);

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			int xposm = event.motion.x, yposm = event.motion.y;
	
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				//buton algoritmi existenti
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 20 && yposm < 70)
					chooseAlgMenu(image);

				//buton introducere formula
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 90 && yposm < 140)
					insertFormulaMenu(image);

				//buton gasire fisiere
				//if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 160 && yposm < 210)
					//findBMPMenu(image);
			}
		}
	}
}

void AppWindow::chooseAlgMenu(Image image)
{
	SDL_Event event;
	bool quit = 0;
	SDL_SetRenderDrawColor(renderer, 83, 150, 201, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	renderFile("assets\\blue.bmp", 0, 0, 325, 480);

	renderFile("assets\\wave.bmp", 20, 20, 280, 50);
	renderFile("assets\\radar.bmp", 20, 90, 280, 50);
	renderFile("assets\\beam.bmp", 20, 160, 280, 50);
	renderFile("assets\\melt.bmp", 20, 230, 280, 50);
	renderFile("assets\\puzzle.bmp", 20, 300, 280, 50);
	renderFile("assets\\butonInapoi.bmp", 20, 370, 280, 50);
	
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			int xposm = event.motion.x, yposm = event.motion.y;

			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 20 && yposm < 70)
				{
					image.generateBMP(1, "example1", "assets");
					renderFile("assets\\example1.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 90 && yposm < 140)
				{
					image.generateBMP(2, "example2", "assets");
					renderFile("assets\\example2.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 145 && yposm < 210)
				{
					image.generateBMP(3, "example3", "assets");
					renderFile("assets\\example3.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 230 && yposm < 290)
				{
					image.generateBMP(4, "example4", "assets");
					renderFile("assets\\example4.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 300 && yposm < 360)
				{
					image.generateBMP(5, "example5", "assets");
					renderFile("assets\\example5.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 370 && yposm < 430)
				{
					mainMenu(image);
				}
				break;
			}
		}
	}
}

void AppWindow::insertFormulaMenu(Image image)
{
	SDL_Event event;
	bool quit = 0;
	SDL_SetRenderDrawColor(renderer, 83, 150, 201, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	renderFile("assets\\blue.bmp", 0, 0, 325, 480);

	renderFile("assets\\butonInapoi.bmp", 20, 370, 280, 50);
	std::string text = "";
	SDL_StartTextInput();

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			int xposm = event.motion.x, yposm = event.motion.y;

			if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN)
			{
				system("cls");
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && text.length() > 0)
				{
					image.insertAlg(text);
					renderFile("assets\\customImage.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
					text = text.substr(0, text.length() - 1);
				else if (event.type == SDL_TEXTINPUT)
					text += event.text.text;
				std::cout << text << std::endl;
				break;
			}
					
			if (event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}

			if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 370 && yposm < 430)
			{
				mainMenu(image);
				break;
			}
		
		}
	}

	SDL_StopTextInput();
}

void AppWindow::findBMPMenu(Image image)
{

}
