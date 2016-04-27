//
// Created by veyrie_f on 4/27/16.
//

#ifndef CPP_INDIE_STUDIO_UIMANAGER_HPP
#define CPP_INDIE_STUDIO_UIMANAGER_HPP

#include <stdexcept>
#include <map>
#include "../include/IrrlichtController.hpp"

class UIManager
{
public:
    UIManager(irr::IrrlichtDevice *device);
    virtual ~UIManager();

    // Encapsulates all the ui components
public:
    irr::gui::IGUISkin *GetSkin() const;
    irr::gui::IGUIFont *GetFont() const;
    void SetFont(irr::gui::IGUIFont *font, irr::gui::EGUI_DEFAULT_FONT def) const;

    // TODO: Changer le id par une string et push dans une map
    void AddButton(irr::core::rect<irr::s32> transform, irr::gui::IGUIElement *parent, irr::s32 id,
                   const wchar_t *text, const wchar_t *tip) const;

    void AddStaticText(irr::core::rect<irr::s32> transform, irr::gui::IGUIElement *parent, irr::s32 id,
                       const wchar_t *text, const wchar_t *tip) const;

    void AddScrollbar(irr::core::rect<irr::s32> transform, irr::gui::IGUIElement *parent, irr::s32 id,
                      const wchar_t *text, const wchar_t *tip) const;

    void AddListBox(irr::core::rect<irr::s32> transform, irr::gui::IGUIElement *parent, irr::s32 id,
                      const wchar_t *text, const wchar_t *tip) const;

    void AddEditBox(irr::core::rect<irr::s32> transform, irr::gui::IGUIElement *parent, irr::s32 id,
                      const wchar_t *text, const wchar_t *tip) const;

    irr::gui::IGUIElement *GetComponent(std::string const& component) const;

    // Exception class
public:
    class UIException : public std::runtime_error
    {
    public:
        UIException(std::string const& msg) : runtime_error(msg)
        {}
    };

private:
    irr::IrrlichtDevice *m_device;
    irr::video::IVideoDriver *m_videoDriver;
    irr::gui::IGUIEnvironment* m_env;

    // Assigns string to int for id
    std::map<std::string, irr::s32> m_componentIds;
};


#endif //CPP_INDIE_STUDIO_UIMANAGER_HPP
