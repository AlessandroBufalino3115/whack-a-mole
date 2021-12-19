#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window): window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
}

bool Game::init()
{
  in_menu = true;

  sf::Clock clock;

#pragma region BackgroundSetting
  if (!background_texture.loadFromFile("Data/Images/background.png"))
  {
    std::cout << "background texture did not load \n";
  }
  background.setTexture(background_texture);

  if (!bird_texture.loadFromFile("Data/Images/bird.png"))
  {
    std::cout << "bird texture did not load \n";
  }
  bird.setTexture(bird_texture);

  if (!bear_texture.loadFromFile("Data/Images/bear.png"))
  {
    std::cout << "bear texture did not load \n";
  }
  bear.setTexture(bear_texture);

  if (!pig_texture.loadFromFile("Data/Images/pig.png"))
  {
    std::cout << "bear texture did not load \n";
  }
  pig.setTexture(pig_texture);
  bird.setScale(0.5f,0.5f);
  pig.setScale(0.6f,0.6f);
  bear.setScale(0.5f,0.5f);

  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }
#pragma endregion

#pragma region menu_text
  menu_text.setString("             Welcome to Whack-a-mole."
                      "\nRules: hit the bird and bear but not the pig."
                      "\n   Get as may points you can in 60 seconds"
                      "\n             What would you like to do?");
  menu_text.setFont(font);
  menu_text.setCharacterSize(20);
  menu_text.setFillColor(sf::Color(255,255,255,128));
  menu_text.setPosition(
    window.getSize().x / 2 - menu_text.getGlobalBounds().width / 2,
    window.getSize().y / 10 - menu_text.getGlobalBounds().height / 2);
#pragma endregion menu_text

#pragma region play_option
  play_option.setString("   Play");
  play_option.setFont(font);
  play_option.setCharacterSize(20);
  play_option.setFillColor(sf::Color(255,255,255,128));
  play_option.setPosition(
    window.getSize().x / 2 - play_option.getGlobalBounds().width / 2 - window.getSize().x / 6,
    window.getSize().y / 4 - play_option.getGlobalBounds().height );
#pragma endregion play_option

#pragma region play_option
  quit_option.setString("   Quit");
  quit_option.setFont(font);
  quit_option.setCharacterSize(20);
  quit_option.setFillColor(sf::Color(255,255,255,128));
  quit_option.setPosition(
    window.getSize().x / 2 - quit_option.getGlobalBounds().width / 2 + window.getSize().x / 6 ,
    window.getSize().y / 4 - quit_option.getGlobalBounds().height );
#pragma endregion play_option

  return true;
}

void Game::update(float dt)
{
  sf::Time elapsed = clock.getElapsedTime();

  std::cout << elapsed.asSeconds() << std::endl;

#pragma region Timer
  timer.setString(std::to_string(elapsed.asSeconds()));
  timer.setFont(font);
  timer.setCharacterSize(20);
  timer.setFillColor(sf::Color(255,255,255,255));
  timer.setPosition(
    window.getSize().x / 2 - timer.getGlobalBounds().width / 2 + window.getSize().x / 6 ,0 );
#pragma endregion

#pragma  region ScoreText
  std::string ScoreCounter = "Score: " + std::to_string(score);
  Score.setString(ScoreCounter);
  Score.setFont(font);
  Score.setCharacterSize(30);
  Score.setPosition(100 ,0);
#pragma  endregion

#pragma region MovementBird1
  if ((bird.getPosition().x > (window.getSize().x - bird.getGlobalBounds().width)) || (bird.getPosition().x < 0))
  {
    reverse_bird = !reverse_bird;
  }

  if ((bird.getPosition().y > (window.getSize().y - bird.getGlobalBounds().height)) || (bird.getPosition().y < 0))
  {
    reverse_bird = !reverse_bird;
  }

  if (reverse_bird)
  {
    bird.move(-1.0f * speed_bird * dt, diag_bird);
    bird.setTextureRect(sf::IntRect(bird.getLocalBounds().width, 0, -bird.getLocalBounds().width, bird.getLocalBounds().height));
  }
  else
  {
    bird.move(1.0f * speed_bird * dt, -diag_bird);
    bird.setTextureRect(sf::IntRect(0, 0, bird.getLocalBounds().width, bird.getLocalBounds().height));
  }
#pragma endregion

#pragma region MovementBear
  if ((bear.getPosition().x > (window.getSize().x - bear.getGlobalBounds().width)) ||
      (bear.getPosition().x < 0))
  {
    reverse_bear = !reverse_bear;
  }

  if ((bear.getPosition().y > (window.getSize().y - bear.getGlobalBounds().height)) || (bear.getPosition().y < 0))
  {
    reverse_bear = !reverse_bear;
  }

  if (reverse_bear)
  {
    bear.move(-1.0f * speed_bear * dt, diag_bear);
    bear.setTextureRect(sf::IntRect(bear.getLocalBounds().width, 0, -bear.getLocalBounds().width, bear.getLocalBounds().height));
  }
  else
  {
    bear.move(1.0f * speed_bear * dt, -diag_bear);
    bear.setTextureRect(sf::IntRect(0, 0, bear.getLocalBounds().width, bear.getLocalBounds().height));
  }
#pragma endregion

#pragma region MovementPig
  if ((pig.getPosition().x > (window.getSize().x - pig.getGlobalBounds().width)) ||
      (pig.getPosition().x < 0))
  {
    reverse_pig = !reverse_pig;
  }

  if ((pig.getPosition().y > (window.getSize().y - pig.getGlobalBounds().height)) || (pig.getPosition().y < 0))
  {
    reverse_pig = !reverse_pig;
  }

  if (reverse_pig)
  {
    pig.move(-1.0f * speed_pig * dt, diag_pig);
    pig.setTextureRect(sf::IntRect(pig.getLocalBounds().width, 0, -bear.getLocalBounds().width, pig.getLocalBounds().height));
  }
  else
  {
    pig.move(1.0f * speed_pig * dt, -diag_pig);
    pig.setTextureRect(sf::IntRect(0, 0, bear.getLocalBounds().width, pig.getLocalBounds().height));
  }
#pragma endregion

  if (elapsed.asSeconds() >= 15)
  {
    in_menu = true;
  }

}

void Game::render()
{
  if (in_menu)
  {
    window.draw(menu_text);
    window.draw(play_option);
    window.draw(quit_option);

    if (score != 0)
    {
      window.draw(Score);
    }
  }
  else
  {
    window.draw(background);
    window.draw(Score);
    window.draw(timer);
    spawn();
  }

  if (draw_bird && !in_menu)
  {
    window.draw(bird);
  }
  if (draw_bear && !in_menu)
  {
    window.draw(bear);
  }
  if (draw_pig && !in_menu)
  {
    window.draw(pig);
  }
}


void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  //might have to make the collision check run on click and return the bird to then delete if we want to add multiple ones
  // check if in bounds of bird Sprite
  if (collisionCheck(click, bird))
  {
    score ++;
    draw_bird = false;
    Score.setFillColor(sf::Color(0,255,0,255));
  }

  if (collisionCheck(click, bear))
  {
    score ++;
    draw_bear = false;
    Score.setFillColor(sf::Color(0,255,0,255));
  }

  if (collisionCheck(click, pig))
  {
    score --;
    Score.setFillColor(sf::Color(255,0,0,255));
    draw_pig = false;
  }
}



void Game::keyPressed(sf::Event event)
{
  if ((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::Right))
  {
    play_selected = !play_selected;
    if (play_selected)
    {
      play_option.setString("> Play <");
      quit_option.setString("   Quit");
    }
    else
    {
      play_option.setString("   Play");
      quit_option.setString("> Quit <");
    }
  }
  else if (event.key.code == sf::Keyboard::Enter)
  {
    if (play_selected)
    {
      clock.restart();
      score = 0;
      draw_pig  = false;
      draw_bird = false;
      draw_bear = false;
      in_menu = false;
    }
    else
    {
      window.close();
    }
  }
}


















bool Game::collisionCheck(sf::Vector2i click, sf::Sprite sprite)
{
    x_max = sprite.getPosition().x + sprite.getGlobalBounds().width;
    x_min = sprite.getPosition().x;
    y_min = sprite.getPosition().y;
    y_max = sprite.getPosition().y + sprite.getGlobalBounds().height;

    if (((x_min < click.x) && (click.x < x_max)) && ((y_min < click.y) && (click.y < y_max)) )
    {
      return true;
    }

  return false;
}




void Game::spawn()
{

  if (!draw_bear && !draw_bird)
  {
    int enemies = rand() % 3 + 1;

    if (enemies == 1)
    {
      bird.setPosition(rand() % 400 + 1,rand() % 500 + 1);
      draw_bird  = true;
      speed_bird = rand() % 500 + 50;
      diag_bird  = rand() %  6 + -3;
    }
    else if (enemies == 2)
    {
      bird.setPosition(rand() % 400 + 1,rand() % 500 + 1);
      draw_bird  = true;
      speed_bird = rand() % 500 + 50;
      diag_bird  = rand() %  6 + -3;

      bear.setPosition(rand() % 400 + 1,rand() % 600 + 1);
      draw_bear = true;
      speed_bear = rand() % 500 + 50;
      diag_bear  = rand() % 6 + -3;
    }
    else if (enemies == 3)
    {
      bird.setPosition(rand() % 400 + 1,rand() % 500 + 1);
      draw_bird  = true;
      speed_bird = rand() % 500 + 50;
      diag_bird  = rand() %  6 + -3;

      if (!draw_pig)
      {
        pig.setPosition(rand() % 400 + 1,rand() % 600 + 1);
        draw_pig = true;
        speed_pig = rand() % 500 + 50;
        diag_pig = rand() %  6 + -3;
      }
      bear.setPosition(rand() % 400 + 1,rand() % 600 + 1);
      draw_bear = true;
      speed_bear = rand() % 500 + 50;
      diag_bear   = rand() % 6 + -3;
    }
  }
}
