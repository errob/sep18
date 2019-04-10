//------------------------------------------------------------------------------
// CommandHelp.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#include "CommandHelp.h"
#include "Game.h"

using Sep::CommandHelp;

//----------------------------------------------------------------------------
CommandHelp::CommandHelp(std::string name) : Command(name)
{
}

//----------------------------------------------------------------------------
CommandHelp::~CommandHelp() noexcept
{
}

//----------------------------------------------------------------------------
bool CommandHelp::execute(Sep::Game &game, std::vector<std::string> &params)
{
  game.help();
  return true;
}




