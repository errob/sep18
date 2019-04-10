//------------------------------------------------------------------------------
// Resident.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//
#ifndef RESIDENT_H_INCLUDED
#define RESIDENT_H_INCLUDED


#include <string>
#include <memory>

namespace Sep
{
  class Home;

  //----------------------------------------------------------------------------
  // Resident Class
  // class to create Residents
  //
  class Resident
  {
  private:

    //------------------------------------------------------------------------
    // Attribute id for residents
    //
    std::string id_;


    //------------------------------------------------------------------------
    // Attribute id for residents
    //
    std::shared_ptr<Home> home_;

  public:

    //------------------------------------------------------------------------
    // Standard constructor
    //
    Resident(const std::shared_ptr<Home> home);


    //------------------------------------------------------------------------
    // Deleted copy constructor
    //
    Resident(const Resident &original) = delete;


    //------------------------------------------------------------------------
    // Deleted assignment operator
    //
    Resident &operator=(const Resident &original) = delete;


    //------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Resident() noexcept;

    std::shared_ptr<Home> getHome();
  };
}
#endif  //RESIDENT_H_INCLUDED
