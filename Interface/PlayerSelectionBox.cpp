//
// Created by veyrie_f on 5/11/16.
//

#include "PlayerSelectionBox.hpp"

PlayerSelectionBox::PlayerSelectionBox(UIManager *uiManager, irr::io::path const &sprite, irr::core::rect<irr::s32> pos,
                                       UIElement::Menu elemName, bool bIsIaPlayer) :
        m_manager(uiManager),
        m_bIsIaPlayer(bIsIaPlayer),
        m_pos(pos)
{
    m_driver = m_manager->GetDevice()->getVideoDriver();
    m_sceneManager = m_manager->GetDevice()->getSceneManager();
    m_camera = m_sceneManager->addCameraSceneNode(nullptr, irr::core::vector3df(0, 12, -30), irr::core::vector3df(0, 12, 0));
    // TODO: set a different image id !
    img = m_manager->GetEnv()->addImage(pos, nullptr, 42, L"", true);
    irr::gui::IGUIButton *b = m_manager->GetEnv()->addButton(pos, nullptr, elemName, L"", L"");
    b->setImage(m_manager->GetEnv()->getVideoDriver()->getTexture(sprite));
    b->setScaleImage(true);
    b->setUseAlphaChannel(true);
    b->setDrawBorder(false);
}

PlayerSelectionBox::~PlayerSelectionBox()
{
    // TODO: destroy mesh
    //m_modelNode->remove();
}

/*
 * \brief If it is an IA, it swap the sprites
 * otherwise change the 3D model
 */
void PlayerSelectionBox::SelectNext() const
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

    }
}

/*
 * \brief If it is an IA, it swap the sprites
 * otherwise change the 3D model
 */
void PlayerSelectionBox::SelectPrev() const
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
            m_model = m_sceneManager->getMesh("../media/ziggs.md3");
        }
        if (m_model != nullptr && m_modelNode == nullptr)
        {
            m_modelNode = m_sceneManager->addAnimatedMeshSceneNode(m_model);
            if (m_modelNode)
            {
                irr::video::ITexture *texture = m_driver->getTexture("../media/ziggs.png");
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
        img->setImage(m_images.front());
    }
}
