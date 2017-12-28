/**
 * vigenere.c
 *
 * James Dreher
 * james.d.dreher@gmail.com
 *
 * Program that simulates the Vigenere cipher, encrypting
 * a plaintext value based on a keyword passed by command-line.
 */
 
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

//variables
string plaintext = "";
string keyword = "";

//prototypes
void FctEncrypt(string input, string key);

int main(int argc, string argv[])
{
    
    //get key from command-line argument
    if(argc == 2){
        keyword = (argv[1]);
        //make sure is all alphabetical characters
        
        for(int a=0, b=strlen(keyword); a < b; a++){
            if( (keyword[a]>='a' && keyword[a]<='z') || (keyword[a]>='A' && keyword[a]<='Z')){
                //input is ok
            }else{
                printf("Not an alphabetic key imported from command-line!\n");
                return 1;
            }
        }
    }else{
        printf("Invalid command-line input!\n");
        return 1;
    } 
    
    //obtain plaintext input from user
    //printf("Please enter the message to encrypt: ");
    plaintext = GetString();
    
    //encrpyt the plaintext
    FctEncrypt(plaintext, keyword);
    printf("\n");
    
    return 0; //success
    
} //main



/**
 * Encrypts the plaintext based on the alphbetic key.
 */
void FctEncrypt(string input, string key){
    
    int k = 13;//varies depending on character in key array
    int klength = strlen(key);
    int spaces = 0;
    
    if(input != NULL){
        //printf("imported keyval is %s\n", key);
        
        for(int i=0, n = strlen(input); i < n; i++){
            
            int ascii =  (int)input[i];
        
            //determine k, the keysize based on letter   
            //uppercase
            if((int)key[i % klength] < 91){
                if((int)key[i % klength] > 64){
                    //printf("%i", (int)key[i % klength]);
                    k = ((int)key[(i % klength)-spaces]) - 65;
                    //printf("uppercase k=%i", k);
                }
            }
        
            //lowercase   
            if((int)key[i % klength] < 123){
                if((int)key[i % klength] > 96){
                    //printf("%i", (int)key[i % klength]);
                    k = ((int)key[(i % klength)-spaces]) - 97;
                    //printf("lowercase k=%i", k);
                }
            }
          
            
            //formula should be c[i] = (p[i] + k[j]) % 26
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
           
           //account for spaces
            if(ascii == 32){
                spaces++;
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