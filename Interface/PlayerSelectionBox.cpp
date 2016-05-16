//
// Created by veyrie_f on 5/11/16.
//

#include "PlayerSelectionBox.hpp"
#include "../include/Texture.hpp"

PlayerSelectionBox::PlayerSelectionBox(UIManager *uiManager, irr::io::path const &sprite, irr::core::rect<irr::s32> pos,
                                       UIElement::Menu elemName, bool bIsIaPlayer, UIElement::Menu id) :
        m_manager(uiManager),
        m_bIsIaPlayer(bIsIaPlayer),
        m_pos(pos)
{
    // Get all the needed vars
    m_driver = m_manager->GetDevice()->getVideoDriver();
    m_sceneManager = m_manager->GetDevice()->getSceneManager();
    m_camera = m_sceneManager->addCameraSceneNode(nullptr, irr::core::vector3df(0, 12, -30), irr::core::vector3df(0, 12, 0));
    m_image = m_manager->GetEnv()->addImage(pos, nullptr, id, L"", true);

    // Creates the button box
    irr::gui::IGUIButton *b = m_manager->GetEnv()->addButton(pos, nullptr, elemName, L"", L"");
    b->setImage(m_manager->GetEnv()->getVideoDriver()->getTexture(sprite));
    b->setScaleImage(true);
    b->setUseAlphaChannel(true);
    b->setDrawBorder(false);

    // Loads the models and the sprites
    m_models.push_back(m_sceneManager->getMesh(BomberManTexture::getModel("ziggs").mesh.c_str()));
    m_images.push_back(m_driver->getTexture(BomberManTexture::getModel("playerButtonIa").texture.c_str()));
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
            irr::scene::IAnimatedMesh *mesh = m_models.back();
            m_models.pop_back();
            m_models.push_front(mesh);

            m_modelNode = m_sceneManager->addAnimatedMeshSceneNode(m_models.front());
        }
    }
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
            irr::scene::IAnimatedMesh *mesh = m_models.front();
            m_models.pop_front();
            m_models.push_back(mesh);

            m_modelNode = m_sceneManager->addAnimatedMeshSceneNode(m_models.front());
        }
    }
}

void PlayerSelectionBox::AddSprite(irr::io::path sprite)
{
    m_images.push_back(m_driver->getTexture(sprite));
}

void PlayerSelectionBox::Update()
{
    if (!m_bIsIaPlayer)
    {
        // Copies viewport state
        //irr::core::rect<irr::s32> viewPort = m_driver->getViewPort();
        //irr::scene::ICameraSceneNode *camera = m_sceneManager->getActiveCamera();

        //m_driver->setViewPort(m_pos);
        //m_sceneManager->setActiveCamera(m_camera);

        if (m_model == nullptr)
        {
            m_model = m_sceneManager->getMesh(BomberManTexture::getModel("ziggs").mesh.c_str());
        }
        if (m_model != nullptr && m_modelNode == nullptr)
        {
            m_modelNode = m_sceneManager->addAnimatedMeshSceneNode(m_model);
            if (m_modelNode)
            {
                irr::video::ITexture *texture = m_driver->getTexture(BomberManTexture::getModel("ziggs").texture.c_str());
                m_modelNode->setMaterialTexture(0, texture);
                m_modelNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            }
        }

        IrrlichtController::getDevice()->getSceneManager()->drawAll();

        // Sets the viewport to its initial state
        //m_driver->setViewPort(viewPort);
        //m_sceneManager->setActiveCamera(camera);
    }
    else
    {
        m_image->setImage(m_images.front());
    }
}
