// snake_console.cpp : main project file.

#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
	// create and initialize game application class
	app		game_app;
	game_app.init();

	

	// enter main loop
	while (!game_app.exit())
	{
		game_app.update();
		game_app.process();
	}
	
    return 0;
}
