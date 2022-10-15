#include "OrchardView.h"
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
			"Special shop", PositionX(0.3f), PositionY(25),
			[this]()
			{
				_game->ChangeView(new SpecialShopView(_game));
			},
			true, true
		));
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

	RenderUtility::DisplayTreeCount(screen, _game, 6);
	RenderUtility::DisplayTreeData(screen, _treeData);
	RenderUtility::DisplayAverageWeightPerMonth(screen, _averageWeightPerMonth, _game);

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
