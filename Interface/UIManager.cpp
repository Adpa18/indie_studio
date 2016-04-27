//
// Created by veyrie_f on 4/27/16.
//

#include "UIManager.hpp"

UIManager::UIManager(irr::IrrlichtDevice *device) :
        m_device(device)
{
    if (m_device == nullptr)
    {
        throw UIException("No device assigned");
    }

    if ((m_videoDriver = m_device->getVideoDriver()) == nullptr)
    {
        throw UIException("No video driver found");
    }

    if ((m_env = m_device->getGUIEnvironment()) == nullptr)
    {
        throw UIException("No GUI environment found");
    }
}

UIManager::~UIManager()
{

}

irr::gui::IGUIElement *UIManager::GetComponent(std::string const &component) const
{
    return m_env->getRootGUIElement()->getElementFromId(m_componentIds[component]);
}
