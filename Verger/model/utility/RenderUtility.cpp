#include "RenderUtility.h"

namespace RenderUtility
{
	void DrawBar(Console::Screen& screen, const Bar& bar)
	{
		int y = bar.Y;

		if (bar.YCentered)
		{
			y += bar.Height / 2;
		}

		// Draw the background
		screen.DrawLine(
			bar.X,
			y,
			bar.X + bar.Width,
			y,
			bar.Height,
			bar.BackgroundColor
		);

		// Draw the content
		screen.DrawLine(
			bar.X,
			y,
			static_cast<int>(bar.X + bar.Width * bar.Percent),
			y,
			bar.Height,
			bar.Color
		);
	}
}