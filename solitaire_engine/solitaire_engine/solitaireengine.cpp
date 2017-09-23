// solitaireengine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "engine.h"
#include "constants.h"


/// TODO: Delete all print() methods from classes as they are only used for debugging
/// TODO: Alternatively, switch these print methods into log messages for easier debugging which can be turned off in deployment

int main()
{
	Engine engine;
	engine.init();
	engine.deal();
	std::cin.get();
    return 0;
}