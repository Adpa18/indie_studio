//
// GameManager.cpp for MANAGER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Mon May  9 10:38:55 2016 Victor Gouet
// Last update Wed May 25 22:39:38 2016 Victor Gouet
//

#include <sstream>
#include "Intro.hpp"
#include "../include/GameManager.hpp"
#include "../include/Texture.hpp"
#include "../include/GameObjectTimeContainer.hpp"
#include "../ia/IAPlayer.hpp"


GameManager::GameManager()
{
    IrrlichtController::getDevice(false);
    BomberManTexture::loadTexture();
    m_gameState = PLAY;
    setGameState(SPLASH_SCREEN);
    _state = PREV_MENU;
    uiManager = NULL;
    uiEventReceiver = NULL;
    eventGame = new EventGame();
    IrrlichtController::getDevice()->setEventReceiver(eventGame);

    m_cameras[0] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                             irr::core::vector3df(100, 12, -30),
                                                                             irr::core::vector3df(100, 12, 0));
    m_cameras[1] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                             irr::core::vector3df(200, 12, -30),
                                                                             irr::core::vector3df(200, 12, 0));
    m_cameras[2] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                             irr::core::vector3df(300, 12, -30),
                                                                             irr::core::vector3df(300, 12, 0));
    m_cameras[3] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                             irr::core::vector3df(400, 12, -30),
                                                                             irr::core::vector3df(400, 12, 0));
//    IAPlayer::initIA();
}

GameManager::~GameManager()
{
//    std::cout << "\e[31mOn suppr le gamemanager\e[0m" << std::endl;
    delete uiEventReceiver;
    delete uiManager;
    delete eventGame;
    IrrlichtController::getDevice()->drop();
    IrrlichtController::getIrrKlangDevice()->drop();
}

GameManager *GameManager::SharedInstance()
{
    static GameManager	*GM = NULL;

    if (GM == NULL)
    {
        GM = new GameManager();
    }
    return (GM);
}

void        GameManager::setGameState(GameState state)
{
    m_gameSatePrev = m_gameState;
    m_gameState = state;
    // if (state == PLAY)
    //   fptr = &GameManager::willStartGame;
    // if (state >= SPLASH_SCREEN && state <= MENU_MAP)
    //   fptr = &GameManager::willStartMenu;
}

GameManager::GameState    GameManager::getGameState() const
{
    return (m_gameState);
}

void        GameManager::setPrevGameState(GameState state)
{
    m_gameSatePrev = state;
}

GameManager::GameState    GameManager::getPrevGameState() const
{
    return (m_gameSatePrev);
}

void    GameManager::run()
{
    Intro *intro = new Intro(eventGame);
    intro->run();
    delete intro;
    uiManager = new UIManager(IrrlichtController::getDevice(false));
    uiEventReceiver = new UIEventReceiver(*uiManager);

    setFptr(&GameManager::willStartMenu);

    while (IrrlichtController::getDevice()->run()
           && IrrlichtController::getDriver())
    {
        if (IrrlichtController::getDevice()->isWindowActive())
        {
            IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
            if (fptr)
                (this->*fptr)();
            fptr = NULL;
            if (m_gameState == PAUSE)
                GameObjectTimeContainer::SharedInstance()->timerStop();
            if (m_gameState == PLAY)
            {
                _state = GAME;
                onGame();
            }
            else
            {
                // if (_state != MENU && m_gameState != PAUSE)
                // 	{
                // 	  BomberMap::deleteMap();
                _state = MENU;
                // }
                onMenu();
            }

            IrrlichtController::getSceneManager()->drawAll();
            IrrlichtController::getGUIEnvironment()->drawAll();
            IrrlichtController::getDriver()->endScene();
        }
    }
//    std::cout << "\e[32mOn part du run\e[0m" << std::endl;
}

void    GameManager::onMenu()
{
    if (GameManager::SharedInstance()->getGameState() == GameManager::PAUSE)
        return;

    // Copies viewport state
    irr::core::rect<irr::s32> viewPort = IrrlichtController::getDriver()->getViewPort();
    irr::scene::ICameraSceneNode *camera = IrrlichtController::getSceneManager()->getActiveCamera();

    if (GameManager::SharedInstance()->getGameState() == GameManager::MAIN_MENU)
    {
        // Moves the main camera away
        //camera->setPosition(irr::core::vector3df(-10000, 250, -10000));

        // Camera 1
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.014, IrrlichtController::height * 0.445,
                                      IrrlichtController::width * 0.24, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[0]);
        m_cameras[0]->setPosition(irr::core::vector3df(100, 12, -30));
        m_cameras[0]->setTarget(irr::core::vector3df(100, 12, 0));
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

        // Camera 2
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.262, IrrlichtController::height * 0.445,
                                      IrrlichtController::width * 0.49, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[1]);
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

        // Camera 3
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.515, IrrlichtController::height * 0.445,
                                      IrrlichtController::width * 0.743, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[2]);
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

        // Camera 4
        // HACK
        m_cameras[3]->setPosition(irr::core::vector3df(400, 12, -30));
        m_cameras[3]->setTarget(irr::core::vector3df(400, 12, 0));
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.762, IrrlichtController::height * 0.445,
                                      IrrlichtController::width * 0.99, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[3]);
        IrrlichtController::getDevice()->getSceneManager()->drawAll();
        // HACK: Moves the last used camera away
        m_cameras[3]->setPosition(irr::core::vector3df(-40000, 12, -30));

    }
    else if (GameManager::SharedInstance()->getGameState() == GameManager::MENU_MAP)
    {
        static double x = 0, y = 0;
        // Camera 1
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.01, IrrlichtController::height * 0.1,
                                      IrrlichtController::width * 0.6, IrrlichtController::height * 0.9));

        // Moves the main camera away
        irr::scene::ICameraSceneNode *mainCam = IrrlichtController::getSceneManager()->getActiveCamera();
        mainCam->setPosition(irr::core::vector3df(-10000, 250, -10000));

        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[0]);
        // Y is vertial axe
        m_cameras[0]->setPosition(irr::core::vector3df(-300 * cos(x += 0.01), 250, -300 * sin(y += 0.01)));
        m_cameras[0]->setTarget(irr::core::vector3df(0, 0, 0));
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

        // TODO: try with animator
        // irr::scene::ISceneNodeAnimator* anim = 0;
        // anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(0, 100, 0), 250.0f);
        // m_cameras[0].addAnimator(anim);
    }
    else if (GameManager::SharedInstance()->getGameState() == GameManager::RANKING_SCREEN)
        displayRankingScreen();

    // Resets the viewport
    IrrlichtController::getDriver()->setViewPort(viewPort);
    IrrlichtController::getSceneManager()->setActiveCamera(camera);
}

void    GameManager::displayRankingScreen()
{
    int i = 0;
    static int set = 0;

    if (!set)
    {
        set = 1;
        std::vector<std::pair<int, int>> ranking;
//        irr::gui::IGUIImage *image = uiManager->GetEnv()->addImage(
//            irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
//            nullptr, UIElement::SPLASH_BACKGROUND, L"", true);
//        image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(
//            BomberManTexture::getModel("victory").texture.c_str()));
//
//        image->setScaleImage(true);

        int size = (int) m_winners.size();
        for (std::vector<ACharacter *>::const_iterator it = characters.begin(); it !=  characters.end(); ++it) {
            int count = 0;
            i = 0;
            while (i < size)
            {
                if (m_winners[i] != -1)
                {
                    if ((*it)->get_player() == m_winners[i])
                        ++count;
                }
                ++i;
            }
            if (count)
                ranking.push_back(std::make_pair((*it)->getID(), count));
        }
        //IrrlichtController::getDevice()->getSceneManager()->drawAll();
        m_cameras[0]->setPosition(irr::core::vector3df(-50, 25, 0));
        m_cameras[0]->setTarget(irr::core::vector3df(0, 25, 0));
        std::sort(ranking.begin(), ranking.end(),  [] (std::pair<int, int> p1, std::pair<int, int> p2) { return p1.second > p2.second; } );
        int winner = -1;
        if (ranking[0].second > 2)
        {
            for (std::vector<ACharacter *>::const_iterator it = characters.begin(); it !=  characters.end(); ++it) {
                (*it)->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));
                (*it)->setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
                if ((*it)->get_player() == ranking[0].first)
                {
                    (*it)->getSceneNode()->setPosition(irr::core::vector3df(0, 0, 0));
                    winner = ranking[0].first;
                }
                else if ((*it)->get_player() == ranking[1].first)
                    (*it)->getSceneNode()->setPosition(irr::core::vector3df(50, 0, 50));
                else if ((*it)->get_player() == ranking[2].first)
                    (*it)->getSceneNode()->setPosition(irr::core::vector3df(50, 0, -50));
            }
        }
        else
        {
            winner = tmp_ranking.top()->get_player();
            tmp_ranking.top()->getSceneNode()->setPosition(irr::core::vector3df(0, 0, 0));
            tmp_ranking.top()->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));
            tmp_ranking.top()->setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
            tmp_ranking.pop();
            tmp_ranking.top()->getSceneNode()->setPosition(irr::core::vector3df(50, 0, 50));
            tmp_ranking.top()->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));
            tmp_ranking.top()->setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
            tmp_ranking.pop();
            tmp_ranking.top()->getSceneNode()->setPosition(irr::core::vector3df(50, 0, -50));
            tmp_ranking.top()->getSceneNode()->setRotation(irr::core::vector3df(0, 45, 0));
            tmp_ranking.top()->setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
            tmp_ranking.pop();
            while (!tmp_ranking.empty())
                tmp_ranking.pop();
        }
        irr::gui::IGUIEnvironment* env = IrrlichtController::getDevice()->getGUIEnvironment();
        irr::gui::IGUISkin* skin = env->getSkin();
        irr::gui::IGUIFont* font = env->getFont("./media/font/arcade_font.xml");
        if (font)
            skin->setFont(font);
        std::wstringstream ss;
        ss << "Player " <<  winner << " win!";
        irr::gui::IGUIStaticText *st_text = env->addStaticText(
            ss.str().c_str(),
            irr::core::rect<irr::s32>(0, 100,
                                      (irr::s32) IrrlichtController::width, 200),
            false, // border?
            true);
        st_text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
        //text->setBackgroundColor(irr::video::SColor(255, 0, 255, 255));
        st_text->setTextAlignment(irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER,
                                  irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER);
        env->drawAll();
    }
}

void    GameManager::onGame()
{
    // std::vector<ACharacter *>::iterator it_2 = characters.begin();
    // while (it_2 != characters.end())
    //   {
    // irr::gui::IGUIFont *fnt = IrrlichtController::getGUIEnvironment()->getFont("media/font/fonthaettenschweiler.bmp");
    // irr::core::dimension2d<irr::u32> size = fnt->getDimension(L"azkekazokezozaojezoaeazeijozeiajzeojazeojazeiojazeoiazejoiezjozeijazeojazeio");
    // fnt->draw(L"zakoazekoazekoazejoazejazeoijazeojazeoiazejiozaej",
    // 		irr::core::rect<irr::s32>(0,
    // 					  0,
    // 					  (0 + size.Width),
    // 					  (0 + size.Height)),
    // 		irr::video::SColor(255,255,255,255));
    // IrrlichtController::getGUIEnvironment()->addStaticText(L"azkezoazekoezko",
    // 							 irr::core::rect<irr::s32>(100, 100, 100, 100), false);
    // }

    if (eventGame->IsKeyDownOneTime(irr::EKEY_CODE::KEY_KEY_P))
    {
        setGameState(PAUSE);
        IrrlichtController::getDevice()->setEventReceiver(uiEventReceiver);
        uiEventReceiver->DisplayPauseMenu();
        return ;
    }
    if (eventGame->IsKeyDownOneTime(irr::EKEY_CODE::KEY_KEY_S))
    {
        BomberMap::getMap()->save();
    }

    GameObjectTimeContainer::SharedInstance()->callTimeOutObjects();

    std::vector<ACharacter *>::iterator it = characters.begin();
    size_t nb_dead = 0;
    ACharacter *winner;
    while (it != characters.end())
    {
        if (!(*it)->isDead())
        {
            (*it)->compute();
            winner = (*it);
        }
        else
            ++nb_dead;
        ++it;
    }
    if (nb_dead >= characters.size() -1) {
        if (nb_dead == characters.size())
            m_winners.push_back(-1);
        else
        {
            tmp_ranking.push(winner);
            m_winners.push_back(winner->get_player());
        }
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[0]);
        BomberMap::deleteMap();
        IrrlichtController::getIrrKlangDevice()->stopAllSounds();
        setGameState(RANKING_SCREEN);
        IrrlichtController::getDevice()->setEventReceiver(uiEventReceiver);
    }
}

void    GameManager::addDeadPlayer(ACharacter *player)
{
    tmp_ranking.push(player);
}

void    GameManager::willRestartGame()
{
    if (SOUND)
    {
        IrrlichtController::getIrrKlangDevice()->play2D((IrrlichtController::soundPath + "startGame.wav").c_str(), false);
        IrrlichtController::getIrrKlangDevice()->play2D((IrrlichtController::soundPath + "ambianceGame.wav").c_str(), true);
    }

    std::vector<irr::core::vector2df> const &spawn = BomberMap::getMap()->getSpawn();
    IrrlichtController::getDevice()->setEventReceiver(eventGame);
    int i = 0;
    for (std::vector<ACharacter *>::const_iterator it = characters.begin(); it !=  characters.end(); ++it) {
        (*it)->setPos(spawn[i]);
        ++i;
    }
    if (BomberMap::getMap()->get_camera())
    {
        IrrlichtController::getSceneManager()->setActiveCamera(BomberMap::getMap()->get_camera());
        BomberMap::getMap()->refreshCamera();
    }
    else
    {
        irr::scene::ICameraSceneNode *camera = IrrlichtController::getSceneManager()->addCameraSceneNode
            (0, irr::core::vector3df(0, 250, -100), irr::core::vector3df(0, 5, 0));
        camera->setTarget(irr::core::vector3df(0, 0, 0));
        camera->setAutomaticCulling(irr::scene::EAC_OFF);
        camera->setFarValue(1000);
        camera->setNearValue(10);
    }
}

void    GameManager::willStartGame()
{
    //BomberMap::newMap(BomberMap::Size::SMALL);
    //BomberMap::getMap()->genMap();

    if (SOUND)
    {
        IrrlichtController::getIrrKlangDevice()->play2D((IrrlichtController::soundPath + "startGame.wav").c_str(), false);
        IrrlichtController::getIrrKlangDevice()->play2D((IrrlichtController::soundPath + "ambianceGame.wav").c_str(), true);
    }
    std::vector<irr::core::vector2df> const &spawn = BomberMap::getMap()->getSpawn();

    characters.clear();
    IrrlichtController::getDevice()->setEventReceiver(eventGame);

    int		i = 0;

    for (std::list<PlayerInfo *>::iterator	it = m_playerInfo.begin() ;  it != m_playerInfo.end() ;)
    {
        //todo comment 'i == 0' and uncomment '(*it)->GetIsIA()'
        if ((*it)->GetIsIA())
        {
            characters.push_back(new IAPlayer((*it)->GetName(),
                                              (*it)->GetPos() == NULL ? spawn[i] : *((*it)->GetPos()),
                                              (*it)->GetMesh(),
                                              (*it)->GetTexture(),
                                              i+1));
        }
        else
        {
            characters.push_back(new Player((*it)->GetName(),
                                            (*it)->GetPos() == NULL ? spawn[i] : *((*it)->GetPos()),
                                            (*it)->GetMesh(),
                                            (*it)->GetTexture(),
                                            i+1, *eventGame));
        }
        delete (*it);
        it = m_playerInfo.erase(it);
        ++i;
    }

    // int	scorePos = 0;

    // while (scorePos < 4)
    //   {
    //     scoreText[scorePos] = IrrlichtController::getGUIEnvironment()->addStaticText(L"salut", irr::core::rect<irr::s32>(0, scorePos * 10, 50, 10), false);
    //     scoreText[scorePos]->setBackgroundColor(irr::video::SColor(100, 100, 100, 100));
    //     ++scorePos;
    //   }
    if (BomberMap::getMap()->get_camera())
    {
        IrrlichtController::getSceneManager()->setActiveCamera(BomberMap::getMap()->get_camera());
        BomberMap::getMap()->refreshCamera();
    }
    else
    {
        irr::scene::ICameraSceneNode *camera = IrrlichtController::getSceneManager()->addCameraSceneNode
            (0, irr::core::vector3df(0, 250, -100), irr::core::vector3df(0, 5, 0));
        camera->setTarget(irr::core::vector3df(0, 0, 0));
        camera->setAutomaticCulling(irr::scene::EAC_OFF);
        camera->setFarValue(1000);
        camera->setNearValue(10);
    }
}

void    GameManager::willStartMenu()
{
    IrrlichtController::getDevice()->setEventReceiver(uiEventReceiver);

}

UIManager *GameManager::getUIManager() const
{
    return (this->uiManager);
}

EventGame *GameManager::getEventGame() const
{
    return (this->eventGame);
}

void        GameManager::setFptr(initInstance _fptr)
{
    this->fptr = _fptr;
}

void GameManager::AddPlayer(PlayerInfo *player)
{
    if (player != nullptr)
    {
        m_playerInfo.push_back(player);
    }
}

void GameManager::ClearPlayers()
{
    m_playerInfo.clear();
}

void GameManager::AddPlayerFromUI(PlayerInfo *player)
{
    if (player != nullptr)
    {
        m_playerInfoUI.push_back(player);
    }
}

std::list<PlayerInfo *>::const_iterator GameManager::GetPlayers() const
{
    return m_playerInfo.begin();
}

std::string GameManager::ToString(std::wstring const &str)
{
    return std::string(str.begin(), str.end());
}

std::wstring GameManager::ToWstring(std::string const &str)
{
    return std::wstring(str.begin(), str.end());
}

void GameManager::SwapCharacterList()
{
    m_playerInfo.clear();
    m_playerInfo.merge(m_playerInfoUI);
}
