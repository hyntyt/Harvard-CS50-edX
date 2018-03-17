/**
* mario.c
*
* James Dreher
*
* Program that recreates the half-pyramid from Super 
* Mario Bros. using a user-inputed Integer. 
*/
 
#include <cs50.h>
#include <stdio.h>
#include <string.h>
 
//prototype
void FctBuildPyramid(int intHeight);
 
 
int main(void)
{
     
    string strHello = "Welcome to the Super Mario Bros. pyramid recreation simulator."; //string is defined in the CS50.c class
    string strInputInst = "Please enter an integer: ";
     
    printf("\n%s\n\n", strHello);
    printf("%s", strInputInst);
     
    int intHeight = 0; //the height of the pyramid
    bool verified = false; //the height has been verified
    int intUserInput = 0; //the user inputed value (unverified)
       
     
    //verify input
    while(verified == false){
    intUserInput = GetInt(); //GetString() should be defined in stdio.c class
        if(intUserInput >= 0 && intUserInput <= 23){
            intHeight = intUserInput;
            verified = true;
        }
        else{
            printf("Retry:"); 
        }
    }
 
     
    //build pryamid via abstracted method outside of main class    
    FctBuildPyramid(intHeight); 
     
}
 
 
 
/**
* Prints the pyramid based on the verified user input.
*/
void FctBuildPyramid(int intHeight){
     
    int i = intHeight;
           
    while(i > 0){  
        
       int inverse = (intHeight - i) + 2; //plus 2 for the top level
     
       //print the appropriate number of spaces
       for (int a = 1; a < i; a++){
            printf(" ");
        }
                 
       //print the appropriate number of hashes           
       for (int a = 1; a <= inverse; a++){
            printf("#");
        }
              
        //move cursor to next line for next loop iteration
        printf("\n");
        i--;   
    }
     
}
