//
// Created by veyrie_f on 5/11/16.
//

#include "PlayerSelectionBox.hpp"
#include "../include/Texture.hpp"

PlayerSelectionBox::PlayerSelectionBox(UIManager *uiManager, irr::io::path const &sprite, irr::core::rect<irr::s32> pos,
                                       UIElement::Menu elemName, bool bIsIaPlayer, UIElement::Menu id, int playerID) :
        m_manager(uiManager),
        m_bIsIaPlayer(bIsIaPlayer),
        m_pos(pos),
        m_playerID(playerID),
        m_id(elemName)
{
    // Get all the needed vars
    m_driver = m_manager->GetDevice()->getVideoDriver();
    m_sceneManager = m_manager->GetDevice()->getSceneManager();
    m_image = m_manager->GetEnv()->addImage(pos, nullptr, id, L"", true);

    // Creates the button box
    m_button = m_manager->GetEnv()->addButton(pos, nullptr, elemName, L"", L"");
    m_button->setImage(m_manager->GetEnv()->getVideoDriver()->getTexture(sprite));
    m_button->setScaleImage(true);
    m_button->setUseAlphaChannel(true);
    m_button->setDrawBorder(false);

    // Creates the name input field box
    m_playerName = m_manager->GetEnv()->addEditBox(L"", irr::core::rect<irr::s32>(pos.UpperLeftCorner.X,
                                                                  IrrlichtController::height * 0.88,
                                                                  pos.LowerRightCorner.X,
                                                                  IrrlichtController::height * 0.91));
    m_playerName->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
    m_playerName->setText((L"Player " + std::to_wstring(playerID)).c_str());

    // Loads the models and the sprites
    m_models.push_back("ziggs");
    m_models.push_back("ziggsGeneral");
    m_models.push_back("ziggsMad");
    m_models.push_back("ziggsSnow");
    m_images.push_back(m_driver->getTexture(BomberManTexture::getModel("IAEasy").texture.c_str()));
    m_images.push_back(m_driver->getTexture(BomberManTexture::getModel("IAMedium").texture.c_str()));
    m_images.push_back(m_driver->getTexture(BomberManTexture::getModel("IAHard").texture.c_str()));

    Update();
}

PlayerSelectionBox::~PlayerSelectionBox()
{
    if (m_modelNode != nullptr)
    {
        m_modelNode->remove();
    }
}

/*
 * \brief If it is an IA, it swap the sprites
 * otherwise change the 3D model
 */
void PlayerSelectionBox::SelectNext()
{
    if (m_bIsIaPlayer)
    {
        if (m_images.size() > 0)
        {
            irr::video::ITexture *t = m_images.front();
            m_images.pop_front();
            m_images.push_back(t);
        }
    }
    else
    {
        if (m_modelNode != nullptr)
        {
            m_modelNode->remove();
            m_modelNode = nullptr;
        }
        if (m_models.size() > 0)
        {
            std::string string = m_models.back();
            m_models.pop_back();
            m_models.push_front(string);

        }
    }
    Update();
}

/*
 * \brief If it is an IA, it swap the sprites
 * otherwise change the 3D model
 */
void PlayerSelectionBox::SelectPrev()
{
    if (m_bIsIaPlayer)
    {
        if (m_images.size() > 0)
        {
            irr::video::ITexture *t = m_images.back();
            m_images.pop_back();
            m_images.push_front(t);
        }
    }
    else
    {
        if (m_modelNode != nullptr)
        {
            m_modelNode->remove();
            m_modelNode = nullptr;
        }
        if (m_models.size() > 0)
        {
            std::string string = m_models.front();
            m_models.pop_front();
            m_models.push_back(string);

        }
    }
    Update();
}

void PlayerSelectionBox::AddSprite(irr::io::path sprite)
{
    m_images.push_back(m_driver->getTexture(sprite));
}

void PlayerSelectionBox::Update()
{
    if (!m_bIsIaPlayer)
    {
        m_image->setImage(nullptr);
        if (m_modelNode == nullptr && m_models.size() > 0)
        {
            irr::scene::IAnimatedMesh *mesh = m_sceneManager->getMesh(BomberManTexture::getModel(m_models.front()).mesh.c_str());
            m_modelNode = m_sceneManager->addAnimatedMeshSceneNode(mesh);
            if (m_modelNode)
            {
                irr::video::ITexture *texture = m_driver->getTexture(BomberManTexture::getModel(m_models.front()).texture.c_str());
                m_modelNode->setMaterialTexture(0, texture);
                m_modelNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                m_modelNode->setPosition(irr::core::vector3df(100 * m_playerID, 0, 0));
            }
        }
    }
    else
    {
        m_image->setImage(m_images.front());
    }
}

irr::gui::IGUIButton const &PlayerSelectionBox::GetButton() const
{
    return *m_button;
}

UIElement::Menu PlayerSelectionBox::GetId() const
{
    return m_id;
}

void PlayerSelectionBox::SetFocus(bool bIsFocused) const
{
    if (bIsFocused)
    {
        m_button->setImage(m_driver->getTexture(BomberManTexture::getModel("playerButtonSelected").texture.c_str()));
    }
    else
    {
        m_button->setImage(m_driver->getTexture(BomberManTexture::getModel("playerButton").texture.c_str()));
    }
}

bool PlayerSelectionBox::GetIaStatus() const
{
    return m_bIsIaPlayer;
}

void PlayerSelectionBox::SetIaStatus(bool isIA)
{
    m_bIsIaPlayer = isIA;
    Update();
}

std::wstring const PlayerSelectionBox::GetPlayerName() const
{
    return std::wstring(m_playerName->getText());
}

std::string const &PlayerSelectionBox::GetSkin() const
{
    return m_models.front();
}
