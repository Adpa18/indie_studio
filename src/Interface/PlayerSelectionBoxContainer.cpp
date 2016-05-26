//
// Created by veyrie_f on 5/15/16.
//

#include <algorithm>
#include "PlayerSelectionBoxContainer.hpp"
#include "../include/Texture.hpp"
#include "../include/GameManager.hpp"

PlayerSelectionBoxContainer::PlayerSelectionBoxContainer(UIManager *uiManager) :
            m_manager(uiManager)
{
    // Set default available skins
    m_availableSkins.push_back("ziggs");
    m_availableSkins.push_back("ziggsSnow");
    m_availableSkins.push_back("ziggsGeneral");
    m_availableSkins.push_back("ziggsPool");
    m_availableSkins.push_back("ziggsMad");

    m_boxes.push_back(new PlayerSelectionBox(uiManager, this, BomberManTexture::getModel("playerButtonSelected").texture.c_str(),
                                             irr::core::rect<irr::s32>(IrrlichtController::width * 0.014, IrrlichtController::height * 0.445,
                                                                       IrrlichtController::width * 0.24, IrrlichtController::height * 0.85),
                                             UIElement::MAIN_MENU_BUTTON_1P, true, UIElement::PLAYERBOX_1, 1));
    m_boxes.push_back(new PlayerSelectionBox(uiManager, this, BomberManTexture::getModel("playerButton").texture.c_str(),
                                             irr::core::rect<irr::s32>(IrrlichtController::width * 0.262, IrrlichtController::height * 0.445,
                                                                       IrrlichtController::width * 0.49, IrrlichtController::height * 0.85),
                                             UIElement::MAIN_MENU_BUTTON_2P, true, UIElement::PLAYERBOX_2, 2));
    m_boxes.push_back(new PlayerSelectionBox(uiManager, this, BomberManTexture::getModel("playerButton").texture.c_str(),
                                             irr::core::rect<irr::s32>(IrrlichtController::width * 0.515, IrrlichtController::height * 0.445,
                                                                       IrrlichtController::width * 0.743, IrrlichtController::height * 0.85),
                                             UIElement::MAIN_MENU_BUTTON_3P, true, UIElement::PLAYERBOX_3, 3));
    m_boxes.push_back(new PlayerSelectionBox(uiManager, this, BomberManTexture::getModel("playerButton").texture.c_str(),
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
    m_boxes.front()->SelectPrev();
}

void PlayerSelectionBoxContainer::SelectDown()
{
    m_boxes.front()->SelectNext();
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

void PlayerSelectionBoxContainer::PlayerJoin(int playerID)
{
    if (!(*std::next(m_boxes.begin(), playerID - 1))->GetIaStatus() || m_joined[playerID - 1])
    {
        return;
    }
    (*std::next(m_boxes.begin(), playerID - 1))->SetIaStatus(false);
    (*std::next(m_boxes.begin(), playerID - 1))->SelectNext();
    m_joined[playerID - 1] = true;
}

// TODO: keyboard shortcuts + player join with controller
// TODO: redo gui assets
void PlayerSelectionBoxContainer::SaveSelection()
{
    for (std::list<PlayerSelectionBox*>::const_iterator it = m_boxes.begin(); it != m_boxes.end(); ++it)
    {
        GameManager::SharedInstance()->AddPlayerFromUI(new PlayerInfo(GameManager::ToString((*it)->GetPlayerName()),
                                                                (*it)->GetSkin(),
                                                                (*it)->GetIaStatus(),
                                                                (*it)->GetIAStrength()));
    }
}

void PlayerSelectionBoxContainer::SelectSkin(std::string const &skin)
{
    m_availableSkins.remove(skin);
}

void PlayerSelectionBoxContainer::UnselectSkin(std::string const &skin)
{
    if (std::find(m_availableSkins.begin(), m_availableSkins.end(), skin) == m_availableSkins.end())
    {
        m_availableSkins.push_back(skin);
    }
}

bool PlayerSelectionBoxContainer::IsSkinAvailable(std::string const& skin) const
{
    return std::find(m_availableSkins.begin(), m_availableSkins.end(), skin) != m_availableSkins.end();
}
