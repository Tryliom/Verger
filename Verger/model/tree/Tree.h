#pragma once
#include "Month.h"

enum class TreeType
{
	CHERRY,
	PEAR,
	APPLE,
	END
};

struct TreeData
{
	TreeType Type;
	float MinTotalWeight;
	float MaxTotalWeight;
	Month StartHarvestDate;
	Month EndHarvestDate;
};

class Tree
{
private:
	TreeType _type;
	Month _startHarvestDate;
	Month _endHarvestDate;

	int _fruitWeight;
	int _minNbFruit;
	int _maxNbFruit;

	int _currentNbMaxFruit;
	int _currentNbFruit;
public:
	Tree(TreeType type, Month startHarvestDate, Month endHarvestDate, int fruitWeight, int minNbFruit, int maxNbFruit);

	[[nodiscard]] int GetNbFruit() const { return _currentNbFruit; }
	[[nodiscard]] int GetCurrentWeight() const { return _currentNbFruit * _fruitWeight; }
	[[nodiscard]] TreeType GetType() const { return _type; }

	[[nodiscard]] bool CanBeHarvested(const Month currentMonth) const;
	TreeData GetData() const;

	/**
	 * \brief Called every month
	 * \param currentMonth The current month in the game
	 */
	void OnMonth(Month currentMonth);
	/**
	 * \brief Harvest the tree and return his total weight
	 * \return The weight of the fruits harvested
	 */
	int Harvest(Month currentMonth);
};

class CherryTree final : public Tree
{
public:
	CherryTree() : Tree(TreeType::CHERRY, Month::MAY, Month::JUNE, 5, 45000, 60000) {}
};

class PearTree final : public Tree
{
public:
	PearTree() : Tree(TreeType::PEAR, Month::OCTOBER, Month::NOVEMBER, 90, 1600, 2500) {}
};

class AppleTree final : public Tree
{
public:
	AppleTree() : Tree(TreeType::APPLE, Month::SEPTEMBER, Month::NOVEMBER, 150, 600, 850) {}
};