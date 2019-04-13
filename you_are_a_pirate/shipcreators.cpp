#include "shipcreators.hpp"
#include <exception>

ShipFactory::ShipFactory() : creators(std::vector<ShipCreator*>(0)){
    creators.push_back(new DefaultCreator<FourHitShip>);
    creators.push_back(new DefaultCreator<ThreeHitShip>);
    creators.push_back(new DefaultCreator<TwoHitShip>);
    creators.push_back(new DefaultCreator<OneHitShip>);
}

void ShipFactory::initialize(std::vector<std::shared_ptr<BattleShip>>& fleet){
    for (size_t i = 0; i < creators.size(); ++i){
        for (size_t j = 0; j < i + 1; ++j){
            fleet.push_back(creators[i] -> gimmeShip());
        }
    }
    if (fleet.size() != 10){
        throw std::range_error("Ur fleet doesn't meet requirements, prepare for ur repression");
    }
}