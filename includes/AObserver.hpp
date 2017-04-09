//
// AObserver.hpp for  in /home/anthony/rendu/cpp/cpp_arcade/sources
//
// Made by Anthony Jouvel
// Login   <anthony.jouvel@epitech.eu>
//
// Started on  Tue Apr  4 19:06:07 2017 Anthony Jouvel
// Last update Sun Apr  9 13:30:19 2017 thomas vigier
//

#ifndef AOBSERVER_HPP_
# define AOBSERVER_HPP_

class Observable;

class AObserver
{
public:
  virtual void		actualize(Observable const &) = 0;
  virtual		~AObserver() {}
};

#endif // AOBSERVER_HPP_
