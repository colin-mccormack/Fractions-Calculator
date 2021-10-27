/*

  IO

  IO also stands for Input/Output, as its name suggests, this library
  contains functions that allow the program to interact with user, and
  vice versa.

  This library forms an interface between user and the computer.

*/

#include <stdio.h>
#include <stdlib.h>
#include "IO.h"

/*

    void showMenu(int *choice);
  
    This function is responsible for showing available
    options on the screen.

    It takes in an pointer to a variable local to the 
    callent function and assigns the value (or option)
    given by the user.
  
*/

void showMenu() {

  //Clearing Console of everything in it.
  //To read more about this check out : https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
  printf("\e[1;1H\e[2J");

  // Printing the options.
  printf("Options:\n");
  printf ("1. Create Random Fraction\n");
  printf ("2. Get Fraction From User\n");
  printf ("3. Display Fractions\n");
  printf ("4. Add Fractions\n");
  printf ("5. Subtract Fractions\n");
  printf ("6. Divide Fractions\n");
  printf ("7. Multiply\n");
  printf ("8. Display All Equations\n");
  printf ("9. Quit\n");

}

/*

  int getResponse();


  This function is responsible for prompting user to
  enter values for the fraction.

  Prompts user again and again until user enters a 
  valid fraction.

*/

int getResponse() {


  int choice;

  // Displaying Question
  printf ("\nPlease choose an option:\n>");

  // Getting Input
  scanf ("%i", &choice);
  
  // Clearing Buffer  
  fflush(stdin);

  // Returing the option.
  return choice;
}
/*

  void ClearConsole();

  This function clears the entire console.

  And displays the menu options again.

*/

void ClearConsole() {

  fflush(stdin);

  showMenu();
}


/*

  Function for validating fraction

*/


static int ValidateFraction(int numerator, int denominator) {
  return 
    numerator   > IO_MIN_NUMERATOR   && // These symbolic constatns are in IO.h
    numerator   < IO_MAX_NUMERATOR   &&
    denominator > IO_MIN_DENOMINATOR &&
    denominator < IO_MAX_DENOMINATOR ;

}

/*

  void getUserFraction (int *numer, int *denom);
  
    This function is responsible for prompting user to
    enter values for the fraction.

    Prompts again and again until user enters a valid fraction.
  
*/


void getUserFraction (int *numer, int *denom) {
  
  /*

    Get a valid fraction from the user
    by prompting for valid input until valid input is found.

    If no valid input then print error and run loop again.

  */

  //Initiate valid input flag
  int validInput = 0;

  //While input is invalid run loop
  while(!validInput) {
    
    /*
      
      Prompt user and store results
    
    */
    
    printf ("Please enter fraction numerator : ");
    //Variable already passed by refrence so this is equivlent to setting address for scanf argument
    scanf  ("%i", numer);
    
    printf ("Please enter fraction denomenator : ");
    //Variable already passed by refrence so this is equivlent to setting address for scanf argument
    scanf  ("%i", denom);

    /*
    
      Clear Buffer
    
    */
    fflush(stdin);

    /*
    
      Check if the fraction is valid.

      If valid, break out. 
      (Values are already passed to callent function, Pointers Remember!)
    
    */ 
    
    if(ValidateFraction(*numer,*denom))
      validInput = 1;
    else 
      printf("Invalid Fraction. Please Retry. \n");

    /*
    
      If valid set loop to not true since it doesn't need to run again.
      Else print error.

    */

  }

}
