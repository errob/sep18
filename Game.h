//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

#include "Field.h"
#include "Grass.h"
#include "Street.h"
#include "Water.h"
#include "Obstacle.h"
#include "Home.h"
#include "Townhall.h"
#include "Clinic.h"
#include "Market.h"
#include "Interface.h"
#include "Car.h"
#include <queue>

namespace Sep {

  //----------------------------------------------------------------------------
  // Game Class
  // class with the game logic
  //
  class Game {
  private:

    //--------------------------------------------------------------------------
    // Attribute for the board width
    //
    int board_width_;

    //--------------------------------------------------------------------------
    // Attribute for the board height
    //
    int board_height_;

    //--------------------------------------------------------------------------
    // Attribute for the ingame money
    //
    int money_;

    //--------------------------------------------------------------------------
    // Attribute for the game interface
    //
    Interface &io_;

    //--------------------------------------------------------------------------
    // Attribute for the game config
    //
    std::string config_;
/**/
    //--------------------------------------------------------------------------
    // Attribute for the Board of the game
    //
    std::vector<std::vector<std::shared_ptr<Field>>> map_;

    //--------------------------------------------------------------------------
    // Attribute for the number of rounds that are played
    //
    int rounds_;

    //--------------------------------------------------------------------------
    // vector of Homes for Residents
    //
    std::vector<std::shared_ptr<Sep::Resident>> residents_;

    //--------------------------------------------------------------------------
    // vector of Homes for Residents
    //
    std::vector<std::shared_ptr<Sep::Home>> homes_;

    //--------------------------------------------------------------------------
    // vector of Supermarkets
    //
    std::vector<std::shared_ptr<Sep::Market>> markets_;

    //--------------------------------------------------------------------------
    // vector of Clinics
    //
    std::vector<std::shared_ptr<Sep::Clinic>> clinics_;

    //--------------------------------------------------------------------------
    // vector of Townhalls
    //
    std::vector<std::shared_ptr<Sep::Townhall>> townhalls_;

    //--------------------------------------------------------------------------
    // vector of Cars
    //
    std::vector<std::shared_ptr<Sep::Car>> cars_;

  public:
    //--------------------------------------------------------------------------
    // Constant to grass field
    //
    static const std::shared_ptr<Field> GRASSPTR;

    //--------------------------------------------------------------------------
    // Constant to obstacle field
    //
    static const std::shared_ptr<Field> OBSTACLEPTR;

    //--------------------------------------------------------------------------
    // Constant to water field
    //
    static const std::shared_ptr<Field> WATERPTR;

    //--------------------------------------------------------------------------
    // Constructor
    // @param io referenze to interface
    // @param config contains the configfilename
    //
    Game(Interface &io, std::string config);

    //--------------------------------------------------------------------------
    // Deleted copy constructor
    //
    Game(const Game &original) = delete;

    //--------------------------------------------------------------------------
    // Deleted assignment operator
    //
    Game &operator=(const Game &original) = delete;

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Game() noexcept;

    //--------------------------------------------------------------------------
    // Getter
    //
    int getWidth();

    int getHeight();

    int getMoney();

    std::vector<std::vector<std::shared_ptr<Field>>> getMap();

    std::vector<std::shared_ptr<Home>> getHomes();

    std::vector<std::shared_ptr<Market>> getMarkets();

    std::vector<std::shared_ptr<Townhall>> getTownhalls();

    //--------------------------------------------------------------------------
    // Setter
    //
    void setWidth(const int width);

    void setHeight(const int height);

    void setMoney(const int money);

    void setMap(const std::vector<std::shared_ptr<Field>> column_vec);

    void setHomes(const std::shared_ptr<Home> home);

    void setMarkets(const std::shared_ptr<Market> market);

    void setTownhalls(const std::shared_ptr<Townhall> townhall);

    void setTownhallMap();


    //--------------------------------------------------------------------------
    // Method to start the game logic
    //
    void run();

    //--------------------------------------------------------------------------
    // Method to build the Field fieldType at position (x, y)
    // @param field_type contains the corresponding Field enum type
    // @param x contains x coordinates
    // @param y contains y coordinates
    //
    void build(Field::FieldType field_type, int x, int y);

    //--------------------------------------------------------------------------
    // Method to build the Field fieldType at position (x, y)
    // with the size width*height
    // @param field_type contains the corresponding Field enum type
    // @param x contains x coordinates
    // @param y contains y coordinates
    // @param width contains the width of the fieldtype
    // @param height contains the height of the fieldtype
    //
    void build(Field::FieldType field_type, int x,
               int y, int width, int height);

    //--------------------------------------------------------------------------
    // Method to destroy the field at position (x, y)
    // @param x contains x coordinates
    // @param y contains y coordinates
    //
    void destroy(int x, int y);

    //--------------------------------------------------------------------------
    // Method to run the game logic before the game quits
    //
    void quit();

    //--------------------------------------------------------------------------
    // Method to check if the position is near any building
    // @param x contains x coordinates
    // @param y contains y coordinates
    // @param width contains the width of the field
    // @param height contains the height of the field
    // @return returns if it has neightbours true or false
    //
    bool hasNeighbour(int x, int y, int width, int height);

    //--------------------------------------------------------------------------
    // Method to get all neighbours which are from type Type
    // @param pos contains the coordinates
    // @param width contains the width of the field
    // @param height contains the height of the field
    //
    template<typename Type>
    std::vector<std::pair<int, int>> getNeighbours(std::pair<int, int> pos,
                                                   int width = 1,
                                                   int height = 1);

    //--------------------------------------------------------------------------
    // Method to find the fastest route between two coordinates
    // Implementation of the A* search algorithm
    // https://en.wikipedia.org/wiki/A*_search_algorithm
    // @param start contains the start coordinates
    // @param goal contains the goal coordinates
    // @return returns a vector containing the route
    //
    std::vector<std::pair<int, int>> findRoute(std::pair<int, int> start,
                                               std::pair<int, int> goal);

    //--------------------------------------------------------------------------
    // Method to reconstruct the path for the A* search algorithm
    // https://en.wikipedia.org/wiki/A*_search_algorithm
    // @param start contains the start coordinates
    // @param goal contains the goal coordinates
    // @return returns a vector containing the route
    //
    std::vector<std::pair<int, int>> reconstructPath(
                std::map<std::pair<int, int>,
                std::pair<int, int>> cameFrom, std::pair<int, int> current);

    //--------------------------------------------------------------------------
    // Method to set a Field in the Map
    // @param fieldType contains the corresponding Field
    // @param x contains x coordinates
    // @param y contains y coordinates
    // @param width contains the width of the fieldtype
    // @param height contains the height of the fieldtype
    // @param is_building contains if buildable
    // @return returns if Field is set true or false
    //
    bool setField(std::shared_ptr<Field> field, int x, int y, int width = 1,
                  int height = 1, bool is_building = false);

    //--------------------------------------------------------------------------
    // Method to print the map
    //
    void printMap();

    //--------------------------------------------------------------------------
    // Method to print Help Info
    //
    void help();

    //--------------------------------------------------------------------------
    // Method to play rounds
    //
    void play(const int rounds);

    void setHomeConnectedToTownhall();

    void setMarketConnectedToTownhall();

    //--------------------------------------------------------------------------
    // Method to calculate to Number of Residents for the game in this round
    //
    int calculateMaxResidentsNumber();

    //--------------------------------------------------------------------------
    // Method to move in new residents
    //
    void moveIn(int resident_count_move_in);

    //--------------------------------------------------------------------------
    // Method to move out residents
    //
    void moveOutMarket(int resident_count_move_out);

    //--------------------------------------------------------------------------
    // Method to move out residents, connection to townhall was destroyed
    //
    void moveOutHome(const std::shared_ptr<Sep::Home> home);

    //--------------------------------------------------------------------------
    // Method to levy Taxes
    //
    void levyTaxes();

    //--------------------------------------------------------------------------
    // Method to Pay for those nasty Bills
    //
    void payBills();

    //--------------------------------------------------------------------------
    // Method to move the Cars
    //
    void moveCars();

    //--------------------------------------------------------------------------
    // Method to update the Routes for all cars
    //
    void updateRoutes();

    //--------------------------------------------------------------------------
    // Method to assign Routes for all cars
    // @param number contains the number of cars wich can be assigned
    //
    void assignRoutes(int number);

    //--------------------------------------------------------------------------
    // Method to update the Route for a car
    // @param car contains a shared pointer to the car
    //
    void updateRoute(std::shared_ptr<Car> car);

    //--------------------------------------------------------------------------
    // Method to create an Emergency at position (x, y)
    // @param x contains x coordinates
    // @param y contains y coordinates
    //
    void emergency(int x, int y);

    //--------------------------------------------------------------------------
    // Method to check if all coordinates are in board
    // @param x contains x coordinates
    // @param y contains y coordinates
    // @param width contains the width of the coordinates
    // @param height contains the height of the coordinates
    // @return returns if all Coordinate is in Board
    //
    bool isNotInBoard(int x, int y, int width = 1, int height = 1);
  };
}
#endif // GAME_H_INCLUDED