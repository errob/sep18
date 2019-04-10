//------------------------------------------------------------------------------
// CommandDestroy.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#ifndef COMMANDDESTROY_H_INCLUDED
#define COMMANDDESTROY_H_INCLUDED

#include "Command.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Command Destroy Class
  // class to handle destructions
  //
  class CommandDestroy : public Command
  {
  public:

    //--------------------------------------------------------------------------
    // Constructor
    // @param name Name of the command destroy
    //
    CommandDestroy(std::string name);


    //--------------------------------------------------------------------------
    // Destructor
    virtual ~CommandDestroy() noexcept;


    //--------------------------------------------------------------------------
    // Executes the command.
    // @param game The game where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    //
    virtual bool execute(Game &game, std::vector<std::string> &params);
  };
}
#endif //COMMANDDESTROY_H_INCLUDED