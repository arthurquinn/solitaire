#include "stdafx.h"
#include "engine.h"


Engine::Engine() {

}

void Engine::init() {
	deck.shuffle();
	deck.print();
}


Engine::~Engine() {

}
