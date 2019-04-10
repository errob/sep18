//------------------------------------------------------------------------------
// CommandPlay.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#include "CommandPlay.h"
#include "Game.h"

using Sep::CommandPlay;

//------------------------------------------------------------------------------
CommandPlay::CommandPlay(std::string name) : Command(name)
{
}

//------------------------------------------------------------------------------
CommandPlay::~CommandPlay() noexcept
{
}

//------------------------------------------------------------------------------
bool CommandPlay::execute(Game &game, std::vector<std::string> &params)
{
  int rounds;
  if(params.empty())
  {
    rounds = 1;
  }
  else if(params.size() == 1 )
  {
    try {
      rounds = std::stoi(params.at(0));
    }
    catch (std::exception &e)
    {
      return false;
    }
  }

game.play(rounds);


  return true;
}