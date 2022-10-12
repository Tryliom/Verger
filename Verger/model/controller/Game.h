#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../tree/Tree.h"

class Game final : public Console::Controller
{
private:
	std::vector<Tree> _trees;
	Month _currentMonth = Month::JANUARY;
	int _totalWeight = 0;
	int _goalWeight = 20000000;
	int _harvestLeft = 1;
	int _maxHarvest = 1;

	void nextYear();
public:
	Game();

	[[nodiscard]] int GetNbFruit() const;
	[[nodiscard]] int GetPotentialWeight() const;
	[[nodiscard]] int GetCurrentWeight() const { return _totalWeight; }
	[[nodiscard]] Month GetCurrentMonth() const { return _currentMonth; }
	[[nodiscard]] int GetGoalWeight() const { return _goalWeight; }

	void NextMonth();
	void Harvest();
};

