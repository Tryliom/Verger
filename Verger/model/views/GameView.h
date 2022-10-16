#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../controller/Game.h"

class GameView : public Console::View
{
private:
	Game* _game;

	CompletionData _completionData;
	std::vector<std::string> _treeInformation;

	void updateData();
public:
	explicit GameView(Game* game);

	void Update(Console::Screen& screen) override;
	void OnKeyPressed(char key) override;
};

