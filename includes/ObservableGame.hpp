//
// ObservableGame.hpp for arcade in /home/benito/rendu/cpp/cpp_arcade
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Wed Mar 29 19:15:55 2017 benito
// Last update Wed Mar 29 20:06:38 2017 Anthony
//

#ifndef OBSERVABLEGAME_HPP
# define OBSERVABLEGAME_HPP

#include "Observable.hpp"

class		ObservableGame : public Observable
{
protected:
  State				_state;
public:
  void				setState(State const &);
  State const&			getState() const;
};

#endif /* !OBSERVABLEGAME_HPP */
