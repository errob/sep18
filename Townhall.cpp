//------------------------------------------------------------------------------
// Townhall.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//
 
#include "Townhall.h"

using Sep::Townhall;
using Sep::Field;

//------------------------------------------------------------------------------
Townhall::Townhall(const int pos_x, const int pos_y) 
    : Building(FieldType::TOWNHALL, "T", false, false,
               0, 0, pos_x, pos_y, 1, 1)
{
}
//------------------------------------------------------------------------------
Townhall::Townhall(const int pos_x, const int pos_y,
                   const int width, const int height) 
        : Building(FieldType::TOWNHALL, "T", false, false, 0, 0,
                   pos_x, pos_y, width, height)
{
}

//------------------------------------------------------------------------------
Townhall::~Townhall() noexcept
{
}



