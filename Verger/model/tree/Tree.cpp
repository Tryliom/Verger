#include "Tree.h"
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

Tree::Tree(
	const TreeType type, const Month startHarvestDate, const Month endHarvestDate,
	const int fruitWeight, const int minNbFruit, const int maxNbFruit
)
{
	_type = type;
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

TreeData Tree::GetData() const
{
	return TreeData
	(
		_type,
		_minNbFruit * _fruitWeight,
		_maxNbFruit * _fruitWeight,
		_startHarvestDate,
		_endHarvestDate
	);
}

std::unordered_map<Month, FruitsWeightData> Tree::GetAverageWeightPerMonth()
{
	std::unordered_map<Month, FruitsWeightData> averageWeightPerMonth;
	int nbFruit = 0;
	int nbFruitMax = 0;
	int harvestableWeight = 0;

	for (int i = 1; i <= 12; i++)
	{
		auto month = static_cast<Month>(i);

		if (month == Month::APRIL)
		{
			nbFruit = _minNbFruit + (_maxNbFruit - _minNbFruit) / 2;
		}

		if (month >= Month::APRIL && month <= _endHarvestDate)
		{
			nbFruit -= static_cast<int>(static_cast<float>(nbFruit) * 0.065f);
			nbFruitMax = nbFruit;
		}

		if (month > _endHarvestDate && month < Month::DECEMBER)
		{
			const int rottenMonths = static_cast<int>(Month::DECEMBER) - static_cast<int>(_endHarvestDate);

			nbFruit -= static_cast<int>(
				static_cast<float>(nbFruitMax) * 1.0f / static_cast<float>(rottenMonths)
			);
		}

		if (month == Month::DECEMBER)
		{
			nbFruit = 0;
		}

		if (month >= _startHarvestDate && month <= Month::DECEMBER)
		{
			harvestableWeight = nbFruit * _fruitWeight;
		}

		averageWeightPerMonth[month] = FruitsWeightData(nbFruit * _fruitWeight, harvestableWeight);
	}

	return averageWeightPerMonth;
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
