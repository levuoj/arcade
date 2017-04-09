//
// Snake.cpp for  in /home/anthony/rendu/cpp/cpp_arcade/sources/src_nibbler
//
// Made by Anthony Jouvel
// Login   <anthony.jouvel@epitech.eu>
//
// Started on  Wed Apr  5 12:13:41 2017 Anthony Jouvel
// Last update Sun Apr  9 01:47:26 2017 benito
//

#include "Snake.hpp"
#include "ArcadeNibbler.hpp"

Snake::Snake(int x, int y)
{
  for (int i = x; i != x - 4; --i)
    {
      _body.push_back(std::pair<int, int>(i, y));
    }
  _dir = Snake::RIGHT;
}

Snake::~Snake()
{}

std::vector<std::pair<int, int>> const&	Snake::getBody() const
{
  return (_body);
}

void			Snake::move(std::unordered_map<std::pair<int, int>, Element, pairHash>& map)
{
  map[_body.back()] = ArcadeNibbler::getElementByChar(' ');
  map[_body.front()] = ArcadeNibbler::getElementByChar('~');
  for (int i = _body.size() - 1; i > 0; --i)
    {
      _body[i] = _body[i - 1];
    }
  switch (_dir) {
  case Snake::RIGHT :
    _body.front().first += 1;
    map[_body.front()] = ArcadeNibbler::getElementByChar('>');
    break;
  case Snake::LEFT :
    _body.front().first -= 1;
    map[_body.front()] = ArcadeNibbler::getElementByChar('<');
    break;
  case Snake::UP :
    _body.front().second -= 1;
    map[_body.front()] = ArcadeNibbler::getElementByChar('^');
    break;
  case Snake::DOWN :
    _body.front().second += 1;
    map[_body.front()] = ArcadeNibbler::getElementByChar('v');
    break;
  }
}

std::pair<int, int>	Snake::getPairByDir(std::pair<int, int> const& p, Snake::Direction dir) const
{
  if (dir == Snake::LEFT)
    return (std::pair<int, int>(p.first - 1, p.second));
  else if (dir == Snake::UP)
    return (std::pair<int, int>(p.first, p.second - 1));
  else if (dir == Snake::DOWN)
    return (std::pair<int, int>(p.first, p.second + 1));
  return (std::pair<int, int>(p.first + 1, p.second));
}

Action	Snake::grow(std::unordered_map<std::pair<int, int>, Element, pairHash>& map)
{
  std::pair<int, int>	tl(_body.back());
  std::pair<int, int>	ntl;

  if (map[getPairByDir(tl, Snake::LEFT)].getType() == arcade::TileType::EMPTY)
    ntl = getPairByDir(tl, Snake::LEFT);
  else if (map[getPairByDir(tl, Snake::RIGHT)].getType() == arcade::TileType::EMPTY)
    ntl = getPairByDir(tl, Snake::RIGHT);
  else if (map[getPairByDir(tl, Snake::UP)].getType() == arcade::TileType::EMPTY)
    ntl = getPairByDir(tl, Snake::UP);
  else if (map[getPairByDir(tl, Snake::UP)].getType() == arcade::TileType::EMPTY)
    ntl = getPairByDir(tl, Snake::UP);
  else
    return (Action::LOST);
  map[ntl] = ArcadeNibbler::getElementByChar('~');
  _body.push_back(ntl);
  return (Action::ATE);
}

void			Snake::setDirection(Snake::Direction dir)
{
  _dir = dir;
}

Snake::Direction const&	Snake::getDirection() const
{
  return (_dir);
}

int			Snake::getHeadX() const
{
  return (_body.front().first);
}

int			Snake::getHeadY() const
{
  return (_body.front().second);
}
