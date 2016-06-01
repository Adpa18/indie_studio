//
// Created by gaspar_q on 6/1/16.
//

#ifndef CPP_INDIE_STUDIO_RANKING_HPP
#define CPP_INDIE_STUDIO_RANKING_HPP

#include <vector>
#include <stack>
#include "ACharacter.hpp"
#include "GameOver.hpp"

class Ranking
{
public:
    enum State
    {
        DEFAULT,
        DRAW,
        WIN
    };

public:
    Ranking(size_t nbPlayers = 0);
    Ranking(Ranking const &);
    ~Ranking();
    Ranking &operator=(Ranking const &ref);

public:
    bool isTheEndOfTheGame(ACharacter *winner, size_t nbDeads);
    void displayRankingScreen(std::vector<ACharacter *> &chara);
    ACharacter *getMaxScoredPlayer(std::vector<ACharacter *> const &chars) const;
    std::vector<ACharacter *>   getPodium(std::vector<ACharacter *> const &chars) const;

public:
    void addWinner(ACharacter *winner);
    void addWinner(int playerId);
    void addPlayerToRank(ACharacter *toRank);
    void setNbPlayers(size_t nbPlayers);
    size_t getNbPlayers(void) const;
    GameOver *getGameOver(void) const;
    State getState(void) const;
    void setState(State state);
    void destroyGameOver(void);
    size_t getPlayedGames(void) const;
    void setPlayedGames(size_t nbGames);
    ACharacter *getPlayerFromId(int id, std::vector<ACharacter *> const &chars) const;
    std::vector<int> const &getWinners(void) const;
    std::stack<ACharacter *> const &getRanks(void) const;
    void clear(void);

private:
    std::map<int, size_t>       m_players;
    std::vector<int>            m_winners;
    std::stack<ACharacter *>    m_rankedPlayers;
    size_t                      m_nbplayers;
    GameOver                    *m_gameover;
    State                       m_state;
    size_t                      m_playedGames;
};

#endif //CPP_INDIE_STUDIO_RANKING_HPP
