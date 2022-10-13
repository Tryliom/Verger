#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../controller/Game.h"

class GameView : public Console::View
{
private:
	Game* _game;

	void setupComponents();
public:
	explicit GameView(Game* game);

	void Update(Console::Screen& screen) override;
	void OnKeyPressed(char key) override;
};

