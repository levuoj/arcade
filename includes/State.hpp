//
// State.hpp for arcade in /home/zawadi_p/rendu/CPP/cpp_arcade/header
//
// Made by Pierre Zawadil
// Login   <pierre.zawadil@epitech.eu>
//
// Started on  Thu Mar 23 15:35:22 2017 Pierre Zawadil
// Last update Sun Apr  9 13:15:45 2017 thomas vigier
//

#ifndef STATE_HPP
# define STATE_HPP

#include <unordered_map>
#include <utility>
#include "Element.hpp"
#include "Coords.hpp"

struct pairHash
{
  template <typename T, typename U>
  std::size_t operator() (const std::pair<T, U> &p) const
  {
    auto hash1 = std::hash<T>{}(p.first);
    auto hash2 = std::hash<U>{}(p.second);

    return (hash1 ^ hash2);
  }
};

class						State
{
private:
  std::unordered_map<std::pair<int, int>, Element, pairHash>	_map;
  int						_time;
  int						_score;
  int						_life;
  Coords					_mapSize;
  std::string					_name;
public:
  std::unordered_map<std::pair<int, int>, Element, pairHash> const&	getMap() const;
  int						getTime() const;
  int						getScore() const;
  int						getLife() const;
  Coords const&					getMapSize() const;
  std::string const&				getName() const;
  void						setMap(std::unordered_map<std::pair<int, int>, Element, pairHash>);
  void						setTime(int);
  void						setScore(int);
  void						setLife(int);
  void						setMapSize(Coords const&);
  void						setName(std::string const&);
  State();
  State(int, int, int, Coords const&, std::string const&);
  ~State();
};

#endif /* !STATE_HPP */
