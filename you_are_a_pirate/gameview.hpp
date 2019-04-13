#ifndef YOU_ARE_A_PIRATE_GAMEVIEW_HPP
#define YOU_ARE_A_PIRATE_GAMEVIEW_HPP
#include "seafield.hpp"

class GameView{
public:
    //virtual void Draw_for_player_both(PlayerViewField* p_field, EnemyViewField* e_field) = 0;
    virtual void Draw_for_player(std::string&& indicator) = 0;
    virtual void display_message(const std::string &text) = 0;
};

class ConsoleView : public GameView{
public:
    ConsoleView(PlayerViewField* p1, PlayerViewField* p2, EnemyViewField* e1, EnemyViewField* e2) :
            player1_view(p1), player2_view(p2), player1_enemy_view(e1), player2_enemy_view(e2){}

    /*void Draw_for_player_both(PlayerViewField* p_field, EnemyViewField* e_field) override{
        p_field -> DrawField();
        e_field -> DrawField();
    }*/

    void Draw_for_player(std::string&& indicator) override;

    void display_message(const std::string &text) override;

private:
    PlayerViewField* player1_view;
    PlayerViewField* player2_view;
    EnemyViewField* player1_enemy_view;
    EnemyViewField* player2_enemy_view;

};



#endif
