#include "battleships.hpp"

int BattleShip::showHitPoints(){
    return hit_points;
};

void BattleShip::sufferDamage(){
    hit_points--;
}

std::string BattleShip::showHitMessage() {
    std::string condition = (hit_points > 0) ? "damaged" : "destroyed";
    std::string name = (condition == "damaged") ? "ship" : getName();

    return "Dat " + name + " has been " + condition;
}

std::string FourHitShip::getName(){
    return "battleship";
}

std::string ThreeHitShip::getName(){
    return "cruiser";
}

std::string TwoHitShip::getName(){
    return "destroyer";
}

std::string OneHitShip::getName(){
    return "submarine";
}