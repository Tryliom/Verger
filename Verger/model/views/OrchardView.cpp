#include "OrchardView.h"

#include <ranges>

#include "GameView.h"
#include "SpecialShopView.h"
#include "../tree/TreeFactory.h"
#include "../utility/RenderUtility.h"

OrchardView::OrchardView(Game* game) : View()
{
	_game = game;
	_treeData = TreeFactory::GetTreeData();
	_averageWeightPerMonth = _game->GetAverageWeightPerMonth();

	Console::AudioManager::Play(MAIN_THEME_PATH, true);

	setComponents({
		new Console::BasicButton(
			"Buy a cherry tree [25$]", PositionX(0.3f), PositionY(10),
			[this]()
			{
				if (_game->HasEnoughMoney(25))
				{
					_game->BuyTree(CherryTree(), 25);
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
			"Buy a pear tree [12$]", PositionX(0.3f), PositionY(15),
			[this]()
			{
				if (_game->HasEnoughMoney(12))
				{
					_game->BuyTree(PearTree(), 12);
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
			"Buy an apple tree [10$]", PositionX(0.3f), PositionY(20),
			[this]()
			{
				if (_game->HasEnoughMoney(10))
				{
					_game->BuyTree(AppleTree(), 10);
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

	for (const auto& weight : _averageWeightPerMonth | std::views::values)
	{
		if (weight > maxValue)
		{
			maxValue = weight;
		}
	}

	// Draw bars for each month based on the max value
	int x = xLeft;
	int y = yTop + maxHeight;

	for (const auto& weight : _averageWeightPerMonth | std::views::values)
	{
		if (weight > 0)
		{
			// Growth fruit weight
			screen.DrawRect(
				x + widthBar,
				y - maxHeight * weight / maxValue,
				widthBar,
				maxHeight * weight / maxValue,
				RGB(0, 204, 102),
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
