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
#include "GameOver.hpp"

GameOver::GameOver(irr::scene::ICameraSceneNode *cam, const std::vector<int>   &win, const std::vector<ACharacter *> &chara, std::stack<ACharacter *> *ranking)
 : m_winners(win), characters(chara)
{
  camera = cam;
  tmp_ranking = ranking;
  env = IrrlichtController::getDevice()->getGUIEnvironment();
  skin = env->getSkin();
  font = env->getFont("./media/font/arcade_font.xml");
  if (font)
    skin->setFont(font);
  st_text = NULL;
}

void GameOver::show() {
  int i = 0;
  std::vector<std::pair<int, int>> ranking;
  int size = (int) m_winners.size();

  ranking.push_back(std::make_pair(-1, -1));
    for (std::vector<ACharacter *>::const_iterator it = characters.begin(); it !=  characters.end(); ++it)
    {
      int count = 0;
      i = 0;
      while (i < size)
      {
        if (m_winners[i] != -1)
        {
          if ((*it)->get_player() == m_winners[i])
            ++count;
        }
        ++i;
      }
      if (count)
        ranking.push_back(std::make_pair((*it)->get_player(), count));
    }
    //IrrlichtController::getDevice()->getSceneManager()->drawAll();
    IrrlichtController::getSceneManager()->setActiveCamera(camera);
    camera->setPosition(irr::core::vector3df(-50, 25, 0));
    camera->setTarget(irr::core::vector3df(0, 25, 0));
    std::sort(ranking.begin(), ranking.end(),  [] (std::pair<int, int> p1, std::pair<int, int> p2) { return p1.second > p2.second; } );
    int winner = -1;
    if (ranking[0].first != -1)
    {
      if (ranking[0].second > 2)
      {
        for (std::vector<ACharacter *>::const_iterator it = characters.begin(); it !=  characters.end(); ++it) {
          (*it)->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));
          (*it)->setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
          if ((*it)->get_player() == ranking[0].first)
          {
            winner = ranking[0].first;
            (*it)->getSceneNode()->setPosition(irr::core::vector3df(0, 0, 0));
          }
          else if ((*it)->get_player() == ranking[1].first)
            (*it)->getSceneNode()->setPosition(irr::core::vector3df(50, 0, 50));
          else if ((*it)->get_player() == ranking[2].first)
            (*it)->getSceneNode()->setPosition(irr::core::vector3df(50, 0, -50));
        }
        std::wstringstream ss;
        ss << "The winner is player " <<  winner << "!";
        st_text = env->addStaticText(
            ss.str().c_str(),
            irr::core::rect<irr::s32>(0, 100,
                                      (irr::s32) IrrlichtController::width, 200),
            false,
            true);
      }
      else
      {
        if (!tmp_ranking->empty())
        {

          winner = tmp_ranking->top()->get_player();
          tmp_ranking->top()->getSceneNode()->setPosition(irr::core::vector3df(0, 0, 0));
          tmp_ranking->top()->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));
          tmp_ranking->top()->setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
          tmp_ranking->pop();
        }
        if (!tmp_ranking->empty())
        {
          tmp_ranking->top()->getSceneNode()->setPosition(irr::core::vector3df(50, 0, 50));
          tmp_ranking->top()->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));
          tmp_ranking->top()->setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
          tmp_ranking->pop();
        }
        if (!tmp_ranking->empty())
        {
          tmp_ranking->top()->getSceneNode()->setPosition(irr::core::vector3df(50, 0, -50));
          tmp_ranking->top()->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));
          tmp_ranking->top()->setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
          tmp_ranking->pop();
        }
        while (!tmp_ranking->empty())
          tmp_ranking->pop();
        std::wstringstream ss;
        ss << "Player " <<  winner << " win!";
        st_text = env->addStaticText(
            ss.str().c_str(),
            irr::core::rect<irr::s32>(0, 100,
                                      (irr::s32) IrrlichtController::width, 200),
            false,
            true);
      }
    }
    else
      st_text = env->addStaticText(
          L"Draw !",
          irr::core::rect<irr::s32>(0, 100,
                                    (irr::s32) IrrlichtController::width, 200),
          false,
          true);
    st_text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    st_text->setTextAlignment(irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER,
                            irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER);
    env->drawAll();
}