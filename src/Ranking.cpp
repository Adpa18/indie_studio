//
// Created by gaspar_q on 6/1/16.
//

#include <GameManager.hpp>
#include "Ranking.hpp"

Ranking::Ranking(size_t nbPlayers) :
    m_winners(),
    m_rankedPlayers(),
    m_nbplayers(nbPlayers),
    m_gameover(NULL)
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
    m_winners = ranking.m_winners;
    m_rankedPlayers = ranking.m_rankedPlayers;
    m_nbplayers = ranking.m_nbplayers;
    m_gameover = ranking.m_gameover;
    return *this;
}

bool Ranking::isTheEndOfTheGame(ACharacter *winner, size_t nbDeads)
{
    if (nbDeads >= m_nbplayers - 1)
    {
        if (winner)
        {
            addWinner(winner);
        }
        else
        {
            clear();
            m_winners.push_back(-1);
        }
        return (true);
    }
    return (false);
}

void Ranking::addWinner(ACharacter *winner)
{
    addWinner(winner->getType());
}

void Ranking::addWinner(int playerId)
{
    m_winners.push_back(playerId);
}

void Ranking::addPlayerToRank(ACharacter *character)
{
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

std::vector<int> const &Ranking::getWinners(void) const
{
    return m_winners;
}

std::stack<ACharacter *> const &Ranking::getRanks(void) const
{
    return m_rankedPlayers;
}

void Ranking::clear(void)
{
    m_winners.clear();
    while (!m_rankedPlayers.empty())
    {
        m_rankedPlayers.pop();
    }
    m_nbplayers = 0;
    if (m_gameover)
    {
        delete(m_gameover);
        m_gameover = NULL;
    }
}

void Ranking::displayRankingScreen(std::vector<ACharacter *> &chara)
{
    if (!m_gameover)
        m_gameover = new GameOver(m_winners, chara, &m_rankedPlayers);
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
        delete(m_gameover);
        m_gameover = NULL;
    }
}
