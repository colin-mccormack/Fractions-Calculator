/*

  Operations

  This file is responsible for performing all types of calculations
  in our program, including Addition, Subtraction, Multiplication etc.

  How it works:

    caller function will provide getFunctionToRun() the option user has chosen,
    getFunctionToRun() will return pointer to the function based on userchoice to
    the main function. callent function will run that respective function.


  All functions follow a pattern, they return void (Nothing), and take in 0 
  arguments. To access data, they use functions from DataBase.h. To manipulate
  the data, even for that they use functions from DataBase.h

  ONLY getFunctionToRun() is visible outside of this file.

*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "IO.h"
#include "DataBase.h"

/*

    User Choices

*/

#define OP_GENERATE_RANDOM_FRACTION  1
#define OP_GET_FRACTIONS             2  
#define OP_DISPLAY_FRACTIONS         3 

#define OP_ADD_FRACTIONS             4
#define OP_SUB_FRACTIONS             5
#define OP_DIV_FRACTIONS             6
#define OP_MUL_FRACTIONS             7

#define OP_DISPLAY_ALL_EQUATIONS     8

#define OP_QUIT_PROGRAM              9

/*

  Error Messages

*/

#define DISPLAY_FRACTION_LIMIT_REACHED_ERROR printf("Fractions Limit Reached\n");
#define DISPLAY_INVALID_OPTION_ERROR         printf("No working case. Retry.\n");

/*

  Data type of our function, this is the data type
  to store the returned function used by the main function.

*/

typedef void function();

/*

  These are the function that perform all sorts of calculations.
  These are abstracted, and only the pointer to these are returned
  to the main function, and main function can indirectly use the pointer
  to run this function.

*/

void CreateRandomFraction();
void GetFractionFromUser();
void DisplayFractions();

void AddFractions();
void SubtractFractions();
void MultiplyFractions();
void DivideFractions();

void DisplayAllEquations();

void QuitProgram();

void invalidCase();

/*

  function *getFunctionToRun(int Choice);

  This function takes in user choice, and returns
  reference to the function that completes the task
  that user wants the program to do. 


*/

function *getFunctionToRun(int Choice) {

  switch (Choice) {

    // If users wants to generat random fraction
    case OP_GENERATE_RANDOM_FRACTION:
      return &CreateRandomFraction;

    // If users wants the program to store a fraction
    case OP_GET_FRACTIONS:
      return &GetFractionFromUser;

    // If users wants to display stored fractions
    case OP_DISPLAY_FRACTIONS:
      return &DisplayFractions;

    // If users wants to add two fractions
    case OP_ADD_FRACTIONS: 
      return &AddFractions; 
      
    // If users wants to subtract two fractions
    case OP_SUB_FRACTIONS: 
      return  &SubtractFractions; 

    // If users wants to multiply two fractions
    case OP_MUL_FRACTIONS: 
      return &MultiplyFractions; 
      
    // If users wants to divide two fractions
    case OP_DIV_FRACTIONS: 
      return  &DivideFractions; 

    // If user wants to display all equations stored in
    case OP_DISPLAY_ALL_EQUATIONS:
      return &DisplayAllEquations;

    // If user wants to close the program
    case OP_QUIT_PROGRAM:
      return &QuitProgram;

    // This is an easter egg hidden, this clears the console,
    // this was added by us to see if you would suffer through this much code reading.
    case 256:
      return &ClearConsole;

    // If users gives us an invalid input.
    default:
      return &invalidCase; 
    
  }

}


/*

    Helper functions which will be eventually used.

    static functions because we are abstracting these.

*/

/*

  static int getGCD(int numRe, int denRe)

  GCD is an acronym for Greatest Common Factor

  Using eulicd's algorithm we efficently check for the gcd.
  This algorithm swaps the location of (a,b) each time,
  reducing the first term by the remainder from division of the second term each time.

*/

static int getGCD(int numRe, int denRe) {
  
  if (numRe == 0) return denRe;

  /*

  Using recursion this function will call itself until it gets to a return value,
  but will never 'unfold' recursivly since we are also returning the next function call.

  */

  return getGCD(denRe % numRe, numRe);
}

/*

    Used for Simplifying Fractions

*/

static void simplifyFractions(int *numerator, int *denominator) {

  int GCD = getGCD(*numerator,*denominator);

  *numerator   = *numerator   / GCD;
  *denominator = *denominator / GCD;
}


/*

  Used for Displaying Values in the form of Equation

  Print the fraction out in the format -> Fraction 1: 2/2 = 1/1

  Arguments in order are : 
    numerator 1,
    denomenator 1,
    numerator 2,
    denomenator 2,
    resulting numerator,
    resulting denominator.

*/

static void formatAndDisplayInEquation(int num1,int den1,int num2,int den2,int num,int den,char operator) {

  printf(
    "%i/%i %c %i/%i = %i/%i\n",
     num1, den1, operator, num2, den2,num, den
    );
}


/*

  Code for All the operation functions starts from here

*/

/*

  Option 1

  Create RandomFraction

*/

void CreateRandomFraction() {

  /*
  
    Checking if we have not reached the limit
    to add fractions.

    if we can add the fraction, then generate
    and add the fraction.

  */

  if (DataBase_canAddFraction()) {

  /*
  
    Setting a random seed, so that everytime 
    this function is called, it generates numbers 
    randomly, since the seed is being changed evertime.

    If you didn't understand what this does,
    then read it hear:
    https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
  
  */
  
   srand((unsigned int)rand());
  
  /*
  
    Generating random numerator and Denomerator
  
  */

    int num, den = 0;
    
    // Generator Numerator
    num = rand() % IO_MAX_NUMERATOR;
    
    // Generate Denominator
    //While loop checks if denominator is zero and if so regenerate until you get a valid one
    while(!den)
      den = rand() % IO_MAX_DENOMINATOR;

    /* 

      Its boring to have only positive fractions,
      so we flip coin to decide wether to make it negetive
      or positive.
    
    */ 
    if (rand() % 2)
      num = - num;

    /*
  
      Storing the generated fraction in our DataBase.
  
    */


    DataBase_addToStoredFractions(num, den);
    
  }

  /*
  
    If we cannot add fraction (if limit is reached),
    then tell user we cannot add the fraction.
  
  */
  else 
   DISPLAY_FRACTION_LIMIT_REACHED_ERROR
  
  
}


/*

  Option 2

  Get Fraction From User

*/


void GetFractionFromUser() {
  
  
  int num, den;
  
  /*
  
    Prompt users for fractions if there is still room to add fraction.
  
    (This function is from IO.h)

  */

  if (DataBase_canAddFraction()) {


    getUserFraction(&num, &den);
    
    

    /*
    
      Adding response to data base
    
      (This function is from DataBase.h)

    */

    DataBase_addToStoredFractions(num, den);

  } 


  
  else 
    
      DISPLAY_FRACTION_LIMIT_REACHED_ERROR
  

}

/*

  Option 3

  Display Elements

*/

/*

  void displayElements(int index, int num, int den);

  Print the fraction out in the format -> Fraction 1: 2/2 = 1/1

  Arguments in order are : 
    fraction number indexded from 0 (so +1),
    numerator,
    denomenator,
    numerator/gcd (reduced) multiplied by a saftey function to avoid negatives in denomenator,
    denomenator/gcd (reduced) multiplied by a saftey function to avoid negatives in denomenator.

*/

static void displayElements(int index, int num, int den) {

  int 
    simplifiednum = num,
    simplifiedden = den;

  /*
  
    Simplifying Fractions.
  
  */

  simplifyFractions(&simplifiednum,&simplifiedden);
  
  /*
  
    Print fraction in the format :
      Fraction #: original numerator/original denominator = reduced numerator/reduced denominator
  
  */

  printf("Fraction %i: %i/%i = %i/%i\n", index+1, num, den, simplifiednum, simplifiedden);
  
}

/*

  Display Fractions

  This function is the state of the art of Abstraction.

  This function calls DataBase_forEachValueInStoredFractions()
  from DataBase.h and passes reference of displayElements() to it,
  so that it can run that function on each fraction stored in the 
  data base in order. 

*/
void DisplayFractions() {

  // For everything stored in Fractions Array in database file array excecute displayElements
  DataBase_forEachValueInStoredFractions(&displayElements);

}

/*

  Calculations

*/

/*

  Option 4

  Add Fractions

*/

void AddFractions() {
  
  /*

    This function will add two fractions entered by the user.
    Get user input from our existing get fractions (they also validate).
    The code makes the common denomenator den1*den2 to avoid finding lcd since they will be reduced in the end anyways.
    Finally the expression is added to history.

  */

  int num1, den1, num2, den2, num, den;

  /*
  
    Get fractions
  
  */


  printf("Fraction 1:\n");
  getUserFraction(&num1, &den1);
  

  printf("Fraction 2:\n");
  getUserFraction(&num2, &den2);
  

  
  // Add fractions
  num = num1*den2 + num2*den1;
  den = den1*den2;

  /*

    Simplifying Fractions
    
  */
  
  simplifyFractions( &num, &den);


  // Adding equation to the history
  DataBase_addToHistory(num1, den1, num2, den2, num, den, '+');
 
  // Displaying the result
  formatAndDisplayInEquation(num1, den1, num2, den2, num, den, '+');

}

/*

  Option 5

  Subtract Fractions

*/

void SubtractFractions() {
  
  /*

    This function will subtract two fractions entered by the user.
    Get user input from our existing get fractions (they also validate).
    The code makes the common denomenator den1*den2 to avoid finding lcd since they will be reduced in the end anyways.
    Finally the expression is added to history.

  */

  int num1, den1, num2, den2, num, den;
  
  /*
  
    Get fractions
  
  */


  printf("Fraction 1:\n");
  getUserFraction(&num1, &den1);
  

  printf("Fraction 2:\n");
  getUserFraction(&num2, &den2);
  

  
  // Subtract fractions
  num = num1*den2 - num2*den1;
  den = den1*den2;

  /*

    Simplifying Fractions
    
  */
  
  simplifyFractions( &num, &den);


  // Adding equation to the history
  DataBase_addToHistory(num1, den1, num2, den2, num, den, '-');
 
  // Displaying the result
  formatAndDisplayInEquation(num1, den1, num2, den2, num, den, '-');
}

/*

  Option 6

  Divide Fractions

*/

void DivideFractions() {

  /*

    Divide Fractions by first receiving user input, 
    then by running checks on numerator,
    then multiply the reciprocals,
    and finally simplify with gcd function.

  */

  int num1, den1, num2, den2, num, den, tempNum;

  /*
  
    Get fractions
  
  */


  printf("Fraction 1:\n");
  getUserFraction(&num1, &den1);
  

  printf("Fraction 2:\n");
  getUserFraction(&num2, &den2);
  

  /*
    
    If second numerator is 0,
    taking a reciprocal will make it from
    
    0 / x to x / 0
    
    which is invalid, aka undefined.

  */

  while (num2 == 0) {
    printf ("Invalid second fraction numerator.\n");
    getUserFraction(&num2,&den2);
  }

  // Multiply the reciprocals
  num = num1*den2;
  den = den1*num2;


  /*

    Simplifying Fractions
    
  */
  
  simplifyFractions( &num, &den);

  // Adding equation to the history
  DataBase_addToHistory(num1, den1, num2, den2, num, den, '/');
 
  // Displaying the result
  formatAndDisplayInEquation(num1, den1, num2, den2, num, den, '/');

}

/*

  Option 7

  Multiply Fractions

*/

void MultiplyFractions() {

  /*

    Get user input using our existing program to get the fractions from user to multiply.
    Multiply numerator and denomenator then simplify the fraction using gcd.
    Finally add to history and output the answer using our handler for output with the symbol passed to the function.

  */

  int num1, den1, num2, den2, num, den;

  /*
  
    Get fractions
  
  */


  printf("Fraction 1:\n");
  getUserFraction(&num1, &den1);
  

  printf("Fraction 2:\n");
  getUserFraction(&num2, &den2);
  

  
  // Multiply Fractions
  num = num1*num2;
  den = den1*den2;

  /*

    Simplifying Fractions
    
  */
  
  simplifyFractions( &num, &den);


  // Adding equation to the history
  DataBase_addToHistory(num1, den1, num2, den2, num, den, 'x');
 
  // Displaying the result
  formatAndDisplayInEquation(num1, den1, num2, den2, num, den, 'x');

}

/*

  Option 8

  Display All Fractions

*/

void DisplayAllEquations() {

  /*

    Display All Fractions by passing adress of our format and display function
    to a handler function in Database.c which willl run the function on all stored equations.

  */

  printf("Here are all equations stored in history:\n");

  DataBase_forEachValueStoredInHistory(&formatAndDisplayInEquation);
}

/*

  Option 9

  To Quit Program 

*/

void QuitProgram() {

  printf("\nGood bye!\n");

  /*

    This calls DataBase_SetFlagToStopProgram()
    which will set flag for Main function to 
    stop running program.

  */

  DataBase_SetFlagToStopProgram();
}


/*

  Invalid Option
  
*/

void invalidCase() {

  /*

    Ask them to retry with error prompt
  
  */

  DISPLAY_INVALID_OPTION_ERROR
}
