#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../controller/Game.h"

class OrchardView : public Console::View
{
private:
	Game* _game;

	std::string _errorMessage;

	void displayTrees(Console::Screen& screen) const;
public:
	explicit OrchardView(Game* game);

	void Update(Console::Screen& screen) override;
	void OnKeyPressed(char key) override;
};

