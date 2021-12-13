// This program searches a given string inside another string using hash code matching.
// Written by Amitabha Roy, Roll No.: 19012.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// Function to compute hash code for a given string.
/* 1. For the first time, this function will iterate over the full string and compute the code.
   2. For furthur computations, the function will subtract the contribution of the first character and 
      include the contribution of the newly introduced character from the other end in the code.
*/
unsigned long long computeHash(char* pStr, int nSliderPos, int nSliderLen, unsigned long long nPrevHshCode, char cNewChar, char cFirstChar)
{
    unsigned long long nHashCode = 0;

    // Check whether this is the computation for the first time.
    if (nPrevHshCode == 0)
    {
        for(int i = nSliderLen - 1; i >= 0;i--)
        {
            // Add the contribution of the i'th character to the code.
            nHashCode = nHashCode * 1000 + ((int) pStr[nSliderPos + i]); 
        }
    }
    else // Recompute hash code by including and deleting the contributions of the new character and the first character's respectively.
        nHashCode = ((nPrevHshCode - ((int) cFirstChar)) / 1000) + pow(1000, nSliderLen - 1) * ((int) cNewChar);             

    return nHashCode;
}

// Main function.
void main( )
{ 
    printf("Welcome to hashing based string patterning matching program.\n");
    
    // Reserve 10000 characters for text input and search strings.
    char pTextStr[10000],
         pSearchStr[10000];
    int nTextLen = 0, nSearchLen = 0;

    do
    { 
        // Accept text.
        printf("Enter a text: ");
        fgets(pTextStr, 10000, stdin);
        
        nTextLen = strlen(pTextStr);
        
        // Remove the new line characters.
        pTextStr[nTextLen - 1] = '\0';
        
        if (!strcmp(pTextStr, ""))
        {
            printf("Empty text cannot be accepted as input!Please re-enter.\n");
            continue;
        }

        // Decrement the lengths.
        nTextLen--;
        break;
    } while(1);

    do
    {
        // Accept search string.
        printf("Enter search string: ");
        fgets(pSearchStr, 10000, stdin);

        nSearchLen = strlen(pSearchStr);

        // Remove the new line characters.
        pSearchStr[nSearchLen - 1] = '\0';

        if (!strcmp(pSearchStr, ""))
        {
            printf("Empty string cannot be accepted as input!Please re-enter.\n");
            continue;
        }

        // Decrement the lengths.
        nSearchLen--;
        break;
    } while(1);

    unsigned long long nSearchCode = computeHash(pSearchStr, 0, nSearchLen, 0, 0, 0), // Compute hash code of the search string.
                       nSliderCode = 0;  // Stores the code of the slider during iteration.
    char cFlag = 0; // Flag variable.

    //printf("Search hash code: %llu\n", nSearchCode);

    // Slider loop.
    for(int i = 0; i <= (nTextLen - nSearchLen); i++)
    {
        if (i == 0) // First iteration.
            nSliderCode = computeHash(pTextStr, 0, nSearchLen, 0, 0, 0);
        else // Furthur iterations.
            nSliderCode = computeHash(pTextStr, i, nSearchLen, nSliderCode, pTextStr[i + nSearchLen - 1], pTextStr[i - 1]);

        //printf("Hash code at %d'th step: %llu\n", (i + 1), nSliderCode);

        if (nSliderCode == nSearchCode)
        {
            printf("The search string '%s' found at position %d in the text!\n", pSearchStr, (i + 1));
            cFlag = 1;
        }
    }

    if (!cFlag) // In case the search failed.
        printf("'%s' not found in the text.\n", pSearchStr);
}
