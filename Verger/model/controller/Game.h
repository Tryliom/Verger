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
	TreeType Type;
	int CurrentWeight;
	int CurrentNbFruit;
	bool CanBeHarvested;
};

const std::string MAIN_THEME_PATH = "assets/audio/main_theme.wav";
const std::string VICTORY_THEME_PATH = "assets/audio/victory_theme.wav";
const std::string DEFEAT_THEME_PATH = "assets/audio/defeat_theme.wav";

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

	[[nodiscard]] std::unordered_map<TreeType, int> GetTrees() const;
	[[nodiscard]] std::vector<std::string> GetTreeInformation() const;
	std::unordered_map<Month, int> GetAverageWeightPerMonth();

	void NextMonth();
	void NextYear();
	void Harvest();
	void Restart();

	void BuyTree(const Tree& tree, int price);
	void BuyHarvest(int price);

	[[nodiscard]] bool HasSurpassGoal() const { return _totalWeight >= _goalWeight; }
};

