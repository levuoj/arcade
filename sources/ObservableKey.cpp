//
// ObservableKey.cpp for ObservableKey in /home/pashervz/Epitech/C++/Arcade/cpp_arcade/header
// 
// Made by Pashervz
// Login   <paul.julien@epitech.eu>
// 
// Started on  Sat Apr  1 18:45:59 2017 Pashervz
// Last update Thu Apr  6 14:37:58 2017 benito
//

#include "ObservableKey.hpp"

ObservableKey::ObservableKey() : _key(ObservableKey::Unknown), _isFinished(false)
{}

ObservableKey::Keys	ObservableKey::getKey() const
{
  return (_key);
}

bool			ObservableKey::isFinished() const
{
  return (_isFinished);
}

void			ObservableKey::finish()
{
  _isFinished = true;
}
