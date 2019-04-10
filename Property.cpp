//------------------------------------------------------------------------------
// Property.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//
 
#include "Property.h"
 
using Sep::Property;

//------------------------------------------------------------------------------
Property::Property()
{
}

//------------------------------------------------------------------------------
Property::Property(const FieldType type, const std::string abbrebation,
                   const bool buildable, const bool destroyable,
                   const int build_cost, const int destroy_cost,
                   const int size)
           : Field(type, abbrebation, buildable, destroyable, build_cost,
                   destroy_cost, size)
{
}

//------------------------------------------------------------------------------
Property::~Property() noexcept
{
}