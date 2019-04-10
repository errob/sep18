//------------------------------------------------------------------------------
// Field.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <iostream>
#include <vector>

namespace Sep
{
  //----------------------------------------------------------------------------
  // Field Class
  // class to assign field types 
  //
  class Field
  {
  public:

    //------------------------------------------------------------------------
    // Enumeration of all supported field types
    //
    enum FieldType {GRASS, WATER, OBSTACLE, STREET, HOME, MARKET, CLINIC,
      TOWNHALL};

  private:

    //------------------------------------------------------------------------
    // variable to store Field Type
    //
    FieldType type_;

    //------------------------------------------------------------------------
    // variable to store Field Name
    //
    std::string field_name_;

    //------------------------------------------------------------------------
    // variable to store Abbrevation on Field
    //
    std::string abbrevation_on_field_;

    //------------------------------------------------------------------------
    // variable to store if the Field is buildable
    //
    bool buildable_;

    //------------------------------------------------------------------------
    // variable to store if the Field is destroyable
    //
    bool destroyable_;

    //------------------------------------------------------------------------
    // variable to store if the Fields destroy costs
    //
    int build_cost_;

    //------------------------------------------------------------------------
    // variable to store if the Fields destroy costs
    //
    int destroy_cost_;

    //------------------------------------------------------------------------
    // variable to store size of Building
    //
    int size_;

  public:

    //------------------------------------------------------------------------
    // Standard Constructor
    //
    Field();

    //------------------------------------------------------------------------
    // Overloaded constructor to assign values
    // @param type contains the FieldType enum
    // @param abbrebation contains the single char for config file
    // @param buildable contains buildable information
    // @param destroyable contains destroyable information
    // @param build_cost contains building cost information
    // @param destroy_cost conains destroy cost information
    // @param size contains the size of the field
    //
    Field(const FieldType type, const std::string abbrebation,
          const bool buildable, const bool destroyable, const int build_cost,
          const int destroy_cost, const int size);

    //------------------------------------------------------------------------
    // Deleted copy constructor
    //
    Field (const Field& original) = delete;

    //------------------------------------------------------------------------
    // Deleted assignment operator
    //
    Field& operator=(const Field& original) = delete;

    //------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Field() noexcept;

    //------------------------------------------------------------------------
    // Getter Methods
    //
    static std::string getName(FieldType type);
    FieldType getType();
    std::string getAbbrebation();
    bool isBuildable();
    bool isDestroyable();
    int getBuildCost();
    int getDestroyCost();
    int getSize();
  };
}
#endif  // FIELD_H_INCLUDED