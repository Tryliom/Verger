#include "model/controller/Game.h"

int main()
{
    Game game;

    Console::Screen::EnableVirtualTerminalProcessing();
    Console::Screen::CenterWindow();

    game.Start();
}
