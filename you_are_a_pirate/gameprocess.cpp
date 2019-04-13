#include "gameprocess.hpp"
#include <thread>
#include <chrono>

std::string Game::process(GameView &ui){
    Player1 -> emplacement_strategy(ui);
    Player2 -> emplacement_strategy(ui);

    //TODO delete checker
    ui.Draw_for_player("my2");

    bool first_success = false, second_success = false;

    while (Player1 -> showShipsLeft() > 0 && Player2 -> showShipsLeft() > 0){
        do{
            ui.display_message("Player 1 shoots");

            if (typeid(*Player1).name() == typeid(ConsoleGamer).name()){
                ui.display_message("your field");
                ui.Draw_for_player("my1");
            }

            ui.display_message("enemy's field");
            ui.Draw_for_player("enemy1");
            first_success = Player1 -> playing_strategy(ui);
        } while (first_success && Player2 -> showShipsLeft() > 0);
        if (Player2 -> showShipsLeft() == 0){
            break;
        }
        do{
            ui.display_message("Player 2 shoots");

            if (typeid(*Player2) == typeid(ConsoleGamer)){
                ui.display_message("your field");
                ui.Draw_for_player("my2");
            }

            ui.display_message("enemy's field");
            ui.Draw_for_player("enemy2");
            second_success = Player2 -> playing_strategy(ui);
        } while (second_success && Player1 ->showShipsLeft() > 0);
    }

    if (Player1 -> showShipsLeft() > 0){
        return "Player 1 wins";
    }

    return "Player 2 wins";
}