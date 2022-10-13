#pragma once
#include <string>

#include "Month.h"

class Tree
{
private:
	std::string _name;
	Month _startHarvestDate;
	Month _endHarvestDate;

	int _fruitWeight;
	int _minNbFruit;
	int _maxNbFruit;

	int _currentNbMaxFruit;
	int _currentNbFruit;
public:
	Tree(const std::string& name, Month startHarvestDate, Month endHarvestDate, int fruitWeight, int minNbFruit, int maxNbFruit);

	[[nodiscard]] int GetNbFruit() const { return _currentNbFruit; }
	[[nodiscard]] int GetCurrentWeight() const { return _currentNbFruit * _fruitWeight; }
	[[nodiscard]] std::string GetName() const { return _name; }

	[[nodiscard]] bool CanBeHarvested(const Month currentMonth) const;

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
	CherryTree() : Tree("Cherry tree", Month::MAY, Month::JUNE, 5, 45000, 60000) {}
};

class PearTree final : public Tree
{
public:
	PearTree() : Tree("Pear tree", Month::OCTOBER, Month::NOVEMBER, 90, 1600, 2500) {}
};

class AppleTree final : public Tree
{
public:
	AppleTree() : Tree("Apple tree", Month::SEPTEMBER, Month::NOVEMBER, 150, 600, 850) {}
};