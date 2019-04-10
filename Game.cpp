//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#include "Game.h"
#include "ConfigFile.h"
#include "CommandManager.h"


using Sep::Game;
using std::vector;
using std::string;
using std::map;
using std::pair;

//------------------------------------------------------------------------------
const std::shared_ptr<Sep::Field> Game::GRASSPTR =
  std::shared_ptr<Field>(new Grass());

//------------------------------------------------------------------------------
const std::shared_ptr<Sep::Field> Game::OBSTACLEPTR =
  std::shared_ptr<Field>(new Obstacle());

//------------------------------------------------------------------------------
const std::shared_ptr<Sep::Field> Game::WATERPTR =
  std::shared_ptr<Field>(new Water());

//------------------------------------------------------------------------------
Game::Game(Interface &io, string config) : io_(io), config_(config)
{
  ConfigFile config_file(config_, *this);
  if (!config_file.openFile())
  {
    throw std::invalid_argument(Sep::Interface::ERROR_INVALID_CONFIG);
  }
  setTownhallMap();
  rounds_ = 1;

  io_.out(Interface::SETTING, "BOARDSIZE " + std::to_string(board_width_)
                              + " " + std::to_string(board_height_));
}

//------------------------------------------------------------------------------
Game::~Game() noexcept
{
}

//------------------------------------------------------------------------------
int Game::getWidth()
{
  return board_width_;
}

//------------------------------------------------------------------------------
int Game::getHeight()
{
  return board_height_;
}

//------------------------------------------------------------------------------
int Game::getMoney()
{
  return money_;
}

//------------------------------------------------------------------------------
vector<vector<std::shared_ptr<Sep::Field>>> Game::getMap()
{
  return map_;
}

//------------------------------------------------------------------------------
vector<std::shared_ptr<Sep::Home>> Game::getHomes()
{
  return homes_;
}

//------------------------------------------------------------------------------
vector<std::shared_ptr<Sep::Market>> Game::getMarkets()
{
  return markets_;
}

//------------------------------------------------------------------------------
vector<std::shared_ptr<Sep::Townhall>> Game::getTownhalls()
{
  return townhalls_;
}

//------------------------------------------------------------------------------
void Game::setWidth(const int width)
{
  board_width_ = width;
}

//------------------------------------------------------------------------------
void Game::setHeight(const int height)
{
  board_height_ = height;
}

//------------------------------------------------------------------------------
void Game::setMoney(const int money)
{
  money_ = money;
}

//------------------------------------------------------------------------------
void Game::setMap(const vector<std::shared_ptr<Field>> column_vec)
{
  map_.push_back(column_vec);
}

//------------------------------------------------------------------------------
void Game::setHomes(const std::shared_ptr<Home> home)
{
  homes_.push_back(home);
}

//------------------------------------------------------------------------------
void Game::setMarkets(const std::shared_ptr<Market> market)
{
  markets_.push_back(market);
}

//------------------------------------------------------------------------------
void Game::setTownhalls(const std::shared_ptr<Townhall> townhall)
{
  townhalls_.push_back(townhall);
}

//------------------------------------------------------------------------------
void Game::setTownhallMap()
{
  for (int row = 0; row < board_height_; row++)
  {
    for (int column = 0; column < board_width_; column++)
    {
      if (map_.at(row).at(column)->getType() ==
          Sep::Field::FieldType::TOWNHALL)
      {
        std::shared_ptr<Field> field = std::shared_ptr<Field>
          (new Townhall(row, column));
        map_.at(row).at(column) = field;
      }
    }
  }
}

//------------------------------------------------------------------------------
void Game::run()
{
  //Only for Testing
  printMap();
  CommandManager cmd(io_, *this);
  cmd.start();
}

//------------------------------------------------------------------------------
void Game::build(Field::FieldType fieldType, int x, int y)
{
  std::shared_ptr<Field> field = nullptr;
  if (fieldType == Field::FieldType::OBSTACLE)
  {
    field = std::shared_ptr<Field>(new Obstacle());
  } else if (fieldType == Field::FieldType::STREET)
  {
    field = std::shared_ptr<Field>(new Street());
  } else if (fieldType == Field::FieldType::WATER)
  {
    field = std::shared_ptr<Field>(new Water());
  }
  if (setField(field, x, y))
  {
    if (fieldType == Field::FieldType::STREET)
    {
      updateRoutes();
    }
    printMap();
  }
}

//------------------------------------------------------------------------------
void Game::build(Field::FieldType fieldType, int x, int y,
                 int width, int height)
{
  std::shared_ptr<Field> field = nullptr;
  if (fieldType == Field::FieldType::CLINIC)
  {
    field = std::shared_ptr<Field>(new Clinic(x, y, width, height));
  } else if (fieldType == Field::FieldType::HOME)
  {
    field = std::shared_ptr<Field>(new Home(x, y, width, height));
  } else if (fieldType == Field::FieldType::MARKET)
  {
    field = std::shared_ptr<Field>(new Market(x, y, width, height));
  }
  if (setField(field, x, y, width, height, true))
  {
    if (field->getType() == Field::FieldType::HOME)
    {
      homes_.push_back(std::dynamic_pointer_cast<Home>(field));
    } else if (field->getType() == Field::FieldType::MARKET)
    {
      markets_.push_back(std::dynamic_pointer_cast<Market>(field));
    } else if (field->getType() == Field::FieldType::CLINIC)
    {
      clinics_.push_back(std::dynamic_pointer_cast<Clinic>(field));
      assignRoutes(width*height);
    }
    printMap();
  }
}

//------------------------------------------------------------------------------
void Game::destroy(int x, int y)
{
  if (isNotInBoard(x, y))
  {
    io_.out(Interface::INFO, Interface::INFO_OUTSIDE_BOARD);
    return;
  }
  if (!(*map_.at(y).at(x)).isDestroyable())
  {
    io_.out(Interface::INFO, Interface::INFO_CANNOT_DESTROY);
    return;
  }
  if ((*map_.at(y).at(x)).getDestroyCost() > money_)
  {
    io_.out(Interface::INFO, Interface::INFO_NOT_ENOUGH_MONEY);
    return;
  }
  money_ -= (*map_.at(y).at(x)).getDestroyCost();
  std::shared_ptr<Building> obj =
    std::dynamic_pointer_cast<Building>(map_.at(y).at(x));
  if (obj != nullptr)
  {
    int posX = obj->getPosX();
    int posY = obj->getPosY();
    int width = obj->getWidth();
    int height = obj->getHeight();

    if ((*map_.at(posY).at(posX)).getType() == Field::FieldType::HOME)
    {
      for (auto i = 0; i < homes_.size(); i++)
      {
        if (homes_.at(i)->getPosX() == posX && homes_.at(i)->getPosY() == posY)
        {
          for (auto it = residents_.begin(); it != residents_.end();)
          {
            if ((*it)->getHome() == homes_.at(i))
            {
              residents_.erase(it);
            }
            else {
              it++;
            }
          }
          homes_.erase(homes_.begin() + i);
          break;
        }
      }
      for (auto car : cars_)
      {
        if (car->getHome() == std::make_pair(posX, posY) && !car->isReturning())
        {
          if (car->isNoRoute())
          {
            cars_.erase(std::find(cars_.begin(), cars_.end(), car));
            continue;
          }
          (car)->setReturning(true);
          if (car->isUpdated())
          {
            updateRoute(car);
          }
          else
          {
            vector<pair<int, int>> route = car->getRoute();
            std::reverse(route.begin(), route.end());
            (car)->setRoute(route);
            (car)->setGoal(car->getStart());
          }
        }
      }
    }
    if ((*map_.at(posY).at(posX)).getType() == Field::FieldType::MARKET)
    {
      for (auto i = 0; i < markets_.size(); i++)
      {
        if (markets_.at(i)->getPosX() == posX && markets_.at(i)->getPosY() == posY)
        {
          markets_.erase(markets_.begin() + i);
        }
      }
    }
    if ((*map_.at(posY).at(posX)).getType() == Field::FieldType::CLINIC)
    {
      for (auto i = 0; i < clinics_.size(); i++)
      {
        if (clinics_.at(i)->getPosX() == posX && clinics_.at(i)->getPosY() == posY)
        {
          std::vector<std::shared_ptr<Car>> cars = clinics_.at(i)->getCars();
          for (auto car : cars)
          {
            if (car->isAway())
            {
              car->setNoRoute(true);
            }
          }
          clinics_.erase(clinics_.begin() + i);
          break;
        }
      }
    }

    for (int col = 0; col < width; col++)
    {
      for (int row = 0; row < height; row++)
      {
        map_.at(posY + row).at(posX + col) = GRASSPTR;
      }
    }
  } else
  {
    if ((*map_.at(y).at(x)).getType() == Field::FieldType::STREET)
    {
      for (auto car : cars_)
      {
        if (car->getPos() == std::make_pair(x,y) && !car->isNoRoute())
        {
          io_.out(Interface::INFO, Interface::INFO_CANNOT_DESTROY);
          return;
        }
      }
    }
    map_.at(y).at(x) = GRASSPTR;
    if ((*map_.at(y).at(x)).getType() == Field::FieldType::STREET)
    {
      updateRoutes();
    }
  }
  printMap();
}

//------------------------------------------------------------------------------
void Game::quit()
{
  io_.out(Interface::INFO, Interface::INFO_QUIT_MSG);
  money_ = 0;
  printMap();
}

//------------------------------------------------------------------------------
bool Game::setField(std::shared_ptr<Sep::Field> field, int x, int y,
                    int width, int height, bool is_building)
{
  if (field == nullptr)
  {
    return false;
  }
  if (isNotInBoard(x, y, width, height))
  {
    io_.out(Interface::INFO, Interface::INFO_OUTSIDE_BOARD);
    return false;
  }
  for (int col = 0; col < width; col++)
  {
    for (int row = 0; row < height; row++)
    {
      if ((*map_.at(y + row).at(x + col)).getType() !=
          Field::FieldType::GRASS)
      {
        io_.out(Interface::INFO, Interface::INFO_GRASS_ONLY);
        return false;
      }
    }
  }
  if (width > 3 || height > 3)
  {
    io_.out(Interface::INFO, Interface::INFO_MAX_SIZE);
    return false;
  }
  if (is_building)
  {
    if (hasNeighbour(x, y, width, height))
    {
      io_.out(Interface::INFO, Interface::INFO_SPACING);
      return false;
    }
  }
  if (field->getBuildCost() > money_)
  {
    io_.out(Interface::INFO, Interface::INFO_NOT_ENOUGH_MONEY);
    return false;
  }
  money_ -= field->getBuildCost();
  for (int col = 0; col < width; col++)
  {
    for (int row = 0; row < height; row++)
    {
      map_.at(y + row).at(x + col) = field;
    }
  }
  return true;
}

//------------------------------------------------------------------------------
bool Game::hasNeighbour(int x, int y, int width, int height)
{
  int colMin = x == 0 ? 0 : x - 1;
  int colMax = x + width == board_width_ ? board_width_ : x + width + 1;
  int rowMin = y == 0 ? 0 : y - 1;
  int rowMax = y + height == board_height_ ? board_height_ : y + height + 1;
  for (int row = rowMin; row < rowMax; row++)
  {
    for (int col = colMin; col < colMax; col++)
    {
      if (std::dynamic_pointer_cast<Building>(map_.at(row).at(col)) !=
          nullptr)
      {
        return true;
      }
    }
  }
  return false;
}

//------------------------------------------------------------------------------
void Game::printMap()
{
  io_.out(Interface::RESIDENTS, std::to_string(residents_.size()));
  io_.out(Interface::MONEY, std::to_string(money_));
  vector<vector<Field::FieldType>> map;
  vector<pair<int, int>> cars;
  for (auto row = 0; row < board_width_; row++)
  {
    vector<Field::FieldType> vector_column;
    for (auto column = 0; column < board_height_; column++)
    {
      vector_column.push_back((*map_.at(column).at(row)).getType());
    }
    map.push_back(vector_column);
  }
  for (auto car : cars_)
  {
    if (!car->isNoRoute())
    {
      cars.push_back(car->getPos());
    }
  }
  io_.out(map, cars);
}

//------------------------------------------------------------------------------
void Game::help()
{
  for (unsigned int vectorIndex = 0;
       vectorIndex != Interface::INFO_HELP_MSGS.size();
       ++vectorIndex)
  {
    io_.out(Interface::INFO, Interface::INFO_HELP_MSGS[vectorIndex]);
  }
  printMap();
}

//------------------------------------------------------------------------------
void Game::play(const int rounds)
{
  for (int r = 0; r < rounds; r++)
  {

    io_.out(Interface::INFO,
            Interface::INFO_ROUND_NUM + std::to_string(rounds_));
    rounds_++;
    setHomeConnectedToTownhall();
    setMarketConnectedToTownhall();
    int max_resident_count = calculateMaxResidentsNumber();
    if (max_resident_count < residents_.size())
    {
      moveOutMarket(residents_.size() - max_resident_count);
    }
    moveIn(max_resident_count);
    levyTaxes();
    payBills();
    moveCars();
  }
  printMap();
  if (money_ < 0)
  {
    io_.out(Interface::INFO, Interface::INFO_OUT_OF_MONEY);
    return;
  }
}

//------------------------------------------------------------------------------
void Game::setHomeConnectedToTownhall()
{
  for (auto home : homes_)
  {
    vector<pair<int, int>> route;
    vector<pair<int, int>> new_route;
    vector<pair<int, int>> home_ns = getNeighbours<Street>({home->getPosX(),
                                                            home->getPosY()},
                                                           home->getWidth(),
                                                           home->getHeight());
    if (home_ns.size() == 0 && home->getIsConnected())
    {
      home->setIsConnected(false);
      moveOutHome(home);
    }


    for (auto start : home_ns)
    {
      for (auto townhall : townhalls_)
      {
        vector<pair<int, int>> townhall_ns = getNeighbours<Street>
          ({townhall->getPosX(), townhall->getPosY()},
          townhall->getWidth(), townhall->getHeight());
        for (auto goal : townhall_ns)
        {
          route = findRoute(start, goal);
          if (route.size() > 0)
          {
            home->setIsConnected(true);
          } else if (route.size() == 0 && home->getIsConnected())
          {
            home->setIsConnected(false);
            moveOutHome(home);
          }
        }
      }
    }
  }
}

//------------------------------------------------------------------------------
void Game::setMarketConnectedToTownhall()
{
  for (auto &market : markets_)
  {
    vector<pair<int, int>> route;
    vector<pair<int, int>> new_route;
    vector<pair<int, int>> market_ns = getNeighbours<Street>
      ({market->getPosX(), market->getPosY()},
      market->getWidth(), market->getHeight());
    if (market_ns.size() == 0 && market->getIsConnected())
    {
      market->setIsConnected(false);
    }
    for (auto start : market_ns)
    {
      for (auto &townhall : townhalls_)
      {
        vector<pair<int, int>> townhall_ns = getNeighbours<Street>
          ({townhall->getPosX(), townhall->getPosY()},
          townhall->getWidth(), townhall->getHeight());
        for (auto goal : townhall_ns)
        {
          route = findRoute(start, goal);
          if (route.size() > 0)
          {
            market->setIsConnected(true);
          } else if (route.size() == 0 && market->getIsConnected() == true)
          {
            market->setIsConnected(false);
          }
        }
      }
    }
  }
}

//------------------------------------------------------------------------------
int Game::calculateMaxResidentsNumber()
{
  if (homes_.empty() || markets_.empty())
  {
    return 0;
  }

  int residents_in_homes = 0;
  int residents_in_markets = 0;

  for (auto const &home : homes_)
  {
    if (home->getIsConnected() == true)
    {
      residents_in_homes += home->maxResidentCount();
    }
  }

  for (auto const &market :markets_)
  {
    if (market->getIsConnected() == true)
    {
      residents_in_markets += market->maxResidentCount();
    }
  }
  return std::min(residents_in_markets, residents_in_homes);
}

//------------------------------------------------------------------------------
void Game::moveIn(int max_resident_count)
{
  int residents_to_move_in = std::min(max_resident_count, 10);
  for (auto &home : homes_)
  {
    if (home->getIsConnected() == false && home->getResidents().size() != 0)
    {
      moveOutHome(home);
    } else if (home->getIsConnected() == true)
    {
      int available_resident_space = home->maxResidentCount() -
                                     home->getResidents().size();
      max_resident_count -= home->getResidents().size();

      for (int space = 0; space < available_resident_space; space++)
      {
        if (residents_to_move_in && max_resident_count)
        {
          std::shared_ptr<Resident> resident = std::shared_ptr<Resident>
            (new Resident(home));
          home->addResident(resident);
          residents_.push_back(resident);
          residents_to_move_in--;
          max_resident_count--;
        } else
        {
          return;
        }
      }
    }
  }
}

//------------------------------------------------------------------------------
void Game::moveOutMarket(int resident_count_move_out)
{
  int end = residents_.size() - resident_count_move_out;
  for (int i = residents_.size(); i > end; i--)
  {
    std::shared_ptr<Home> home = residents_.at(i - 1)->getHome();
    home->removeResidentFromResidents();
    residents_.pop_back();
  }
}

//------------------------------------------------------------------------------
void Game::moveOutHome(std::shared_ptr<Sep::Home> home)
{
  for (int i = 0; i < residents_.size();)
  {
    if (residents_.at(i)->getHome() == home)
    {
      residents_.erase(residents_.begin() + i);
    } else
    {
      i++;
    }
  }
  home->removeResidents();
}

//------------------------------------------------------------------------------
void Game::levyTaxes()
{
  for (auto const &home : homes_)
  {
    money_ += home->getResidents().size() * 50;
  }
}

//------------------------------------------------------------------------------
void Game::payBills()
{
  for (auto const &market : markets_)
  {
    money_ += market->computeCosts();
  }

  for (auto const &clinic : clinics_)
  {
    money_ += clinic->computeCosts();
  }
}

//------------------------------------------------------------------------------
void Game::moveCars()
{
  for (auto carIt = cars_.begin(); carIt != cars_.end();)
  {
    pair<int, int> pos = (*carIt)->getPos();
    vector<pair<int, int>> route = (*carIt)->getRoute();
    int time = (*carIt)->getTimeLeft();
    if (pos == (*carIt)->getGoal())
    {
      if ((*carIt)->isReturning())
      {
        (*carIt)->setAway(false);
        cars_.erase(carIt);
        assignRoutes(1);
        continue;
      }
      else
      {
        (*carIt)->setReturning(true);
        if ((*carIt)->isUpdated())
        {
          updateRoute(*carIt);
          route = (*carIt)->getRoute();
        }
        else
        {
          std::reverse(route.begin(), route.end());
          (*carIt)->setRoute(route);
          (*carIt)->setGoal((*carIt)->getStart());
        }
      }
    }
    if (!(*carIt)->isReturning() && time == 0)
    {
      if ((*carIt)->isNoRoute())
      {
        cars_.erase(carIt);
        continue;
      }
      std::reverse(route.begin(), route.end());
      (*carIt)->setRoute(route);
      (*carIt)->setGoal((*carIt)->getStart());
      (*carIt)->setReturning(true);
      moveOutHome(std::dynamic_pointer_cast<Home>
        (map_.at((*carIt)->getHome().second).at((*carIt)->getHome().first)));
    }
    for (auto routeIt = route.begin(); routeIt != route.end(); ++routeIt)
    {
      if (*routeIt == pos)
      {
        if (routeIt + 1 == route.end())
        {
          (*carIt)->setAway(false);
          cars_.erase(carIt);
          assignRoutes(1);
          break;
        }
        pos = *(routeIt + 1);
        (*carIt)->setPos(pos);
        if (!(*carIt)->isReturning())
        {
          (*carIt)->setTimeLeft(time - 1);
        }
        break;
      }
    }
    ++carIt;
  }
}

//------------------------------------------------------------------------------
vector<pair<int, int>> Game::findRoute(pair<int, int> start,
                                       pair<int, int> goal)
{
  map<pair<int, int>, pair<int, int>> closedSet;
  map<pair<int, int>, pair<int, int>> openSet;
  map<pair<int, int>, pair<int, int>> cameFrom;
  // start x/y -> 0,abs
  openSet[start] = {0, std::abs(start.first - goal.first) +
                       std::abs(start.second - goal.second)};
  pair<int, int> current;
  while (openSet.size() != 0)
  {
    //suche min element in openset von begin bis ende
    //für welches x1 > x2 wobei map x,y / x,y second.second = 2es y
    //wird mit first element in current verglichen muss true sein
    current = std::min_element(openSet.begin(), openSet.end(), []
      (const pair<pair<int, int>, pair<int, int>> &x1,
       const pair<pair<int, int>, pair<int, int>> &x2)
      {return x1.second.second > x2.second.second; })->first;
    if (current == goal)
    {
      return reconstructPath(cameFrom, current);
    }
    closedSet[current] = openSet.find(current)->second;
    openSet.erase(current);
    vector<pair<int, int>> neighbours = getNeighbours<Street>(current);
    for (auto neighbor : neighbours)
    {
      if (closedSet.find(neighbor) != closedSet.end())
      {
        continue;
      }
      int tentative_gScore = closedSet.find(current)->second.first + 1;
      if (openSet.find(neighbor) == openSet.end())
      {
        openSet[neighbor] = {tentative_gScore, tentative_gScore +
                            std::abs(neighbor.first - goal.first) +
                            std::abs(neighbor.second - goal.second)};
        cameFrom[neighbor] = current;
        continue;
      }
      int gScoreNeighbor = openSet.find(neighbor)->second.first;
      if (tentative_gScore >= gScoreNeighbor)
      {
        continue;
      }
      cameFrom[neighbor] = current;
      openSet.find(neighbor)->second = {tentative_gScore, tentative_gScore +
                                    std::abs(neighbor.first - goal.first) +
                                    std::abs(neighbor.second - goal.second)};
    }
  }
  return vector<pair<int, int>>();
}

//------------------------------------------------------------------------------
vector<pair<int, int>> Game::reconstructPath(map<pair<int, int>,
  pair<int, int>> cameFrom,
                                             pair<int, int> current)
{
  vector<pair<int, int>> totalPath = {current};
  while (cameFrom.find(current) != cameFrom.end())
  {
    current = cameFrom.find(current)->second;
    totalPath.push_back(current);
  }
  return totalPath;
}

//------------------------------------------------------------------------------
template <typename Type>
vector<pair<int, int>> Game::getNeighbours(pair<int, int> pos,
                                           int width, int height)
{
  vector<pair<int, int>> neighbours;
  pair<int, int> newPos = pos;
  Field field;
  newPos.first--;
  newPos.second += height;
  for (int i = 0; i < width; i++)
  {
    newPos.first++;
    newPos.second -= height + 1;
    if (!isNotInBoard(newPos.first, newPos.second))
    {
      if (std::dynamic_pointer_cast<Type>(map_.at(newPos.second)
                                            .at(newPos.first)) != nullptr)
      {
        neighbours.push_back(newPos);
      }
    }
    newPos.second += height + 1;
    if (!isNotInBoard(newPos.first, newPos.second))
    {
      if (std::dynamic_pointer_cast<Type>(map_.at(newPos.second)
                                            .at(newPos.first)) != nullptr)
      {
        neighbours.push_back(newPos);
      }
    }
  }
  newPos.second -= height + 1;
  newPos.first++;
  for (int i = 0; i < height; i++)
  {
    newPos.second++;
    newPos.first -= width + 1;
    if (!isNotInBoard(newPos.first, newPos.second))
    {
      if (std::dynamic_pointer_cast<Type>(map_.at(newPos.second)
                                            .at(newPos.first)) != nullptr)
      {
        neighbours.push_back(newPos);
      }
    }
    newPos.first += width + 1;
    if (!isNotInBoard(newPos.first, newPos.second))
    {
      if (std::dynamic_pointer_cast<Type>(map_.at(newPos.second)
                                            .at(newPos.first)) != nullptr)
      {
        neighbours.push_back(newPos);
      }
    }
  }
  return neighbours;
}

//------------------------------------------------------------------------------
void Game::emergency(int x, int y)
{
  if (isNotInBoard(x, y))
  {
    io_.out(Interface::INFO, Interface::INFO_OUTSIDE_BOARD);
    return;
  }
  std::shared_ptr<Home> home = std::dynamic_pointer_cast<Home>
    (map_.at(y).at(x));
  if (home == nullptr)
  {
    io_.out(Interface::INFO, Interface::INFO_HOME_ONLY);
    return;
  }
  std::shared_ptr<Car> car;
  vector<pair<int, int>> route;
  vector<pair<int, int>> newRoute;
  pair<int, int> routeClinic;
  pair<int, int> routeStart;
  pair<int, int> routeGoal;
  vector<pair<int, int>> homeNs = getNeighbours<Street>(
    { home->getPosX(), home->getPosY() },
      home->getWidth(), home->getHeight());
  for (auto start : homeNs)
  {
    for (auto clinic : clinics_)
    {
      vector<std::shared_ptr<Car>> cars = clinic->getCars();
      car = nullptr;
      for (auto obj : cars)
      {
        if (!obj->isAway())
        {
          car = obj;
          break;
        }
      }
      if (car != nullptr)
      {
        vector<pair<int, int>> clinicNs = getNeighbours<Street>(
          { clinic->getPosX(), clinic->getPosY() },
          clinic->getWidth(), clinic->getHeight());
        for (auto goal : clinicNs)
        {
          newRoute = findRoute(start, goal);
          if (route.empty() || route.size() > newRoute.size())
          {
            routeClinic = { clinic->getPosX(), clinic->getPosY() };
            route = newRoute;
            routeStart = goal;
            routeGoal = start;
          }
        }
      }
    }
  }
  if (route.empty())
  {
    car = std::shared_ptr<Car>(new Car());
    car->setNoRoute(true);
  }
  car->setHome({ home->getPosX(), home->getPosY() });
  car->setClinic(routeClinic);
  car->setRoute(route);
  car->setStart(routeStart);
  car->setGoal(routeGoal);
  car->setTimeLeft(20);
  car->setAway(true);
  car->setReturning(false);
  car->setPos(routeStart);
  cars_.push_back(car);
  printMap();
}

//--------------------------------------------------------^----------------------
bool Game::isNotInBoard(int x, int y, int width, int height)
{
  if (x + width - 1 >= board_width_ || x < 0 || y + height - 1 >=
                                                board_height_ || y < 0)
  {
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
void Game::updateRoutes()
{
  for (auto car : cars_)
  {
    if (!car->isNoRoute())
    {
      updateRoute(car);
    }
  }
}

//------------------------------------------------------------------------------
void Game::updateRoute(std::shared_ptr<Car> car)
{
  vector<pair<int, int>> route;
  vector<pair<int, int>> newRoute;
  vector<pair<int, int>> goalNs;
  pair<int, int> goal;
  std::shared_ptr<Building> building;

  car->setUpdated(true);
  if (car->isReturning())
  {
    goal = car->getClinic();
  }
  else
  {
    goal = car->getHome();
  }
  building = std::dynamic_pointer_cast<Building>(map_.at(goal.second)
    .at(goal.first));
  goalNs = getNeighbours<Street>({ goal.first, goal.second },
    building->getWidth(), building->getHeight());
  for (auto street : goalNs)
  {
    newRoute = findRoute(street, car->getPos());
    if (route.empty() || route.size() > newRoute.size())
    {
      route = newRoute;
      goal = street;
    }
  }
  car->setRoute(route);
  car->setGoal(goal);
}

//------------------------------------------------------------------------------
void Game::assignRoutes(int number)
{
  int count = number;
  for (auto car : cars_)
  {
    if (car->isNoRoute())
    {
      std::shared_ptr<Home> home = std::dynamic_pointer_cast<Home>
        (map_.at(car->getHome().second).at(car->getHome().first));
      vector<pair<int, int>> route;
      vector<pair<int, int>> newRoute;
      pair<int, int> routeClinic;
      pair<int, int> routeStart;
      pair<int, int> routeGoal;
      vector<pair<int, int>> homeNs = getNeighbours<Street>(
        { home->getPosX(), home->getPosY() },
          home->getWidth(), home->getHeight());
      for (auto start : homeNs)
      {
        for (auto clinic : clinics_)
        {
          vector<std::shared_ptr<Car>> cars = clinic->getCars();
          car = nullptr;
          for (auto obj : cars)
          {
            if (!obj->isAway())
            {
              car = obj;
              break;
            }
          }
          if (car != nullptr)
          {
            vector<pair<int, int>> clinicNs = getNeighbours<Street>(
              { clinic->getPosX(), clinic->getPosY() },
              clinic->getWidth(), clinic->getHeight());
            for (auto goal : clinicNs)
            {
              newRoute = findRoute(start, goal);
              if (route.empty() || route.size() > newRoute.size())
              {
                routeClinic = { clinic->getPosX(), clinic->getPosY() };
                route = newRoute;
                routeStart = goal;
                routeGoal = start;
              }
            }
          }
        }
      }
      if (!route.empty())
      {
        car->setClinic(routeClinic);
        car->setRoute(route);
        car->setStart(routeStart);
        car->setGoal(routeGoal);
        car->setAway(true);
        car->setReturning(false);
        car->setPos(routeStart);
        count--;
      }
    }
    if (count == 0)
    {
      return;
    }
  }
}