#include "GameView.h"
#include "ResultView.h"
#include "../utility/RenderUtility.h"

GameView::GameView(Game* game)
{
	_game = game;
	_treeInformation = _game->GetTreeInformation();
	_completionData = _game->GetCompletionData();

	Console::Screen::SetWindowSize(1200, 700);
	Console::Screen::CenterWindow();

	Console::AudioManager::Play(MAIN_THEME_PATH, true);

	setComponents({
		new Console::BasicButton(
			"Harvest", PositionX(0.25f), PositionY(0.5f),
			[this]()
			{
				_game->Harvest();
				updateData();
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
					updateData();
				}
			},
			true, true
		)
	});
}

void GameView::updateData()
{
	_game->AddToQueue([this]()
		{
			_treeInformation = _game->GetTreeInformation();
			_completionData = _game->GetCompletionData();
		}
	);
}

void GameView::Update(Console::Screen& screen)
{
	View::Update(screen);

	screen.Draw(Console::Text{ 
		.Str = "Month: " + MONTH_TO_STRING.at(_game->GetCurrentMonth()),
		.X = PositionX(0.5f).GetValue(),
		.Y = 5,
		.XCentered = true
	});

	screen.Draw(Console::Text{
		.Str = "Harvest left: " + std::to_string(_game->GetHarvestLeft()),
		.X = PositionX(0.5f).GetValue(),
		.Y = 7,
		.XCentered = true
	});

	RenderUtility::DrawCompletionBar(screen, PositionX(0.1f).GetValue(true), PositionY(2).GetValue(true),
		PositionX(0.8f).GetValue(true), 20, _completionData);
	RenderUtility::DrawLegends(screen, {
			Legend("Goal", RGB(255, 0, 0)),
			Legend("Harvestable", RGB(255, 128, 0)),
			Legend("Harvested", RGB(0, 153, 76))
		}, PositionX(4).GetValue(), 5
	);
}

void GameView::OnKeyPressed(const char key)
{
	moveBetweenComponents(key);

	View::OnKeyPressed(key);
}
