#include "Tree.h"
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

Tree::Tree(
	const std::string& name, const Month startHarvestDate, const Month endHarvestDate, 
	const int fruitWeight, const int minNbFruit, const int maxNbFruit
)
{
	_name = name;
	_startHarvestDate = startHarvestDate;
	_endHarvestDate = endHarvestDate;
	_fruitWeight = fruitWeight;
	_minNbFruit = minNbFruit;
	_maxNbFruit = maxNbFruit;
	_currentNbFruit = 0;
	_currentNbMaxFruit = 0;
}

bool Tree::CanBeHarvested(const Month currentMonth) const
{
	return _currentNbFruit > 0 && currentMonth >= _startHarvestDate && currentMonth <= Month::DECEMBER;
}

void Tree::OnMonth(const Month currentMonth)
{
	if (currentMonth == Month::APRIL)
	{
		if (Random::GetInt(0, 100) < 5)
		{
			_currentNbFruit = 0;
			_currentNbMaxFruit = 0;
		}
		else
		{
			_currentNbFruit = Random::GetInt(_minNbFruit, _maxNbFruit);
			_currentNbMaxFruit = _currentNbFruit;
		}
	}

	if (_currentNbFruit != 0)
	{
		// The harvest period
		if (currentMonth >= Month::APRIL && currentMonth <= _endHarvestDate)
		{
			// Lost 3 to 10% of fruits per month
			_currentNbFruit -= Random::GetInt(_currentNbFruit * 3 / 100, _currentNbFruit * 10 / 100);
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

int Tree::Harvest(const Month currentMonth)
{
	int fruits = 0;

	if (currentMonth >= _startHarvestDate)
	{
		fruits = _currentNbFruit;
		_currentNbFruit = 0;
		_currentNbMaxFruit = 0;
	}

	return fruits * _fruitWeight;
}
