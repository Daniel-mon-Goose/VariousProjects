#ifndef YOU_ARE_A_PIRATE_GAMEPROCESS_HPP
#define YOU_ARE_A_PIRATE_GAMEPROCESS_HPP
#include "players.hpp"

class Game{
public:
    explicit Game(Gamer* pl1, Gamer* pl2) : Player1(pl1), Player2(pl2){}
    std::string process(GameView& ui);
private:
    Gamer* Player1;
    Gamer* Player2;
};

#endif
