//------------------------------------------------------------------------------
// Townhall.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef TOWNHALL_H_INCLUDED
#define TOWNHALL_H_INCLUDED

#include "Building.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Townhall Class
  // class to create field of type Townhall 
  //
  class Townhall : public Building
  {
    public:

      //------------------------------------------------------------------------
      // Standard constructor
      // @param pos_x contains x coordinates
      // @param pos_y contains y coordinates
      //
      Townhall(const int pos_x, const int pos_y);

      //------------------------------------------------------------------------
      // Standard constructor
      // @param pos_x contains x coordinates
      // @param pos_y contains y coordinates
      // @param width contains width of townhall
      // @param height contains height of townhall
      //
      Townhall(const int pos_x, const int pos_y,
               const int width, const int height);

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Townhall (const Townhall& original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Townhall& operator=(const Townhall& original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Townhall() noexcept;
  };
}
#endif  // TOWNHALL_H_INCLUDED