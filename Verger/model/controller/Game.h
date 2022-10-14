#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../tree/Tree.h"

enum class NumberType
{
	WEIGHT,
	QUANTITY
};

struct TreeInformation
{
	std::string Name;
	int CurrentWeight;
	int CurrentNbFruit;
	bool CanBeHarvested;
};

class Game final : public Console::Controller
{
private:
	std::vector<Tree> _trees;
	// Game state
	Month _currentMonth = Month::JANUARY;
	int _totalWeight = 0;
	int _goalWeight = 2000000;
	int _harvestLeft = 1;
	int _currentYear = 1;
	int _money = 250;

	int _maxHarvest = 1;

	[[nodiscard]] std::string formatNumber(int number, NumberType type) const;

	[[nodiscard]] int getMoneyIncome() const { return (_totalWeight - _goalWeight) / 10000; }

public:
	Game();

	[[nodiscard]] std::string GetNbFruit() const;
	[[nodiscard]] std::string GetPotentialWeightFormatted() const;
	[[nodiscard]] std::string GetCompletion() const;
	[[nodiscard]] std::string GetMoney() const;
	[[nodiscard]] std::string GetMoneyIncome() const;

	[[nodiscard]] int GetCurrentWeight() const { return _totalWeight; }
	[[nodiscard]] Month GetCurrentMonth() const { return _currentMonth; }
	[[nodiscard]] int GetGoalWeight() const { return _goalWeight; }
	[[nodiscard]] bool CanHarvest() const { return _harvestLeft > 0; }
	[[nodiscard]] int GetHarvestLeft() const { return _harvestLeft; }
	[[nodiscard]] int GetMaxHarvest() const { return _maxHarvest; }
	[[nodiscard]] bool IsGoalReached() const { return _totalWeight >= _goalWeight; }
	[[nodiscard]] int GetYear() const { return _currentYear; }

	[[nodiscard]] bool HasEnoughMoney(const int price) const { return _money >= price; }

	[[nodiscard]] std::unordered_map<std::string, int> GetTrees() const;
	[[nodiscard]] std::vector<std::string> GetTreeInformation() const;

	void NextMonth();
	void NextYear();
	void Harvest();
	void Restart();

	void BuyRandomTree(int price);
	void BuyTree(const Tree& tree, int price);
	void BuyHarvest(int price);

	[[nodiscard]] bool HasSurpassGoal() const { return _totalWeight >= _goalWeight; }
};

