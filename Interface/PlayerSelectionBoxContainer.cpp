//
// Created by veyrie_f on 5/15/16.
//

#include "PlayerSelectionBoxContainer.hpp"
#include "../include/Texture.hpp"
#include "../include/GameManager.hpp"

// TODO: one character selected means its unavailable for others
PlayerSelectionBoxContainer::PlayerSelectionBoxContainer(UIManager *uiManager) :
            m_manager(uiManager)
{
    m_boxes.push_back(new PlayerSelectionBox(uiManager, BomberManTexture::getModel("playerButtonSelected").texture.c_str(),
                                             irr::core::rect<irr::s32>(IrrlichtController::width * 0.014, IrrlichtController::height * 0.445,
                                                                       IrrlichtController::width * 0.24, IrrlichtController::height * 0.85),
                                             UIElement::MAIN_MENU_BUTTON_1P, false, UIElement::PLAYERBOX_1, 1));
    m_boxes.push_back(new PlayerSelectionBox(uiManager, BomberManTexture::getModel("playerButton").texture.c_str(),
                                             irr::core::rect<irr::s32>(IrrlichtController::width * 0.262, IrrlichtController::height * 0.445,
                                                                       IrrlichtController::width * 0.49, IrrlichtController::height * 0.85),
                                             UIElement::MAIN_MENU_BUTTON_2P, true, UIElement::PLAYERBOX_2, 2));
    m_boxes.push_back(new PlayerSelectionBox(uiManager, BomberManTexture::getModel("playerButton").texture.c_str(),
                                             irr::core::rect<irr::s32>(IrrlichtController::width * 0.515, IrrlichtController::height * 0.445,
                                                                       IrrlichtController::width * 0.743, IrrlichtController::height * 0.85),
                                             UIElement::MAIN_MENU_BUTTON_3P, true, UIElement::PLAYERBOX_3, 3));
    m_boxes.push_back(new PlayerSelectionBox(uiManager, BomberManTexture::getModel("playerButton").texture.c_str(),
                                             irr::core::rect<irr::s32>(IrrlichtController::width * 0.762, IrrlichtController::height * 0.445,
                                                                       IrrlichtController::width * 0.99, IrrlichtController::height * 0.85),
                                             UIElement::MAIN_MENU_BUTTON_4P, true, UIElement::PLAYERBOX_4, 4));

    uiManager->GetEnv()->setFocus(const_cast<irr::gui::IGUIButton*>(&m_boxes.front()->GetButton()));
}

PlayerSelectionBoxContainer::~PlayerSelectionBoxContainer()
{
    SaveSelection();
    for (std::list<PlayerSelectionBox*>::iterator it = m_boxes.begin(); it != m_boxes.end(); ++it)
    {
        delete (*it);
    }
}

void PlayerSelectionBoxContainer::SelectUp()
{
    /*for (std::list<PlayerSelectionBox*>::iterator it = m_boxes.begin(); it != m_boxes.end(); ++it)
    {
        (*it)->SelectNext();
    }*/
    m_boxes.front()->SelectNext();
}

void PlayerSelectionBoxContainer::SelectDown()
{
    /*for (std::list<PlayerSelectionBox*>::iterator it = m_boxes.begin(); it != m_boxes.end(); ++it)
    {
        (*it)->SelectPrev();
    }*/
    m_boxes.front()->SelectPrev();
}

void PlayerSelectionBoxContainer::SelectLeft()
{
    PlayerSelectionBox *box = m_boxes.back();
    m_boxes.pop_back();
    m_boxes.push_front(box);
    m_manager->GetEnv()->setFocus(const_cast<irr::gui::IGUIButton*>(&m_boxes.front()->GetButton()));
}

void PlayerSelectionBoxContainer::SelectRight()
{
    PlayerSelectionBox *box = m_boxes.front();
    m_boxes.pop_front();
    m_boxes.push_back(box);
    m_manager->GetEnv()->setFocus(const_cast<irr::gui::IGUIButton*>(&m_boxes.front()->GetButton()));
}

void PlayerSelectionBoxContainer::UpdateBoxes(irr::s32 id)
{
    for (std::list<PlayerSelectionBox*>::const_iterator it = m_boxes.begin(); it != m_boxes.end(); ++it)
    {
        (*it)->SetFocus((*it)->GetId() == id);
    }
}

void PlayerSelectionBoxContainer::PlayerJoin()
{
    for (std::list<PlayerSelectionBox*>::const_iterator it = m_boxes.begin(); it != m_boxes.end(); ++it)
    {
        if ((*it)->GetIaStatus())
        {
            (*it)->SetIaStatus(false);
            break;
        }
    }
}

// TODO: handle ia strength
void PlayerSelectionBoxContainer::SaveSelection()
{
    for (std::list<PlayerSelectionBox*>::const_iterator it = m_boxes.begin(); it != m_boxes.end(); ++it)
    {
        GameManager::SharedInstance()->AddPlayer(new PlayerInfo(std::string((*it)->GetPlayerName().begin(), (*it)->GetPlayerName().end()),
                                                                (*it)->GetSkin(),
                                                                (*it)->GetIaStatus(),
                                                                PlayerInfo::EASY));
    }
}
