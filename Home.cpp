//------------------------------------------------------------------------------
// Home.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#include "Home.h"
#include <memory>

using Sep::Field;
using Sep::Home;


//------------------------------------------------------------------------------
Home::Home(const int pos_x, const int pos_y,
           const int width, const int height)
        : Building(FieldType::HOME, "H", true, true,
                   100, 100, pos_x, pos_y, width, height)
{
}

//------------------------------------------------------------------------------
Home::~Home() noexcept
{
}

//------------------------------------------------------------------------------
bool Home::getIsConnected()
{
  return is_connected_;
}

//------------------------------------------------------------------------------
void Home::setIsConnected(bool connected)
{
  is_connected_ = connected;
}

//------------------------------------------------------------------------------
std::vector<std::shared_ptr<Sep::Resident>> Home::getResidents()
{
  return residents_;
}

//------------------------------------------------------------------------------
void Home::addResident(std::shared_ptr<Resident> resident)
{
  residents_.push_back(resident);
}

//------------------------------------------------------------------------------
int Home::maxResidentCount()
{
  int size = width_ * height_;
  return (10 *  size + (size - 1) * 2);
}

//------------------------------------------------------------------------------
void Home::removeResidents()
{
  residents_.clear();
}

//------------------------------------------------------------------------------
void Home::removeResidentFromResidents()
{
  residents_.pop_back();
}
