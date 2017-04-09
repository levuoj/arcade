//
// DLLoader.cpp for arcade in /home/benito/rendu/cpp/cpp_arcade
// 
// Made by benito
// Login   <benoit.linsey@epitech.eu>
// 
// Started on  Sat Mar 25 18:42:37 2017 benito
// Last update Sun Apr  9 22:20:23 2017 benito
//

#include <stdexcept>
#include "DLLoader.hpp"

const std::string	DLLoader::ENTRY_POINT = "entryPoint";
const std::string	DLLoader::PATH_LIBS = "./lib/";
const std::string	DLLoader::PATH_GAMES = "./games/";
const std::string	DLLoader::BAD_LIB = "Unknown library";

DLLoader::DLLoader() : _lib(NULL), _game(NULL)
{
  DIR		*Dir = opendir(DLLoader::PATH_LIBS.c_str());
  struct dirent	*DirEntry;
  std::string	name;

  while ((DirEntry=readdir(Dir)) != NULL)
    {
      name = std::string(DirEntry->d_name);
      if (DirEntry->d_type != DT_DIR && name.find(".so") != std::string::npos)
	_libraries.push_back(std::make_pair(name.substr(0, name.length() - 3),
					    DLLoader::PATH_LIBS + DirEntry->d_name));
    }
  closedir(Dir);
  Dir = opendir(DLLoader::PATH_GAMES.c_str());
  while ((DirEntry=readdir(Dir)) != NULL)
    {
      name = std::string(DirEntry->d_name);
      if (DirEntry->d_type != DT_DIR &&
	  name.find(".so") != std::string::npos)
	_games.push_back(std::make_pair(name.substr(11, name.length() - 14),
					DLLoader::PATH_GAMES + DirEntry->d_name));
    }
}

DLLoader::~DLLoader()
{
  if (_lib)
    closeLib();
  if (_game)
    closeGame();
}

void		*DLLoader::openLib(const char *name)
{
  void			*dlhandle;
  char			*err;

  dlerror();
  dlhandle = dlopen(name, RTLD_LAZY);
  err = dlerror();
  if (dlhandle == NULL)
    {
      std::cerr << err << std::endl;
      throw std::runtime_error("An error occured when loading " + std::string(name));
    }
  return (dlhandle);
}

void		DLLoader::closeLib()
{
  dlclose(_lib);
  _lib = NULL;
}

void		DLLoader::closeGame()
{
  dlclose(_game);
  _game = NULL;
}

int		DLLoader::getLibIdx() const
{
  return (_libIdx);
}

ILibraries*     DLLoader::loadLibrary(std::string const& libName)
{
  if (_lib != NULL)
    closeLib();
  _libIdx = 0;
  for (auto const& it : _libraries)
    {
      if (it.second == libName)
	{
	  _lib = openLib(libName.c_str());
	  return (createInstance<ILibraries *>(_lib));
	}
      _libIdx++;
    }
  throw std::runtime_error(DLLoader::BAD_LIB);
  return NULL;
}

IGames*         DLLoader::loadGame(std::string const& gameName)
{
  if (_game != NULL)
    closeGame();
  for (auto const& it : _games)
    {
      if (it.second == gameName)
	{
	  _game = openLib(gameName.c_str());
	  return (createInstance<IGames *>(_game));
	}
    }
  throw std::runtime_error(DLLoader::BAD_LIB);
  return NULL;
}

std::vector<std::pair<std::string, std::string>> const& DLLoader::getLibraries() const
{
  return (_libraries);
}

std::vector<std::pair<std::string, std::string>> const& DLLoader::getGames() const
{
  return (_games);
}

template <typename T>
T			DLLoader::createInstance(void *dlhandle)
{
  return (reinterpret_cast<T (*)()>(dlsym(dlhandle, DLLoader::ENTRY_POINT.c_str()))());
}
