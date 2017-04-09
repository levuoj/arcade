//
// Coords.cpp for Coords.cpp in /home/tvigier/cpp_arcade
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Fri Mar 24 14:51:03 2017 thomas vigier
// Last update Sun Apr  9 22:15:48 2017 benito
//

#include "Coords.hpp"

Coords::Coords(int x, int y) : _x(x), _y(y) {}

Coords::Coords() {}

int	Coords::getX() const
{
  return (_x);
}

int	Coords::getY() const
{
  return (_y);
}

bool	Coords::operator==(const Coords &other) const
{
  return (_x == other._x && _y == other._y);
}
