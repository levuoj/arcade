//
// BugBlaster.cpp for BugBlaster.cpp in /home/tvigier/cpp_arcade
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Fri Apr  7 09:37:04 2017 thomas vigier
// Last update Sun Apr  9 22:14:28 2017 benito
//

#include "BugBlaster.hpp"

BugBlaster::BugBlaster()
{
  _pos = std::pair<int, int>(15, 28);
}

BugBlaster::BugBlaster(std::pair<int, int>) : _pos(std::pair<int, int>(15, 28))
{}

BugBlaster::~BugBlaster()
{}

std::pair<int, int> const &	BugBlaster::getPos() const
{
  return (_pos);
}

void		BugBlaster::setPos(std::pair<int, int> const& other)
{
  _pos = other;
}
