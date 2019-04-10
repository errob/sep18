//------------------------------------------------------------------------------
// Filename: main.cpp
// Description: simple main
// Authors: Tutors
// Tutor: Tutors
// Group: 42
// Created: 32.13.2048
// Last change: 33.13.2048
//------------------------------------------------------------------------------

#include "Interface.h"
#include "Field.h"
#include "Game.h"

#include <iostream>



namespace Sep
{
  static constexpr int RETURN_OK = 0;
  static constexpr int RETURN_ERROR_BAD_CONFIG = -1;
  static constexpr int RETURN_ERROR_ALLOC = -2;
  static constexpr int RETURN_ERROR_FRAMEWORK = -3;
  static constexpr int RETURN_ERROR_ARGUMENT = -4;
}

//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param *argv argument values
// @return return value for the OS
//
int main(int argc, char *argv[])
{
  bool use_web = false;
  if (argc != 2 && argc != 3)
  {
    Sep::Interface::error(Sep::Interface::ERROR_WRONG_ARGUMENTS);
    return Sep::RETURN_ERROR_ARGUMENT;
  }

  if (argc == 3)
  {
    if (std::string(argv[2]) == "use_web")
    {
      use_web = true;
    }
    else
    {
      Sep::Interface::error(Sep::Interface::ERROR_WRONG_ARGUMENTS);
      return Sep::RETURN_ERROR_ARGUMENT;
    }
  }

  try
  {
    Sep::Interface::start(use_web);
    Sep::Interface io;
    Sep::Game game(io, std::string(argv[1]));
    game.run();
    Sep::Interface::stop();
    return Sep::RETURN_OK;
  }

  catch (std::bad_alloc &e)
  {
    Sep::Interface::error(Sep::Interface::ERROR_BAD_ALLOC);
    Sep::Interface::stop();
    return Sep::RETURN_ERROR_ALLOC;
  }
  catch (Web::InterfaceDisconnect &e)
  {
    Sep::Interface::error(e.what());
    Sep::Interface::stop();
    return Sep::RETURN_ERROR_FRAMEWORK;
  }
  catch (Web::InterfaceException &e)
  {
    Sep::Interface::error(e.what());
    Sep::Interface::stop();
    return Sep::RETURN_ERROR_FRAMEWORK;
  }
    // catch errorhandling config file
  catch (std::invalid_argument &e)
  {
    Sep::Interface::error(e.what());
    Sep::Interface::stop();
    return Sep::RETURN_ERROR_BAD_CONFIG;
  }
}
