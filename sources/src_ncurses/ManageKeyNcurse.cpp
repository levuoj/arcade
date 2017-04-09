//
// ManageKeyNcurse.cpp for arcade in /home/benito/rendu/cpp/cpp_arcade
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Sun Apr  2 17:10:35 2017 benito
// Last update Sun Apr  9 22:10:02 2017 benito
//

#include <ncurses.h>
#include "ManageKeyNcurse.hpp"

ManageKeyNcurse::ManageKeyNcurse(WINDOW *win) : _win(win)
{
  keypad(win,TRUE);
  halfdelay(1);
}

void		ManageKeyNcurse::catchKey()
{
  char		c;

  while (!_isFinished)
    {
      c = wgetch(_win);
      switch (c) {
      case 2:
	_key = ObservableKey::Down;
	break;
      case 3:
	_key = ObservableKey::Up;
	break;
      case 4:
	_key = ObservableKey::Left;
	break;
      case 5:
	_key = ObservableKey::Right;
	break;
      case 10:
	_key = ObservableKey::Return;
	break;
      case 32:
	_key = ObservableKey::Space;
	break;
      case 27:
	_key = ObservableKey::Escape;
	break;
      case '2':
	_key = ObservableKey::Num2;
	break;
      case '3':
	_key = ObservableKey::Num3;
	break;
      case '4':
	_key = ObservableKey::Num4;
	break;
      case '5':
	_key = ObservableKey::Num5;
	break;
      case '6':
	_key = ObservableKey::Num6;
	break;
      case '7':
	_key = ObservableKey::Num7;
	break;
      case '8':
	_key = ObservableKey::Num8;
	break;
      case '9':
	_key = ObservableKey::Num9;
	break;
      default:
	_key = ObservableKey::Unknown;
	break;
      }
      notify();
    }
}
