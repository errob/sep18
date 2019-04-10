//----------------------------------------------------------------------------
// CommandBuild.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#ifndef COMMANDBUILD_H_INCLUDED
#define COMMANDBUILD_H_INCLUDED

#include "Command.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // Command Build Class
  // class to handle command build
  //
  class CommandBuild : public Command
  {
  public:

    //------------------------------------------------------------------------
    // Constructor
    // @param name userinput command name
    //
    CommandBuild(std::string name);


    //------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandBuild() noexcept;

    //------------------------------------------------------------------------
    // Executes the command.
    // @param game The game where action should be performed on
    // @param params Possible parameters needed for the execution
    // @return Integer representing the success of the action
    //
    virtual bool execute(Game &game, std::vector<std::string> &params);
  };
}
#endif //COMMANDBUILD_H_INCLUDED