#include "Tree.h"

#include <random>

Tree::Tree(
	const std::string& name, const Month growthDate, const Month harvestDate, 
	const int fruitWeight, const int minNbFruit, const int maxNbFruit
)
{
	_name = name;
	_startHarvestDate = growthDate;
	_endHarvestDate = harvestDate;
	_fruitWeight = fruitWeight;
	_minNbFruit = minNbFruit;
	_maxNbFruit = maxNbFruit;
	_currentNbFruit = 0;
}


int GetRandomNumber(const int min, const int max) {
	std::random_device osSeed;
	uint_least32_t seed = osSeed();

	std::mt19937 generator(seed);
	std::uniform_int_distribution<uint_least32_t> distribute(min, max);

	return static_cast<int>(distribute(generator));
}

void Tree::OnMonth(const Month currentMonth)
{
	if (currentMonth == Month::APRIL)
	{
		if (GetRandomNumber(0, 100) < 5)
		{
			_currentNbFruit = 0;
			_currentNbMaxFruit = 0;
		}
		else
		{
			_currentNbFruit = GetRandomNumber(_minNbFruit, _maxNbFruit);
			_currentNbMaxFruit = _currentNbFruit;
		}
	}

	if (_currentNbFruit != 0)
	{
		// The harvest period
		if (currentMonth >= Month::APRIL && currentMonth <= _endHarvestDate)
		{
			// Lost 3 to 10% of fruits per month
			_currentNbFruit -= GetRandomNumber(_currentNbFruit * 3 / 100, _currentNbFruit * 10 / 100);
			_currentNbMaxFruit = _currentNbFruit;
		}
		// The fruit begin to rotten, losing a portion of fruits each months
		else if (currentMonth > _endHarvestDate && currentMonth <= Month::DECEMBER)
		{
			const int rottenMonths = static_cast<int>(Month::DECEMBER) - static_cast<int>(_endHarvestDate);

			_currentNbFruit -= static_cast<int>(
				static_cast<float>(_currentNbMaxFruit) * 1.0f / static_cast<float>(rottenMonths)
			);

			if (currentMonth == Month::DECEMBER)
			{
				_currentNbFruit = 0;
			}
		}
		// The winter period
		else if (currentMonth >= Month::JANUARY && currentMonth <= Month::MARCH)
		{
			_currentNbFruit = 0;
			_currentNbMaxFruit = 0;
		}
	}
}

int Tree::Harvest()
{
	const int fruits = _currentNbFruit;
	_currentNbFruit = 0;
	_currentNbMaxFruit = 0;

	return fruits * _fruitWeight;
}
