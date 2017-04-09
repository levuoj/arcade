//
// Snake.cpp for  in /home/anthony/rendu/cpp/cpp_arcade/sources/src_nibbler
//
// Made by Anthony Jouvel
// Login   <anthony.jouvel@epitech.eu>
//
// Started on  Wed Apr  5 12:13:41 2017 Anthony Jouvel
// Last update Sun Apr  9 20:47:04 2017 Anthony Jouvel
//

#include "Snake.hpp"
#include "ArcadeCentipede.hpp"

Snake::Snake(int x, int y)
{
  for (int i = x; i != x - 8; --i)
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
  map[_body.back()] = ArcadeCentipede::getElementByChar(' ');
  map[_body.front()] = ArcadeCentipede::getElementByChar('~');
  for (int i = _body.size() - 1; i > 0; --i)
    {
      _body[i] = _body[i - 1];
    }
  switch (_dir) {
  case Snake::RIGHT :
    _body.front().first += 1;
    map[_body.front()] = ArcadeCentipede::getElementByChar('>');
    break;
  case Snake::LEFT :
    _body.front().first -= 1;
    map[_body.front()] = ArcadeCentipede::getElementByChar('<');
    break;
  case Snake::UP :
    _body.front().second -= 1;
    map[_body.front()] = ArcadeCentipede::getElementByChar('^');
    break;
  case Snake::DOWN :
    _body.front().second += 1;
    map[_body.front()] = ArcadeCentipede::getElementByChar('v');
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

int			Snake::getTailX() const
{
  return (_body.back().first);
}

int			Snake::getTailY() const
{
  return (_body.back().second);
}

void			Snake::loseTail()
{
  _body.pop_back();
}

int			Snake::getSize() const
{
  return (_body.size());
}
