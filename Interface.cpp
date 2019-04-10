//------------------------------------------------------------------------------
// Interface.cpp
//
// Authors: Tutors
//
//------------------------------------------------------------------------------
//

#include "Interface.h"

#include <iostream>
#include <algorithm>

//------------------------------------------------------------------------------
// include the system readline lib headers if readline make target is compiled
#ifdef USE_READLINE
  #include <readline/readline.h>
  #include <readline/history.h>
#endif

using Sep::Interface;

//------------------------------------------------------------------------------
//choose the right library for your system
#if defined(__i386) || defined(_M_IX86)
  #define OS_ARCH_X86_32
#elif defined(__x86_64__) || defined(_M_X64)
  #define OS_ARCH_X86_64
#else
  #error "OS architecture not supported"
#endif

#if defined(_WIN32) || defined(_WIN64)
  #define OS_WINDOWS
  #include <windows.h>
  #undef ERROR
  #ifdef OS_ARCH_X86_32
    const std::string Interface::lib_name_ = "lib\\libweb_win_i386.dll";
  #elif defined(OS_ARCH_X86_64)
    const std::string Interface::lib_name_ = "lib\\libweb_win_amd64.dll";
  #else
    const std::string Interface::lib_name_ = "";
  #endif
#elif defined(__linux__)
  #define OS_LINUX
  #include <dlfcn.h>
  #ifdef OS_ARCH_X86_32
    const std::string Interface::lib_name_ = "lib/libweb_lin_i386.so";
  #elif defined(OS_ARCH_X86_64)
    const std::string Interface::lib_name_ = "lib/libweb_lin_amd64.so";
  #else
    const std::string Interface::lib_name_ = "";
  #endif
#elif defined(__APPLE__) || defined(__MACH__)
  #define OS_MACOS
  #include <dlfcn.h>
  const std::string Interface::lib_name_ = "lib/libweb_mac.so";
#else
  #error "Operating system not supported."
  const std::string Interface::lib_name_ = "";
#endif

//------------------------------------------------------------------------------
// static constants
const std::string Interface::ERROR_WRONG_ARGUMENTS =
  "Usage: ./sepcity <config-file> [use_web]";
const std::string Interface::ERROR_BAD_ALLOC = "Memory error!";
const std::string Interface::ERROR_INVALID_CONFIG = "Invalid Config File!";

const std::string Interface::WARNING_UNKNOWN_COMMAND = "Unknown command!";
const std::string Interface::WARNING_WRONG_PARAMETER =
  "Wrong command parameter!";

const std::string Interface::INFO_NOT_ENOUGH_MONEY = "Insufficient funds!";
const std::string Interface::INFO_CANNOT_DESTROY = "Field can't be destroyed!";
const std::string Interface::INFO_OUTSIDE_BOARD =
  "Coordinates are outside the board!";
const std::string Interface::INFO_GRASS_ONLY = "Can only build on Grass!";
const std::string Interface::INFO_MAX_SIZE = "Max Building size is 3x3!";
const std::string Interface::INFO_CONNECTION =
  "Building must be connected to street network!";
const std::string Interface::INFO_SPACING =
  "Can not build directly next to other building!";
const std::string Interface::INFO_HOME_ONLY = "Emergency Home only!";
const std::string Interface::INFO_OUT_OF_MONEY = "You are fired!";
const std::string Interface::INFO_ROUND_NUM = "Round: ";
const std::string Interface::INFO_QUIT_MSG =
  "Stealing money and skipping town.";
const std::vector<std::string> Interface::INFO_HELP_MSGS =
{
  "Available Commands:",
  "  Play [<rounds>]",
  "    Simulate the City for a given number of rounds (default 1 round).",
  "  Build [Street] [Obstacle] [Water] <x> <y>",
  "    Build a Field element at position x y.",
  "  Build [Home] [Clinic] [Market] <x> <y> <width> <height>",
  "    Build a Building of size width * height at position x y.",
  "  Destroy <x> <y>",
  "    Destroy something at position x y.",
  "  Emergency <x> <y>",
  "    Deploy ambulance to home at x y.",
  "  Quit",
  "    End the game.",
  "  Help",
  "    Display this help."
};

const std::string Interface::COMMAND_BUILD = "build";
const std::string Interface::COMMAND_DESTROY = "destroy";
const std::string Interface::COMMAND_PLAY = "play";
const std::string Interface::COMMAND_EMERGENCY = "emergency";
const std::string Interface::COMMAND_HELP = "help";
const std::string Interface::COMMAND_QUIT = "quit";

const std::string Interface::COMMAND_PROMPT = "sepcity> ";

const std::map<const Interface::OutputType, const std::string>
  Interface::PROTOCOL =
{
  {DEBUG, "[DEBUG]"},
  {ERROR, "[ERROR]"},
  {WARNING, "[WARNING]"},
  {INFO, "[INFO]"},
  {SETTING, "[SETTING]"},
  {MONEY, "[MONEY]"},
  {RESIDENTS, "[RESIDENTS]"}
};
const std::string Interface::PROTOCOL_MAP = "[BOARD]";
const std::string Interface::PROTOCOL_CAR = "[CAR]";

const std::map<const Interface::OutputType, const std::string>
  Interface::COLOR_TEXT =
{
  {DEBUG, "\033[0m"},
  {ERROR, "\033[31m"}, //RED
  {WARNING, "\033[31m"}, //RED
  {INFO, "\033[34m"}, //BLUE
  {SETTING, "\033[0m"},
  {MONEY, "\033[0m"},
  {RESIDENTS, "\033[0m"}
};
const std::map<const Sep::Field::FieldType, const std::string>
  Interface::COLOR_MAP =
{
  {Field::FieldType::GRASS, "\033[32;42m"}, //green text on green bg
  {Field::FieldType::WATER, "\033[34;44m"}, //blue text on blue bg
  {Field::FieldType::OBSTACLE, "\033[30;42m"}, //black text on green bg
  {Field::FieldType::STREET, "\033[37;47m"}, //white text on white bg
  {Field::FieldType::HOME, "\033[37;40m"}, //white text on black bg
  {Field::FieldType::MARKET, "\033[37;40m"}, //white text on black bg
  {Field::FieldType::CLINIC, "\033[37;41m"}, //white text on red bg
  {Field::FieldType::TOWNHALL, "\033[35;45m"}, //magenta text on magenta bg
};
const std::string Interface::COLOR_AMBULANCE = "\033[31;47m";
const std::string Interface::COLOR_END = "\033[0m";

const std::string Interface::OUT_MAP = "[MAP]";
const std::string Interface::OUT_AMBULANCE = "A";

//------------------------------------------------------------------------------
// static member
Web::Interface* Interface::web_ = NULL;
void* Interface::io_lib_ = NULL;

//------------------------------------------------------------------------------
Interface::Interface() : instance_id_(0)
{
}

//------------------------------------------------------------------------------
Interface::Interface(unsigned int id) : instance_id_(id)
{
}

//------------------------------------------------------------------------------
Interface::~Interface() noexcept
{
  #ifdef USE_READLINE
    clear_history();
  #endif
}

//------------------------------------------------------------------------------
int Interface::start(bool use_web, std::function<int(unsigned int)> play)
{
  if(use_web)
  {
    #ifdef OS_WINDOWS
      io_lib_ = (void*)LoadLibrary(lib_name_.c_str());
    #else
      io_lib_ = dlopen(lib_name_.c_str(), RTLD_LAZY);
    #endif

    if(io_lib_ == nullptr)
    {
      std::cout << "Failed to load library: using fallback solution!"
                << std::endl;
      return play(0); //start game
    }

    #ifdef OS_WINDOWS
      WEBINTERFACE_FACTORYFUNC factory = (WEBINTERFACE_FACTORYFUNC)
        GetProcAddress((HINSTANCE)io_lib_, "makePlugin");
    #else
      WEBINTERFACE_FACTORYFUNC factory = (WEBINTERFACE_FACTORYFUNC)
        dlsym(io_lib_, "makePlugin");
    #endif

    if(!factory)
    {
      std::cout << "Failed to load library functions: using fallback solution!"
                << std::endl;
      return play(0); //start game
    }

    web_ = factory(); //create instance of webserver

    return web_->start(play); //start webserver
  }
  else
  {
    return play(0); //start game
  }
}

//------------------------------------------------------------------------------
void Interface::stop() noexcept
{
  if(web_ != nullptr)
  {
    web_->stop();

    delete web_;

    #ifdef OS_WINDOWS
      FreeLibrary((HINSTANCE)io_lib_);
    #else
      dlclose(io_lib_);
    #endif
  }
  web_ = nullptr;
}

//------------------------------------------------------------------------------
void Interface::out(const std::vector<std::vector<Field::FieldType>> board,
  const std::vector<std::pair<int, int>> cars) const
{
  if(web_ == nullptr)
  {
    std::cout << OUT_MAP << std::endl;
  }
  for(unsigned int y = 0; y < board[0].size(); y++)
  {
    for(unsigned int x = 0; x < board.size(); x++)
    {
      if(web_ == nullptr)
      {
        auto it = std::find(cars.begin(), cars.end(), std::pair<int,int>(x,y));
        if (it == cars.end())
        {
          #ifdef USE_COLOR
            std::cout << COLOR_MAP.at(board[x][y])
                      << Field::getName(board[x][y])[0]
                      << COLOR_END;
          #else
            std::cout << Field::getName(board[x][y])[0];
          #endif
        }
        else
        {
          #ifdef USE_COLOR
            std::cout << COLOR_AMBULANCE << OUT_AMBULANCE << COLOR_END;
          #else
            std::cout << OUT_AMBULANCE;
          #endif
        }
      }
      else
      {
        web_->write(instance_id_, PROTOCOL_MAP + " " + std::to_string(x) + " " +
          std::to_string(y) + " " + Field::getName(board[x][y]));
        //clear all cars
        web_->write(instance_id_, PROTOCOL_CAR + " " + std::to_string(x) + " " +
          std::to_string(y) + " 0");
      }
    }
    if(web_ == nullptr)
    {
      std::cout << std::endl;
    }
  }

  if(web_ != nullptr)
  {
    for(std::pair<int, int> car : cars)
    {
      web_->write(instance_id_, PROTOCOL_CAR + " " + std::to_string(car.first) +
        " " + std::to_string(car.second) + " 1");
    }
  }
}

//------------------------------------------------------------------------------
void Interface::out(const OutputType type, const std::string msg) const
{
  if(web_ != nullptr)
  {
    web_->write(instance_id_, PROTOCOL.at(type) + " " + msg);
  }
  else
  {
    std::cout
    #ifdef USE_COLOR
      << COLOR_TEXT.at(type)
    #endif
      << PROTOCOL.at(type) + " " + msg
    #ifdef USE_COLOR
      << COLOR_END
    #endif
      << std::endl;
  }
}

//------------------------------------------------------------------------------
std::string Interface::in() const
{
  if(web_ != nullptr)
  {
    return web_->read(instance_id_);
  }
  else
  {
    std::string input_string;

    #ifndef USE_READLINE
      // Display prompt
      std::cout << COMMAND_PROMPT << std::flush;
      std::getline(std::cin, input_string);

      if(std::cin.eof())
        input_string = Interface::COMMAND_QUIT;
    #else
      char* buf = readline(COMMAND_PROMPT.c_str());

      if(buf == NULL)
      {
        input_string = Interface::COMMAND_QUIT;
      }
      else
      {
        input_string = std::string(buf);

        if (strlen(buf) > 0)
        {
          add_history(buf);
        }

        free(buf);
      }
    #endif

    return input_string;
  }
}

//------------------------------------------------------------------------------
void Interface::log(const std::string msg) const
{
  #ifndef RELEASE
    out(DEBUG, msg);
  #endif
}

//------------------------------------------------------------------------------
void Interface::error(const std::string msg)
{
  std::cout << PROTOCOL.at(ERROR) << " " << msg << std::endl;
}

//------------------------------------------------------------------------------
void Interface::error(const char* const msg)
{
  std::cout << PROTOCOL.at(ERROR) << " " << msg << std::endl;
}

//------------------------------------------------------------------------------
int Interface::defaultCallback(int id)
{
  return 0;
}

//------------------------------------------------------------------------------
void Interface::setWebinterface(Web::Interface* web)
{
  web_ = web;
}
