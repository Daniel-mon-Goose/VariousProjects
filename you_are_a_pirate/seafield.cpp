#include "seafield.hpp"

Field::Field(size_t size) : data(std::vector<std::vector<cell>>(size, std::vector<cell>( size, cell() ))){
    if (!(size >= 10 && size <= 16)){
        throw std::runtime_error("choose another size of ur field, niBBa");
    }
}

size_t Field::fieldSize(){
    return data.size();
}

void Field::emplace_ship(std::shared_ptr<BattleShip> &ship, int x, int y, int isHorizontal){
    if (isHorizontal != 0 && isHorizontal != 1){
        throw std::range_error("unexpected position behavior");
    }

    if (isHorizontal == 0 && y < data.size() && x <= data.size() - ship -> showHitPoints()){
        for (int i = x; i < x + ship -> showHitPoints(); ++i){
            if (!isAllowedEmplacement(i, y)){
                throw std::runtime_error("Move ur ship further from ur fleet, admiral-nigga");
            }
        }

        for (int i = x; i < x + ship -> showHitPoints(); ++i){
            data[i][y].ship_indicator = ship;
            data[i][y].lamp = cell_indicator::filled;
            this -> Notify();
        }
    }
    else if (isHorizontal == 1 && x < data.size() && y <= data.size() - ship -> showHitPoints()){
        for (int j = y; j < y + ship -> showHitPoints(); ++j){
            if (!isAllowedEmplacement(x, j)){
                throw std::runtime_error("Move ur ship further from ur fleet, admiral-nigga");
            }
        }

        for (int j = y; j < y + ship -> showHitPoints(); ++j){
            data[x][j].ship_indicator = ship;
            data[x][j].lamp = cell_indicator::filled;
            this -> Notify();
        }
    }
    else{
        throw std::runtime_error("Nah-ah-ah, dat's restricted, man");
    }
}

bool Field::isAllowedEmplacement(int x, int y){
    int lower = ((y + 1) == data.size()) ? y : y + 1,
            upper = ((y - 1) < 0) ? 0 : y - 1,
            left = ((x - 1) < 0) ? 0 : x - 1,
            right = ((x + 1) == data.size()) ? x : x + 1;
    for (int i = left; i <= right; ++i){
        for (int j = upper; j <= lower; ++j){
            if (data[i][j].ship_indicator != nullptr){
                return false;
            }
        }
    }

    return true;
}

void ViewField::DrawLine(char c){
    std::cout << "   ";
    for (size_t i = 0; i < 2 * data.size() + 1; ++i){
        std::cout << c;
    }
}

void ViewField::DrawComplexLine(size_t pos){
    if (pos < 10){
        std::cout << ' ' << pos << ' ';
    }
    else {
        std::cout << pos << ' ';
    }
    for (size_t i = 0; i < 2 * 10 + 1; ++i){
        if (i % 2 == 0){
            std::cout << '|';
        }
        else{
            switch (data[pos - 1][i / 2].lamp){
                case cell_indicator::free: { std::cout << ' '; break; }
                case cell_indicator::splashed: {std::cout << 'o'; break;}
                case cell_indicator::hit: { std::cout << 'x'; break; }
                case cell_indicator::filled: { std::cout << '*'; break; }
                default: {
                    throw std::logic_error("WTF");
                }
            }
        }
    }
}

void ViewField::DrawLetters(){
    std::cout << "   ";
    for (int i = 0; i < 2 * data.size() + 1; ++i){
        if (i % 2 != 0){
            std::cout << char('A' + i / 2);
        }
        else {
            std::cout << " ";
        }
    }
}

void ViewField::DrawField(){
    DrawLetters();
    std::cout << std::endl;
    for (size_t i = 0; i < data.size(); ++i){
        DrawLine('-');
        std::cout << std::endl;
        DrawComplexLine(i + 1);
        std::cout << std::endl;
    }
    DrawLine('-');
    std::cout << std::endl;
}

PlayerViewField::PlayerViewField(Field *f) : ViewField(f -> data.size()){
    subj = f;
    subj -> Attach(this);
}

void PlayerViewField::Update(Subject *theChangedSubject){
    if (theChangedSubject == subj){
        this -> data = subj -> data;
    }
}

EnemyViewField::EnemyViewField(Field *f) : ViewField(f -> data.size()){
    subj = f;
    subj -> Attach(this);
}

void EnemyViewField::Update(Subject *theChangedSubject){
    if (theChangedSubject == subj){
        this -> data = subj -> data;
        for (auto& line : this -> data){
            for (auto& seacell : line){
                if (seacell.lamp == cell_indicator::filled){
                    seacell.lamp = cell_indicator::free;
                }
            }
        }
    }
}