#include "RenderUtility.h"
#include "../tree/TreeFactory.h"

#include <ranges>

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

	void DisplayAverageWeightPerMonth(Console::Screen& screen, 
		const std::unordered_map<Month, FruitsWeightData>& averageWeightPerMonth, const Game* game)
	{
		const int widthPerMonth = PositionX(0.8f).GetValue(true) / 12;
		const int widthBar = widthPerMonth / 3;
		const int maxHeight = PositionY(-30, 0.9f).GetValue(true);
		const int yTop = PositionY(30).GetValue(true);
		const int xLeft = PositionX(0.15f).GetValue(true);
		int maxValue = game->GetGoalWeight();

		for (const auto& fruits : averageWeightPerMonth | std::views::values)
		{
			if (fruits.GrowthWeight > maxValue)
			{
				maxValue = fruits.GrowthWeight;
			}
			if (fruits.HarvestableWeight > maxValue)
			{
				maxValue = fruits.HarvestableWeight;
			}
		}

		// Draw bars for each month based on the max value
		int x = xLeft;
		int y = yTop + maxHeight;

		for (const auto& fruits : averageWeightPerMonth | std::views::values)
		{
			if (fruits.GrowthWeight > 0)
			{
				// Growth fruit weight
				screen.DrawRect(
					x + widthBar,
					y - maxHeight * fruits.GrowthWeight / maxValue,
					widthBar / 2,
					maxHeight * fruits.GrowthWeight / maxValue,
					RGB(0, 204, 102),
					false
				);
			}

			if (fruits.HarvestableWeight > 0)
			{
				// Growth fruit weight
				screen.DrawRect(
					x + widthBar * 3 / 2,
					y - maxHeight * fruits.HarvestableWeight / maxValue,
					widthBar / 2,
					maxHeight * fruits.HarvestableWeight / maxValue,
					RGB(255, 128, 0),
					false
				);
			}

			x += widthPerMonth;
		}

		// Draw bottom line
		screen.DrawLine(
			xLeft,
			y,
			xLeft + PositionX(0.8f).GetValue(true),
			y,
			3,
			RGB(200, 200, 200)
		);

		// Draw left line
		screen.DrawLine(
			xLeft,
			y,
			xLeft,
			yTop,
			3,
			RGB(200, 200, 200)
		);

		// Draw goal line
		screen.DrawLine(
			xLeft,
			y - maxHeight * game->GetGoalWeight() / maxValue,
			xLeft + PositionX(0.8f).GetValue(true),
			y - maxHeight * game->GetGoalWeight() / maxValue,
			3,
			RGB(255, 0, 0)
		);

		// Draw month names
		x = xLeft + widthPerMonth / 2;

		for (const auto& month : averageWeightPerMonth | std::views::keys)
		{
			screen.Draw(Console::Text{
				.Str = MONTH_TO_STRING.at(month),
				.X = x / Console::Screen::PIXEL_RATIO_X,
				.Y = y / Console::Screen::PIXEL_RATIO_Y + 1,
				.XCentered = true
				});

			x += widthPerMonth;
		}

		// Draw legends, green for growth, orange for harvestable and red for goal
		screen.Draw(Console::Text{
			.Str = "Total",
			.X = 4,
			.Y = yTop / Console::Screen::PIXEL_RATIO_Y + 3
			});

		screen.DrawRect(
			PositionX(2).GetValue(true),
			yTop + PositionY(3).GetValue(true) + PositionY(1).GetValue(true) / 4,
			10,
			10,
			RGB(0, 204, 102)
		);

		screen.Draw(Console::Text{
			.Str = "Harvestable",
			.X = 4,
			.Y = yTop / Console::Screen::PIXEL_RATIO_Y + 5
			});

		screen.DrawRect(
			PositionX(2).GetValue(true),
			yTop + PositionY(5).GetValue(true) + PositionY(1).GetValue(true) / 4,
			10,
			10,
			RGB(255, 128, 0)
		);

		screen.Draw(Console::Text{
			.Str = "Goal",
			.X = 4,
			.Y = yTop / Console::Screen::PIXEL_RATIO_Y + 7
			});

		screen.DrawRect(
			PositionX(2).GetValue(true),
			yTop + PositionY(7).GetValue(true) + PositionY(1).GetValue(true) / 4,
			10,
			10,
			RGB(255, 0, 0)
		);
	}

	void DisplayTreeData(Console::Screen& screen, const std::vector<TreeData>& treeData)
	{
		screen.Draw(Console::Text{
		.Str = "Production per year",
		.X = PositionX(0.4f).GetValue(),
		.Y = 5
			});

		const float widthBar = static_cast<float>(PositionX(0.15f).GetValue(true));
		int y = 10;

		for (auto& data : treeData)
		{
			RenderUtility::DrawBar(
				screen,
				Bar{
					.X = PositionX(1, 0.4f).GetValue(true),
					.Y = PositionY(y).GetValue(true) + PositionY(1).GetValue(true) / 3,
					.Width = static_cast<int>(widthBar * data.MaxTotalWeight),
					.Height = 8,
					.Percent = data.MinTotalWeight / data.MaxTotalWeight,
					.Color = RGB(0, 204, 102),
					.BackgroundColor = RGB(0, 153, 76),
					.YCentered = true
				}
			);
			y += 5;
		}
	}

	void DisplayTreeCount(Console::Screen& screen, const Game* game, int y)
	{
		// Display the three type of trees and their number
		const std::unordered_map<TreeType, int> treeCount = game->GetTrees();

		for (auto& tree : treeCount)
		{
			screen.Draw(Console::Text{
				.Str = TreeFactory::GetTreeName(tree.first) + ": " + std::to_string(tree.second),
				.X = 2,
				.Y = y
				});

			y++;
		}
	}

	void DrawCompletionBar(Console::Screen& screen, const int x, const int y, const int width, const int height, CompletionData data)
	{
		// Draw a grey bar for the background
		screen.DrawRect(
			x,
			y,
			width,
			height,
			RGB(60, 60, 60)
		);

		// Draw a orange bar for the potential harvestable weight
		screen.DrawRect(
			x,
			y,
			static_cast<int>(width * data.PotentialWeight / static_cast<float>(data.MaxWeight)),
			height,
			RGB(255, 128, 0)
		);

		// Draw a light green bar for the current harvested weight
		screen.DrawRect(
			x,
			y,
			static_cast<int>(width * data.CurrentWeight / static_cast<float>(data.MaxWeight)),
			height,
			RGB(0, 153, 76)
		);

		// Draw a red circle for the goal
		screen.DrawCircle(
			x + static_cast<int>(width * data.GoalWeight / static_cast<float>(data.MaxWeight)) - height / 2,
			y,
			height / 2,
			RGB(255, 0, 0)
		);
	}

	void DrawLegends(Console::Screen& screen, const std::vector<Legend>& legends, int x, int y)
	{
		// Draw the legends
		for (auto& legend : legends)
		{
			screen.Draw(Console::Text{
				.Str = legend.Name,
				.X = x,
				.Y = y
				});

			screen.DrawRect(
				x * Console::Screen::PIXEL_RATIO_X - 20,
				y * Console::Screen::PIXEL_RATIO_Y + PositionY(1).GetValue(true) / 4,
				10,
				10,
				legend.Color
			);

			y += 2;
		}
	}
}
