//
// Created by consta_n on 25/05/16.
//

#ifndef CPP_INDIE_STUDIO_GAMEOVER_HPP
#define CPP_INDIE_STUDIO_GAMEOVER_HPP

#include <vector>
#include "ACharacter.hpp"
#include <stack>

class Ranking;

class GameOver
{
private:
    std::vector<ACharacter *> &m_characters;
    Ranking                   *m_ranking;
    bool                      m_status;
    irr::gui::IGUIEnvironment *m_env;
    irr::gui::IGUISkin        *m_skin;
    irr::gui::IGUIFont        *m_save_font;
    irr::gui::IGUIFont        *m_font;
    irr::gui::IGUIStaticText  *m_st_text;
    //    const std::vector<int>              &m_winners;
    //  std::stack<ACharacter *>            *tmp_ranking;

public:
    GameOver(Ranking *ranking, std::vector<ACharacter *> &characters);

    ~GameOver();

public:
    void show();

    bool getStatus() const;

private:
    int dispFinalWin(std::vector<ACharacter *> const &podium);
    int dispCurrWin(std::vector<ACharacter *> const &podium);
};


#endif //CPP_INDIE_STUDIO_GAMEOVER_HPP
