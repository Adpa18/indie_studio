//
// GameManager.cpp for MANAGER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Mon May  9 10:38:55 2016 Victor Gouet
// Last update Wed Jun  1 16:06:30 2016 Victor Gouet
//

#include <sstream>
#include "Intro.hpp"
#include "../include/Intro.hpp"
#include "../include/SoundManager.hpp"
#include "../include/GameManager.hpp"
#include "../include/Texture.hpp"
#include "../include/GameObjectTimeContainer.hpp"
#include "../ia/IAPlayer.hpp"


GameManager::GameManager()
{
  try {
    IrrlichtController::getDevice(false);
  } catch (std::exception &e)
    {
      std::cout << e.what() << std::endl;
      exit(0);
    }
    BomberManTexture::loadTexture();
    m_gameState = PLAY;
    setGameState(SPLASH_SCREEN);
    _state = PREV_MENU;
    uiManager = NULL;
    uiEventReceiver = NULL;
    eventGame = new EventGame();
    IrrlichtController::getDevice()->setEventReceiver(eventGame);
    m_cameras[MENU_CAM_1] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                             irr::core::vector3df(100, 12, -30),
                                                                             irr::core::vector3df(100, 12, 0));
    m_cameras[MENU_CAM_2] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                             irr::core::vector3df(200, 12, -30),
                                                                             irr::core::vector3df(200, 12, 0));
    m_cameras[MENU_CAM_3] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                             irr::core::vector3df(300, 12, -30),
                                                                             irr::core::vector3df(300, 12, 0));
    m_cameras[MENU_CAM_4] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                             irr::core::vector3df(400, 12, -30),
                                                                             irr::core::vector3df(400, 12, 0));
    m_cameras[GAME_CAMERA] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                                       irr::core::vector3df(0, 0, 0),
                                                                                       irr::core::vector3df(0, 0, 0));
    m_cameras[MAIN_MENU_CAM] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                                         irr::core::vector3df(0, 0, 0),
                                                                                         irr::core::vector3df(0, 0, 0));
//    IAPlayer::initIA();
    m_gameOver = NULL;
    is_gameOver = false;
}

GameManager::~GameManager()
{
//    std::cout << "\e[31mOn suppr le gamemanager\e[0m" << std::endl;
    delete uiEventReceiver;
    delete uiManager;
    delete eventGame;
    IrrlichtController::getDevice()->drop();
    delete SoundManager::getManager();
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
    irr::scene::ICameraSceneNode *camera = m_cameras[MAIN_MENU_CAM];

    if (GameManager::SharedInstance()->getGameState() == GameManager::MAIN_MENU)
    {
        m_gameOver = NULL;
        m_winners.clear();
        characters.clear();
        if (m_gameOver)
            destroyGameOver();
        // Moves the main camera away
        //camera->setPosition(irr::core::vector3df(-10000, 250, -10000));

        // Camera 1
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.014, IrrlichtController::height * 0.445,
                                      IrrlichtController::width * 0.24, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[MENU_CAM_1]);
//        m_cameras[MAIN_MENU_CAM]->setPosition(irr::core::vector3df(100, 12, -30));
//        m_cameras[MAIN_MENU_CAM]->setTarget(irr::core::vector3df(100, 12, 0));
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

        // Camera 2
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.262, IrrlichtController::height * 0.445,
                                      IrrlichtController::width * 0.49, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[MENU_CAM_2]);
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

        // Camera 3
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.515, IrrlichtController::height * 0.445,
                                      IrrlichtController::width * 0.743, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[MENU_CAM_3]);
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

//        // Camera 4
//        // HACK
//        m_cameras[3]->setPosition(irr::core::vector3df(400, 12, -30));
//        m_cameras[3]->setTarget(irr::core::vector3df(400, 12, 0));
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
            irr::core::rect<irr::s32>(IrrlichtController::width * 0.762, IrrlichtController::height * 0.445,
                                      IrrlichtController::width * 0.99, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[MENU_CAM_4]);
        IrrlichtController::getDevice()->getSceneManager()->drawAll();
        // HACK: Moves the last used camera away
//        m_cameras[3]->setPosition(irr::core::vector3df(-40000, 12, -30));

    }
    else if (GameManager::SharedInstance()->getGameState() == GameManager::MENU_MAP)
    {
        static double x = 0, y = 0;
        // Camera 1


        // Moves the main camera away
//        irr::scene::ICameraSceneNode *mainCam = IrrlichtController::getSceneManager()->getActiveCamera();
//        mainCam->setPosition(irr::core::vector3df(-10000, 250, -10000));

        activeCam(MAIN_MENU_CAM);
//        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
//            irr::core::rect<irr::s32>(IrrlichtController::width * 0.01, IrrlichtController::height * 0.1,
//                                      IrrlichtController::width * 0.6, IrrlichtController::height * 0.9));
        // Y is vertial axe
        m_cameras[MAIN_MENU_CAM]->setPosition(irr::core::vector3df(-300 * cos(x += 0.01), 250, -300 * sin(y += 0.01)));
        m_cameras[MAIN_MENU_CAM]->setTarget(irr::core::vector3df(0, 0, 0));
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

        // TODO: try with animator
        // irr::scene::ISceneNodeAnimator* anim = 0;
        // anim = IrrlichtController::getSceneManager()->createFlyCircleAnimator(irr::core::vector3df(0, 100, 0), 250.0f);
        // m_cameras[0].addAnimator(anim);
    }
    else if (GameManager::SharedInstance()->getGameState() == GameManager::RANKING_SCREEN)
    {
        displayRankingScreen();
        is_gameOver = false;
    }
    // Resets the viewport
    IrrlichtController::getDriver()->setViewPort(viewPort);
    if (camera)
      IrrlichtController::getSceneManager()->setActiveCamera(camera);
}

void    GameManager::displayRankingScreen()
{
    if (!m_gameOver)
        m_gameOver = new GameOver(m_winners, characters, &tmp_ranking);
    if (is_gameOver)
        m_gameOver->show();
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

    
   
    GameObjectTimeContainer::SharedInstance()->callTimeOutObjects();
   
    std::vector<ACharacter *>::iterator it = characters.begin();
    size_t nb_dead = 0;
    ACharacter *winner = NULL;

    while (it != characters.end())
    {
        if (!(*it)->isDead())
        {
	    (*it)->compute();
	    winner = (*it);
        }
        else
        {
            ++nb_dead;
        }
        ++it;
    }
    if (nb_dead >= characters.size() -1) {
        if (nb_dead == characters.size())
        {
            m_winners.push_back(-1);
            while (!tmp_ranking.empty())
                tmp_ranking.pop();
        }
        else if (winner)
        {
            tmp_ranking.push(winner);
            m_winners.push_back(winner->get_player());
        }
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[0]);
//	    BomberMap::deleteMap();
        BomberMap::getMap()->removeBlocks();
        SoundManager::getManager()->stopAll();
        is_gameOver = true;
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
    SoundManager::getManager()->stopAll();
    SoundManager::getManager()->play("startGame.wav");
    SoundManager::getManager()->play("ambianceGame.wav", 0, true, 0.1);

//    eventGame->reset();
//    std::vector<irr::core::vector2df> const &spawn = BomberMap::getMap()->getSpawn();
//    IrrlichtController::getDevice()->setEventReceiver(eventGame);
//    int i = 0;
//    characters.clear();
    willStartGame();
//    for (std::vector<ACharacter *>::const_iterator it = characters.begin(); it !=  characters.end(); ++it) {
//        (*it)->reset();
//        (*it)->setPos(spawn[i]);
//        ++i;
//    }
    /*if (BomberMap::getMap()->get_camera())
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
    }*/
}

#include "../include/WallOfDead.hpp"
void    GameManager::willStartGame()
{
    //BomberMap::newMap(BomberMap::Size::SMALL);
    //BomberMap::getMap()->genMap();
  GameObjectTimeContainer::SharedInstance()->removeAll();

  WallOfDead::createWallOfDead(BomberMap::getMap()->getSize());
    SoundManager::getManager()->stopAll();
    SoundManager::getManager()->play("startGame.wav");
    SoundManager::getManager()->play("ambianceGame.wav", 0, true, 0.1);
    std::vector<irr::core::vector2df> const &spawn = BomberMap::getMap()->getSpawn();

    characters.clear();
    while (!tmp_ranking.empty())
        tmp_ranking.pop();
    IrrlichtController::getDevice()->setEventReceiver(eventGame);

    int		i = 0;
    int		u = 0;

    eventGame->reset();
    for (std::list<PlayerInfo *>::iterator	it = m_playerInfo.begin() ;  it != m_playerInfo.end() ; ++it)
    {
        if ((*it)->GetIsIA())
        {
	      characters.push_back(new IAPlayer((*it)->GetName(),
	      					(*it)->GetPos() == NULL ? spawn[i] : *((*it)->GetPos()),
	      					(*it)->GetMesh(),
	      					(*it)->GetTexture(),
	      					i + 1,
	      					IAPlayer::getDifficultyFromCode((*it)->GetIAStrength()
	      									)
	      					));
        }
        else
        {
            characters.push_back(new Player((*it)->GetName(),
                                            (*it)->GetPos() == NULL ? spawn[i] : *((*it)->GetPos()),
                                            (*it)->GetMesh(),
                                            (*it)->GetTexture(),
                                            i+1, *eventGame));
	}
        ++i;
    }


    // int	scorePos = 0;

    // while (scorePos < 4)
    //   {
    //     scoreText[scorePos] = IrrlichtController::getGUIEnvironment()->addStaticText(L"salut", irr::core::rect<irr::s32>(0, scorePos * 10, 50, 10), false);
    //     scoreText[scorePos]->setBackgroundColor(irr::video::SColor(100, 100, 100, 100));
    //     ++scorePos;
    //   }
//    if (BomberMap::getMap()->get_camera())
//    {
    activeCam(GameManager::GameCamera::GAME_CAMERA);
    BomberMap::getMap()->refreshCamera();
//    }
//    else
//    {
//        irr::scene::ICameraSceneNode *camera = IrrlichtController::getSceneManager()->addCameraSceneNode
//            (0, irr::core::vector3df(0, 250, -100), irr::core::vector3df(0, 5, 0));
//        camera->setTarget(irr::core::vector3df(0, 0, 0));
//        camera->setAutomaticCulling(irr::scene::EAC_OFF);
//        camera->setFarValue(1000);
//        camera->setNearValue(10);
//    }
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

GameOver *GameManager::getGameOver() const {
    return m_gameOver;
}

void GameManager::destroyGameOver()
{
    delete(m_gameOver);
    m_gameOver = NULL;
}

irr::scene::ICameraSceneNode *GameManager::getCam(GameCamera cam) {
    return m_cameras[cam];
}

void GameManager::activeCam(GameCamera cam) {
    IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[cam]);
}




