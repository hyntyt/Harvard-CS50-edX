/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 * 
 * James Dreher
 * james.d.dreher@gmail.com
 * 
 * TEST ARGS
 * compile: make speller
 * run: ./speller dictionaries/large text
 * test: ./speller dictionaries/small texts/jd.txt
 * grade: check50 2015.fall.pset5.speller dictionary.c dictionary.h Makefile
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"


// number of words in the associated dictionary file
unsigned int wordcount;

// basic hash function, based on ascii values
int hashfunction(const char* word)
{
    int hashindex = 0; //default, not-hashed

    if(word[0] == 39){
        hashindex = 27; //apostrophe
    }else{
        hashindex = word[0] - 96; //linear alpha-numeric from lowercase (1 through 26)
    }
    
    if(hashindex > 27 || hashindex < 0){
        //printf("hashindex of [%i] is out of bounds for word [%s].\n", hashindex, word);
        hashindex = hashindex + 32; //linear alpha-numeric from uppercase letter (1 through 26)
        //printf("hashindex is now [%i] for word [%s].\n\n", hashindex, word);
    }
    
    //printf("hashindex of %i for word %s.\n", hashindex, word);
    return hashindex;
}


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* checknode = malloc(sizeof(node)); //new node to traverse through dictionary
    int hashvalue = hashfunction(word);

    checknode = hashtable[hashvalue]; //move node to proper row in hashtable

    while(checknode != NULL){
        
        if(strcasecmp(checknode->word, word) == 0){
            return true;
        }
        checknode = checknode->next; // not true so move to next node in linked-list
    }
    
    return false; //not found
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    // STEP 1: Open file
    FILE* file = fopen(dictionary, "r");
    
    // validate file
    if(file == NULL){
        return false;
    }


    // STEP 2: Load file contents into a hashed linked-list

    for(int i = 0; i < HASHSIZE; i++){
        hashtable[i] = NULL; //inialize hashtable to null
    }
    
    char word[LENGTH + 1]; //storage for each word read from textfile
     
    while(fscanf(file, "%s\n", word) != EOF){
        
        node* freshnode = malloc(sizeof(node)); // new node
        strcpy(freshnode->word, word);
        int hashvalue = hashfunction(word);
        //printf("Word from dictionary file [%s]with hash value [%i]\n", word, hashvalue);
        
        if(hashtable[hashvalue] == NULL){
           hashtable[hashvalue] = freshnode;
           freshnode->next = NULL;
        }
        else{
            freshnode->next = hashtable[hashvalue];
            hashtable[hashvalue] = freshnode;
        }
        
        ++wordcount; //increase wordcount each time
    }
    
    fclose(file);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    
    return wordcount;  //implemented within the load() function as a running global count
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    
    for(int i = 0; i < HASHSIZE; i++){ //iterate through each hashtable entry
        node *freenode;
        freenode = hashtable[i];
        
        while(freenode){ //free the current node and move to the next
            node* temp = freenode;
            freenode = freenode->next;
            free(temp);
        }
        
        hashtable[i] = NULL; //clear hash value
  }
    
    return true;
}
