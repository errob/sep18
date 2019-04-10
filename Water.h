//------------------------------------------------------------------------------
// Water.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef WATER_H_INCLUDED
#define WATER_H_INCLUDED


#include "Property.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Water class
  // class to build new property field with type water
  //
  class Water : public Property
  {
    public:

      //------------------------------------------------------------------------
      // Standard constructor
      //
      Water();

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Water (const Water& original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Water& operator=(const Water& original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Water() noexcept;
  };
}
#endif  // WATER_H_INCLUDED