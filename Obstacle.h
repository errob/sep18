//------------------------------------------------------------------------------
// Obstacle.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED

#include "Property.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // abstract Property Class
  // class to assign field types 
  //
  class Obstacle : public Property
  {
    public:

      //------------------------------------------------------------------------
      // Standard constructor
      //
      Obstacle();

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Obstacle (const Obstacle& original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Obstacle& operator=(const Obstacle& original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Obstacle() noexcept;
  };
}
#endif  // OBSTACLE_H_INCLUDED