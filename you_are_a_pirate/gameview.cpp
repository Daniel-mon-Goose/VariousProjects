#include "gameview.hpp"

void ConsoleView::Draw_for_player(std::string &&indicator){
    if (indicator == "my1"){
        player1_view -> DrawField();
    }
    else if (indicator == "enemy1"){
        player1_enemy_view -> DrawField();
    }
    else if (indicator == "my2"){
        player2_view -> DrawField();
    }
    else {
        player2_enemy_view -> DrawField();
    }
}

void ConsoleView::display_message(const std::string &text){
    std::cout << text << std::endl;
}

bool Field::game_modify(int x, int y, GameView& ui){
    cell& sea_cell = data[x][y];
    if(sea_cell.lamp == cell_indicator::free){
        sea_cell.lamp = cell_indicator::splashed;
        this -> Notify();
        ui.display_message("You missed");
        return false;
    }
    else if(sea_cell.lamp == cell_indicator::filled){
        sea_cell.lamp = cell_indicator::hit;
        sea_cell.ship_indicator -> sufferDamage();
        ui.display_message(sea_cell.ship_indicator -> showHitMessage());
        this -> Notify();
        return true;
    }
    else{
        throw std::invalid_argument("Please, choose another cell");
    }
}