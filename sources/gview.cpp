#include "gview.h"

GView::GView() {
  window_ = new sf::RenderWindow(sf::VideoMode(screen_x_, screen_y_), "My window");
  window_->setVerticalSyncEnabled(true);
  window_->setFramerateLimit(60);

  auto checker = [&]() {
    if (!rabbit_.loadFromFile("../../images/rabbit.png") ||
        !shead_up_.loadFromFile("../../images/shead_up.png") ||
        !shead_down_.loadFromFile("../../images/shead_down.png") ||
        !shead_left_.loadFromFile("../../images/shead_left.png") ||
        !shead_right_.loadFromFile("../../images/shead_right.png") ||
        !sbody_.loadFromFile("../../images/snake_body.png"))
      return true;

    return false;
  };

  if (checker()) {
    delete window_;
    exit(-1);
  }
  rabbit_.setSmooth(true);
  shead_down_.setSmooth(true);
  shead_left_.setSmooth(true);
  shead_right_.setSmooth(true);
  shead_up_.setSmooth(true);
  sbody_.setSmooth(true);
}

GView::~GView() {
  delete window_;
}

void GView::draw() {
  drawBox();
}

void GView::main_loop() {
  Game process;
  Snake snake1({screen_x_ / (2 * szSprite_), screen_y_ / (2 * szSprite_)});
  Snake snake2({screen_x_ / (2 * szSprite_), screen_y_ / (2 * szSprite_) + 1});
  process.addRabbits(nRabbits_, screen_y_ / szSprite_, screen_x_ / szSprite_ - 4);
  using namespace std::chrono_literals;
  auto timer = std::chrono::steady_clock::now();

  while (window_->isOpen()) {
    sf::Event event;
    while (window_->pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window_->close();
          break;
        case sf::Event::KeyPressed:
          switch (event.key.code) {
            case sf::Keyboard::Q:
              window_->close();
              break;
            case sf::Keyboard::W:
              snake1.setDirection(UP);
              break;
            case sf::Keyboard::S:
              snake1.setDirection(DOWN);
              break;
            case sf::Keyboard::A:
              snake1.setDirection(LEFT);
              break;
            case sf::Keyboard::D:
              snake1.setDirection(RIGHT);
              break;
            case sf::Keyboard::I:
              snake2.setDirection(UP);
              break;
            case sf::Keyboard::K:
              snake2.setDirection(DOWN);
              break;
            case sf::Keyboard::J:
              snake2.setDirection(LEFT);
              break;
            case sf::Keyboard::L:
              snake2.setDirection(RIGHT);
              break;
            default:
              break;
          }

        default:
          break;
      }
    }

    window_->clear();
    drawBox();
    drawRabbits(process);
    drawSnake(snake1);
    drawSnake(snake2);
    if (std::chrono::steady_clock::now() >= timer + 200ms) {
      snake1.snakestep(process, snake2, screen_y_ / szSprite_, screen_x_ / szSprite_ - 4);
      snake2.snakestep(process, snake1, screen_y_ / szSprite_, screen_x_ / szSprite_ - 4);
      timer = std::chrono::steady_clock::now();
    }
    window_->display();
  }
}

void GView::drawBox() {
  sf::Vector2u size = window_->getSize();
  size = {static_cast<unsigned int>(size.x - size.x % szSprite_),
          static_cast<unsigned int>(size.y - size.y % szSprite_)};
  sf::RectangleShape frame({float(size.x), float(size.y)});
  frame.move(szSprite_, szSprite_);
  frame.setFillColor(sf::Color::Magenta);
  sf::RectangleShape frameIn({float(size.x - 3 * szSprite_), float(size.y - 3 * szSprite_)});
  frameIn.setFillColor(sf::Color::Black);
  frameIn.move(2 * szSprite_, 2 * szSprite_);
  window_->draw(frame);
  window_->draw(frameIn);
}

void GView::drawSnake(Snake& snake) {
  auto arr = snake.getcoord();
  auto dir = snake.getDirection();

  sf::RectangleShape rectangle(sf::Vector2f(szSprite_, szSprite_));

  for (size_t i = 0; i < arr.size(); ++i) {
    if (i == 0) {
      switch (dir) {
        case UP:
          rectangle.setTexture(&shead_up_);
          break;
        case DOWN:
          rectangle.setTexture(&shead_down_);
          break;
        case LEFT:
          rectangle.setTexture(&shead_left_);
          break;
        case RIGHT:
          rectangle.setTexture(&shead_right_);
          break;

        default:
          break;
      }
    } else {
      rectangle.setTexture(&sbody_);
    }
    rectangle.setPosition(sf::Vector2f(arr[i].first * szSprite_, arr[i].second * szSprite_));
    window_->draw(rectangle);
  }
}

void GView::drawRabbits(Game& game) {
  sf::RectangleShape rectangle(sf::Vector2f(szSprite_, szSprite_));
  rectangle.setTexture(&rabbit_);
  auto arr = game.getcoords();

  for (auto el : arr) {
    rectangle.setPosition(el.first * szSprite_, el.second * szSprite_);
    window_->draw(rectangle);
  }
}