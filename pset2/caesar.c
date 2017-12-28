/**
 * caesar.c
 *
 * James Dreher
 * james.d.dreher@gmail.com
 *
 * Program that outputs cryptotext based on plaintext input from a user.
 */
 
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

//variables
string plaintext = "";
string cyphertext = "";
int key = 0;

//prototypes
void FctEncrypt(string input, string output, int k);

int main(int argc, string argv[])
{
    
    //get key from command-line argument
    if(argc == 2){
        key = atoi(argv[1]);
    }else{
    printf("Invalid input!\n");
    return 1;
    } 
    
    
    
    
    //obtain plaintext input from user
    //printf("Please enter the message to encrypt: ");
    plaintext = GetString();
    
    //encrpyt the plaintext
    FctEncrypt(plaintext, cyphertext, key);
    printf("\n");
    
    return 0;
    
} //main



/**
 * Encrypts the inputed string, by rotating each character k times.
 */
void FctEncrypt(string input, string output, int k){
    
    if(input != NULL){
        
        output = input;
        
        for(int i=0, n = strlen(input); i < n; i++){
            
            int ascii =  (int)input[i];
           
            //uppcase case, needs encrypting
            if(ascii < 91){
                if(ascii > 64){
                    ascii = ascii - 64;
                    ascii = (ascii + k) % 26;
                    ascii = ascii + 64;
                    printf("%c", ascii);
                }
            }
            
            //lowercase, needs encrypting
            if(ascii < 123){
                if(ascii > 96){
                    ascii = ascii - 96;
                    ascii = (ascii + k) % 26;
                    ascii = ascii + 96;
                    printf("%c", ascii);
                }
            }
            
            //numbers and special characters, no encryption needed
            if(ascii < 65){
                if(ascii > 31){
                    printf("%c", input[i]);
                }
            }
        
            //numbers and special characters, no encryption needed
            if(ascii < 97){
                if(ascii > 90){
                    printf("%c", input[i]);
                }
            }
            
            //numbers and special characters, no encryption needed
            if(ascii < 127){
                if(ascii > 122){
                    printf("%c", input[i]);
                }
            }
        
        }
    }
    
}