//
// Created by gaspar_q on 6/1/16.
//

#include <algorithm>
#include <GameManager.hpp>
#include "Ranking.hpp"

Ranking::Ranking(size_t nbPlayers) :
        m_nbplayers(nbPlayers), m_gameover(NULL), m_state(DEFAULT), m_playedGames(0)
{

}

Ranking::Ranking(const Ranking &ranking)
{
    *this = ranking;
}

Ranking::~Ranking()
{
    clear();
}

Ranking &Ranking::operator=(const Ranking &ranking)
{
    m_rankedPlayers = ranking.m_rankedPlayers;
    m_nbplayers     = ranking.m_nbplayers;
    m_gameover      = ranking.m_gameover;
    m_state         = ranking.m_state;
    m_playedGames   = ranking.m_playedGames;
    return *this;
}

bool Ranking::isTheEndOfTheGame(ACharacter *winner, size_t nbDeads)
{
    if (nbDeads >= m_nbplayers - 1)
    {
        if (nbDeads == m_nbplayers)
        {
            clear();
            m_state = DRAW;
        }
        else if (winner)
        {
            addWinner(winner);
            m_state = WIN;
        }
        m_playedGames++;
        return (true);
    }
    return (false);
}

void Ranking::addWinner(ACharacter *winner)
{
    addPlayerToRank(winner);
    if (m_players.find(winner->get_player()) == m_players.end())
        m_players[winner->get_player()] += 1;
}

void Ranking::addPlayerToRank(ACharacter *character)
{
    if (m_players.find(character->get_player()) == m_players.end())
        m_players[character->get_player()] = 0;
    m_rankedPlayers.push(character);
}

void Ranking::setNbPlayers(size_t nbPlayers)
{
    m_nbplayers = nbPlayers;
}

size_t Ranking::getNbPlayers(void) const
{
    return m_nbplayers;
}

std::stack<ACharacter *> const &Ranking::getRanks(void) const
{
    return m_rankedPlayers;
}

void Ranking::clear(void)
{
    while (!m_rankedPlayers.empty())
    {
        m_rankedPlayers.pop();
    }
    m_nbplayers = 0;
    destroyGameOver();
}

void Ranking::displayRankingScreen(std::vector<ACharacter *> &chara)
{
    if (!m_gameover)
        m_gameover = new GameOver(this, chara);
    m_gameover->show();
}

GameOver *Ranking::getGameOver(void) const
{
    return m_gameover;
}

void Ranking::destroyGameOver(void)
{
    if (m_gameover)
    {
        delete (m_gameover);
        m_gameover = NULL;
    }
}

Ranking::State Ranking::getState(void) const
{
    return m_state;
}

void Ranking::setState(Ranking::State state)
{
    m_state = state;
}

size_t Ranking::getPlayedGames(void) const
{
    return m_playedGames;
}

void Ranking::setPlayedGames(size_t nbGames)
{
    m_playedGames = nbGames;
}

ACharacter *Ranking::getMaxScoredPlayer(std::vector<ACharacter *> const &chars) const
{
    ACharacter                            *maxScored    = NULL;
    ACharacter                            *secondScored = NULL;
    std::map<int, size_t>::const_iterator player;
    size_t                                score         = 0;

    for (std::vector<ACharacter *>::const_iterator it = chars.begin(), end = chars.end(); it != end; ++it)
    {
        player = m_players.find((*it)->get_player());
        if (maxScored == NULL || (player != m_players.end() && score <= player->second))
        {
            if (maxScored != NULL && score == player->second)
                secondScored = *it;
            else
                secondScored = NULL;
            maxScored        = *it;
            score            = player->second;
        }
    }
    if (secondScored != NULL)
        return (NULL);
    return maxScored;
}

std::vector<ACharacter *> Ranking::getPodium()
{
    std::vector<ACharacter *>   podium;

    for (int i = 0; i < 3; ++i)
    {
        podium.push_back(m_rankedPlayers.top());
        m_rankedPlayers.pop();
    }
    return podium;
}

ACharacter *Ranking::getPlayerFromId(int id, std::vector<ACharacter *> const &chars) const
{
    for (std::vector<ACharacter *>::const_iterator it = chars.begin(), end = chars.end(); it != end; ++it)
    {
        if ((*it)->get_player() == id)
            return *it;
    }
    return nullptr;
}

void Ranking::reset(void)
{
    clear();
    m_players.clear();
}

std::vector<ACharacter *> Ranking::getFinalPodium(std::vector<ACharacter *> const &chars) const
{
    std::vector<std::pair<int, size_t >> rank;
    std::vector<ACharacter *>   podium;

    for (std::map<int, size_t>::const_iterator it = m_players.begin(), end = m_players.end(); it != end; ++it)
    {
        rank.push_back(std::make_pair(it->first, it->second));
    }
    std::sort(rank.begin(), rank.end(),
              [](std::pair<int, int> p1, std::pair<int, int> p2)
                  {
                      return p1.second > p2.second;
                  });
    podium.push_back(getPlayerFromId(rank[0].first, chars));
    podium.push_back(getPlayerFromId(rank[1].first, chars));
    podium.push_back(getPlayerFromId(rank[2].first, chars));
    return podium;
}
