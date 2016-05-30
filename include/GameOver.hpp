//
// Created by consta_n on 25/05/16.
//

#ifndef CPP_INDIE_STUDIO_GAMEOVER_HPP
#define CPP_INDIE_STUDIO_GAMEOVER_HPP


class GameOver {
private:
  bool                                status;
  irr::scene::ICameraSceneNode        *camera;
  const std::vector<int>              &m_winners;
  std::vector<ACharacter *>     &characters;
  std::stack<ACharacter *>            *tmp_ranking;
  irr::gui::IGUIEnvironment* env;
  irr::gui::IGUISkin* skin;
  irr::gui::IGUIFont* font;
  irr::gui::IGUIFont* save_font;
  irr::gui::IGUIStaticText *st_text;

public:
  GameOver(irr::scene::ICameraSceneNode *camera,
             const std::vector<int> &m_winners,
             std::vector<ACharacter *> &characters,
             std::stack<ACharacter *> *tmp_ranking);
  ~GameOver();
  void show();
  bool getStatus() const;
};


#endif //CPP_INDIE_STUDIO_GAMEOVER_HPP
