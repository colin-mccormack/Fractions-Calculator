# A01 Fraction Program

## Program Structure:

### Main File:
Runs fnctions from various header files.
    
### IO.h
Header file containing IO functions, 
Interface between User and Program 

#Operations.h
Header file containing all functions created for specific operations,
Including Addition, Subtraction, Multiplication, and so on...
All those functions are abstracted away.
The only visible function visible is getFunctionToRun()
decideWhatToDo will return a function pointer that can be ran.


#DataBase.h
Contains MultiDimensional Arrays that can be used to store data.
Syntax Sugar: Just include this header file to access these arrays instead
of passing them by reference each time.

## Authors

Abdul Mannan Syed, asyed24@ocdsb.ca
Collin McMcormack, cmcco3@ocdsb.ca

10/26/2021

