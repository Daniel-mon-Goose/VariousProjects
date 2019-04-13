#ifndef YOU_ARE_A_PIRATE_SEAFIELD_HPP
#define YOU_ARE_A_PIRATE_SEAFIELD_HPP
#include <vector>
#include <stdexcept>
#include <memory>
#include "battleships.hpp"
#include <iostream>
#include "observer_pattern.hpp"

class GameView;

enum class cell_indicator{
    free, filled, splashed, hit
};

struct cell{
    cell(){
        lamp = cell_indicator::free;
        ship_indicator = nullptr;
    }
    cell_indicator lamp;
    std::shared_ptr<BattleShip> ship_indicator;
};

class PlayerViewField;
class EnemyViewField;

class Field : public Subject{
    friend PlayerViewField;
    friend EnemyViewField;
public:
    explicit Field(size_t size);
    size_t fieldSize();

    bool game_modify(int x, int y, GameView& ui);

    void emplace_ship(std::shared_ptr<BattleShip>& ship, int x, int y, int isHorizontal);
private:
    std::vector<std::vector<cell>> data;

    bool isAllowedEmplacement(int x, int y);
};

class ViewField : public Observer{
private:
    void DrawLine(char c);

    void DrawComplexLine(size_t pos);

    void DrawLetters();
protected:
    std::vector<std::vector<cell>> data;
public:
    explicit ViewField(size_t size) : data(std::vector(size, std::vector<cell>(size))){}
    void DrawField();
};


class PlayerViewField : public ViewField{
public:
    explicit PlayerViewField(Field* f);
    void Update(Subject* theChangedSubject) override;
    size_t fieldSize(){
        return data.size();
    }
private:
    Field* subj;
};

class EnemyViewField : public ViewField{
public:
    explicit EnemyViewField(Field* f);
    void Update(Subject* theChangedSubject) override;
    size_t fieldSize(){
        return data.size();
    }
private:
    Field* subj;
    //std::vector<std::vector<cell>> data;
};

#endif
