#include "Game.h"

#include <format>

#include "../views/OrchardView.h"
#include "../tree/TreeFactory.h"

Game::Game()
{
	_trees = {
		CherryTree(),
		PearTree(),
		AppleTree()
	};

	SetView(new OrchardView(this));
}

std::string Game::formatNumber(const int number, NumberType type) const
{
	std::string unit;
	auto numberToDisplay = static_cast<float>(number);

	if (type == NumberType::WEIGHT)
	{
		unit = "g";
	}

	if (number >= 1000000)
	{
		numberToDisplay /= 1000000;

		if (type == NumberType::WEIGHT)
		{
			unit = "t";
		}
		else if (type == NumberType::QUANTITY)
		{
			unit = "m";
		}
	}
	else if (number >= 1000)
	{
		numberToDisplay /= 1000;

		if (type == NumberType::WEIGHT)
		{
			unit = "kg";
		}
		else if (type == NumberType::QUANTITY)
		{
			unit = "k";
		}
	}
	else
	{
		return std::to_string(number);
	}

	return std::format("{:.2f}", numberToDisplay) + unit;
}

std::unordered_map<std::string, int> Game::GetTrees() const
{
	std::unordered_map<std::string, int> trees;

	for (const auto& tree : _trees)
	{
		if (!trees.contains(tree.GetName()))
		{
			trees[tree.GetName()] = 0;
		}
		
		trees[tree.GetName()]++;
	}

	return trees;
}

void Game::NextMonth()
{
	if (_currentMonth != Month::DECEMBER)
	{
		_currentMonth = static_cast<Month>(static_cast<int>(_currentMonth) + 1);

		for (auto& tree : _trees)
		{
			tree.OnMonth(_currentMonth);
		}
	}
}

std::string Game::GetNbFruit() const
{
	int nbFruit = 0;
	for (const auto& tree : _trees)
	{
		nbFruit += tree.GetNbFruit();
	}

	return formatNumber(nbFruit, NumberType::QUANTITY);
}

std::string Game::GetPotentialWeightFormatted() const
{
	int weight = 0;
	for (const auto& tree : _trees)
	{
		if (tree.CanBeHarvested(_currentMonth))
		{
			weight += tree.GetCurrentWeight();
		}
	}

	return formatNumber(weight, NumberType::WEIGHT);
}

std::string Game::GetCompletion() const
{
	return formatNumber(_totalWeight, NumberType::WEIGHT) + "/" + formatNumber(_goalWeight, NumberType::WEIGHT);
}

std::string Game::GetMoney() const
{
	return formatNumber(_money, NumberType::QUANTITY) + " $";
}

std::string Game::GetMoneyIncome() const
{
	return formatNumber(getMoneyIncome(), NumberType::QUANTITY) + " $";
}

void Game::Harvest()
{
	if (CanHarvest())
	{
		for (auto& tree : _trees)
		{
			_totalWeight += tree.Harvest(_currentMonth);
		}

		_harvestLeft--;
	}
}

void Game::BuyRandomTree(int price)
{
	if (_money >= price)
	{
		_money -= price;

		_trees.emplace_back(TreeFactory::GetRandomTree());
	}
}

void Game::BuyTree(const Tree& tree, const int price)
{
	if (_money >= price)
	{
		_money -= price;

		_trees.emplace_back(tree);
	}
}

void Game::BuyHarvest(const int price)
{
	if (_money >= price)
	{
		_money -= price;

		_maxHarvest++;
	}
}

void Game::NextYear()
{
	_money += getMoneyIncome();
	_goalWeight += 100000;
	_currentYear++;
	_totalWeight = 0;
	_currentMonth = Month::JANUARY;
	_harvestLeft = _maxHarvest;

	SetView(new OrchardView(this));
}

void Game::Restart()
{
	_trees = {
		CherryTree(),
		PearTree(),
		AppleTree()
	};

	_money = 250;
	_currentYear = 1;
	_goalWeight = 2000000;
	_totalWeight = 0;
	_currentMonth = Month::JANUARY;
	_maxHarvest = 1;
	_harvestLeft = _maxHarvest;

	SetView(new OrchardView(this));
}