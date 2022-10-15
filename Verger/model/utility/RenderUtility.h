#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

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

namespace RenderUtility
{
	void DrawBar(Console::Screen& screen, const Bar& bar);
};

