//
// GameManager.hpp for MANAGER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 10:38:09 2016 Victor Gouet
// Last update Mon May 16 10:31:31 2016 Victor Gouet
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

class	GameManager
{
public:
   enum GameState
    {
        SPLASH_SCREEN = 1,
        MAIN_MENU = 2,
        MENU_MAP = 3,
        PLAY = 4,
        PAUSE
    };

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

public:


public:
  static GameManager	*SharedInstance();

private:
  void	onMenu();
  void	onGame();
  void	willStartGame();
  void	willStartMenu();
  void	onPause();

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
  // UIManager		*uiManager;
  // UIEventReceiver	*uiEventReceiver;
  EventGame		*eventGame;
  std::vector<ACharacter *>     characters;

private:
  static GameManager	*GM;
};

#endif
