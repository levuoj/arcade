//
// ManageKeySFML.cpp for Arcade in /home/tvigier/cpp_arcade
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Tue Apr  4 18:50:01 2017 thomas vigier
// Last update Sun Apr  9 22:15:15 2017 benito
//

#include "ManageKeySFML.hpp"

ManageKeySFML::ManageKeySFML(sf::RenderWindow *win) : _win(win)
{
}

void		ManageKeySFML::catchKey()
{
  sf::Event event;
  while (!_isFinished)
    {
      _key = ObservableKey::Unknown;
      while (_win->pollEvent(event))
      	{
	  if (event.type == sf::Event::KeyPressed)
	    {
	      switch (event.key.code) {
	      case sf::Keyboard::Down:
		_key = ObservableKey::Down;
		break;
	      case sf::Keyboard::Up:
		_key = ObservableKey::Up;
		break;
	      case sf::Keyboard::Left:
		_key = ObservableKey::Left;
		break;
	      case sf::Keyboard::Right:
		_key = ObservableKey::Right;
		break;
	      case sf::Keyboard::Return:
		_key = ObservableKey::Return;
		break;
	      case sf::Keyboard::Space:
		_key = ObservableKey::Space;
		break;
	      case sf::Keyboard::Escape:
		_key = ObservableKey::Escape;
		break;
	      case sf::Keyboard::Num2:
		_key = ObservableKey::Num2;
		break;
	      case sf::Keyboard::Num3:
		_key = ObservableKey::Num3;
		break;
	      case sf::Keyboard::Num4:
		_key = ObservableKey::Num4;
		break;
	      case sf::Keyboard::Num5:
		_key = ObservableKey::Num5;
		break;
	      case sf::Keyboard::Num8:
		_key = ObservableKey::Num8;
		break;
	      case sf::Keyboard::Num9:
		_key = ObservableKey::Num9;
		break;

	      default:
		_key = ObservableKey::Unknown;
		break;
	      }
	    }
	}
      notify();
    }
}
