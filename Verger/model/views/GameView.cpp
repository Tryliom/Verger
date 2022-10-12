#include "GameView.h"

GameView::GameView(Game* game)
{
	_game = game;

	setComponents({
		new Console::BasicButton(
			"Harvest", PositionX(0.25f), PositionY(0.5f),
			[game]()
			{
				game->Harvest();
			},
			true, true
		),
		new Console::BasicButton(
			"Next month", PositionX(0.75f), PositionY(0.5f),
			[game]()
			{
				game->NextMonth();
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
		.Str = "Harvested weight: " + std::to_string(_game->GetCurrentWeight()) + "g",
		.X = 2,
		.Y = 8
	});

	screen.Draw(Console::Text{
		.Str = "Goal: " + std::to_string(_game->GetGoalWeight()) + "g",
		.X = Console::Screen::WIDTH / 2,
		.Y = 2,
		.XCentered = true
	});
}

void GameView::OnKeyPressed(const char key)
{
	if (Console::Key::Right == key)
	{
		IncrementCurrentButton();
	}
	else if (Console::Key::Left == key)
	{
		DecrementCurrentButton();
	}

	View::OnKeyPressed(key);
}
