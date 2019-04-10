//------------------------------------------------------------------------------
// ConfigFile.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef CONFIGFILE_H_INCLUDED
#define CONFIGFILE_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream> 
#include <regex>

#include "Game.h"

namespace Sep
{

  //----------------------------------------------------------------------------
  // Config File Class
  // class to create ConfigFile handling
  //
  class ConfigFile
  {
    private:

      //------------------------------------------------------------------------
      // variable to store name of file
      //
      std::string file_name_;

      //------------------------------------------------------------------------
      // variable to file
      //
      std::ifstream infile_;

      //------------------------------------------------------------------------
      // variable to store current line read in from config file
      //
      std::string line_;

      //------------------------------------------------------------------------
      // variable to store map from config file to validate
      //
      std::vector<std::string> config_map_;

      //------------------------------------------------------------------------
      // Reference to current game
      //
      Game & game_;

      //------------------------------------------------------------------------
      // print Config Map method
      // to print Config Maps for test purposes
      //
      void printConfigMap();

    public:

      //------------------------------------------------------------------------
      // Standard constructor
      // @param file_name String to save config file name
      // @param game Game to set members
      //
      ConfigFile(std::string file_name, Game &game);


      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      ConfigFile (const ConfigFile& original) = delete;


      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      ConfigFile& operator=(const ConfigFile& original) = delete;


      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~ConfigFile() noexcept;


      //------------------------------------------------------------------------
      // Constants
      // "All" strings required to check config file (to minimize typos)
      //
      const static std::string MAGIC_VALUE;
      const static std::string COMMENT_IDENTIFIER;
      const static std::string FIRST_WORD_SIZE;
      const static std::string FIRST_WORD_MONEY;
      const static std::string FIRST_WORD_MAP;
      const static std::regex REGEX_SPACE;
      const static std::regex REGEX_LEADING_WHITESPACE;
      const static std::string ALLOWED_FIELDS;
      const static char FIELD_GRASS;
      const static char FIELD_OBSTACLE;
      const static char FIELD_WATER;
      const static char FIELD_TOWNHALL;
      const static char TOWNHALL_REPLACEMENT;


      const static int MONEY_MIN;
      const static int MONEY_MAX;
      const static int HEIGHT_MIN;
      const static int HEIGHT_MAX;
      const static int WIDTH_MIN;
      const static int WIDTH_MAX;


      //------------------------------------------------------------------------
      // openFile method
      // opens config File
      // @return returns if Filename was valid and is open
      //
      bool openFile();


      //------------------------------------------------------------------------
      // MagicValue Check method
      // Checks if Config File comes with mandatory #SEPCITY line
      // @return returns if magicvalue was valid
      //
      bool checkMagicValue();


      //------------------------------------------------------------------------
      // readLine method
      // reads lines from config File, skips Comments replaces Whitespaces
      // @return returns if lines have been correctly read
      //
      bool readLine();


      //------------------------------------------------------------------------
      // Size method
      // checks for valid SIZE: parameters from config File and sets width and 
      // height in game
      // @return returns if size values were correct
      //
      bool sizeSetSuccessfully();


      //------------------------------------------------------------------------
      // Money method
      // checks for valid MONEY: parameters from config File and sets money in 
      // game
      // @return returns if money values were correct
      //
      bool moneySetSuccessfully();


      //------------------------------------------------------------------------
      // mapset method
      // checks for valid MAP: parameters from config File sets start Map
      // @return returns if map was valid
      //
      bool mapSetSuccessfully();


      //------------------------------------------------------------------------
      // checkTownhall method
      // checks for Towhnhall placements from config File
      // @return returns if Townhalls were valid
      //
      bool checkTownhall();


      //------------------------------------------------------------------------
      // compute Townhall Size & Form method
      // computes Townhall from File for allowed Size and Constelations
      // @param row Placement in rows
      // @param column Placement in columns
      // @return returns if Townhalls had the right size and form
      //
      bool computeTownhallSizeAndCheckForm(int row, int column);


      //------------------------------------------------------------------------
      // check Townhall form method
      // checks for valid Townhall Shape and Sizes
      // @param upper_left_col Upper left columns coordinates
      // @param upper_left_row Upper left rows coordinates
      // @param upper_right_col Upper right columns coordinates
      // @param lower_left_row Lower left rows coordinates
      // @return if Townhall form was valid
      bool checkTownhallForm(int upper_left_col, int upper_left_row, 
                             int upper_right_col, int lower_left_row);


      //------------------------------------------------------------------------
      // check Townhall Neighbours method
      // checks if Neighbour Fields of Townhall are empty
      // @param upper_left_col Upper left columns coordinates
      // @param upper_left_row Upper left rows coordinates
      // @param upper_right_col Upper right columns coordinates
      // @param lower_left_row Lower left rows coordinates
      // @return returns if Townhall had neighbours
      //
      bool checkTownhallNeighbours(int upper_left_col, int upper_left_row, 
                                   int upper_right_col, int lower_left_row);
  };
}

#endif  // CONFIGFILE_H_INCLUDED