//
// Created by veyrie_f on 5/27/16.
//

#include <algorithm>
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
    delete(m_controller);
}

void KeySelectionBox::SelectNext()
{
    if (m_keys.size() > 0)
    {
        std::rotate(m_keys.begin(), std::next(m_keys.begin(), 1), m_keys.end());
    }
    else if (m_motions.size() > 0)
    {
        std::rotate(m_motions.begin(), std::next(m_motions.begin(), 1), m_motions.end());
    }
    Update();
}

void KeySelectionBox::SelectPrev()
{
    if (m_keys.size() > 0)
    {
        std::rotate(m_keys.begin(), std::prev(m_keys.end(), 1), m_keys.end());
    }
    else if (m_motions.size() > 0)
    {
        std::rotate(m_motions.begin(), std::prev(m_motions.end(), 1), m_motions.end());
    }
    Update();
}

void KeySelectionBox::Update()
{
    if (m_keys.size() > 0)
        m_listBox->setSelected(GameManager::ToWstring(m_keys.front().ToString()).c_str());
    else if (m_motions.size() > 0)
        m_listBox->setSelected(GameManager::ToWstring(m_motions.front().ToString()).c_str());
}

void KeySelectionBox::SetActive(bool bActive) const
{
    m_listBox->setVisible(bActive);
}

void KeySelectionBox::CreateListBox(irr::core::rect<irr::s32> pos, UIElement::Menu elemID)
{
    m_listBox = m_manager->GetEnv()->addListBox(pos, nullptr, elemID, true);
    UpdateElements();
}

bool KeySelectionBox::IsActive() const
{
    return m_listBox->isVisible();
}

// TODO: send pressed key, forbid any action in selection mode
void KeySelectionBox::OnSelect()
{
    if (!m_isSelecting)
    {
        m_isSelecting = true;
        m_listBox->setItemOverrideColor(m_listBox->getSelected(), irr::video::SColor(255, 255, 0, 0));
    }
}

void KeySelectionBox::UpdateElements()
{
    bool isFirst = true;

    m_listBox->clear();
    KeysController *k = dynamic_cast<KeysController*>(m_controller);
    if (k != nullptr)
    {
        m_keys = k->ToString();
        for (std::vector<KeysController::KeyInfo>::iterator it = m_keys.begin(); it != m_keys.end(); ++it)
        {
            if (isFirst)
            {
                isFirst = false;
                m_listBox->setSelected(m_listBox->addItem(GameManager::ToWstring((*it).ToString()).c_str()));
            }
            else
            {
                m_listBox->addItem(GameManager::ToWstring((*it).ToString()).c_str());
            }
        }
    }
    MotionController *m = dynamic_cast<MotionController*>(m_controller);
    if (m != nullptr)
    {
        m_motions = m->ToString();
        for (std::vector<MotionController::KeyInfo>::iterator it = m_motions.begin(); it != m_motions.end(); ++it)
        {
            if (isFirst)
            {
                isFirst = false;
                m_listBox->setSelected(m_listBox->addItem(GameManager::ToWstring((*it).ToString()).c_str()));
            }
            else
            {
                m_listBox->addItem(GameManager::ToWstring((*it).ToString()).c_str());
            }
        }
    }
}

void KeySelectionBox::OnKeyPress(irr::EKEY_CODE key)
{
    if (m_isSelecting)
    {
        m_isSelecting = false;
        m_listBox->setItemOverrideColor(m_listBox->getSelected(), irr::video::SColor(255, 0, 0, 0));

        KeysController *k;
        if ((k = dynamic_cast<KeysController*>(m_controller)) != nullptr)
        {
            k->BindAction(m_keys.front().GetAction(), key);
        }
        UpdateElements();
    }
}

void KeySelectionBox::OnKeyPress(irr::u32 key)
{
    if (m_isSelecting && key != 0)
    {
        m_isSelecting = false;
        m_listBox->setItemOverrideColor(m_listBox->getSelected(), irr::video::SColor(255, 0, 0, 0));

        MotionController *m;
        if ((m = dynamic_cast<MotionController*>(m_controller)) != nullptr)
        {
            m->BindAction(m_motions.front().GetAction(), static_cast<MotionController::ControllerKey>(key));
        }
        UpdateElements();
    }
}

bool KeySelectionBox::IsSelecting() const
{
    return m_isSelecting;
}

