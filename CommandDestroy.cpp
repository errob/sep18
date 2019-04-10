//------------------------------------------------------------------------------
// CommandDestroy.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#include "CommandDestroy.h"
#include "Game.h"

using Sep::CommandDestroy;
//------------------------------------------------------------------------------
CommandDestroy::CommandDestroy(std::string name) : Command(name)
{
}

//------------------------------------------------------------------------------
CommandDestroy::~CommandDestroy() noexcept
{
}

//------------------------------------------------------------------------------
bool CommandDestroy::execute(Game &game, std::vector<std::string> &params)
{
  if (params.size() == 2)
  {
    int x = std::stoi(params[0]);
    int y = std::stoi(params[1]);
    game.destroy(x, y);
    return true;
  }
  return false;
}