#include "Game.h"

#include <format>
#include <ranges>

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

std::unordered_map<TreeType, int> Game::GetTrees() const
{
	std::unordered_map<TreeType, int> trees;

	for (const auto& tree : _trees)
	{
		if (!trees.contains(tree.GetType()))
		{
			trees[tree.GetType()] = 0;
		}
		
		trees[tree.GetType()]++;
	}

	return trees;
}

std::vector<std::string> Game::GetTreeInformation() const
{
	std::unordered_map<TreeType, TreeInformation> treeData;

	for (const auto& tree : _trees)
	{
		if (!treeData.contains(tree.GetType()))
		{
			treeData[tree.GetType()] = TreeInformation(tree.GetType(), 0, 0, tree.CanBeHarvested(_currentMonth));
		}

		treeData[tree.GetType()].CurrentNbFruit += tree.GetNbFruit();
		treeData[tree.GetType()].CurrentWeight += tree.GetCurrentWeight();
	}

	std::vector<std::string> treeInformation = {};
	int totalFruits = 0;
	int totalWeight = 0;

	for (const auto& data : treeData | std::views::values)
	{
		treeInformation.emplace_back(
			TreeFactory::GetTreeName(data.Type) + ": " +
			formatNumber(data.CurrentNbFruit, NumberType::QUANTITY) + " fruits (" +
			formatNumber(data.CurrentWeight, NumberType::WEIGHT) + ")" +
			(data.CanBeHarvested ? " READY" : " NOT READY")
		);

		totalFruits += data.CurrentNbFruit;

		if (data.CanBeHarvested)
		{
			totalWeight += data.CurrentWeight;
		}
	}

	treeInformation.emplace_back(
		"Total: " +
		formatNumber(totalFruits, NumberType::QUANTITY) + " fruits (" +
		formatNumber(totalWeight, NumberType::WEIGHT) + " READY)"
	);

	return treeInformation;
}

std::unordered_map<Month, FruitsWeightData> Game::GetAverageWeightPerMonth()
{
	std::unordered_map<Month, FruitsWeightData> averageWeightPerMonth;

	for (auto& tree : _trees)
	{
		for (const auto& [month, fruits] : tree.GetAverageWeightPerMonth())
		{
			if (!averageWeightPerMonth.contains(month))
			{
				averageWeightPerMonth[month] = FruitsWeightData(0, 0);
			}

			averageWeightPerMonth[month].GrowthWeight += fruits.GrowthWeight;
			averageWeightPerMonth[month].HarvestableWeight += fruits.HarvestableWeight;
		}
	}

	return averageWeightPerMonth;
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
		_harvestLeft = _maxHarvest;
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