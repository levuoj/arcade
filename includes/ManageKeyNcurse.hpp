//
// ManageKeyNcurse.hpp for arcade in /home/benito/rendu/cpp/cpp_arcade
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Sun Apr  2 17:06:18 2017 benito
// Last update Sun Apr  9 22:09:05 2017 benito
//

#ifndef _MANAGE_KEY_NCURSE_HPP_
# define _MANAGE_KEY_NCURSE_HPP_

#include <ncurses.h>
#include "IManageKey.hpp"

class		ManageKeyNcurse : public IManageKey
{
protected:
  WINDOW	*_win;
public:
  virtual void	catchKey();

  ManageKeyNcurse(WINDOW *);
  virtual	~ManageKeyNcurse() {};
};

# endif // _MANAGE_KEY_NCURSE_HPP_
