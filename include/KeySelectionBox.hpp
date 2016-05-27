//
// Created by veyrie_f on 5/27/16.
//

#ifndef CPP_INDIE_STUDIO_KEYSELECTIONBOX_HPP
#define CPP_INDIE_STUDIO_KEYSELECTIONBOX_HPP


#include "ISelectionBox.hpp"
#include "UIManager.hpp"
#include "UIElements.hpp"
#include "AController.hpp"

class KeySelectionBox : public ISelectionBox
{
public:
    enum ControllerType
    { KEYBOARD, CONTROLLER };

public:
    explicit KeySelectionBox(UIManager *uiManager, irr::core::rect<irr::s32> pos, UIElement::Menu elemID, int playerID);
    explicit KeySelectionBox(UIManager *uiManager, irr::core::rect<irr::s32> pos, UIElement::Menu elemID, int playerID, irr::SJoystickInfo info);
    virtual ~KeySelectionBox();

public:
    void SelectNext();
    void SelectPrev();
    void Update();

public:
    void SetActive(bool bActive) const;

private:
    void CreateListBox(irr::core::rect<irr::s32> pos, UIElement::Menu elemID);

private:
    UIManager *m_manager;
    int m_playerID;
    irr::gui::IGUIListBox *m_listBox;
    AController *m_controller;
};


#endif //CPP_INDIE_STUDIO_KEYSELECTIONBOX_HPP
