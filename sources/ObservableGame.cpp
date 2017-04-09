//
// ObservableGame.cpp for arcade in /home/benito/rendu/cpp/cpp_arcade
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Wed Mar 29 19:46:13 2017 benito
// Last update Wed Mar 29 20:26:23 2017 Anthony
//

#include "ObservableGame.hpp"

State const& ObservableGame::getState() const
{
  return (_state);
}

void         ObservableGame::setState(State const &state)
{
  _state = state;
}
