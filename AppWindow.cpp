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
	SDL_DestroyTexture(texture);										//free texture memory
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
	renderFile("assets\\buton4.bmp", 20, 230, 280, 50);

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
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 160 && yposm < 210)
					findBMPMenu(image);

				//buton exit
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 230 && yposm < 280)
				{
					quit = true;
				}
			}
		}
	}
}

void AppWindow::chooseAlgMenu(Image image)
{
	SDL_Event event;
	bool quit = 0;
	bool doContinue = false;
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
					image.generateBMP(1, "example1", "pictures");
					renderFile("pictures\\example1.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 90 && yposm < 140)
				{
					image.generateBMP(2, "example2", "pictures");
					renderFile("pictures\\example2.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 145 && yposm < 210)
				{
					image.generateBMP(3, "example3", "pictures");
					renderFile("pictures\\example3.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 230 && yposm < 290)
				{
					image.generateBMP(4, "example4", "pictures");
					renderFile("pictures\\example4.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 300 && yposm < 360)
				{
					image.generateBMP(5, "example5", "pictures");
					renderFile("pictures\\example5.bmp", 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}
				if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 370 && yposm < 430)
				{
					mainMenu(image);
					break;
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
	bool textBox1Clicked = false;
	bool textBox2Clicked = false;
	SDL_SetRenderDrawColor(renderer, 83, 150, 201, 255);
	SDL_RenderClear(renderer);
	renderFile("assets\\blue.bmp", 0, 0, 325, 480);
	renderFile("assets\\white.bmp", 20, 20, 280, 35);
	renderFile("assets\\white.bmp", 20, 90, 280, 35);

	//text input
	TTF_Init();
	TTF_Font* Sans = TTF_OpenFont("OpenSans-Bold.ttf", 22);
	SDL_Color Black = { 0, 0, 0 };
	SDL_Surface* placeholderMessage1 =
		TTF_RenderText_Solid(Sans, "Formula...", Black);
	SDL_Surface* placeholderMessage2 =
		TTF_RenderText_Solid(Sans, "Image name...", Black);
	SDL_Surface* userMessage1;
	SDL_Surface* userMessage2;
	SDL_Texture* Message1 = SDL_CreateTextureFromSurface(renderer, placeholderMessage1);
	SDL_Texture* Message2 = SDL_CreateTextureFromSurface(renderer, placeholderMessage2);

	SDL_Rect Message_rect1;
	Message_rect1.x = 25;
	Message_rect1.y = 20;
	Message_rect1.w = placeholderMessage1->w;
	Message_rect1.h = placeholderMessage1->h;

	SDL_Rect Message_rect2;
	Message_rect2.x = 25;
	Message_rect2.y = 90;
	Message_rect2.w = placeholderMessage2->w;
	Message_rect2.h = placeholderMessage2->h;

	SDL_RenderCopy(renderer, Message1, NULL, &Message_rect1);
	SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);
	SDL_FreeSurface(placeholderMessage1);
	SDL_FreeSurface(placeholderMessage2);
	SDL_DestroyTexture(Message1);
	SDL_DestroyTexture(Message2);

	renderFile("assets\\butonInapoi.bmp", 20, 370, 280, 50);
	std::string text1 = "", text2 = "";
	SDL_StartTextInput();

	while (!quit)
	{
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event))
		{
			int xposm = event.motion.x, yposm = event.motion.y;

			//interact with box 1
			if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 20 && yposm < 70)
			{
				textBox1Clicked = true;
				textBox2Clicked = false;
			}

			//interact with box 2
			if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 90 && yposm < 140)
			{
				textBox2Clicked = true;
				textBox1Clicked = false;
			}

			//one box clicked
			if ((textBox1Clicked == true || textBox2Clicked == true) && (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN))
			{
				//press enter
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && text1.length() > 0)
				{
					std::string file;
					file.append("pictures\\");
					file.append(text2);
					file.append(".bmp");
					const char* str2 = file.c_str();

					image.insertAlg(text1, text2);
					renderFile(str2, 321, 0, 640, 480);
					SDL_RenderPresent(renderer);
				}

				//delete from box 1
				if (textBox1Clicked == true && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && text1.length() > 0)
				{
					SDL_RenderClear(renderer);
					renderFile("assets\\blue.bmp", 0, 0, 325, 480);
					renderFile("assets\\white.bmp", 20, 20, 280, 35);
					renderFile("assets\\white.bmp", 20, 90, 280, 35);
					renderFile("assets\\butonInapoi.bmp", 20, 370, 280, 50);

					text1 = text1.substr(0, text1.length() - 1);
					const char* str1 = text1.c_str();

					if (text1.length() > 0)
					{
						userMessage1 = TTF_RenderText_Solid(Sans, str1, Black);
						Message_rect1.w = userMessage1->w;
						Message_rect1.h = userMessage1->h;
						if (text2.length() > 0)
						{
							const char* str2 = text2.c_str();
							userMessage2 = TTF_RenderText_Solid(Sans, str2, Black);
							Message_rect2.w = userMessage2->w;
							Message_rect2.h = userMessage2->h;
							Message2 = SDL_CreateTextureFromSurface(renderer, userMessage2);
						}
						Message1 = SDL_CreateTextureFromSurface(renderer, userMessage1);		
						SDL_RenderCopy(renderer, Message1, NULL, &Message_rect1);
						SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);
					}
					
				}

				//delete from box 2
				if (textBox2Clicked == true && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && text2.length() > 0)
				{
					SDL_RenderClear(renderer);
					renderFile("assets\\blue.bmp", 0, 0, 325, 480);
					renderFile("assets\\white.bmp", 20, 20, 280, 35);
					renderFile("assets\\white.bmp", 20, 90, 280, 35);
					renderFile("assets\\butonInapoi.bmp", 20, 370, 280, 50);

					
					text2 = text2.substr(0, text2.length() - 1);
					const char* str2 = text2.c_str();

					

					if (text2.length() > 0)
					{
						if (text1.length() > 0)
						{
							const char* str1 = text1.c_str();
							userMessage1 = TTF_RenderText_Solid(Sans, str1, Black);
							Message_rect1.w = userMessage1->w;
							Message_rect1.h = userMessage1->h;
							Message1 = SDL_CreateTextureFromSurface(renderer, userMessage1);
						}
						userMessage2 = TTF_RenderText_Solid(Sans, str2, Black);
						Message_rect2.w = userMessage2->w;
						Message_rect2.h = userMessage2->h;
						Message2 = SDL_CreateTextureFromSurface(renderer, userMessage2);
						SDL_RenderCopy(renderer, Message1, NULL, &Message_rect1);
						SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);
					}
					
				}
				
				//write
				else if (event.type == SDL_TEXTINPUT)
				{
					renderFile("assets\\blue.bmp", 0, 0, 325, 480);
					renderFile("assets\\white.bmp", 20, 20, 280, 35);
					renderFile("assets\\white.bmp", 20, 90, 280, 35);
					renderFile("assets\\butonInapoi.bmp", 20, 370, 280, 50);

					//write in box 1
					if (textBox1Clicked == true)
					{
						text1 += event.text.text;
						const char* str1 = text1.c_str();

						const char* str2 = text2.c_str();

						userMessage1 = TTF_RenderText_Solid(Sans, str1, Black);
						Message_rect1.w = userMessage1->w;
						Message_rect1.h = userMessage1->h;
						if (text2.length() > 0)
						{
							userMessage2 = TTF_RenderText_Solid(Sans, str2, Black);
							Message_rect2.w = userMessage2->w;
							Message_rect2.h = userMessage2->h;
							Message2 = SDL_CreateTextureFromSurface(renderer, userMessage2);
						}
						Message1 = SDL_CreateTextureFromSurface(renderer, userMessage1);
						
						SDL_RenderCopy(renderer, Message1, NULL, &Message_rect1);
						SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);
						SDL_FreeSurface(userMessage1);
						SDL_DestroyTexture(Message1);
					}

					//write in box 2
					if (textBox2Clicked == true)
					{
						text2 += event.text.text;
						const char* str2 = text2.c_str();

						const char* str1 = text1.c_str();

						if (text1.length() > 0)
						{
							userMessage1 = TTF_RenderText_Solid(Sans, str1, Black);
							Message_rect1.w = userMessage1->w;
							Message_rect1.h = userMessage1->h;
							Message1 = SDL_CreateTextureFromSurface(renderer, userMessage1);
						}
						userMessage2 = TTF_RenderText_Solid(Sans, str2, Black);
						Message_rect2.w = userMessage2->w;
						Message_rect2.h = userMessage2->h;
						
						Message2 = SDL_CreateTextureFromSurface(renderer, userMessage2);
						SDL_RenderCopy(renderer, Message1, NULL, &Message_rect1);
						SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);
						SDL_FreeSurface(userMessage2);
						SDL_DestroyTexture(Message2);
					}
				}
				break;
			}
			
			//back button
			if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 370 && yposm < 430)
			{
				mainMenu(image);
				break;
			}

			//quit app
			if (event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}
		
		}
	}

	SDL_StopTextInput();
}

void AppWindow::findBMPMenu(Image image)
{
	SDL_Event event;

	bool quit = 0;
	bool textBoxClicked = false;
	SDL_SetRenderDrawColor(renderer, 83, 150, 201, 255);
	SDL_RenderClear(renderer);
	renderFile("assets\\blue.bmp", 0, 0, 325, 480);
	renderFile("assets\\white.bmp", 20, 20, 280, 35);

	//text input
	TTF_Init();
	TTF_Font* Sans = TTF_OpenFont("OpenSans-Bold.ttf", 22);
	SDL_Color Black = { 0, 0, 0 };
	SDL_Color Red = { 255, 0, 0 };
	SDL_Surface* placeholderMessage =
		TTF_RenderText_Solid(Sans, "File name...", Black);
	SDL_Surface* errorMessage =
		TTF_RenderText_Solid(Sans, "File does not exist!", Red);
	SDL_Surface* userMessage;
	SDL_Texture* Message1 = SDL_CreateTextureFromSurface(renderer, placeholderMessage);
	SDL_Texture* Message2 = SDL_CreateTextureFromSurface(renderer, errorMessage);

	SDL_Rect Message_rect1;
	Message_rect1.x = 25;
	Message_rect1.y = 20;
	Message_rect1.w = placeholderMessage->w;
	Message_rect1.h = placeholderMessage->h;

	SDL_Rect Message_rect2;
	Message_rect2.x = 23;
	Message_rect2.y = 60;
	Message_rect2.w = errorMessage->w;
	Message_rect2.h = errorMessage->h;

	SDL_RenderCopy(renderer, Message1, NULL, &Message_rect1);
	SDL_FreeSurface(placeholderMessage);
	SDL_FreeSurface(errorMessage);
	SDL_DestroyTexture(Message1);

	renderFile("assets\\butonInapoi.bmp", 20, 370, 280, 50);
	std::string text = "";
	SDL_StartTextInput();

	while (!quit)
	{
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event))
		{
			int xposm = event.motion.x, yposm = event.motion.y;

			if (event.button.button == SDL_BUTTON_LEFT && xposm > 20 && xposm < 280 && yposm > 20 && yposm < 70)
			{
				textBoxClicked = true;
			}

			if (textBoxClicked == true && event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN)
			{
				system("cls");
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && text.length() > 0)
				{
					std::string file;
					file.append("pictures\\");
					file.append(text);
					file.append(".bmp");
					const char* str = file.c_str();
					if(IMG_Load(str))
						renderFile(str, 321, 0, 640, 480);
					else
						SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);
						
				}
				else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
				{
					SDL_RenderClear(renderer);
					renderFile("assets\\blue.bmp", 0, 0, 325, 480);
					renderFile("assets\\white.bmp", 20, 20, 280, 35);
					renderFile("assets\\butonInapoi.bmp", 20, 370, 280, 50);

					text = text.substr(0, text.length() - 1);
					const char* str = text.c_str();
					if (text.length() > 0)
					{
						userMessage = TTF_RenderText_Solid(Sans, str, Black);
						Message_rect1.w = userMessage->w;
						Message_rect1.h = userMessage->h;
						Message1 = SDL_CreateTextureFromSurface(renderer, userMessage);
						SDL_RenderCopy(renderer, Message1, NULL, &Message_rect1);
						SDL_FreeSurface(userMessage);
						SDL_DestroyTexture(Message1);
					}

				}
				else if (event.type == SDL_TEXTINPUT)
				{
					SDL_RenderClear(renderer);
					renderFile("assets\\blue.bmp", 0, 0, 325, 480);
					renderFile("assets\\white.bmp", 20, 20, 280, 35);
					renderFile("assets\\butonInapoi.bmp", 20, 370, 280, 50);

					text += event.text.text;
					const char* str = text.c_str();
					userMessage = TTF_RenderText_Solid(Sans, str, Black);
					Message_rect1.w = userMessage->w;
					Message_rect1.h = userMessage->h;
					Message1 = SDL_CreateTextureFromSurface(renderer, userMessage);
					SDL_RenderCopy(renderer, Message1, NULL, &Message_rect1);
					SDL_FreeSurface(userMessage);
					SDL_DestroyTexture(Message1);
				}
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
