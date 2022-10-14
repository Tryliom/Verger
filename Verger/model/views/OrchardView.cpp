#include "OrchardView.h"

#include "GameView.h"
#include "SpecialShopView.h"

OrchardView::OrchardView(Game* game) : View()
{
	_game = game;

	setComponents({
		new Console::BasicButton(
			"Buy a random tree [15$]", PositionX(0.25f), PositionY(10),
			[this]()
			{
				if (_game->HasEnoughMoney(15))
				{
					_game->BuyRandomTree(15);
				}
				else
				{
					_errorMessage = "Not enough money";
				}
			},
			true, true
		),
		new Console::BasicButton(
			"Buy a cherry tree [25$]", PositionX(0.75f), PositionY(10),
			[this]()
			{
				if (_game->HasEnoughMoney(25))
				{
					_game->BuyTree(CherryTree(), 25);
				}
				else
				{
					_errorMessage = "Not enough money";
				}
			},
			true, true
		),
		new Console::BasicButton(
			"Buy a pear tree [12$]", PositionX(0.25f), PositionY(15),
			[this]()
			{
				if (_game->HasEnoughMoney(12))
				{
					_game->BuyTree(PearTree(), 12);
				}
				else
				{
					_errorMessage = "Not enough money";
				}
			},
			true, true
		),
		new Console::BasicButton(
			"Buy an apple tree [10$]", PositionX(0.75f), PositionY(15),
			[this]()
			{
				if (_game->HasEnoughMoney(10))
				{
					_game->BuyTree(AppleTree(), 10);
				}
				else
				{
					_errorMessage = "Not enough money";
				}
			},
			true, true
		),
		new Console::BasicButton(
			"Start the year", PositionX(0.5f), PositionY(20),
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
	const std::unordered_map<std::string, int> treeCount = _game->GetTrees();
	int y = 8;

	for (auto& tree : treeCount)
	{
		screen.Draw(Console::Text{
			.Str = tree.first + ": " + std::to_string(tree.second),
			.X = 2,
			.Y = y
		});

		y++;
	}
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
		.X = 2,
		.Y = 6
	});

	displayTrees(screen);

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

	moveBetweenComponents(key, true, true);

	View::OnKeyPressed(key);
}
