//
// ILibraries.hpp for  in /home/anthony/rendu/cpp/cpp_arcade
// 
// Made by Anthony
// Login   <anthony.jouvel@epitech.eu>
// 
// Started on  Thu Mar 23 13:54:42 2017 Anthony
// Last update Tue Apr  4 18:10:25 2017 benito
//

# ifndef ILIBRARIES_HPP
# define ILIBRARIES_HPP

#include <memory>
#include "AObserver.hpp"
#include "ObservableGame.hpp"
#include "State.hpp"
#include "IManageKey.hpp"

class		ILibraries : public AObserver
{
  virtual void		display(State const&) = 0;

  virtual void		displayMap(State const&) = 0;
  virtual void		displayScore(State const&) = 0;
  virtual void		displayTimer(State const&) = 0;
  virtual void		displayLife(State const&) = 0;
  virtual void		displayName(State const&) = 0;
public:
  virtual IManageKey	*getManager() const = 0;
  virtual ~ILibraries() {};
};

# endif /* !ILIBRARIES_HPP */
