//------------------------------------------------------------------------------
// Field.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#include "Field.h"

using Sep::Field;
//------------------------------------------------------------------------------
Field::Field()
{
}

//------------------------------------------------------------------------------
Field::Field(const FieldType type, const std::string abbrebation,
           const bool buildable, const bool destroyable, const int build_cost,
           const int destroy_cost, const int size) : type_(type),
           abbrevation_on_field_(abbrebation), buildable_(buildable),
           destroyable_(destroyable), size_(size)
{
  build_cost_ = build_cost * size_;
  destroy_cost_ = destroy_cost * size_;
}

//------------------------------------------------------------------------------
Field::~Field() noexcept
{
}

//------------------------------------------------------------------------------
std::string Field::getName(FieldType type)
{
  switch (type)
  {
    case GRASS:
      return "Grass";
    case WATER:
      return "Water";
    case OBSTACLE:
      return "Obstacle";
    case STREET:
      return "Street";
    case HOME:
      return "Home";
    case MARKET:
      return "Market";
    case CLINIC:
      return "Clinic";
    case TOWNHALL:
      return "Town Hall";
    default:
      return "";
  }
}

//------------------------------------------------------------------------------
Field::FieldType Field::getType()
{
  return type_;
}

//------------------------------------------------------------------------------
std::string Field::getAbbrebation()
{
  return abbrevation_on_field_;
}

//------------------------------------------------------------------------------
bool Field::isBuildable()
{
  return buildable_;
}

//------------------------------------------------------------------------------
bool Field::isDestroyable()
{
  return destroyable_;
}

//------------------------------------------------------------------------------
int Field::getBuildCost()
{
  return build_cost_;
}

//------------------------------------------------------------------------------
int Field::getDestroyCost()
{
  return destroy_cost_;
}

//------------------------------------------------------------------------------
int Field::getSize()
{
  return size_;
}
