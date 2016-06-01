//
// Created by gaspar_q on 6/1/16.
//

#ifndef CPP_INDIE_STUDIO_RANKING_HPP
#define CPP_INDIE_STUDIO_RANKING_HPP

#include <vector>
#include <stack>
#include "ACharacter.hpp"

class Ranking
{
public:
    Ranking(size_t nbPlayers = 0);
    Ranking(Ranking const &);
    ~Ranking();
    Ranking &operator=(Ranking const &ref);

public:
    bool isTheEndOfTheGame(ACharacter *winner, size_t nbDeads);
    void displayRankingScreen(irr::scene::ICameraSceneNode *cam, std::vector<ACharacter *> &chara);

public:
    void addWinner(ACharacter *winner);
    void addWinner(int playerId);
    void addPlayerToRank(ACharacter *toRank);
    void setNbPlayers(size_t nbPlayers);
    size_t getNbPlayers(void) const;
    GameOver *getGameOver(void) const;
    void destroyGameOver(void);
    std::vector<int> const &getWinners(void) const;
    std::stack<ACharacter *> const &getRanks(void) const;
    void clear(void);

private:
    std::vector<int>            m_winners;
    std::stack<ACharacter *>    m_rankedPlayers;
    size_t                      m_nbplayers;
    GameOver                    *m_gameover;
};

#endif //CPP_INDIE_STUDIO_RANKING_HPP
