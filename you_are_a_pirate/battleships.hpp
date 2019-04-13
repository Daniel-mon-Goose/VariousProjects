#ifndef YOU_ARE_A_PIRATE_BATTLESHIPS_HPP
#define YOU_ARE_A_PIRATE_BATTLESHIPS_HPP
#include <string>

class BattleShip{
public:
    explicit BattleShip(int points) : hit_points(points){}

    virtual int showHitPoints();

    virtual void sufferDamage();

    std::string showHitMessage();

    virtual std::string getName() = 0;

    virtual ~BattleShip() = default;
private:
    int hit_points;
};

class FourHitShip : public BattleShip{
public:
    FourHitShip() : BattleShip(4){}
    std::string getName() override;
};

class ThreeHitShip : public BattleShip{
public:
    ThreeHitShip() : BattleShip(3){}
    std::string getName() override;
};

class TwoHitShip : public BattleShip{
public:
    TwoHitShip() : BattleShip(2){}
    std::string getName() override;
};

class OneHitShip : public BattleShip{
public:
    OneHitShip() : BattleShip(1){}
    std::string getName() override;
};

#endif