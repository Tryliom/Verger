#include "GameView.h"

GameView::GameView(Game* game)
{
	_game = game;

	setupComponents();
}

void GameView::setupComponents()
{
	clearComponents();

	if (_game->GetCurrentMonth() != Month::END)
	{
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
				_game->NextMonth();

				if (_game->GetCurrentMonth() == Month::END)
				{
					setupComponents();
				}
			},
			true, true
		)
			});
	}
	else
	{

	}
}

void GameView::Update(Console::Screen& screen)
{
	View::Update(screen);

	if (_game->GetCurrentMonth() != Month::END)
	{
		screen.Draw(Console::Text{ 
			.Str = "Month: " + MONTH_TO_STRING.at(_game->GetCurrentMonth()),
			.X = 2,
			.Y = 2
		});

		screen.Draw(Console::Text{
			.Str = "Fruits: " + std::to_string(_game->GetNbFruit()),
			.X = 2,
			.Y = 4
		});

		screen.Draw(Console::Text{
			.Str = "How many gram you can get if you harvest now: " + std::to_string(_game->GetPotentialWeight()) + "g",
			.X = 2,
			.Y = 6
		});

		screen.Draw(Console::Text{
			.Str = "Harvested weight: " + std::to_string(_game->GetCurrentWeight()) + "/" + std::to_string(_game->GetGoalWeight()) + "g",
			.X = 2,
			.Y = 8,
			.Foreground = _game->HasSurpassGoal() ? Console::Foreground::RED : Console::Foreground::GREEN
		});

		screen.Draw(Console::Text{
			.Str = "Harvest left: " + std::to_string(_game->GetHarvestLeft()),
			.X = 2,
			.Y = 10
		});
	}
	else
	{
		// Display result of the year

	}
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
