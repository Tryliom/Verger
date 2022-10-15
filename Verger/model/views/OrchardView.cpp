#include "OrchardView.h"

#include <ranges>

#include "GameView.h"
#include "SpecialShopView.h"
#include "../tree/TreeFactory.h"
#include "../utility/RenderUtility.h"

OrchardView::OrchardView(Game* game) : View()
{
	_game = game;

	// Gain one tree of each type every time the game is started or the player wins
	_game->AddTree(TreeFactory::GetTree(TreeType::CHERRY));
	_game->AddTree(TreeFactory::GetTree(TreeType::PEAR));
	_game->AddTree(TreeFactory::GetTree(TreeType::APPLE));

	_treeData = TreeFactory::GetTreeData();
	_averageWeightPerMonth = _game->GetAverageWeightPerMonth();

	Console::Screen::SetWindowSize(1200, 1000);
	Console::Screen::CenterWindow();

	Console::AudioManager::Play(ORCHARD_THEME_PATH, true);

	setComponents({
		new Console::BasicButton(
			"Buy a cherry tree [30$]", PositionX(0.3f), PositionY(10),
			[this]()
			{
				if (_game->HasEnoughMoney(30))
				{
					_game->BuyTree(CherryTree(), 30);
					updateAverageWeightPerMonth();
				}
				else
				{
					_errorMessage = "Not enough money";
				}
			},
			true, true
		),
		new Console::BasicButton(
			"Buy a pear tree [14$]", PositionX(0.3f), PositionY(15),
			[this]()
			{
				if (_game->HasEnoughMoney(14))
				{
					_game->BuyTree(PearTree(), 14);
					updateAverageWeightPerMonth();
				}
				else
				{
					_errorMessage = "Not enough money";
				}
			},
			true, true
		),
		new Console::BasicButton(
			"Buy an apple tree [8$]", PositionX(0.3f), PositionY(20),
			[this]()
			{
				if (_game->HasEnoughMoney(8))
				{
					_game->BuyTree(AppleTree(), 8);
					updateAverageWeightPerMonth();
				}
				else
				{
					_errorMessage = "Not enough money";
				}
			},
			true, true
		),
		new Console::BasicButton(
			"Start the year", PositionX(0.5f), PositionY(25),
			[this]()
			{
				_game->ClearStack();
				_game->SetView(new GameView(_game));
			},
			true, true
		)
	});

	if (_game->GetYear() % 5 == 0)
	{
		// Add the button to go to the special shop
		addComponent(new Console::BasicButton(
			"Special shop", PositionX(0.5f), PositionY(15),
			[this]()
			{
				_game->ChangeView(new SpecialShopView(_game));
			},
			true, true
		));
	}
}


void OrchardView::displayTrees(Console::Screen& screen) const
{
	// Display the three type of trees and their number
	const std::unordered_map<TreeType, int> treeCount = _game->GetTrees();
	int y = 6;

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

void OrchardView::displayTreeData(Console::Screen& screen) const
{
	screen.Draw(Console::Text{
		.Str = "Production per year",
		.X = PositionX(0.4f).GetValue(),
		.Y = 5
	});

	const float widthBar = static_cast<float>(PositionX(0.15f).GetValue(true));
	int y = 10;

	for (auto& data : _treeData)
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

void OrchardView::displayAverageWeightPerMonth(Console::Screen& screen) const
{
	const int widthPerMonth = PositionX(0.8f).GetValue(true) / 12;
	const int widthBar = widthPerMonth / 3;
	const int maxHeight = PositionY(-30, 0.9f).GetValue(true);
	const int yTop = PositionY(30).GetValue(true);
	const int xLeft = PositionX(0.1f).GetValue(true);
	int maxValue = _game->GetGoalWeight();

	for (const auto& fruits : _averageWeightPerMonth | std::views::values)
	{
		if (fruits.GrowthWeight > maxValue)
		{
			maxValue = fruits.GrowthWeight;
		}
	}

	// Draw bars for each month based on the max value
	int x = xLeft;
	int y = yTop + maxHeight;

	for (const auto& fruits : _averageWeightPerMonth | std::views::values)
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
		PositionX(0.1f).GetValue(true),
		y,
		PositionX(0.9f).GetValue(true),
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
		PositionX(0.1f).GetValue(true),
		y - maxHeight * _game->GetGoalWeight() / maxValue,
		PositionX(0.9f).GetValue(true),
		y - maxHeight * _game->GetGoalWeight() / maxValue,
		3,
		RGB(255, 0, 0)
	);

	// Draw month names
	x = xLeft + widthPerMonth / 2;

	for (const auto& month : _averageWeightPerMonth | std::views::keys)
	{
		screen.Draw(Console::Text{
			.Str = MONTH_TO_STRING.at(month),
			.X = x / Console::Screen::PIXEL_RATIO_X,
			.Y = y / Console::Screen::PIXEL_RATIO_Y + 1,
			.XCentered = true
		});

		x += widthPerMonth;
	}
}

void OrchardView::updateAverageWeightPerMonth()
{
	_game->AddToQueue([this]()
		{
			_averageWeightPerMonth = _game->GetAverageWeightPerMonth();
		}
	);
}

void OrchardView::Update(Console::Screen& screen)
{
	View::Update(screen);

	screen.Draw(Console::Text{
		.Str = "Money: " + _game->GetMoney(),
		.X = 2,
		.Y = 2
	});

	screen.Draw(Console::Text{
		.Str = "Max harvest per year: " + std::to_string(_game->GetMaxHarvest()),
		.X = 2,
		.Y = 4
	});

	screen.Draw(Console::Text{
		.Str = "Year " + std::to_string(_game->GetYear()),
		.X = Console::Screen::WIDTH / 2,
		.Y = 2
	});

	displayTrees(screen);
	displayTreeData(screen);
	displayAverageWeightPerMonth(screen);

	// Display the error message
	if (!_errorMessage.empty())
	{
		screen.Draw(Console::Text{
			.Str = _errorMessage,
			.X = Console::Screen::WIDTH / 2,
			.Y = Console::Screen::HEIGHT - 3,
			.XCentered = true,
			.Foreground = Console::Foreground::RED
		});
	}
}

void OrchardView::OnKeyPressed(const char key)
{
	_errorMessage.clear();

	moveBetweenComponents(key);

	View::OnKeyPressed(key);
}
