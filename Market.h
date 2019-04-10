//------------------------------------------------------------------------------
// Market.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef MARKET_H_INCLUDED
#define MARKET_H_INCLUDED

#include "Building.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Market Class
  // class to create field of type Market 
  //
  class Market : public Building
  {
  public:

    //------------------------------------------------------------------------
    // Deleted copy constructor
    //
    bool is_connected_ = false;

    //------------------------------------------------------------------------
    // Standard constructor
    // @param pos_x contains x coordinates of market
    // @param pos_y contains y coordinates of market
    // @param width contains width of market
    // @param height contains height of market
    //
    Market(const int pos_x, const int pos_y, const int width,
      const int height);


    //------------------------------------------------------------------------
    // Deleted copy constructor
    //
    Market(const Market &original) = delete;


    //------------------------------------------------------------------------
    // Deleted assignment operator
    //
    Market &operator=(const Market &original) = delete;


    //------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Market() noexcept;

    //------------------------------------------------------------------------
    // Getter
    //
    bool getIsConnected();

    //------------------------------------------------------------------------
    // Setter
    //
    void setIsConnected(bool connected);

    //------------------------------------------------------------------------
    // Method to compute maximum number for Residents
    //
    int maxResidentCount();

    //------------------------------------------------------------------------
    // Method to compute costs per round
    //
    int computeCosts();
  };
}
#endif  // MARKET_H_INCLUDED