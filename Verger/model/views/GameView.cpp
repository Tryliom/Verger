#include "GameView.h"

GameView::GameView(Game* game)
{
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

void GameView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	auto game = static_cast<Game*>(controller);

	screen.Draw(Console::Text{ 
		.Str = "Month: " + MONTH_TO_STRING.at(game->GetCurrentMonth()),
		.X = 2,
		.Y = 2
	});

	screen.Draw(Console::Text{
		.Str = "Fruits: " + std::to_string(game->GetNbFruit()),
		.X = 2,
		.Y = 4
	});

	screen.Draw(Console::Text{
		.Str = "How many gram you can get if you harvest now: " + std::to_string(game->GetPotentialWeight()) + "g",
		.X = 2,
		.Y = 6
	});

	screen.Draw(Console::Text{
		.Str = "Harvested weight: " + std::to_string(game->GetCurrentWeight()) + "g",
		.X = 2,
		.Y = 8
	});

	screen.Draw(Console::Text{
		.Str = "Goal: " + std::to_string(game->GetGoalWeight()) + "g",
		.X = Console::Screen::WIDTH / 2,
		.Y = 2,
		.XCentered = true
	});
}

void GameView::OnKeyPressed(Console::Controller* controller, const char key)
{
	if (Console::Key::Right == key)
	{
		IncrementCurrentButton();
	}
	else if (Console::Key::Left == key)
	{
		DecrementCurrentButton();
	}

	View::OnKeyPressed(controller, key);
}
