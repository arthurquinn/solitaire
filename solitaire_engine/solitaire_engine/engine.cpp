#include "stdafx.h"
#include "engine.h"


Engine::Engine() {
	deck = new Deck();
}

void Engine::init() {
	deck->shuffle();
	deck->print();
}


Engine::~Engine() {
	delete deck;
}
