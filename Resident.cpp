//------------------------------------------------------------------------------
// Resident.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#include "Resident.h"
#include "Home.h"

using Sep::Resident;
using Sep::Home;

//------------------------------------------------------------------------------
Resident::Resident(const std::shared_ptr<Home> home) : home_(home)
{
}

//------------------------------------------------------------------------------
Resident::~Resident() noexcept
{
}

//------------------------------------------------------------------------------
std::shared_ptr<Home> Resident::getHome()
{
  return home_;
}
