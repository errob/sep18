//------------------------------------------------------------------------------
// Home.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//
#ifndef HOME_H_INCLUDED
#define HOME_H_INCLUDED


#include "Building.h"
#include "Resident.h"


#include <vector>

namespace Sep
{
  //----------------------------------------------------------------------------
  // Home Class
  // class to create field of type home 
  //
  class Home : public Building
  {
  private:

    //------------------------------------------------------------------------
    // variable to store number of residents
    //
    std::vector<std::shared_ptr<Resident>> residents_;

    //------------------------------------------------------------------------
    // variable to store number of residents
    //
    bool is_connected_ = false;

  public:

    //------------------------------------------------------------------------
    // Standard constructor
    // @param pos_x contains x coordinates of home
    // @param pos_y contains y coordinates of home
    // @param width contains width of home
    // @param height contains height of home
    //
    Home(const int pos_x, const int pos_y,
         const int width, const int height);

    //------------------------------------------------------------------------
    // Deleted copy constructor
    //
    Home(const Home &original) = delete;

    //------------------------------------------------------------------------
    // Deleted assignment operator
    //
    Home &operator=(const Home &original) = delete;

    //------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Home() noexcept;

    //------------------------------------------------------------------------
    // Getter
    //
    std::vector<std::shared_ptr<Resident>> getResidents();

    bool getIsConnected();

    //------------------------------------------------------------------------
    // Setter
    //
    void addResident(std::shared_ptr<Resident> resident);

    void setIsConnected(bool connected);

    //------------------------------------------------------------------------
    // Method to get the maximum Number of Residents that can live in a Home
    //
    int maxResidentCount();

    //------------------------------------------------------------------------
    // Method to remove all residents
    //
    void removeResidents();

    //------------------------------------------------------------------------
    // Method to remove one resident from Residents vector
    //
    void removeResidentFromResidents();
  };
}
#endif  // HOME_H_INCLUDED