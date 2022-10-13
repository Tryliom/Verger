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
	Tree(const std::string& name, Month growthDate, Month harvestDate, int fruitWeight, int minNbFruit, int maxNbFruit);

	[[nodiscard]] int GetNbFruit() const { return _currentNbFruit; }
	[[nodiscard]] int GetCurrentWeight() const { return _currentNbFruit * _fruitWeight; }
	[[nodiscard]] bool CanBeHarvested(const Month currentMonth) const { return _currentNbFruit > 0 && currentMonth >= _startHarvestDate && currentMonth <= Month::DECEMBER; }

	/**
	 * \brief Called every month
	 * \param currentMonth The current month in the game
	 */
	void OnMonth(Month currentMonth);
	/**
	 * \brief Harvest the tree and return his total weight
	 * \return The weight of the fruits harvested
	 */
	int Harvest();
};

class CherryTree final : public Tree
{
public:
	CherryTree() : Tree("Cherry tree", Month::MAY, Month::JUNE, 5, 45000, 60000) {}
};

class AppleTree final : public Tree
{
public:
	AppleTree() : Tree("Apple tree", Month::SEPTEMBER, Month::NOVEMBER, 150, 600, 850) {}
};

class PeerTree final : public Tree
{
public:
	PeerTree() : Tree("Peer tree", Month::OCTOBER, Month::NOVEMBER, 90, 1600, 2500) {}
};