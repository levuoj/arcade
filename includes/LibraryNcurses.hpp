//
// LibraryNcurses.hpp for arcade in /home/anthony/rendu/cpp/cpp_arcade/sources/src_ncurses
// 
// Made by Anthony
// Login   <anthony.jouvel@epitech.eu>
// 
// Started on  Fri Mar 24 15:27:11 2017 Anthony
// Last update Tue Apr  4 18:10:47 2017 benito
//

#ifndef LIBRARYNCURSES_HPP
# define LIBRARYNCURSES_HPP

#include <ncurses.h>
#include <unistd.h>
#include "ILibraries.hpp"
#include "State.hpp"
#include "ManageKeyNcurse.hpp"

class				LibraryNcurses : public ILibraries
{
private:
  WINDOW			*_board;
  int				_maxRow;
  int				_maxCol;

  virtual void			display(State const&);
  virtual void			displayMap(State const&);
  virtual void			displayScore(State const&);
  virtual void			displayTimer(State const&);
  virtual void			displayLife(State const&);
  virtual void			displayName(State const&);
  virtual IManageKey		*getManager() const;
  //attention const
public:
  LibraryNcurses();
  virtual			~LibraryNcurses();
  virtual void			actualize(Observable const &);
};

# endif /* !LIBRARYNCURSES_HPP */
