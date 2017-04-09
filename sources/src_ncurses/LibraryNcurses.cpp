//
// LibraryNcurses.cpp for  in /home/anthony/rendu/cpp/cpp_arcade/sources/src_ncurses
//
// Made by Anthony
// Login   <anthony.jouvel@epitech.eu>
//
// Started on  Fri Mar 24 16:31:08 2017 Anthony
// Last update Sun Apr  9 22:10:31 2017 benito
//

#include "LibraryNcurses.hpp"
#include "ManageKeyNcurse.hpp"

LibraryNcurses::LibraryNcurses()
{
  initscr();
  cbreak();
  curs_set(0);
  start_color();

  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);

  init_pair(11, COLOR_RED, COLOR_RED);
  init_pair(12, COLOR_GREEN, COLOR_GREEN);
  init_pair(13, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(14, COLOR_BLUE, COLOR_BLUE);
  init_pair(15, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(16, COLOR_CYAN, COLOR_CYAN);
  init_pair(17, COLOR_WHITE, COLOR_WHITE);

  _board = subwin(stdscr, 0, 0, 0, 0);
}

LibraryNcurses::~LibraryNcurses()
{
  werase(_board);
  endwin();
}

void			LibraryNcurses::display(State const& state)
{
  wclear(_board);
  clear();
  getmaxyx(stdscr, _maxRow, _maxCol);
  _board = subwin(_board,
		  state.getMapSize().getX() + 2,
		  state.getMapSize().getY() + 2,
		  (_maxRow - state.getMapSize().getX() + 1) / 2,
		  (_maxCol - state.getMapSize().getY() + 1) / 2);
  displayMap(state);
  displayScore(state);
  displayTimer(state);
  displayLife(state);
  displayName(state);
  wrefresh(_board);
  refresh();
}

void			LibraryNcurses::displayMap(State const& state)
{
  wattron(_board, COLOR_PAIR(4));
  wborder(_board, '|', '|', '-', '-', '-', '-', '-', '-');
  wattroff(_board, COLOR_PAIR(4));
  for (auto const& it : state.getMap())
    {
      wattron(_board, COLOR_PAIR(it.second.getColor()));
      mvwprintw(_board,
		it.first.second + 1,
		it.first.first + 1,
		"%s", it.second.getContent().c_str());
      wattroff(_board, COLOR_PAIR(it.second.getColor()));
    }
}

void			LibraryNcurses::displayScore(State const& state)
{
  if (state.getScore() >= 0)
    {
      attron(COLOR_PAIR(5));
      mvprintw((_maxRow - state.getMapSize().getX()) / 2 - 2,
	       (_maxCol - std::to_string(state.getScore()).size()) / 2 - 1,
	       "SCORE");
      mvprintw((_maxRow - state.getMapSize().getY()) / 2 - 1,
	       (_maxCol - std::to_string(state.getScore()).size()) / 2,
	       "%i", state.getScore());
      attroff(COLOR_PAIR(5));
    }
}

void			LibraryNcurses::displayTimer(State const& state)
{
  if (state.getTime() >= 0)
    {
      attron(COLOR_PAIR(1));
      mvprintw((_maxRow - std::to_string(state.getTime()).size()) / 2,
	       (_maxCol - state.getMapSize().getX()) / 2 + state.getMapSize().getY() + 4,
	       "TIMER");
      mvprintw(((_maxRow - std::to_string(state.getTime()).size()) / 2) + 1,
	       (_maxCol - state.getMapSize().getY()) / 2 + state.getMapSize().getY() + 4,
	       "%4i", state.getTime());
      attroff(COLOR_PAIR(1));
    }
}

void			LibraryNcurses::displayLife(State const& state)
{
  if (state.getLife() >= 0)
    {
      attron(COLOR_PAIR(2));
      mvprintw((_maxRow - state.getMapSize().getX()) / 2 + state.getMapSize().getY() + 4,
	       (_maxCol - (std::to_string(state.getLife()).size() + 8)) / 2,
	       "Lives : %i", state.getLife());
      attroff(COLOR_PAIR(2));
    }
}

void			LibraryNcurses::displayName(State const& state)
{
  if (state.getName().size() > 0)
    {
      attron(COLOR_PAIR(3));
      mvprintw(_maxRow / 2,
	       (_maxCol - state.getMapSize().getY()) / 2 -  state.getName().size() - 1,
	       "%s", state.getName().c_str());
      attroff(COLOR_PAIR(3));
    }
}

void			LibraryNcurses::actualize(Observable const &ob)
{
  display(static_cast<const ObservableGame&>(ob).getState());
}

IManageKey		*LibraryNcurses::getManager() const
{
  return (new ManageKeyNcurse(_board));
}

extern "C"
ILibraries		*entryPoint()
{
  return (new LibraryNcurses);
}
