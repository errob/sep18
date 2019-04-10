//------------------------------------------------------------------------------
// Clinic.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef CLINIC_H_INCLUDED
#define CLINIC_H_INCLUDED

#include "Building.h"
#include "Car.h"

#include <vector>
#include <memory>

namespace Sep
{

  //----------------------------------------------------------------------------
  // Clinic Class
  // class to create field of type Clinic 
  //
  class Clinic : public Building
  {
  private:

    //------------------------------------------------------------------------
    // Attribute to store the cars which are belonging to the clinic
    //
    std::vector<std::shared_ptr<Car>> cars_;

  public:

    //------------------------------------------------------------------------
    // Standard constructor
    // @param pos_x contains x coordinates
    // @param pos_y contains y coordinates
    // @param width contains width of clinic
    // @param height contains height of clinic
    //
    Clinic(const int pos_x, const int pos_y, const int width,
           const int height);


    //------------------------------------------------------------------------
    // Deleted copy constructor
    //
    Clinic(const Clinic& original) = delete;


    //------------------------------------------------------------------------
    // Deleted assignment operator
    //
    Clinic& operator=(const Clinic& original) = delete;


    //------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Clinic() noexcept;

    //------------------------------------------------------------------------
    // Method to compute costs per round
    //
    int computeCosts();

    //------------------------------------------------------------------------
    // Getter Methods
    //
    std::vector<std::shared_ptr<Car>> getCars();
  };
}
#endif  // CLINIC_H_INCLUDED