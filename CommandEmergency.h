//------------------------------------------------------------------------------
// CommandEmergency.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------
//

#ifndef COMMANDEMERGENCY_H_INCLUDED
#define COMMANDEMERGENCY_H_INCLUDED

#include "Command.h"

namespace Sep
{
  //----------------------------------------------------------------------------
  // CommandEmergency class
  // Class to handle emergencies
  //
  class CommandEmergency : public Command
  {
  public:

    //------------------------------------------------------------------------
    // Standard constructor
    // @param name Name of the command destroy
    //
    CommandEmergency(std::string name);

    //------------------------------------------------------------------------
    // Deleted copy constructor
    //
    CommandEmergency(const CommandEmergency& original) = delete;

    //------------------------------------------------------------------------
    // Deleted assignment operator
    //
    CommandEmergency& operator=(const CommandEmergency& original) = delete;

    //------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandEmergency() noexcept;

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param game The game where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    //
    virtual bool execute(Game &game, std::vector<std::string> &params);
  };
}
#endif  // COMMANDEMERGENCY_H_INCLUDED