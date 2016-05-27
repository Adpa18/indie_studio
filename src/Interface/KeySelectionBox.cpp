//
// Created by veyrie_f on 5/27/16.
//

#include "../../include/KeySelectionBox.hpp"
#include "../../include/EventGame.hpp"
#include "../../include/GameManager.hpp"

KeySelectionBox::KeySelectionBox(UIManager *uiManager, irr::core::rect<irr::s32> pos, UIElement::Menu elemID,
                                 int playerID) :
        m_manager(uiManager),
        m_playerID(playerID)
{
    m_controller = new KeysController(*std::next(EventGame::_keycodes.begin(), (playerID - 1) % 2));
    CreateListBox(pos, elemID);
}

KeySelectionBox::KeySelectionBox(UIManager *uiManager, irr::core::rect<irr::s32> pos, UIElement::Menu elemID,
                                 int playerID, irr::SJoystickInfo info) :
        m_manager(uiManager),
        m_playerID(playerID)
{
    m_controller = new MotionController(info);
    CreateListBox(pos, elemID);
}


KeySelectionBox::~KeySelectionBox()
{

}

void KeySelectionBox::SelectNext()
{

}

void KeySelectionBox::SelectPrev()
{

}

void KeySelectionBox::Update()
{

}

void KeySelectionBox::SetActive(bool bActive) const
{
    if (bActive)
    {
        m_manager->GetEnv()->setFocus(m_listBox);
    }
    m_listBox->setVisible(bActive);
}

void KeySelectionBox::CreateListBox(irr::core::rect<irr::s32> pos, UIElement::Menu elemID)
{
    m_listBox = m_manager->GetEnv()->addListBox(pos, nullptr, elemID, true);

    std::vector<std::string> str = m_controller->ToString();
    for (std::vector<std::string>::iterator it = str.begin(); it != str.end(); ++it)
    {
        m_listBox->addItem(GameManager::ToWstring(*it).c_str());
    }
}
