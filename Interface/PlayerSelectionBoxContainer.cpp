//
// Created by veyrie_f on 5/15/16.
//

#include "PlayerSelectionBoxContainer.hpp"
#include "../include/Texture.hpp"

PlayerSelectionBoxContainer::PlayerSelectionBoxContainer(UIManager *uiManager)
{
    m_boxes.push_back(new PlayerSelectionBox(uiManager, BomberManTexture::getModel("playerButton").texture.c_str(),
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
}

PlayerSelectionBoxContainer::~PlayerSelectionBoxContainer()
{
    for (std::list<PlayerSelectionBox*>::iterator it = m_boxes.begin(); it != m_boxes.end(); ++it)
    {
        delete (*it);
    }
}

void PlayerSelectionBoxContainer::SelectUp()
{
    for (std::list<PlayerSelectionBox*>::iterator it = m_boxes.begin(); it != m_boxes.end(); ++it)
    {
        (*it)->SelectNext();
    }
}

void PlayerSelectionBoxContainer::SelectDown()
{
    for (std::list<PlayerSelectionBox*>::iterator it = m_boxes.begin(); it != m_boxes.end(); ++it)
    {
        (*it)->SelectPrev();
    }
}
