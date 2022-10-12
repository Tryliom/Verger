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
	if (_currentMonth == Month::DECEMBER)
	{
		nextYear();
	}
	else
	{
		_currentMonth = static_cast<Month>(static_cast<int>(_currentMonth) + 1);
	}

	for (auto& tree : _trees)
	{
		tree.OnMonth(_currentMonth);
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
		weight += tree.GetCurrentWeight();
	}

	return weight;
}

void Game::Harvest()
{
	for (auto& tree : _trees)
	{
		_totalWeight += tree.Harvest();
	}
}

void Game::nextYear()
{
	_totalWeight = 0;
	_currentMonth = Month::JANUARY;
	_harvestLeft = _maxHarvest;
}


