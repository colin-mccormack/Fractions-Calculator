// Header files
#include "IO.h"
#include "Operations.h"
#include "DataBase.h"


// Entry Point of Program
int main() {
  
  /*
  
    Showing the user menu.

  */

  showMenu();

  /*
  
    WHAT IS THIS CODE??
    IS THIS EVEN C?
    REALLY? 

    Yes this is C, we just copied
    the style used in Dynamically Typed 
    Languages like Lua, Java Script, etc.

    DataBase_ProgramCanRun() is from DataBase.h, which we call A for now.
    getResponse() is from IO.h, which we call B for now.
    getFunctionToRun() is from Operations.h, which we call C for now.

    A returns true if the program can still run,
    because a function interally called makes A return false
    so that when A is called next time this loop can stop.
    
    B gets response from the user, basically user input that
    tells the user what program should do next.

    C takes the user response, and returns the address
    to the function that can execute the task.

    We take that function and directly run it.

    This process is repeated until A returns false.


  */

  while(DataBase_ProgramCanRun()) 
    getFunctionToRun(getResponse())();
  
  return 0;
}
