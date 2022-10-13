#include "model/controller/Game.h"

int main()
{
    Game game;

    Console::Screen::EnableVirtualTerminalProcessing();
    Console::Screen::SetTitle("Orchard simulator");
    Console::Screen::SetWindowSize(1200, 700);
    Console::Screen::CenterWindow();

    game.Start();
}
