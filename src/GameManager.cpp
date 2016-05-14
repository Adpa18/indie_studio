//
// GameManager.cpp for MANAGER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Mon May  9 10:38:55 2016 Victor Gouet
// Last update Sat May 14 23:06:32 2016 Victor Gouet
//

#include "../include/GameManager.hpp"
#include "../include/Texture.hpp"
#include "../include/GameObjectTimeContainer.hpp"

GameManager *GameManager::GM = NULL;

GameManager::GameManager()
{
  // m_gameState = PLAY;
  IrrlichtController::getDevice(false);
  setGameState(PLAY);
  m_gameSatePrev = SPLASH_SCREEN;
  // uiManager = new UIManager(IrrlichtController::getDevice(false));
  // uiEventReceiver = new UIEventReceiver(*uiManager);
  IrrlichtController::getGUIEnvironment()->getFont("/home/gouet_v/Downloads/irrlicht-1.8.3/media/fonthaettenschweiler.bmp");
  eventGame = new EventGame();
  BomberManTexture::loadTexture();
  // _state = PREV_GAME;
}

GameManager::~GameManager()
{
  // delete uiManager;
  // delete uiEventReceiver;
  delete eventGame;
}

GameManager	*GameManager::SharedInstance()
{
  if (GM == NULL)
    {
      GM = new GameManager();
    }
  return (GM);
}

void		GameManager::setGameState(GameState state)
{
  m_gameState = state;
  if (state == PLAY)
    _state = PREV_GAME;
  if (state >= SPLASH_SCREEN && state <= MENU_MAP)
    _state = PREV_MENU;
}

GameManager::GameState	GameManager::getGameState() const
{
  return (m_gameState);
}

void		GameManager::setPrevGameState(GameState state)
{
  m_gameSatePrev = state;
}

GameManager::GameState	GameManager::getPrevGameState() const
{
  return (m_gameSatePrev);
}

void	GameManager::run()
{
  while (IrrlichtController::getDevice()->run()
	 && IrrlichtController::getDriver())
    {
      if (IrrlichtController::getDevice()->isWindowActive())
	{
	  if (m_gameState == PLAY)
	    {
	      if (_state == PREV_GAME)
		willStartGame();
	      _state = GAME;
	      onGame();
	    }
	  else if (m_gameState >= SPLASH_SCREEN &&
		   m_gameState <= MENU_MAP)
	    {
	      if (_state == PREV_MENU)
		willStartMenu();
	      _state = MENU;
	      onMenu();
	    }
	  IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
	  IrrlichtController::getSceneManager()->drawAll();
	  IrrlichtController::getGUIEnvironment()->drawAll();
	  IrrlichtController::getDriver()->endScene();
	}
    }
  IrrlichtController::getDevice()->drop();
}

void	GameManager::onMenu()
{

}

void	GameManager::onGame()
{
  GameObjectTimeContainer::SharedInstance()->callTimeOutObjects();

  std::vector<ACharacter*>::iterator it = characters.begin();
  while (it != characters.end())
    {
      if (!(*it)->isDead())
	{
	  (*it)->compute();
	  ++it;
	}
      else
	{
	  delete (*it);
	  it = characters.erase(it);
	}
    }
}

void	GameManager::willStartGame()
{
  BomberMap::newMap(BomberMap::Size::SMALL);
  BomberMap::getMap()->genMap();

  characters.clear();
  characters.push_back(new Player("ROGER", irr::core::vector2df(1, 1), BomberManTexture::getModel("ziggs").mesh, BomberManTexture::getModel("ziggs").texture, 0, *eventGame));
  characters.push_back(new Player("RICHARD", irr::core::vector2df(9, 1), BomberManTexture::getModel("ziggs").mesh, BomberManTexture::getModel("ziggs").texture, 0, *eventGame));

  IrrlichtController::getDevice()->setEventReceiver(eventGame);
  irr::scene::ICameraSceneNode* camera = IrrlichtController::getSceneManager()->addCameraSceneNode
    (0, irr::core::vector3df(0, 250, -100), irr::core::vector3df(0,5,0));
  camera->setTarget(irr::core::vector3df(0, 0, 0));

  camera->setAutomaticCulling(irr::scene::EAC_OFF);
  camera->setFarValue(1000);
  camera->setNearValue(10);

//  IrrlichtController::getSceneManager()->setAmbientLight(irr::video::SColorf(1.0f,
//									     1.0f, 1.0f, 1.0f));

}

void	GameManager::willStartMenu()
{
  // IrrlichtController::getDevice()->setEventReceiver(uiEventReceiver);
}
