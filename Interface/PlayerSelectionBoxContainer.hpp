//
// Created by veyrie_f on 5/15/16.
//

#ifndef CPP_INDIE_STUDIO_PLAYERSELECTIONBOXCONTAINER_HPP
#define CPP_INDIE_STUDIO_PLAYERSELECTIONBOXCONTAINER_HPP

#include <list>
#include "UIManager.hpp"

class PlayerSelectionBox;

/*
 * \brief Container managing all the player boxes in the GUI
 */
class PlayerSelectionBoxContainer
{
public:
    PlayerSelectionBoxContainer(UIManager *uiManager);
    ~PlayerSelectionBoxContainer();

public:
    void SelectUp();
    void SelectDown();
    void SelectLeft();
    void SelectRight();
    void UpdateBoxes(irr::s32 id);
    void PlayerJoin();

    void SelectSkin(std::string const& skin);
    void UnselectSkin(std::string const& skin);
    bool IsSkinAvailable(std::string const& skin) const;

private:
    void SaveSelection();

private:
    // Knows which box is selected by P1
    std::list<PlayerSelectionBox*> m_boxes;
    UIManager *m_manager;
    std::list<std::string> m_availableSkins;
};


#endif //CPP_INDIE_STUDIO_PLAYERSELECTIONBOXCONTAINER_HPP
