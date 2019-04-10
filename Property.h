//------------------------------------------------------------------------------
// Property.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED

#include "Field.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Property Class
  // class to create Property
  //
  class Property : public Field
  {
    public:

      //------------------------------------------------------------------------
      // Standard constructor
      //
      Property();


      //------------------------------------------------------------------------
      // Overloaded constructor to assign values
      // @param type contains the FieldType enum
      // @param abbrebation contains the single char for config file
      // @param buildable contains buildable information
      // @param destroyable contains destroyable information
      // @param build_cost contains building cost information
      // @param destroy_cost conains destroy cost information
      // @param size contains size information
      //
      Property(const FieldType type, const std::string abbrebation,
               const bool buildable, const bool destroyable, 
               const int build_cost, const int destroy_cost, const int size);


      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Property (const Property& original) = delete;


      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Property& operator=(const Property& original) = delete;


      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Property() noexcept;
  };
}
#endif  // PROPERTY_H_INCLUDED