#include "Game.h"
#include "../views/GameView.h"

Game::Game()
{
	_trees = {
		CherryTree()
	};

	ChangeView(new GameView(this));
}

void Game::NextMonth()
{
	if (_currentMonth != Month::END)
	{
		_currentMonth = static_cast<Month>(static_cast<int>(_currentMonth) + 1);

		for (auto& tree : _trees)
		{
			tree.OnMonth(_currentMonth);
		}
	}
}

int Game::GetNbFruit() const
{
	int nbFruit = 0;
	for (const auto& tree : _trees)
	{
		nbFruit += tree.GetNbFruit();
	}

	return nbFruit;
}

int Game::GetPotentialWeight() const
{
	int weight = 0;
	for (const auto& tree : _trees)
	{
		if (tree.CanBeHarvested(_currentMonth))
		{
			weight += tree.GetCurrentWeight();
		}
	}

	return weight;
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

void Game::NextYear()
{
	_totalWeight = 0;
	_currentMonth = Month::JANUARY;
	_harvestLeft = _maxHarvest;
}


