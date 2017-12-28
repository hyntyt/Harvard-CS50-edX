#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How many minutes does your average shower last? \n");
    int minutes = GetInt();
    
    // each minute of showering is equal to 12 bottles of watter
    int bottles = minutes * 12;
    
    //display the output of both values
    printf("minutes: %i \n", minutes);  
    printf("bottles: %i \n", bottles);  
 
}