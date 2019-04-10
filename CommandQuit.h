//------------------------------------------------------------------------------
// CommandQuit.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#ifndef COMMANDQUIT_H_INCLUDED
#define COMMANDQUIT_H_INCLUDED

#include "Command.h"

namespace Sep
{

  //----------------------------------------------------------------------------
  // Command Quit Class
  // class to handle quit commands
  //
  class CommandQuit : public Command
  {
  public:

    //--------------------------------------------------------------------------
    // Constructor
    // @param name command name
    //
    CommandQuit(std::string name);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandQuit() noexcept;

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param game The game where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    //
    virtual bool execute(Game &game, std::vector<std::string> &params);
  };
}
#endif //COMMANDQUIT_H_INCLUDED