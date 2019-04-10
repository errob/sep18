//------------------------------------------------------------------------------
// CommandManager.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#ifndef COMMANDMANAGER_H_INCLUDED
#define COMMANDMANAGER_H_INCLUDED


#include <sstream>
#include <iterator>
#include <iostream>
#include <memory>

#include "Interface.h"

namespace Sep
{
  class Game;
  class Command;

  //----------------------------------------------------------------------------
  // Command Manager class
  // Class do manage commands
  //
  class CommandManager
  {
  private:

    //--------------------------------------------------------------------------
    // Reference to the Game
    //
    Game & game_;

    //--------------------------------------------------------------------------
    // Reference to the Interface of the Game
    //
    Interface & io_;

  public:

    //--------------------------------------------------------------------------
    // Constructor
    // @param io reference to interface
    // @param reference to the game
    //
    CommandManager(Interface &io, Game &game);


    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandManager() noexcept;


    //--------------------------------------------------------------------------
    // Deleted copy constructor
    //
    CommandManager(const CommandManager &original) = delete;


    //--------------------------------------------------------------------------
    // Deleted assignment operator
    //
    CommandManager &operator=(const CommandManager &original) = delete;


    //--------------------------------------------------------------------------
    // Method to start the CommandManager
    //
    void start();
  };
}
#endif //COMMANDMANAGER_H_INCLUDED