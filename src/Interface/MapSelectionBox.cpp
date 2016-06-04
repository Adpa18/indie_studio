//
// Created by veyrie_f on 6/4/16.
//

#include "../../Irrlicht/irrlicht-1.8.3/include/rect.h"
#include "../../include/MapSelectionBox.hpp"
#include "../../include/GameManager.hpp"

MapSelectionBox::MapSelectionBox(UIManager *uiManager, irr::core::rect <irr::s32> pos,
                                 UIElement::Menu elemName) :
        m_manager(uiManager)
{
    m_list = m_manager->GetEnv()->addListBox(pos, nullptr, elemName, true);

    //m_manager->GetEnv()->setFocus(m_list);

    m_names.push_back("Map 1");
    m_names.push_back("Map 2");
    m_names.push_back("Map 3");

    m_list->addItem(L"Map 1");
    m_list->addItem(L"Map 2");
    m_list->addItem(L"Map 3");
    Update();
}

MapSelectionBox::~MapSelectionBox()
{

}

void MapSelectionBox::Update()
{
    if (m_names.size() > 0)
    {
        m_list->setSelected(GameManager::ToWstring(m_names.front()).c_str());
    }
}

void MapSelectionBox::SelectNext()
{
    if (m_names.size() > 0)
    {
        std::rotate(m_names.begin(), std::prev(m_names.end(), 1), m_names.end());
    }
    Update();
}

void MapSelectionBox::SelectPrev()
{
    if (m_names.size() > 0)
    {
        std::rotate(m_names.begin(), std::next(m_names.begin(), 1), m_names.end());
    }
    Update();
}

void MapSelectionBox::OnSelect()
{

}

wchar_t const *MapSelectionBox::GetSelected() const
{
    return m_list->getListItem(m_list->getSelected());
}

void MapSelectionBox::AddItem(std::string const& name)
{
    m_names.push_back(name);
    m_list->addItem(GameManager::ToWstring(name).c_str());
    Update();
}
