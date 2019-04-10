//------------------------------------------------------------------------------
// Interface.h
//
// Authors: Tutors
//
//------------------------------------------------------------------------------
//

#ifndef INCLUDE_INTERFACE_H
#define INCLUDE_INTERFACE_H

#include <string>
#include <vector>
#include <map>
#include <functional>

#include "Field.h"
#include "lib/Interface.h"

//------------------------------------------------------------------------------
namespace Sep
{
  //----------------------------------------------------------------------------
  // Interface Class
  // This class provides an API to either use the Web-GUI or
  // the command-line-interface
  //
  class Interface
  {
    private:
      //------------------------------------------------------------------------
      // Name of the dynamic library to be loaded
      // The name is set by the precompiler
      //
      static const std::string lib_name_;

      //------------------------------------------------------------------------
      // Pointer to the instance of the webserver if gui is enabled
      //
      static Web::Interface *web_;

      //------------------------------------------------------------------------
      // Pointer to the loaded library
      //
      static void *io_lib_;

      //------------------------------------------------------------------------
      // Instance identfier for multiple parallel games
      // Not supported by the default server!
      //
      int instance_id_;

      //------------------------------------------------------------------------
      // Fallback callback handler
      // Used if no parallel games are required
      // @param id Instance identfier for multiple parallel games
      //
      static int defaultCallback(int id);

    public:
      //------------------------------------------------------------------------
      // Standard constructor
      //
      Interface();

      //------------------------------------------------------------------------
      // Overloaded constructor to assign an id
      //
      Interface(unsigned int id);

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Interface() noexcept;

      //------------------------------------------------------------------------
      // Deleted copy constructor
      //
      Interface(const Interface& original) = delete;

      //------------------------------------------------------------------------
      // Deleted assignment operator
      //
      Interface& operator=(const Interface& original) = delete;

      //------------------------------------------------------------------------
      // Enumeration of all supported output formats
      //
      enum OutputType {DEBUG, ERROR, WARNING, INFO, SETTING, MONEY, RESIDENTS};

      //------------------------------------------------------------------------
      // Constants
      // "All" strings required for the desired outputs (to minimize typos)
      //
      const static std::string ERROR_WRONG_ARGUMENTS; //OutputType: ERROR
      const static std::string ERROR_BAD_ALLOC; //OutputType: ERROR
      const static std::string ERROR_INVALID_CONFIG; //OutputType ERROR
      const static std::string ERROR_FRAMEWORK; //OutputType ERROR

      const static std::string WARNING_UNKNOWN_COMMAND; //OutputType: WARNING
      const static std::string WARNING_WRONG_PARAMETER; //OutputType: WARNING

      const static std::string INFO_NOT_ENOUGH_MONEY; //OutputType: INFO
      const static std::string INFO_CANNOT_DESTROY; //OutputType: INFO
      const static std::string INFO_OUTSIDE_BOARD; //OutputType: INFO
      const static std::string INFO_GRASS_ONLY; //OutputType: INFO
      const static std::string INFO_MAX_SIZE; //OutputType: INFO
      const static std::string INFO_CONNECTION; //OutputType: INFO
      const static std::string INFO_SPACING; //OutputType: INFO
      const static std::string INFO_HOME_ONLY; //OutputType: INFO
      const static std::string INFO_OUT_OF_MONEY; //OutputType: INFO
      const static std::string INFO_ROUND_NUM; //OutputType: INFO
      const static std::string INFO_QUIT_MSG; //OutputType: INFO
      const static std::vector<std::string> INFO_HELP_MSGS; //OutputType: INFO

      const static std::string COMMAND_BUILD;
      const static std::string COMMAND_DESTROY;
      const static std::string COMMAND_PLAY;
      const static std::string COMMAND_EMERGENCY;
      const static std::string COMMAND_HELP;
      const static std::string COMMAND_QUIT;

      const static std::string COMMAND_PROMPT;

      const static std::map<const OutputType, const std::string> PROTOCOL;
      const static std::string PROTOCOL_MAP;
      const static std::string PROTOCOL_CAR;

      const static std::map<const OutputType, const std::string> COLOR_TEXT;
      const static std::map<const Field::FieldType, const std::string>
            COLOR_MAP;
      const static std::string COLOR_AMBULANCE;
      const static std::string COLOR_END;

      const static std::string OUT_MAP;
      const static std::string OUT_AMBULANCE;

      //------------------------------------------------------------------------
      // The start function
      // Is used to start the chosen interface
      // Has to be called before creating an interface-instance
      // @param use_web True if the Web-GUI should be used
      //                False for the standard command-line-interface
      // @return Errorcode
      //
      static int start(bool use_web, std::function<int(unsigned int)> callback
        = defaultCallback);

      //------------------------------------------------------------------------
      // The stop function
      // Stops the chosen interface
      // Has to be called before exiting the program
      //
      static void stop() noexcept;

      //------------------------------------------------------------------------
      // The in funciton
      // Getting the user input from the chosen interface
      // Should be used instead of std::cin
      // @return std::string one line of input
      //
      std::string in() const;

      //------------------------------------------------------------------------
      // The out funciton
      // Writes an output to the chosen interface
      // Should be used instead of std::cout
      // @param type the output type of the message
      // @param msg the actual message to print
      //
      void out(const OutputType type, const std::string msg) const;

      //------------------------------------------------------------------------
      // The map-out function
      // Writes the current board and the position of the cars to the chosen
      // Interface
      //
      // @param board 2-dimensional vector containing FieldType for each (x,y)
      //   coordinate on the map.
      // @param cars Optional parameter for output of all cars on the map, it
      //   contains the (x,y) position of every dispatched Ambulance on the map.
      //
      void out(const std::vector<std::vector<Field::FieldType>> board,
          const std::vector<std::pair<int, int>> cars = {}) const;

      //------------------------------------------------------------------------
      // The log function
      // Writes debug messages to the chosen interface
      // (Automatically disabled in RELEASE mode)
      // @param msg the debug message to be printed
      //
      void log(const std::string msg) const;

      //------------------------------------------------------------------------
      // The error functions
      // Prints error messages to the chosen interface.
      // Must only be used before ending the game with an error
      // @param msg the error message to be printed
      //
      static void error(const std::string msg);
      static void error(const char* const msg);

      //------------------------------------------------------------------------
      // Setter Methods
      // Sets the webinterface
      // @param web The used Web-Interface
      //
      static void setWebinterface(Web::Interface* web);
  };
}

#endif /* end of include guard: INCLUDE_INTERFACE_H */
