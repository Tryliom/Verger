#include "ResultView.h"

ResultView::ResultView(Game* game)
{
	_game = game;

	if (_game->HasSurpassGoal())
	{
		addComponent(new Console::BasicButton(
			"Return to your orchard", PositionX(0.5f), PositionY(0.5f),
			[this]()
			{
				_game->NextYear();
			}, true, true
		));
	}
	else
	{
		addComponent(new Console::BasicButton(
			"Restart", PositionX(0.5f), PositionY(0.5f),
			[this]()
			{
				_game->Restart();

			}, true, true
		));
	}
}

void ResultView::Update(Console::Screen& screen)
{
	View::Update(screen);

	if (_game->HasSurpassGoal())
	{
		screen.Draw(Console::Text{
			.Str = "You have surpassed your goal !",
			.X = Console::Screen::WIDTH / 2,
			.Y = 2,
			.XCentered = true
		});

		screen.Draw(Console::Text{
			.Str = "You have harvested " + _game->GetCompletion() + " weight !",
			.X = Console::Screen::WIDTH / 2,
			.Y = 4,
			.XCentered = true
		});

		screen.Draw(Console::Text{
			.Str = "You have gained " + _game->GetMoneyIncome() + " !",
			.X = Console::Screen::WIDTH / 2,
			.Y = 6,
			.XCentered = true
			});
	}
	else
	{
		screen.Draw(Console::Text{
			.Str = "You have not surpassed your goal !",
			.X = Console::Screen::WIDTH / 2,
			.Y = 2,
			.XCentered = true,
			.Background = Console::Background::RED
		});
	}
}
