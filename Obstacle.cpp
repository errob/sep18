//------------------------------------------------------------------------------
// Obstacle.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//
 
#include "Obstacle.h"
 
using Sep::Obstacle;
using Sep::Field;

//------------------------------------------------------------------------------
Obstacle::Obstacle() : Property(FieldType::OBSTACLE, "O",
                                true, true, 10, 20, 1)
{
}

//------------------------------------------------------------------------------
Obstacle::~Obstacle() noexcept
{
}

