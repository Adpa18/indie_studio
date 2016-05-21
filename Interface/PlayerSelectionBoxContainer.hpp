//
// Created by veyrie_f on 5/15/16.
//

#ifndef CPP_INDIE_STUDIO_PLAYERSELECTIONBOXCONTAINER_HPP
#define CPP_INDIE_STUDIO_PLAYERSELECTIONBOXCONTAINER_HPP

#include <list>
#include "PlayerSelectionBox.hpp"

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

private:
    // Knows which box is selected by P1
    std::list<PlayerSelectionBox*> m_boxes;
    UIManager *m_manager;
};


#endif //CPP_INDIE_STUDIO_PLAYERSELECTIONBOXCONTAINER_HPP
