//
// Created by veyrie_f on 5/27/16.
//

#ifndef CPP_INDIE_STUDIO_KEYSELECTIONBOX_HPP
#define CPP_INDIE_STUDIO_KEYSELECTIONBOX_HPP

#include "ISelectionBox.hpp"
#include "UIManager.hpp"
#include "UIElements.hpp"
#include "AController.hpp"
#include "ACharacter.hpp"
#include "KeysController.hpp"

class KeySelectionBox : public ISelectionBox
{
public:
    explicit KeySelectionBox(UIManager *uiManager, irr::core::rect<irr::s32> pos, UIElement::Menu elemID, int playerID);
    explicit KeySelectionBox(UIManager *uiManager, irr::core::rect<irr::s32> pos, UIElement::Menu elemID, int playerID, irr::SJoystickInfo info);
    virtual ~KeySelectionBox();

public:
    void SelectNext();
    void SelectPrev();
    void Update();
    void OnSelect();
    void OnKeyPress(irr::EKEY_CODE key);
    bool IsSelecting() const;

public:
    void SetActive(bool bActive) const;
    bool IsActive() const;

private:
    void CreateListBox(irr::core::rect<irr::s32> pos, UIElement::Menu elemID);
    void UpdateElements();

private:
    UIManager *m_manager;
    int m_playerID;
    irr::gui::IGUIListBox *m_listBox;
    AController *m_controller;
    std::vector<KeysController::KeyInfo> m_keys;
    bool m_isSelecting = false;
};


#endif //CPP_INDIE_STUDIO_KEYSELECTIONBOX_HPP