//------------------------------------------------------------------------------
// Grass.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//
 
#include "Grass.h"
 
using Sep::Grass;
using Sep::Field;

//------------------------------------------------------------------------------
Grass::Grass() : Property(FieldType::GRASS, "G", false, false, 0, 0, 1)
{
}

//------------------------------------------------------------------------------
Grass::~Grass() noexcept
{
}

