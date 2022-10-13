#include "OrchardView.h"

#include "GameView.h"

OrchardView::OrchardView(Game* game) : View()
{
	_game = game;

	setComponents({
		new Console::BasicButton(
			"Buy a random tree [10$]", PositionX(0.25f), PositionY(10),
			[this]()
			{
				if (_game->HasEnoughMoney(10))
				{
					_game->BuyRandomTree(10);
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
			"Buy a pear tree [15$]", PositionX(0.25f), PositionY(15),
			[this]()
			{
				if (_game->HasEnoughMoney(15))
				{
					_game->BuyTree(PearTree(), 15);
				}
				else
				{
					_errorMessage = "Not enough money";
				}
			},
			true, true
		),
		new Console::BasicButton(
			"Buy an apple tree [5$]", PositionX(0.75f), PositionY(15),
			[this]()
			{
				if (_game->HasEnoughMoney(5))
				{
					_game->BuyTree(AppleTree(), 5);
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
				_game->SetView(new GameView(_game));
			},
			true, true
		)
	});

	if (_game->GetYear() >= 5)
	{
		// Add the button to go to the special shop

	}
}


void OrchardView::displayTrees(Console::Screen& screen) const
{
	// Display the three type of trees and their number
	const std::unordered_map<std::string, int> treeCount = _game->GetTrees();
	int y = 4;

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

	if (Console::Key::Up == key)
	{
		setCurrentButton(getCurrentButton() - 2);
	}
	else if (Console::Key::Down == key)
	{
		setCurrentButton(getCurrentButton() + 2);
	}
	else if (Console::Key::Right == key)
	{
		incrementCurrentButton();
	}
	else if (Console::Key::Left == key)
	{
		decrementCurrentButton();
	}

	View::OnKeyPressed(key);
}
