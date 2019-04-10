//------------------------------------------------------------------------------
// ConfigFile.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#include "ConfigFile.h"
#include "Interface.h"
#include <iterator>
#include <limits>

using Sep::ConfigFile;

//------------------------------------------------------------------------------
// static constants
const std::string ConfigFile::MAGIC_VALUE = "#SEPCITY";
const std::string ConfigFile::COMMENT_IDENTIFIER = "#";
const std::string ConfigFile::FIRST_WORD_SIZE = "SIZE:";
const std::string ConfigFile::FIRST_WORD_MONEY = "MONEY:";
const std::string ConfigFile::FIRST_WORD_MAP = "MAP:";
const std::string ConfigFile::ALLOWED_FIELDS = "GWOT ";
const std::regex ConfigFile::REGEX_SPACE(" +");
const std::regex ConfigFile::REGEX_LEADING_WHITESPACE("^ +");
const char ConfigFile::FIELD_GRASS = 'G';
const char ConfigFile::FIELD_OBSTACLE = 'O';
const char ConfigFile::FIELD_WATER = 'W';
const char ConfigFile::FIELD_TOWNHALL = 'T';
const char ConfigFile::TOWNHALL_REPLACEMENT = '7';


const int ConfigFile::MONEY_MIN = 1;
const int ConfigFile::MONEY_MAX = std::numeric_limits<int>::max();
const int ConfigFile::HEIGHT_MIN = 1;
const int ConfigFile::HEIGHT_MAX = 100;
const int ConfigFile::WIDTH_MIN = 1;
const int ConfigFile::WIDTH_MAX = 100;

//------------------------------------------------------------------------------
ConfigFile::ConfigFile(const std::string file_name, Sep::Game &game) :
  file_name_(file_name), game_(game)
{
}

//------------------------------------------------------------------------------
ConfigFile::~ConfigFile() noexcept
{
  //destroy me
}

//------------------------------------------------------------------------------
bool ConfigFile::openFile()
{
  infile_.open(file_name_);
  if(!infile_)
  {
    return false;
  }
  return checkMagicValue();
}

//------------------------------------------------------------------------------
bool ConfigFile::checkMagicValue()
{
  std::string magic_value = ConfigFile::MAGIC_VALUE;
  std::string first_line;
  std::getline(infile_, first_line);
  if(!first_line.compare(magic_value))
  {
    return readLine();
  }
  else
  {
    return false;
  }
}

//------------------------------------------------------------------------------
bool ConfigFile::readLine()
{
  bool valid_config_file = true;
  bool size_exists = false;
  bool money_exists = false;
  bool map_exists = false;

  while(std::getline(infile_, line_))
  {
    if(!valid_config_file)
    {
      return false;
    }
    //skip comments
    if(line_ == "" || !line_.find_first_of(COMMENT_IDENTIFIER))
    {
      continue;
    }
    else
    {
      //replace whitspaces
      line_ = std::regex_replace(line_, REGEX_SPACE, " ");
      line_ = std::regex_replace(line_, REGEX_LEADING_WHITESPACE, "");
      std::string first_word = line_.substr(0, line_.find(' '));
      if(!first_word.compare(FIRST_WORD_SIZE) && !size_exists)
      {
        valid_config_file = sizeSetSuccessfully();
        size_exists = true;
      }
      else if(!first_word.compare(FIRST_WORD_MONEY) && !money_exists)
      {
        valid_config_file = moneySetSuccessfully();
        money_exists = true;
      }
      else if(money_exists && size_exists &&
              !first_word.compare(FIRST_WORD_MAP))
      {
        map_exists = true;
      }
      else if(map_exists)
      {
        if (line_.find_first_not_of(ALLOWED_FIELDS)!= std::string::npos ||
            line_.size() !=  static_cast<unsigned int>(game_.getWidth()))
        {
          return false;
        }
        config_map_.push_back(line_);
      }
      else
      {
        return false;
      }
    }
  }
  if(config_map_.size() != static_cast<unsigned int>(game_.getHeight()))
  {
    return false;
  }
  return mapSetSuccessfully();
}

//------------------------------------------------------------------------------
bool ConfigFile::sizeSetSuccessfully()
{
  std::istringstream iss(line_);
  std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
                                   std::istream_iterator<std::string>{}};
  if(tokens.size() != 3)
  {
    return false;
  }

  try
  {
    game_.setWidth(std::stoi(tokens.at(1)));
    game_.setHeight(std::stoi(tokens.at(2)));
  }
  catch(std::exception &e)
  {
    return false;
  }

  if(game_.getHeight() < HEIGHT_MIN
     || game_.getHeight() > HEIGHT_MAX
     || game_.getWidth() < WIDTH_MIN
     || game_.getWidth() > WIDTH_MAX )
  {
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
bool ConfigFile::moneySetSuccessfully()
{
  std::istringstream iss(line_);
  std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>{}};

  if(tokens.size() != 2)
  {
    return false;
  }

  try
  {
    game_.setMoney(std::stoi(tokens.at(1)));
  }
  catch(std::exception e)
  {
    return false;
  }

  if(game_.getMoney() < MONEY_MIN || game_.getMoney() > MONEY_MAX)
  {
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
bool ConfigFile::mapSetSuccessfully()
{
  if(!checkTownhall())
  {
    return false;
  }

  for (int row = 0; row < game_.getHeight(); row++)
  {
    std::vector<std::shared_ptr<Sep::Field>> vector_column;
    for (int column = 0; column < game_.getWidth(); column++)
    {
      if(config_map_.at(row).at(column) == FIELD_GRASS)
      {
        vector_column.push_back(Sep::Game::GRASSPTR);
      }
      else if(config_map_.at(row).at(column) == FIELD_WATER)
      {
        vector_column.push_back(Sep::Game::WATERPTR);
      }
      else if(config_map_.at(row).at(column) == FIELD_OBSTACLE)
      {
        vector_column.push_back(Sep::Game::OBSTACLEPTR);
      }
      else if(config_map_.at(row).at(column) == TOWNHALL_REPLACEMENT)
      {
        std::shared_ptr<Field> field = std::shared_ptr<Field>
          (new Townhall(row, column));
        vector_column.push_back( field);
        game_.setTownhalls(std::dynamic_pointer_cast<Townhall>(field));
      }
    }
    game_.setMap(vector_column);
  }
  if(game_.getTownhalls().size() == 0)
  {
    return false;
  }
  return true;
}

//------------------------------------------------------------------------------
bool ConfigFile::checkTownhall()
{
  for (int row = 0; row < game_.getHeight(); row++)
  {
    for (int column = 0; column < game_.getWidth(); column++)
    {
      if(config_map_.at(row).at(column) == FIELD_TOWNHALL)
      {
        if(!computeTownhallSizeAndCheckForm(row, column))
          return false;
      }
    }
  }
  return true;
}

//------------------------------------------------------------------------------
bool ConfigFile::computeTownhallSizeAndCheckForm(int row, int column)
{
  bool other_char = false;
  bool vertex_set = false;
  int count_townhall = 0;
  int upper_left_row = row;
  int upper_right_col;
  int lower_left_row;
  int upper_left_col = column;

  for(unsigned int i = column; i < config_map_.at(row).size(); i++)
  {
    if(config_map_.at(row).at(i) == FIELD_TOWNHALL && !other_char)
    {
      count_townhall++;
      if(count_townhall > 3)
      {
        return false;
      }
      if(i == config_map_.at(row).size() - 1)
      {
        upper_right_col = i;
      }
    }
    else
    {
      other_char = true;
      if(count_townhall <= 3 && !vertex_set)
      {
        upper_right_col = i - 1;
        vertex_set = true;
      }
    }
  }

  vertex_set = false;
  other_char = false;
  count_townhall = 0;

  for(unsigned int i = row; i < config_map_.size(); i++)
  {
    if(config_map_.at(i).at(column) == FIELD_TOWNHALL && !other_char)
    {
      count_townhall++;
      if(count_townhall > 3)
      {
        return false;
      }
      if(i == config_map_.size() - 1)
      {
        lower_left_row = i;
      }
    }
    else
    {
      other_char = true;
      if(count_townhall <= 3 && !vertex_set)
      {
        lower_left_row = i - 1;
        vertex_set = true;
      }
    }
  }
  return checkTownhallForm(upper_left_col, upper_left_row, upper_right_col,
                           lower_left_row);
}

//------------------------------------------------------------------------------
bool ConfigFile::checkTownhallForm(int upper_left_col, int upper_left_row,
                                   int upper_right_col, int lower_left_row)
{
  for(int row = upper_left_row; row <= lower_left_row; row++)
  {
    for(int col = upper_left_col; col <= upper_right_col; col++)
    {
      if(config_map_.at(row).at(col) != FIELD_TOWNHALL)
      {
        return false;
      }
      else
      {
        config_map_.at(row).at(col) = TOWNHALL_REPLACEMENT;
      }
    }
  }
  return checkTownhallNeighbours(upper_left_col, upper_left_row,
                                 upper_right_col, lower_left_row);
}

//------------------------------------------------------------------------------
bool ConfigFile::checkTownhallNeighbours(int upper_left_col,
                                         int upper_left_row,
                                         int upper_right_col,
                                         int lower_left_row)
{
  int rowMin = upper_left_row == 0 ? 0 : upper_left_row - 1;
  int rowMax = lower_left_row == (game_.getHeight() - 1)  ?
               (game_.getHeight() - 1) : lower_left_row + 1;
  int colMin = upper_left_col == 0 ? 0 : upper_left_col - 1;
  int colMax = upper_right_col == (game_.getWidth() - 1) ?
               (game_.getWidth() - 1) : upper_right_col + 1;
  for (int i = rowMin; i <= rowMax; i++)
  {
    for (int j = colMin; j <= colMax; j++)
    {
      if (config_map_.at(i).at(j) == FIELD_TOWNHALL)
      {
        return false;
      }
    }
  }
  return true;
}

//------------------------------------------------------------------------------
void ConfigFile::printConfigMap()
{
  for (auto row = 0; row < game_.getHeight(); row++)
  {
    for (auto column = 0; column < game_.getWidth(); column++)
    {
      std::cout << config_map_.at(row).at(column);
    }
    std::cout << std::endl;
  }
}