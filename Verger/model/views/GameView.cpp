#include "GameView.h"
#include "ResultView.h"

GameView::GameView(Game* game)
{
	_game = game;

	setComponents({
		new Console::BasicButton(
			"Harvest", PositionX(0.25f), PositionY(0.5f),
			[this]()
			{
				_game->Harvest();
			},
			true, true
		),
		new Console::BasicButton(
			"Next month", PositionX(0.75f), PositionY(0.5f),
			[this]()
			{
				if (_game->GetCurrentMonth() == Month::DECEMBER)
				{
					_game->SetView(new ResultView(_game));
				}
				else
				{
					_game->NextMonth();
				}
			},
			true, true
		)
	});
}

void GameView::Update(Console::Screen& screen)
{
	View::Update(screen);

	screen.Draw(Console::Text{ 
		.Str = "Month: " + MONTH_TO_STRING.at(_game->GetCurrentMonth()),
		.X = 2,
		.Y = 2
	});

	screen.Draw(Console::Text{
		.Str = "Fruits: " + _game->GetNbFruit(),
		.X = 2,
		.Y = 4
	});

	screen.Draw(Console::Text{
		.Str = "Harvest potential weight: " + _game->GetPotentialWeightFormatted(),
		.X = 2,
		.Y = 6
	});

	screen.Draw(Console::Text{
		.Str = "Harvested weight: " + _game->GetCompletion(),
		.X = 2,
		.Y = 8,
		.Background = _game->HasSurpassGoal() ? Console::Background::GREEN : Console::Background::RED,
		.Foreground = Console::Foreground::WHITE,
	});

	screen.Draw(Console::Text{
		.Str = "Harvest left: " + std::to_string(_game->GetHarvestLeft()),
		.X = 2,
		.Y = 10
	});
}

void GameView::OnKeyPressed(const char key)
{
	if (Console::Key::Right == key)
	{
		incrementCurrentButton();
	}
	else if (Console::Key::Left == key)
	{
		decrementCurrentButton();
	}

	View::OnKeyPressed(key);
}
