#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../controller/Game.h"

class ResultView : public Console::View
{
private:
	Game* _game;

public:
	explicit ResultView(Game* game);

	void Update(Console::Screen& screen) override;
};

