#ifndef YOU_ARE_A_PIRATE_SHIPCREATORS_HPP
#define YOU_ARE_A_PIRATE_SHIPCREATORS_HPP
#include "battleships.hpp"
//#include <exception>
#include <vector>
#include <memory>

class ShipCreator{
public:
    virtual std::shared_ptr<BattleShip> gimmeShip() = 0;
    virtual ~ShipCreator() = default;
};

template <class DatShip>
class DefaultCreator : public ShipCreator{
    std::shared_ptr<BattleShip> gimmeShip() override{
        return std::make_shared<DatShip>();
    }
};

class ShipFactory{
public:
    explicit ShipFactory();

    void initialize(std::vector<std::shared_ptr<BattleShip>>& fleet);
private:
    std::vector<ShipCreator*> creators;
};

#endif
