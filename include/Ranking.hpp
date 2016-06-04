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
        WIN,
        END_GAME
    };

public:
    Ranking(size_t nbPlayers = 0);
    Ranking(Ranking const &);
    ~Ranking();
    Ranking &operator=(Ranking const &ref);

public:
//    bool isTheEndOfTheGame(ACharacter *winner);
//    void displayRankingScreen(std::vector<ACharacter *> &chara);
//    ACharacter *getMaxScoredPlayer(std::vector<ACharacter *> const &chars) const;
//    std::vector<ACharacter *>   getPodium();
//    //todo finish
//    std::vector<ACharacter *>   getFinalPodium(std::vector<ACharacter *> const &chars) const;

//public:
//    void addPlayerToRank(ACharacter *toRank);
//    void setNbPlayers(size_t nbPlayers);
//    size_t getNbPlayers(void) const;
//    GameOver *getGameOver(void) const;
//    State getState(void) const;
//    void setState(State state);
//    void destroyGameOver(void);
//    size_t getPlayedGames(void) const;
//    void setPlayedGames(size_t nbGames);
//    ACharacter *getPlayerFromId(int id, std::vector<ACharacter *> const &chars) const;
//    std::stack<ACharacter *> const &getRanks(void) const;


private:
    size_t                      nbAlives;
    size_t                      nbPlayedGames;
    GameOver                    *m_gameover;
    State                       m_state;
    bool                        endGame;

    std::map<int, size_t>       playersScores;
    std::vector<ACharacter *>   players;
    std::vector<ACharacter *>   podium;

public:
    static const int		winScore[4];

public:
    bool                        isTheEndOfTheGame(ACharacter *winner);
    std::vector<ACharacter *>   getPodium();
    std::vector<ACharacter *>   getFinalPodium();
    void                        addPlayerToRank(ACharacter *toRank);
    void                        setPlayers(std::vector<ACharacter *> &characters);
    void                        displayRankingScreen();
    void                        clear(void);
    void                        reset(void);
    GameOver                    *getGameOver(void) const;
    void                        destroyGameOver(void);
    State                       getState(void) const;
    size_t                      getPlayerScore(int id) const;
    ACharacter                  *getPlayerByID(int id) const;
};

#endif //CPP_INDIE_STUDIO_RANKING_HPP
