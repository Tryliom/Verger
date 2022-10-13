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
	int _currentYear = 1;

public:
	Game();

	[[nodiscard]] int GetNbFruit() const;
	[[nodiscard]] int GetPotentialWeight() const;
	[[nodiscard]] int GetCurrentWeight() const { return _totalWeight; }
	[[nodiscard]] Month GetCurrentMonth() const { return _currentMonth; }
	[[nodiscard]] int GetGoalWeight() const { return _goalWeight; }
	[[nodiscard]] bool CanHarvest() const { return _harvestLeft > 0; }
	[[nodiscard]] int GetHarvestLeft() const { return _harvestLeft; }
	[[nodiscard]] bool IsGoalReached() const { return _totalWeight >= _goalWeight; }
	[[nodiscard]] int GetYear() const { return _currentYear; }

	void NextMonth();
	void NextYear();
	void Harvest();

	[[nodiscard]] bool HasSurpassGoal() const { return _totalWeight >= _goalWeight; }
};

