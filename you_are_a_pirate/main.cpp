#include <iostream>
#include "players.hpp"
#include "shipcreators.hpp"
#include "gameprocess.hpp"
#include "gameview.hpp"
#include <thread>
#include <chrono>

Gamer* ResolveArgs(int argc, char* argv_pos, Field* f1, Field* f2, int number){
    if (std::string(argv_pos) == "random"){
        return new RandomGamer(f1, f2, number);
    }
    else if (std::string(argv_pos) == "console"){
        return new ConsoleGamer(f1, f2, number);
    }
    else {
        throw std::invalid_argument("wrong args");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3){
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    try{
        auto f1 = new Field(10);
        auto f2 = new Field(10);
        auto ev1 = new EnemyViewField(f2), ev2 = new EnemyViewField(f1);
        auto pv1 = new PlayerViewField(f1), pv2 = new PlayerViewField(f2);

        auto UI = ConsoleView(pv1, pv2, ev1, ev2);

        UI.display_message("Hiring Admiral 1");
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto Player1 = ResolveArgs(argc, argv[1], f1, f2, 1);
        UI.display_message("Hiring Admiral 2");
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto Player2 = ResolveArgs(argc, argv[2], f2, f1, 2);

        auto round = Game(Player1, Player2);

        UI.display_message(round.process(UI));

        delete Player2;
        delete Player1;
        delete pv1;
        delete ev1;
        delete f2;
        delete f1;
    }
    catch (std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
        return 2;
    }


    return 0;
}