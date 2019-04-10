//------------------------------------------------------------------------------
// Street.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//
 
#include "Street.h"
 
using Sep::Street;
using Sep::Field;

//------------------------------------------------------------------------------
Street::Street() : Property(FieldType::STREET, "S", true, true, 20, 10, 1)
{
}

//------------------------------------------------------------------------------
Street::~Street() noexcept
{
}