//------------------------------------------------------------------------------
// CommandQuit.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#include "CommandQuit.h"
#include "Game.h"

using Sep::CommandQuit;

//------------------------------------------------------------------------------
CommandQuit::CommandQuit(std::string name) : Command(name)
{
}

//------------------------------------------------------------------------------
CommandQuit::~CommandQuit() noexcept
{
}

//------------------------------------------------------------------------------
bool CommandQuit::execute(Game &game, std::vector<std::string> &params)
{
  game.quit();
  return true;
}