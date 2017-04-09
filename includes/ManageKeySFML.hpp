//
// ManageKeySFML.hpp for ManageKeySFML in /home/tvigier/cpp_arcade
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Tue Apr  4 18:42:47 2017 thomas vigier
// Last update Sun Apr  9 22:08:21 2017 benito
//

#ifndef _MANAGE_KEY_SFML_HPP_
# define _MANAGE_KEY_SFML_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "IManageKey.hpp"

class           ManageKeySFML : public IManageKey
{
protected:
  sf::RenderWindow		*_win;
public:
  virtual void  catchKey();

  ManageKeySFML(sf::RenderWindow*);
  virtual       ~ManageKeySFML() {}
};

# endif // _MANAGE_KEY_SFML_HPP_
