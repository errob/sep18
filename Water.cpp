//------------------------------------------------------------------------------
// Water.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//
 
#include "Water.h"
 
using Sep::Water;
using Sep::Field;

//------------------------------------------------------------------------------
Water::Water() : Property(FieldType::WATER, "W", true, false, 10, 0, 1)
{
}

//------------------------------------------------------------------------------
Water::~Water() noexcept
{
}

