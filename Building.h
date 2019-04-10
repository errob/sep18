//------------------------------------------------------------------------------
// Building.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef BUILIDING_H_INCLUDED
#define BUILIDING_H_INCLUDED

#include "Field.h"

namespace Sep
{

  //----------------------------------------------------------------------------
  // abstract Building Class
  // class to create new fields of type building
  //
  class Building : public Field
  {
  protected:

    //------------------------------------------------------------------------
    // variable to store width of Building
    //
    int width_;

    //------------------------------------------------------------------------
    // variable to store height of Building
    //
    int height_;

    //------------------------------------------------------------------------
    // variable to the x Position of Building
    //
    int pos_x_;

    //------------------------------------------------------------------------
    // variable to the y position of Building
    //
    int pos_y_;


  public:

    //------------------------------------------------------------------------
    // Standard constructor
    //
    Building();


    //------------------------------------------------------------------------
    // Overloaded constructor to assign type
    // @param type contains the FieldType enum
    // @param abbrebation contains the single char for config file
    // @param buildable contains buildable information
    // @param destroyable contains destroyable information
    // @param build_cost contains building cost information
    // @param destroy_cost conains destroy cost information
    // @param pos_x contains the x coordinates
    // @param pos_y contains the y coordinates
    // @param width contains the width of buildings
    // @param height contains the height of buildings
    //
    Building(const FieldType type, const std::string abbrebation,
             const  bool buildable, const bool destroyable,
             const int build_cost, const int destroy_cost, const int pos_x,
             const int pos_y, const int width, const int height);


    //------------------------------------------------------------------------
    // Deleted copy constructor
    //
    Building (const Building& original) = delete;


    //------------------------------------------------------------------------
    // Deleted assignment operator
    //
    Building& operator=(const Building& original) = delete;


    //------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Building() noexcept;

    //------------------------------------------------------------------------
    // Constants
    // required to check for Resident Number
    //
    const static int RESIDENTS_PER_SUPERMARKET_FIELD;

    //------------------------------------------------------------------------
    // Getter methods
    //
    int getWidth();
    int getHeight();
    int getPosX();
    int getPosY();
  };
}
#endif  // BUILIDING_H_INCLUDED