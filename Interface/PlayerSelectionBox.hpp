//
// Created by veyrie_f on 5/11/16.
//

#ifndef CPP_INDIE_STUDIO_PLAYERSELECTIONBOX_HPP
#define CPP_INDIE_STUDIO_PLAYERSELECTIONBOX_HPP


#include "UIManager.hpp"
#include "UIElements.hpp"
#include "ISelectionBox.hpp"

#include <list>

/*
 * \brief Represents a box to select the player character.
 * If it is an ia, the ia level is displayed. Otherwise, the character is displayed
 */
class PlayerSelectionBox : public ISelectionBox
{
public:
    PlayerSelectionBox(UIManager *uiManager, irr::io::path const& sprite, irr::core::rect<irr::s32> pos, UIElement::Menu elemName, bool bIsIaPlayer);
    virtual ~PlayerSelectionBox();

public:
    void Update() const;
    void SelectNext() const;
    void SelectPrev() const;
    void AddSprite(irr::io::path sprite);

private:
    UIManager *m_manager;
    irr::video::IVideoDriver *m_driver;
    std::list<irr::video::ITexture*> m_images;
    bool m_bIsIaPlayer;
    irr::core::rect<irr::s32> m_pos;
    irr::scene::ICameraSceneNode *m_camera;
    irr::scene::ISceneManager *m_sceneManager;
};


#endif //CPP_INDIE_STUDIO_PLAYERSELECTIONBOX_HPP
