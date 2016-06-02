//
// Created by consta_n on 25/05/16.
//

#include <utility>
#include <vector>
#include <ACharacter.hpp>
#include <algorithm>
#include <sstream>
#include <stack>
#include <list>
#include <iostream>
#include <BomberMap.hpp>
#include <GameManager.hpp>
#include "../../include/GameOver.hpp"

GameOver::GameOver(Ranking *ranking, std::vector<ACharacter *> &characters) :
        m_characters(characters),
        m_ranking(ranking),
        m_status(false),
        m_env(IrrlichtController::getDevice()->getGUIEnvironment()),
        m_skin(m_env->getSkin()),
        m_save_font(m_skin->getFont()),
        m_font(m_env->getFont("./media/font/arcade_font.xml")),
        m_st_text(NULL)
{
    if (m_font)
        m_skin->setFont(m_font);
}

GameOver::~GameOver()
{
    if (m_skin)
        m_skin->setFont(m_save_font);
}

void GameOver::show()
{
    irr::scene::ICameraSceneNode    *camera;
    std::wstringstream ss;

    camera = GameManager::SharedInstance()->getCam(GameManager::GameCamera::MAIN_MENU_CAM);
    camera->setPosition(irr::core::vector3df(-50, 25, 0));
    camera->setTarget(irr::core::vector3df(0, 25, 0));
    GameManager::SharedInstance()->activeCam(GameManager::GameCamera::MAIN_MENU_CAM);
    if (m_ranking->getState() == Ranking::WIN)
    {

        if (m_ranking->getPlayedGames() > 2 && m_ranking->getMaxScoredPlayer(m_characters) != NULL)
        {
            ss << "The winner is player " << dispFinalWin(m_ranking->getFinalPodium(m_characters)) << "!";
        }
        else
        {
            ss << "Player " << dispCurrWin(m_ranking->getPodium()) << " win!";
        }
    }
    else
    {
        ss << "Draw !";
    }

    m_st_text = m_env->addStaticText(ss.str().c_str(),
                                     irr::core::rect<irr::s32>(0, 100, (irr::s32) IrrlichtController::width, 200),
                                     false, true);
    m_st_text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    m_st_text->setTextAlignment(irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER, irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER);
    m_env->drawAll();
}

bool GameOver::getStatus() const
{
    return m_status;
}

int GameOver::dispFinalWin(std::vector<ACharacter *> const &podium)
{
    int winner = 0;

    m_status = true;
    for (std::vector<ACharacter *>::const_iterator it = m_characters.begin(); it != m_characters.end(); ++it)
    {
        (*it)->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));
        if (*it == podium[0])
        {
            winner = podium[0]->get_player();
            (*it)->getSceneNode()->setPosition(irr::core::vector3df(0, 0, 0));
        }
        else if (*it == podium[1])
        {
            (*it)->getSceneNode()->setPosition(irr::core::vector3df(50, 0, 50));
        }
        else if (*it == podium[2])
        {
            (*it)->getSceneNode()->setPosition(irr::core::vector3df(50, 0, -50));
        }
    }
    return winner;
}

int GameOver::dispCurrWin(std::vector<ACharacter *> const &podium)
{
    int winner;

    winner = podium[0]->get_player();
    podium[0]->getSceneNode()->setPosition(irr::core::vector3df(0, 0, 0));
    podium[0]->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));

    podium[1]->getSceneNode()->setPosition(irr::core::vector3df(50, 0, 50));
    podium[1]->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));

    podium[2]->getSceneNode()->setPosition(irr::core::vector3df(50, 0, -50));
    podium[2]->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));
    return winner;
}
