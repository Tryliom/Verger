#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../controller/Game.h"

class OrchardView : public Console::View
{
private:
	Game* _game;
	std::string _errorMessage;
	std::vector<TreeData> _treeData;
	std::unordered_map<Month, FruitsWeightData> _averageWeightPerMonth;

	void displayTrees(Console::Screen& screen) const;

	void updateAverageWeightPerMonth();
public:
	explicit OrchardView(Game* game);

	void Update(Console::Screen& screen) override;
	void OnKeyPressed(char key) override;
};

