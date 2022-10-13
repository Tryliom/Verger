#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../controller/Game.h"

class SpecialShopView : public Console::View
{
private:
	Game* _game;

	std::string _errorMessage;

public:
	SpecialShopView(Game* game);

	void Update(Console::Screen& screen) override;
	void OnKeyPressed(char key) override;
};

