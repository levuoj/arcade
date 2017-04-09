//
// DlLoader.hpp for DlLoader.hpp in /home/vigier_t/cpp_arcade/test/ex3
// 
// Made by thomas vigier
// Login   <vigier_t@epitech.net>
// 
// Started on  Mon Mar 20 17:44:38 2017 thomas vigier
// Last update Wed Apr  5 20:22:05 2017 benito
//

#ifndef DLLOADER_HPP_
# define DLLOADER_HPP_

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <dlfcn.h>
#include <vector>
#include <utility>
#include <memory>
#include "ILibraries.hpp"
#include "IGames.hpp"

class			DLLoader
{
public:
  static const std::string	ENTRY_POINT;
  static const std::string	PATH_LIBS;
  static const std::string	PATH_GAMES;
  static const std::string	BAD_LIB;
private:
  void							*_lib;
  void							*_game;
  unsigned int						_libIdx;
  std::vector<std::pair<std::string, std::string>>	_libraries;
  std::vector<std::pair<std::string, std::string>>	_games;

public:

  DLLoader(); // FILL BOTH VECTORS
  ~DLLoader();

  ILibraries	*loadLibrary(std::string const&); // RETURN AN INSTANCE OF LIB
  IGames	*loadGame(std::string const&); // RETURN AN INSTANCE OF GAME

  std::vector<std::pair<std::string, std::string>> const&	getLibraries() const;
  std::vector<std::pair<std::string, std::string>> const&	getGames() const;

  int		getLibIdx() const;

  void		closeLib();
  void		closeGame();

private:
  template <typename T>
  T			createInstance(void *);
  void			*openLib(const char *);
};

#endif // DLLOADER_HPP_
