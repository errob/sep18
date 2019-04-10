//------------------------------------------------------------------------------
// Car.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include <utility>
#include <vector>

namespace Sep
{
  //----------------------------------------------------------------------------
  // Car Class
  //
  class Car
  {
  private:

    //------------------------------------------------------------------------
    // variable to store size of Building
    //
    std::pair<int, int> pos_;

    //------------------------------------------------------------------------
    // variable if the car is away
    //
    bool away_;

    //------------------------------------------------------------------------
    // variable if the car is away
    //
    bool returning_;

    //------------------------------------------------------------------------
    // variable for the emergency counter
    //
    int time_left_;

    //------------------------------------------------------------------------
    // variable for the start position
    //
    std::pair<int, int> start_;

    //------------------------------------------------------------------------
    // variable for the goal position
    //
    std::pair<int, int> goal_;

    //------------------------------------------------------------------------
    // variable for the goal position
    //
    std::vector<std::pair<int, int>> route_;

    //------------------------------------------------------------------------
    // variable to store the position of the clinic
    //
    std::pair<int, int> clinic_;

    //------------------------------------------------------------------------
    // variable to store the position of the home
    //
    std::pair<int, int> home_;

    //------------------------------------------------------------------------
    // variable if ther is no route to the goal
    //
    bool no_route_;

    //------------------------------------------------------------------------
    // variable if the route has been updated
    //
    bool updated_;

  public:

    //------------------------------------------------------------------------
    // Standard Constructor
    //
    Car();

    //------------------------------------------------------------------------
    // Deleted copy constructor
    //
    Car(const Car& original) = delete;

    //------------------------------------------------------------------------
    // Deleted assignment operator
    //
    Car& operator=(const Car& original) = delete;

    //------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Car() noexcept;

    //------------------------------------------------------------------------
    // Getter Methods
    //
    std::pair<int, int> getPos();
    bool isAway();
    int getTimeLeft();
    std::pair<int, int> getStart();
    std::pair<int, int> getGoal();
    std::vector<std::pair<int, int>> getRoute();
    bool isReturning();
    std::pair<int, int> getClinic();
    std::pair<int, int> getHome();
    bool isNoRoute();
    bool isUpdated();

    //------------------------------------------------------------------------
    // Setter Methods
    //
    void setPos(std::pair<int, int> pos);
    void setAway(bool away);
    void setTimeLeft(int timeLeft);
    void setStart(std::pair<int, int> start);
    void setGoal(std::pair<int, int> goal);
    void setRoute(std::vector<std::pair<int, int>> route);
    void setReturning(bool returning);
    void setClinic(std::pair<int, int> clinic);
    void setHome(std::pair<int, int> home);
    void setNoRoute(bool noRoute);
    void setUpdated(bool updated);
  };
}
#endif  // CAR_H_INCLUDED