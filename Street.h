//------------------------------------------------------------------------------
// Street.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef STREET_H_INCLUDED
#define STREET_H_INCLUDED

#include "Property.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Street class
  // class to build new property field of type Street 
  //
  class Street : public Property
  {
    public:

      //------------------------------------------------------------------------
      // Standard constructor
      //
      Street();

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Street (const Street& original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Street& operator=(const Street& original) = delete;

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Street() noexcept;
  };
}
#endif  // STREET_H_INCLUDED