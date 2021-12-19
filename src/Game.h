
#ifndef WHACKAMOLESFML_GAME_H
#define WHACKAMOLESFML_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  bool collisionCheck(sf::Vector2i click, sf::Sprite sprite);
  void spawn();

  sf::RenderWindow& window;
  sf::Sprite background;
  sf::Texture background_texture;
  sf::Sprite bird;
  sf::Sprite bear;
  sf::Sprite pig;
  sf::Texture bird_texture;
  sf::Texture bear_texture;
  sf::Texture pig_texture;
  sf::Font font;

  bool in_menu;
  bool draw_bird = false;
  bool draw_bear = false;
  bool draw_pig  = false;
  sf::Text menu_text;
  sf::Text play_option;
  sf::Text quit_option;
  sf::Text Score;
  sf::Text timer;
  sf::Clock clock;

  bool play_selected = true;

  bool reverse_bird = false;
  bool reverse_bear = false;
  bool reverse_pig = false;
  float speed_bear;
  float speed_bird;
  float speed_pig;
  float diag_bear;
  float diag_pig;
  float diag_bird;

  int x_min =0;
  int x_max =0;
  int y_min =0;
  int y_max =0;

  int score = 0;

};

#endif // WHACKAMOLESFML_GAME_H
