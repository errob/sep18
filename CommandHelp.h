//----------------------------------------------------------------------------
// CommandHelp.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------


#ifndef COMMANDHELP_H
#define COMMANDHELP_H

#include "Command.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Command Help Class
  // class to handle command help
  //
  class CommandHelp : public Command
  {
  public:

    //------------------------------------------------------------------------
    // Constructor
    // @param name userinput command name
    //
    CommandHelp(std::string name);

    //------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandHelp() noexcept;

    //------------------------------------------------------------------------
    // Executes the command.
    // @param game The game where action should be performed on
    // @param params Possible parameters needed for the execution
    // @return bool representing the success of the action
    //
    virtual bool execute(Game &game, std::vector<std::string> &params);
  };
}
#endif //COMMANDHELP_H
