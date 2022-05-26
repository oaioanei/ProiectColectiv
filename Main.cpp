#include "AppWindow.h"
#include "Image.h"
#include "SDL.h"

double Convert(double degree)
{
	double pi = 3.14159265359;
	return (degree * (pi / 180));
}

int main(int argc, char* argv[])
{
	AppWindow appWindow;
	SDL_Event event;
	Image image(640, 480);
	bool quit = 0;

	appWindow.mainMenu(image);

	return 0;
}
