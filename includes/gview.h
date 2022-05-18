#ifndef GVIEW_H
#define GVIEW_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <chrono>
#include <iostream>


#include "view.h"
#include "model.h"
#include "game.h"

class GView final : public View {
 public:
  GView();

  ~GView() override;
  void main_loop() override;

 private:
  size_t screen_x_ = 1980;
  size_t screen_y_ = 1020;
  size_t nRabbits_ = 50;
  size_t szSprite_ = 20;
  sf::RenderWindow* window_;

  std::vector<sf::Texture>* textures_;

  sf::Texture rabbit_;
  sf::Texture shead_up_;
  sf::Texture shead_down_;
  sf::Texture shead_left_;
  sf::Texture shead_right_;
  sf::Texture sbody_;

  virtual void draw();
  void drawBox();
  void drawSnake(Snake& snake);
  void drawRabbits(Game& game);
};

#endif  // GVIEW_H