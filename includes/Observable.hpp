//
// Observable.hpp for  in /home/anthony/rendu/cpp/cpp_arcade/sources
//
// Made by Anthony Jouvel
// Login   <anthony.jouvel@epitech.eu>
//
// Started on  Tue Apr  4 19:07:11 2017 Anthony Jouvel
// Last update Tue Apr  4 19:07:19 2017 Anthony Jouvel
//

#ifndef OBSERVABLE_HPP_
# define OBSERVABLE_HPP_

#include <memory>
#include "State.hpp"

#include "AObserver.hpp"

class		Observable
{
protected:
  AObserver	*_observer;
public:
  Observable();
  virtual ~Observable(){};

  void				notify();
  void				setObserver(AObserver *);
};

#endif // OBSERVABLE_HPP_
