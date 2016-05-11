//
// Created by veyrie_f on 5/11/16.
//

#include "PlayerSelectionBox.hpp"

PlayerSelectionBox::PlayerSelectionBox(UIManager *uiManager, irr::io::path const &sprite, irr::core::rect<irr::s32> pos,
                                       UIElement::Menu elemName, bool bIsIaPlayer) :
        m_manager(uiManager),
        m_bIsIaPlayer(bIsIaPlayer),
        m_pos(pos)
{
    irr::gui::IGUIButton *b = m_manager->GetEnv()->addButton(pos, nullptr, elemName, L"", L"");
    b->setImage(m_manager->GetEnv()->getVideoDriver()->getTexture(sprite));
    b->setScaleImage(true);
    b->setUseAlphaChannel(true);
    b->setDrawBorder(false);
    m_sceneManager = m_manager->GetDevice()->getSceneManager();
    m_camera = m_sceneManager->addCameraSceneNode();
}

PlayerSelectionBox::~PlayerSelectionBox()
{

}

void PlayerSelectionBox::SelectNext() const
{

}

void PlayerSelectionBox::SelectPrev() const
{

}

void PlayerSelectionBox::AddSprite(irr::io::path sprite)
{
    m_images.push_back(m_driver->getTexture(sprite));
}

void PlayerSelectionBox::Update() const
{
    m_driver->setViewPort(m_pos);
    m_sceneManager->setActiveCamera(m_camera);
    m_sceneManager->drawAll();
}
