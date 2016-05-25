//
// GameManager.hpp for MANAGER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 10:38:09 2016 Victor Gouet
// Last update Wed May 25 11:39:51 2016 Victor Gouet
//

#ifndef GAMEMANAGER_HPP_
# define GAMEMANAGER_HPP_

# include "IrrlichtController.hpp"
# include "../Interface/UIManager.hpp"
# include "../Interface/UIEventReceiver.hpp"
# include "FireBomb.hpp"
# include "EventGame.hpp"
# include "Player.hpp"
# include "BomberMap.hpp"
#include "../Interface/PlayerInfo.hpp"

class	GameManager
{
public:
   enum GameState
    {
        SPLASH_SCREEN = 1,
        MAIN_MENU = 2,
        MENU_MAP = 3,
        PLAY = 4,
        PAUSE,
	CLASSMENT_SCREEN
    };

  typedef void	(GameManager::*initInstance)(void);

public:
  GameManager();
  ~GameManager();

public:
  void	run();

public:
  void		setGameState(GameState);
  GameState	getGameState() const;
  void		setPrevGameState(GameState);
  GameState	getPrevGameState() const;
  UIManager	*getUIManager() const;
  EventGame	*getEventGame() const;
  void		setFptr(initInstance _fptr);

  void AddPlayer(PlayerInfo *player);
  std::list<PlayerInfo*>::const_iterator GetPlayers() const;

  static std::string ToString(std::wstring const& str);
  static std::wstring ToWstring(std::string const& str);

public:
  static GameManager	*SharedInstance();

private:
  void	onMenu();
  void	onGame();

public:
  void	willStartGame();
  void	willStartMenu();

private:
  enum	State
    {
      PREV_MENU,
      MENU,
      PREV_GAME,
      GAME
    };
  State		_state;
  bool		_pause;

private:
  GameState m_gameState;
  GameState m_gameSatePrev;
  UIManager		*uiManager;
  UIEventReceiver	*uiEventReceiver;
  EventGame		*eventGame;
  std::vector<ACharacter *>     characters;
  void			(GameManager::*fptr)() = NULL;
  irr::gui::IGUIStaticText *scoreText[4];

    // Cameras for the menu selection
    irr::scene::ICameraSceneNode *m_cameras[4];
    // List of players to be spawned
    std::list<PlayerInfo*> m_playerInfo;

private:
  static GameManager	*GM;
};

#endif
