/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

int FctBinary(int key, int array[], int min, int max);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{

    int index = FctBinary(value, values, 0, n);
   
    if(index >= 0){
        return true;
    }
    else 
        return false;    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{

    // Bubble sort the haystack, based on its size.
    int temp = 0;
    
    for(int k=0;k<n;k++){
        for(int j=0;j<(n-1);j++){
            if(values[j] > values[j+1]){
                temp = values[j];
                values[j] = values[j+1];
                values[j+1] = temp;
            }
        }
    }
    return;

    
}


int FctBinary(int key, int array[], int min, int max){
   
    if(max<min){
        return -1; //not found
    }   
    
    int mid = (min+max)/2;
   
    if(key == array[mid]){
        return mid; //found
    }
   
    if(key > array[mid]){
        return FctBinary(key, array, mid+1, max);
    }
    
    if(key < array[mid]){
        return FctBinary(key, array, min, mid-1);
    }
    else return mid;

}