#include "players.hpp"
#include <thread>
#include <chrono>
#include <algorithm>

long long Gamer::showShipsLeft(){
    return std::count_if(fleet.begin(), fleet.end(), [](std::shared_ptr<BattleShip> s){
        return s -> showHitPoints() > 0;
    });
}

void ConsoleGamer::emplacement_strategy(GameView &ui){
    auto generator = new ShipFactory();
    generator -> initialize(fleet);
    bool error = false, horizontal_position = false;
    std::string y;
    int x = 0;
    for (auto& ship: fleet){
        ui.display_message("Emplace ur fleet, my general");
        do{
            try{
                ui.display_message("Emplacing " + ship -> getName());
                std::string pos;
                std::cin >> y >> x >> pos;
                if (pos == "h"){
                    horizontal_position = true;
                } else if(pos == "v"){
                    horizontal_position = false;
                }
                else{
                    throw std::runtime_error("unclear position");
                }

                if (y.length() != 1){
                    throw std::runtime_error("wrong coordinates");
                }
                if (y[0] < 'A' || y[0] > 'A' + OwnField -> fieldSize() - 1){
                    throw std::runtime_error("wrong coordinates");
                }
                else {
                    y[0] -= 'A';
                }


                if (x < 1 || x > OwnField -> fieldSize()){
                    throw std::runtime_error("wrong coordinates");
                }
                OwnField -> emplace_ship(ship, x - 1, y[0], horizontal_position);
                ui.display_message("Emplaced");
                ui.Draw_for_player("my" + std::to_string(number));
                error = false;
            }
            catch (std::runtime_error& e){
                ui.display_message(e.what());
                error = true;
            }
        } while(error);
    }
    delete generator;
}

bool ConsoleGamer::playing_strategy(GameView &ui){
    int x;
    std::string y;
    bool error = false, result = false;
    do{
        std::cin >> y >> x;
        try{
            if (y.length() != 1){
                throw std::runtime_error("wrong coordinates");
            }

            if (y[0] < 'A' || y[0] > 'A' + OwnField -> fieldSize() - 1){
                throw std::runtime_error("wrong coordinates");
            }
            else {
                y[0] -= 'A';
            }

            if (x < 1 || x > OwnField -> fieldSize()){
                throw std::runtime_error("wrong coordinates");
            }
            result = EnemyField -> game_modify(x - 1, y[0], ui);

            error = false;
        }
        catch(std::exception& e){
            ui.display_message(e.what());
            error = true;
        }
    } while (error);
    return result;
}

RandomGamer::RandomGamer(Field *mine, Field *urs, int num) : Gamer(mine, urs, num){
    auto now = std::chrono::high_resolution_clock::now();
    gen.seed(now.time_since_epoch().count());
}

void RandomGamer::emplacement_strategy(GameView &ui){
    std::uniform_int_distribution<int> dist_field(0, OwnField -> fieldSize() - 1);
    std::uniform_int_distribution<int> dist_bool(0, 1);

    auto generator = new ShipFactory();
    generator -> initialize(fleet);
    bool error = false;
    for (auto& ship: fleet){
        do{
            try{
                OwnField -> emplace_ship(ship, dist_field(gen), dist_field(gen), dist_bool(gen));
                error = false;
            }
            catch (std::runtime_error& e){
                error = true;
            }
        } while(error);
    }

    delete generator;
}

bool RandomGamer::playing_strategy(GameView &ui){
    std::uniform_int_distribution<int> dist_field(0, OwnField -> fieldSize() - 1);

    bool error = false, result = false;
    do{
        try{
            std::this_thread::sleep_for(std::chrono::seconds(3));
            result = EnemyField -> game_modify(dist_field(gen), dist_field(gen), ui);
            error = false;
        }
        catch(std::exception& e){
            error = true;
        }
    } while (error);
    return result;
}