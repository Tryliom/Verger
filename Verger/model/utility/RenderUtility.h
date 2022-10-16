#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"
#include "../controller/Game.h"

struct Bar
{
	int X{0};
	int Y{0};
	int Width{0};
	int Height{0};
	float Percent{1.0f};
	COLORREF Color{ RGB(100, 0, 0) };
	COLORREF BackgroundColor{ RGB(100, 100, 100) };
	bool YCentered{ false };
};

struct Legend
{
	std::string Name;
	COLORREF Color;
};

namespace RenderUtility
{
	void DrawBar(Console::Screen& screen, const Bar& bar);
	void DisplayAverageWeightPerMonth(Console::Screen& screen, const std::unordered_map<Month, FruitsWeightData>& averageWeightPerMonth, const Game* game);
	void DisplayTreeData(Console::Screen& screen, const std::vector<TreeData>& treeData);
	void DisplayTreeCount(Console::Screen& screen, const Game* game, int y);
	void DrawCompletionBar(Console::Screen& screen, int x, int y, int width, int height, CompletionData data);
	void DrawLegends(Console::Screen& screen, const std::vector<Legend>& legends, int x, int y);
};

