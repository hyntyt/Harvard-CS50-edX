/**
 * greedy.c
 *
 * James Dreher
 * james.d.dreher@gmail.com
 *
 * Program that simulates a cash register, in that it 
 * returns the correct amount of change based 
 * on a floating value input from the user. 
 */
 
#include <cs50.h>
#include <stdio.h>
#include <math.h>
 
//prototype
void FctOutputChange(int coins);
 
int main(void)
{

    /**
     * Variables used in the main method
     */
    float fltUserInput = 0;
    int cents = 0;
    bool boolValidInput = false;

    int intTotal = 0; //total coins
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    
    string strHello = "Welcome to the change dispensor simulator!"; //string is defined in the CS50.c class
    string strInputInst = "How much changed is owed: $";

    printf("\n%s\n\n", strHello);

    //obtain and verify input
    while(boolValidInput == false){
        printf("%s", strInputInst);
        fltUserInput = GetFloat(); //GetFloat() should be defined in CS50 library
        if((fltUserInput >= 0) && (fltUserInput <= 99)){
            cents = fltUserInput * 100;
            //printf("success, %i cents remaining\n\n", cents);
            boolValidInput = true; //should exit loop
        }
    }   
    while(cents >= 1){
        
        if(cents >= 25){
        cents = cents - 25;
        ++quarters;
        ++intTotal;    
        //printf("Total coins %i \n", intTotal);
        //printf("Total quarters %i \n", quarters);
        }
        else if(cents >= 10){
        cents = cents - 10;
        ++dimes;
        ++intTotal;
        //printf("Total coins %i \n", intTotal);
        //printf("Total dimes %i \n", dimes);
        }
        else if(cents >= 5){
        cents = cents - 5;
        ++nickels;
        ++intTotal;    
        //printf("Total coins %i \n", intTotal);
        //printf("Total nickels %i \n", nickels);
        }
        else if(cents >= 1){
        cents = cents - 1;
        ++pennies;
        ++intTotal;
        //printf("Total coins %i \n", intTotal);
        //printf("Total pennies %i \n", pennies);    
        }
               
    }
    
    //output the total values of each coin   
   FctOutputChange(intTotal); 

}



/**
 * Prints the pyramid based on the verified user input.
 */
void FctOutputChange(int coins){
    printf("%i\n", coins);
}