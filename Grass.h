//------------------------------------------------------------------------------
// Grass.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef GRASS_H_INCLUDED
#define GRASS_H_INCLUDED

#include "Property.h"


//------------------------------------------------------------------------------
namespace Sep
{
  //----------------------------------------------------------------------------
  // Grass class
  // class to build new property field of type grass
  //
  class Grass : public Property
  {
    public:

      //------------------------------------------------------------------------
      // Standard constructor
      //
      Grass();

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Grass (const Grass& original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Grass& operator=(const Grass& original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Grass() noexcept;
  };
}
#endif  // GRASS_H_INCLUDED