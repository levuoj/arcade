//
// Observable.cpp for Observable.cpp in /home/tvigier/cpp_arcade
// 
// Made by thomas vigier
// Login   <thomas.vigier@epitech.eu>
// 
// Started on  Mon Mar 27 16:12:21 2017 thomas vigier
// Last update Sun Apr  9 00:40:41 2017 benito
//

#include "Observable.hpp"
#include "AObserver.hpp"

Observable::Observable() : _observer(NULL)
{}

void		Observable::notify()
{
  if (_observer)
    _observer->actualize(*this);
}

void		Observable::setObserver(AObserver *ob)
{
  _observer = ob;
}
