#include "SpecialShopView.h"

#include "OrchardView.h"

SpecialShopView::SpecialShopView(Game* game)
{
	_game = game;

	setComponents({
		new Console::BasicButton(
			"Buy an additional harvest [100$]", PositionX(0.25f), PositionY(10),
			[this]()
			{
				//TODO: The max harvest is not applied for the next year
				if (_game->HasEnoughMoney(100))
				{
					_game->BuyHarvest(100);
				}
				else
				{
					_errorMessage = "Not enough money";
				}
			},
			true, true
		),
		/*new Console::BasicButton(
			"Buy  [25$]", PositionX(0.75f), PositionY(10),
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
		),*/
		new Console::BasicButton(
			"Back", PositionX(0.5f), PositionY(20),
			[this]()
			{
				_game->SetView(new OrchardView(_game));
			},
			true, true
		)
	});
}

void SpecialShopView::Update(Console::Screen& screen)
{
	View::Update(screen);

	screen.Draw(Console::Text{
		.Str = "Money: " + _game->GetMoney(),
		.X = 2,
		.Y = 2
	});
}

void SpecialShopView::OnKeyPressed(char key)
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
