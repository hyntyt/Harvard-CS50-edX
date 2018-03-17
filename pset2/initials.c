/**
 * initials.c
 *
 * James Dreher
 *
 * Program that determines a user's initials, based on the name they input. 
 */

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//variables
string strUserName = "";
string strInitials = "";

//prototypes
void FctDetermineInitials(string username);


int main(int argc, string argv[])
{

    //printf("Please enter your full name: ");
    strUserName = GetString();
    
    //calculate initials through function
    FctDetermineInitials(strUserName);

}//main


/**
 * Calculates the initials of the name.
 */
void FctDetermineInitials(string username){
    
    if(username != NULL){
        printf("%c", toupper(username[0]));
        for(int i=0, n = strlen(username); i < n; i++){
            
            int letter =  (int)username[i];
            if(letter == 32){
               printf("%c", toupper(username[i+1]));
            }

        }  

    }
    printf("\n");
}

