// Implementation of the Knuth-Morris-Pratt string pattern matching algorithm.
// Written by Amitabha Roy, Roll No.: 19012.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Pre-processing function.
// The complexity of this function is very high. Probably it can be optimised. Unforunately, I couldn't realise any other way of doing it at that moment.
// Returns the symmetry table of the passed string.
int* generateSymmetryTable(char* pStr)
{
    int nLen = strlen(pStr);
    int* pSymTab = (int *) malloc(sizeof(int) * nLen);
    char *pPrefix = (char *) calloc(sizeof(char) * nLen, 0),
         *pSuffix = (char *) calloc(sizeof(char) * nLen, 0);

    // The value of the first element is always -1.
    pSymTab[0] = -1;

    // Iterate over the full string.
    for(int i = 1; i < nLen; i++)
    {
        int j = 0, l = 0;

        // Loop for finding the length of the longest proper substring.
        for(;j < i;j++)
        {
            // Extract the prefix and suffix of size j.
            strncpy(pPrefix, pStr, j + 1);
            strncpy(pSuffix, pStr + (i - j), j + 1);

            // Introduce the end of string character.
            pPrefix[j + 1] = '\0';
            pSuffix[j + 1] = '\0';   

            printf("%s %s\n", pPrefix, pSuffix);

            // In case they don't match.
            if (!strcmp(pPrefix, pSuffix))
                l = j + 1;
        }

        // Fill in the table accordingly.
        pSymTab[i] = l - 1;
    }

    // Release the allocated spaces.
    free(pPrefix);
    free(pSuffix);

    return pSymTab;
}

// Main function.
void main( )
{ 
    char pTextStr[10000],    // The string in which search is to be peformed.
         pSearchStr[10000];  // The string to be searched in pTextStr.
    int nTextLen = 0, nSearchLen = 0; // The effective lengths of the text and the search strings respectively.

    printf("Welcome to Knuth-Morris-Pratt string pattern matching program.\n");

    // Accept the text string.
    do
    {
        printf("Enter a text (upto 10000 characters only): ");
        fgets(pTextStr, 10000, stdin);

        // Compute length.
        nTextLen = strlen(pTextStr);

        // Remove the new line character.
        pTextStr[nTextLen - 1] = '\0';
        
        // Decrement the length.
        nTextLen--;

        // In case the input string is empty.
        if (!strcmp(pTextStr, ""))
        {
            printf("Empty string is not allowed! Please re-enter.\n");
            continue;
        }

        break;
    } while(1);

    // Accept the search string.
    do
    {
        printf("Enter the search string (upto 10000 characters) : ");
        fgets(pSearchStr, 10000, stdin);

        // Compute length.
        nSearchLen = strlen(pSearchStr);

        // Remove the new line character.
        pSearchStr[nSearchLen - 1] = '\0';
        
        // Decrement the length.
        nSearchLen--;

        // In case the input string is empty.
        if (!strcmp(pSearchStr, ""))
        {
            printf("Empty string is not allowed! Please re-enter.\n");
            continue;
        }

        break;
    } while(1);

    int* pSymTab = generateSymmetryTable(pSearchStr); // Compute the symmetry table for the search string.

    /*
    // Display the symbol table for the search string.
    for(int i = 0;i < nSearchLen;i++)
    {
        printf("%d ", pSymTab[i]);
    }

    printf("\n"); // Go to new line.
    */

    int j = -1; // Counter for the search string.
    
    // KMP search loop.
    for(int i = 0;i < nTextLen;)
    {  
        // In case we have scanned the full search pattern and found a match.
        if (j == (nSearchLen - 1))
        {
            printf("%s found inside the string at position %d!\n", pSearchStr, i - nSearchLen + 1);
            j = -1;
            continue;
        }

        // Either reach the left end of the search string or stop when a match is found.
        while((j > -1) && (pTextStr[i] != pSearchStr[j + 1]))
            j = pSymTab[j]; // Keep jumping back in the symbol table.

        if (pTextStr[i] == pSearchStr[j + 1])
            j++;  // Increment the counter.        

        // Increment the counter.
        i++;    
    }

    // In case a match was found at the end of the string.
    if (j == (nSearchLen - 1))
        printf("%s found inside the string at position %d!\n", pSearchStr, nTextLen - nSearchLen + 1);
}