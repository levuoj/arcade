//
// State.cpp for State.cpp in /home/anthony/rendu/cpp/cpp_arcade
//
// Made by Anthony
// Login   <anthony.jouvel@epitech.eu>
//
// Started on  Mon Mar 27 13:41:06 2017 Anthony
// Last update Sun Apr  9 22:15:35 2017 benito
//

#include "State.hpp"

State::State() {}

State::State(int t, int s, int l, Coords const& mS, std::string const& n) : _time(t), _score(s), _life(l), _mapSize(mS), _name(n)
{}

State::~State() {}

std::unordered_map<std::pair<int, int>, Element, pairHash>const&	State::getMap() const
{
  return (_map);
}

int					State::getTime() const
{
  return (_time);
}

int					State::getScore() const
{
  return (_score);
}

int					State::getLife() const
{
  return (_life);
}

std::string const&			State::getName() const
{
  return (_name);
}

Coords const&				State::getMapSize() const
{
  return (_mapSize);
}

void					State::setMap(std::unordered_map<std::pair<int, int>, Element, pairHash> map)
{
  _map = map;
}

void					State::setTime(int time)
{
  _time = time;
}

void					State::setScore(int score)
{
  _score = score;
}

void					State::setName(std::string const& name)
{
  _name = name;
}

void					State::setLife(int life)
{
  _life = life;
}

void					State::setMapSize(Coords const& max)
{
  _mapSize = max;
}
