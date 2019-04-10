//------------------------------------------------------------------------------
// CommandBuild.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#include "CommandBuild.h"
#include "Game.h"

using Sep::CommandBuild;
//----------------------------------------------------------------------------
CommandBuild::CommandBuild(std::string name) : Command(name)
{
}

//----------------------------------------------------------------------------
CommandBuild::~CommandBuild()
{
}

//----------------------------------------------------------------------------
bool CommandBuild::execute(Game &game, std::vector<std::string> &params)
{
  Field::FieldType type;
  if (params.size() == 3)
  {
    params[0][0] = toupper(params[0][0]);
    if (params[0] == Field::getName(Field::FieldType::STREET))
    {
      type = Field::FieldType::STREET;
    }
    else if (params[0] == Field::getName(Field::FieldType::OBSTACLE))
    {
      type = Field::FieldType::OBSTACLE;
    }
    else if (params[0] == Field::getName(Field::FieldType::WATER))
    {
      type = Field::FieldType::WATER;
    }
    else
    {
      return false;
    }

    int x = std::stoi(params[1]);
    int y = std::stoi(params[2]);
    game.build(type, x, y);
    return true;
  }

  if (params.size() == 5)
  {
    params[0][0] = toupper(params[0][0]);
    if (params[0] == Field::getName(Field::FieldType::HOME))
    {
      type = Field::FieldType::HOME;
    }
    else if (params[0] == Field::getName(Field::FieldType::CLINIC))
    {
      type = Field::FieldType::CLINIC;
    }
    else if (params[0] == Field::getName(Field::FieldType::MARKET))
    {
      type = Field::FieldType::MARKET;
    }
    else
    {
      return false;
    }

    int x = std::stoi(params[1]);
    int y = std::stoi(params[2]);
    int width = std::stoi(params[3]);
    int height = std::stoi(params[4]);

    if (width < 1 || height < 1)
    {
      return false;
    }
    game.build(type, x, y, width, height);
    return true;
  }
  return false;
}