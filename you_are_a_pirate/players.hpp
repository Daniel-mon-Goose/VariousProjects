#ifndef YOU_ARE_A_PIRATE_PLAYERS_HPP
#define YOU_ARE_A_PIRATE_PLAYERS_HPP
#include "battleships.hpp"
#include "shipcreators.hpp"
#include "seafield.hpp"
#include <list>
#include <memory>
#include <random>
#include <iostream>
#include <typeinfo>
#include "gameview.hpp"

class Gamer{
public:
    explicit Gamer(Field* mine, Field* urs, int num) : OwnField(mine), EnemyField(urs), number(num){}
    virtual void emplacement_strategy(GameView& ui) = 0;
    virtual bool playing_strategy(GameView& ui) = 0;
    virtual long long showShipsLeft();
    virtual ~Gamer() = default;
protected:
    std::vector<std::shared_ptr<BattleShip>> fleet;
    Field* OwnField;
    Field* EnemyField;
    int number;
};

class ConsoleGamer : public Gamer{
public:
    ConsoleGamer(Field* mine, Field* urs, int num) : Gamer(mine, urs, num){}
    void emplacement_strategy(GameView& ui) override;

    bool playing_strategy(GameView& ui) override;
};

class RandomGamer : public Gamer{
public:
    RandomGamer(Field* mine, Field* urs, int num);
    void emplacement_strategy(GameView& ui) override;

    bool playing_strategy(GameView& ui) override;
private:
    std::mt19937_64 gen;
};

class OptimalGamer : public Gamer{

};

#endif