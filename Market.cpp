//------------------------------------------------------------------------------
// Market.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//
 
#include "Market.h"

using Sep::Market;
using Sep::Field;

//------------------------------------------------------------------------------
Market::Market(const int pos_x, const int pos_y, const int width,
               const int height)
                : Building(FieldType::MARKET, "M", true, true,
                  150, 100, pos_x, pos_y, width, height)
{
}

//------------------------------------------------------------------------------
Market::~Market() noexcept
{
}

//------------------------------------------------------------------------------
bool Market::getIsConnected()
{
  return is_connected_;
}

//------------------------------------------------------------------------------
void Market::setIsConnected(bool connected)
{
  is_connected_ = connected;
}

//------------------------------------------------------------------------------
int Market::maxResidentCount()
{
  return width_ * height_ * Building::RESIDENTS_PER_SUPERMARKET_FIELD;
}

//------------------------------------------------------------------------------
int Market::computeCosts()
{
  int size = width_ * height_;
  return (size * (-450) - 50);
}


