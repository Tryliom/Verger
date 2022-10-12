#pragma once
#include <unordered_map>

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER,
	END
};

const std::unordered_map<Month, std::string> MONTH_TO_STRING = {
	{ Month::JANUARY, "January" },
	{ Month::FEBRUARY, "February" },
	{ Month::MARCH, "March" },
	{ Month::APRIL, "April" },
	{ Month::MAY, "May" },
	{ Month::JUNE, "June" },
	{ Month::JULY, "July" },
	{ Month::AUGUST, "August" },
	{ Month::SEPTEMBER, "September" },
	{ Month::OCTOBER, "October" },
	{ Month::NOVEMBER, "November" },
	{ Month::DECEMBER, "December" },
};
