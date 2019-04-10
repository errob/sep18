//------------------------------------------------------------------------------
// WebInterface.h
//
// Authors: Tutors
//
//------------------------------------------------------------------------------
//

#ifndef INCLUDE_WEBINTERFACE_H
#define INCLUDE_WEBINTERFACE_H

#include <string>
#include <functional>
#include <exception>

//------------------------------------------------------------------------------
namespace Web
{
  //----------------------------------------------------------------------------
  // InterfaceDisconnect exception
  // Is thrown when the Interface is disconnected unexpectedly
  //
  class InterfaceDisconnect : public std::exception
  {
    public:
      //------------------------------------------------------------------------
      // Overwrite the what-function
      //
      virtual const char* what() const throw()
      {
        return "Disconnect!";
      }
  };
}

//------------------------------------------------------------------------------
namespace Web
{
  //----------------------------------------------------------------------------
  // InterfaceDisconnect exception
  // Is thrown when the Interface gets an uncexpected error
  //
  class InterfaceException : public std::exception
  {
    public:
      //------------------------------------------------------------------------
      // Overwrite the what-function
      //
      virtual const char* what() const throw()
      {
        return "This should not have happened!!!\n"
               "  If you are not able to resolve the problem\n"
               "  with the previous error message contact us through\n"
               "  the News Group.";
      }
  };
}

//------------------------------------------------------------------------------
namespace Web
{
  //----------------------------------------------------------------------------
  // Interface class
  // This class provides an API to use the Web-GUI
  //
  class Interface
  {
    public:
      //------------------------------------------------------------------------
      // Standard constructor
      //
      Interface() {};

      //------------------------------------------------------------------------
      // Destructor
      //
      virtual ~Interface() noexcept {};

      //------------------------------------------------------------------------
      // Pure virtual method to start the interface
      // @param play_callback The function called by the server
      //                      when a new connection is opened
      // @return Errorcode
      //
      virtual int start(std::function<int(unsigned int)> play_callback) = 0;

      //------------------------------------------------------------------------
      // Pure virtaul method to stop the interface
      //
      virtual void stop() noexcept = 0;

      //------------------------------------------------------------------------
      // Pure virtaul method to read from the interface
      // @param id The id of the connection
      // @return The read string
      //
      virtual std::string read(unsigned int id) = 0;

      //------------------------------------------------------------------------
      // Pure virtaul method to write to interface
      // @param id The id of the connection
      // @param msg The string to be written
      //
      virtual void write(unsigned int id, std::string msg) = 0;
  };
}

//------------------------------------------------------------------------------
// Factory function definition for Web Interface creation
//
typedef Web::Interface *(*WEBINTERFACE_FACTORYFUNC)();

#endif /* end of include guard: INCLUDE_WEBINTERFACE_H */
