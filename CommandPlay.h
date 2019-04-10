//------------------------------------------------------------------------------
// CommandPlay.h
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#ifndef COMMANDPLAY_H_INCLUDED
#define COMMANDPLAY_H_INCLUDED

#include "Command.h"
#include "Interface.h"

namespace Sep
{

  //----------------------------------------------------------------------------
  // Command Play Class
  // class to handle play command
  //
  class CommandPlay : public Command
  {
  public:

    //--------------------------------------------------------------------------
    // Constructor
    // @param name command name
    //
    CommandPlay(std::string name);

    //--------------------------------------------------------------------------
    // Destructor
    //
    virtual ~CommandPlay() noexcept;

    //--------------------------------------------------------------------------
    // Executes the command.
    // @param game The game where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    //
    virtual bool execute(Game &game, std::vector<std::string> &params);
  };
}
#endif //COMMANDPLAY_H_INCLUDED