//------------------------------------------------------------------------------
// CommandManager.cpp
//
// Group: Group 18622, study assistant Roman Walch
//
// Authors: Christina Dionysio (01610877)
// Johannes Mayerhofer (11739820)
// Robert Ertl (01114419)
//------------------------------------------------------------------------------

#include "CommandManager.h"
#include "Command.h"
#include "CommandBuild.h"
#include "CommandDestroy.h"
#include "CommandQuit.h"
#include "CommandHelp.h"
#include "CommandPlay.h"
#include "CommandEmergency.h"
#include "Game.h"

using Sep::CommandManager;

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
CommandManager::CommandManager(Interface &io, Game &game)
  : game_(game), io_(io)
{
}

//------------------------------------------------------------------------------
CommandManager::~CommandManager() noexcept
{
}

//------------------------------------------------------------------------------
void CommandManager::start()
{
  std::map<std::string, std::unique_ptr<Command>> commands;
  commands[Interface::COMMAND_BUILD] =
    std::unique_ptr<Command>(new CommandBuild(Interface::COMMAND_BUILD));
  commands[Interface::COMMAND_DESTROY] =
    std::unique_ptr<Command>(new CommandDestroy(Interface::COMMAND_DESTROY));
  commands[Interface::COMMAND_HELP] =
    std::unique_ptr<Command>(new CommandHelp(Interface::COMMAND_HELP));
  commands[Interface::COMMAND_QUIT] =
    std::unique_ptr<Command>(new CommandQuit(Interface::COMMAND_QUIT));
  commands[Interface::COMMAND_PLAY] =
    std::unique_ptr<Command>(new CommandPlay(Interface::COMMAND_PLAY));
  commands[Interface::COMMAND_EMERGENCY] =
    std::unique_ptr<Command>(new CommandEmergency
                               (Interface::COMMAND_EMERGENCY));
  std::string input;
  while (true)
  {
    input = io_.in();
    //lower case transform
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    //string like a stream
    std::istringstream inputStream(input);
    std::vector<std::string>
      cmd{ std::istream_iterator<std::string>{inputStream},
           std::istream_iterator<std::string>{} };
    if (cmd.empty())
    {
      continue;
    }
    try
    {
      auto it = commands.find(cmd[0]);
      if (it != commands.end())
      {
        cmd.erase(cmd.begin());
        if (!it->second->execute(game_, cmd))
        {
          io_.out(Interface::WARNING, Interface::WARNING_WRONG_PARAMETER);
          continue;
        }
        if (it->first == Interface::COMMAND_QUIT)
        {
          break;
        }
        if (it->first == Interface::COMMAND_PLAY && game_.getMoney() < 0)
        {
          break;
        }
      }
      else {
        io_.out(Interface::WARNING, Interface::WARNING_UNKNOWN_COMMAND);
        continue;
      }
    }
    catch (const std::invalid_argument &e)
    {
      io_.out(Interface::WARNING, Interface::WARNING_WRONG_PARAMETER);
      continue;
    }
    catch (const std::out_of_range &e)
    {
      io_.out(Interface::WARNING, Interface::WARNING_WRONG_PARAMETER);
      continue;
    }
  }
}