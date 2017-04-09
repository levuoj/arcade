//
// IGames.hpp for  in /home/anthony/rendu/cpp/cpp_arcade
//
// Made by Anthony Jouvel
// Login   <anthony.jouvel@epitech.eu>
//
// Started on  Sat Mar 25 17:53:56 2017 benito
// Last update Sun Apr  9 13:20:42 2017 thomas vigier
//

#ifndef IGAMES_HPP
# define IGAMES_HPP

#include "IManageKey.hpp"
#include "AObserver.hpp"
#include "ObservableGame.hpp"
#include "IManageKey.hpp"
#include "AObserver.hpp"

class			IGames : public ObservableGame
{
public:
  enum gameState
    {
      FINISHED,
      PLAYING
    };
  virtual		~IGames() {};
  virtual gameState	manageKey(ObservableKey::Keys) = 0;
};

#endif /* !IGAMES_HPP */
