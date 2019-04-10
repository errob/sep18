//------------------------------------------------------------------------------
// Clinic.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#include "Clinic.h"

using Sep::Clinic;
using Sep::Field;
using Sep::Car;

//------------------------------------------------------------------------------
Clinic::Clinic(const int pos_x, const int pos_y, const int width, 
               const int height): Building(FieldType::CLINIC, "C", true,
               true, 200, 100, pos_x, pos_y, width, height)
{
  for (int i = 0; i < width_*height_; i++)
  {
    cars_.push_back(std::shared_ptr<Car>(new Car()));
  }
}

//------------------------------------------------------------------------------
Clinic::~Clinic() noexcept
{
}

//------------------------------------------------------------------------------
int Clinic::computeCosts()
{
  int size = width_ * height_;
  return (size * (-500));
}

//------------------------------------------------------------------------------
std::vector<std::shared_ptr<Car>> Clinic::getCars()
{
  return cars_;
}