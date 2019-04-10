//------------------------------------------------------------------------------
// Building.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#include "Building.h"

using Sep::Building;
using Sep::Field;

//------------------------------------------------------------------------------
// static constants
const int Building::RESIDENTS_PER_SUPERMARKET_FIELD = 25;

//------------------------------------------------------------------------------
Building::Building()
{
}

//------------------------------------------------------------------------------
Building::Building(const FieldType type, const std::string abbrebation,
                   const bool buildable, const bool destroyable,
                   const int build_cost, const int destroy_cost,
                   const int pos_x, const int pos_y,
                   const int width, const int height)
            : Field(type, abbrebation, buildable, destroyable, build_cost,
                    destroy_cost, height * width),
              width_(width), height_(height), pos_x_(pos_x), pos_y_(pos_y)
{
}

//------------------------------------------------------------------------------
Building::~Building() noexcept
{
}

//------------------------------------------------------------------------------
int Building::getWidth()
{
  return width_;
}

//------------------------------------------------------------------------------
int Building::getHeight()
{
  return height_;
}

//------------------------------------------------------------------------------
int Building::getPosX()
{
  return pos_x_;
}

//------------------------------------------------------------------------------
int Building::getPosY()
{
  return pos_y_;
}