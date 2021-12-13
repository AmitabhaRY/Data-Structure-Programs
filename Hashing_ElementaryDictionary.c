// This program is an implementation of an elementary dictionary using a hash table.
// Each partition of the set of all words is a circular linked list of words beginning with the same alphabet.
// Note: Only words are allowed in this program.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _SHashTableDataNode
{
    int nHashCode; // The hash code of the string stored in this node.
    char* pStrVal; // String value stored at this node.
    struct _SHashTableDataNode* pPrevNode; // Parent node.
    struct _SHashTableDataNode* pNextNode; // Child node.
} SHashTableDataNode;

// An array of pointers, each pointer corresponding uniquely to one of the hash codes.
SHashTableDataNode* pHashClassNodes[26];

// Function to compute the hash code of a given string.
// Returns a code from the range 0 to 25 such that all strings beginning with the same alphabet, irrespective of case, map to the same hash code.
// Returns -1 when the passed string cannot be processed.
int computeHash(char* pStr)
{
    if ((pStr[0] >= 65) && (pStr[0] <= 90))
        return (((int) pStr[0]) - 65); // The first upper-case alphabet has ASCII code 65.
    else if ((pStr[0] >= 97) && (pStr[0] <= 123))
        return (((int) pStr[0]) - 97); // The first lower-case alphabet has ASCII code 97.
    else 
        return -1; // Error return.
}

// Checks if the passed string contains only alphabets or not.
int isAlphabeticString(char* pStr)
{
    for(int i = 0;i < strlen(pStr);i++)
    {
        // Create a tiny string of the character at location i for using the hash function.
        char sChAr[2] = { pStr[0], '\0'};

        // Check if the hash code corresponding to the character at location i is an alphabet or not via the hash function.
        if (computeHash(sChAr) == -1)
            return 0;
    }

    // The string contains only alphabets.
    return 1;
}

// Inserts a word in the hash table.
SHashTableDataNode* insertWord(char* pWordStr, int nHashCode)
{
    SHashTableDataNode* pList = pHashClassNodes[nHashCode]; // Reference to the hash class to which the passed string belongs.

    // Allocate the first node if the list is empty.
    if (!pList)
    {
        pList = (SHashTableDataNode *) malloc(sizeof(SHashTableDataNode));

        // In case of allocation failure.
        if (!pList) return 0;

        // Assign values to the new node...
        pList->nHashCode = nHashCode;
        pList->pStrVal = pWordStr; 
        pList->pPrevNode = pList;
        pList->pNextNode = pList;
        
        return pList; // Return the pointer to the first node.
    }

    // Allocate a new student object.
    SHashTableDataNode* pNewNode = (SHashTableDataNode *) malloc(sizeof(SHashTableDataNode));

    // In case of allocation failure.
    if (!pNewNode) return 0;    

    // Assign values to the new node...
    pNewNode->nHashCode = nHashCode;
    pNewNode->pStrVal = pWordStr;
    pNewNode->pPrevNode = pList->pPrevNode; // The tail of the linked list is the parent of the new node.
    pNewNode->pNextNode = pList; // The head node of the linked list is the child of the new node.
    pNewNode->pPrevNode->pNextNode = pNewNode; // Connect the new node with the tail of the linked list.

    pList->pPrevNode = pNewNode;// Connect the new node with the head of the linked list.
    
    // Return as success flag.
    return pNewNode;
}

// Finds a word in the hash table on the basis of its hash code and contents.
SHashTableDataNode* findWord(char* pWordStr, int nHashCode)
{
    SHashTableDataNode* pList = pHashClassNodes[nHashCode]; // Reference to the hash class to which the passed string belongs.

    // In case the list is empty.
    if (!pList) 
        return NULL;

    // In case the list has only one element.
    if (pList->pNextNode == pList)
    {
        if (!strcmp(pList->pStrVal, pWordStr))
            return pList;
        else
            return NULL;
    }

    SHashTableDataNode* pNode = pList;

    // For the case where there are more than one element.
    do
    {
        // Check for match with given roll number.
        if (!strcmp(pNode->pStrVal, pWordStr)) 
            return pNode;

        // Go to the next node.     
        pNode = pNode->pNextNode;
    } while (pNode != pList);

    return NULL; // Search failed..
}

// Deletes a word from the hash table.
SHashTableDataNode* deleteWord(SHashTableDataNode* pWordNode)
{
    SHashTableDataNode* pList = pHashClassNodes[pWordNode->nHashCode]; // Reference to the hash class to which the passed string belongs.

    // If the list contains only one element.
    if (pList->pNextNode == pList)
    {
        free(pList); // Free the first node itself.
        return NULL;
    }
    
    // In case the reference node of the list is to be deleted. We consider the child of this node as the new reference node for the list.
    if (pWordNode == pList) 
        pList = pList->pNextNode;

    // The parent node of pWordNode can be accessed directly. This is where we have an advantage in case of double linked list over single linked list.
    // Connect the parent of pWordNode with the child of pWordNode child.
    pWordNode->pPrevNode->pNextNode = pWordNode->pNextNode;

    // Connnect the child of pStudent with the parent of pStudent.  
    pWordNode->pNextNode->pPrevNode = pWordNode->pPrevNode;

    free(pWordNode->pStrVal); // Release the memory of the string.
    free(pWordNode); // Release the given node...
    return pList; // Return the first node pointer.
}

// Displays the contents of the hash table.
void displayTable()
{
    printf("Display the contents of the dictionary in order of their first alphabet:-\n");

    // Global word counter.
    int nCounter = 1;

    // Loop over all the hash classes.
    for(int i = 0; i < 26;i++)
    {  
        SHashTableDataNode *pList = pHashClassNodes[i],   
                           *pWordNode = pHashClassNodes[i]; // Reference to the hash class to which the passed string belongs.

        // In case this class is empty, move to the next class.
        if (!pWordNode) 
            continue;

        // Reach to the end of the list via an exit controlled loop...
        do
        {
            printf("%d) %s.\n", nCounter, pWordNode->pStrVal); // Display student details.
            pWordNode = pWordNode->pNextNode;
            nCounter++;
        } while(pWordNode != pList);
    }
}

// Reads an alphabetic string from the user.
void readAlphabeticString(char* pWord)
{
    // Ensure proper input.
    while(1)
    {
        // Accept search word.
        printf("Enter word (upto 100 characters only): ");
        scanf("%s", pWord);

        if (!strcmp(pWord, ""))
        {
            printf("Empty string is not allowed as input!Please re-enter.\n"); 
            continue;
        }            
        else if (!isAlphabeticString(pWord))
        {
            printf("The entered word contains non-alphabets. It cannot be put in the dictionary!Please re-enter.\n");
            continue;
        }

        break; // End the loop.
    }                    
}

// Main function.
void main()
{ 
    printf("Welcome to elementary dictionary program!\n");

    // Nullify all the pointers to hash code classes.
    for(int i = 0; i < 26; i++)
        pHashClassNodes[i] = NULL;
    
    // Start an infinite for loop.
    while(1)
    {
        // Display the choices to the user.
        printf("1. Insert a word in the dictionary.\n");
        printf("2. Find a word in the dictionary.\n");
        printf("3. Change a word in the dictionary.\n");
        printf("4. Delete a word in the dictionary.\n");
        printf("5. Display the words in the dictionary.\n");
        printf("6. Exit.\n");

        int nChoice = 0; // Stores the user's choice.

        // Accept input from the user...
        printf("Enter your choice: ");
        scanf("%d", &nChoice);

        // Global declarations relative to the switch block...
        SHashTableDataNode* pSTemp = NULL;
        char* pWord = NULL;
        int nHashCode = 0;
    
        switch(nChoice)
        {
            case 1:
                pWord = (char *) malloc(sizeof(char) * 101); // Allocate a 100 bytes string.
                
                // Ensure proper input and uniqueness of word in the hash table.
                while(1)
                {
                    // Accept an alphabetic string from the user.
                    readAlphabeticString(pWord);

                    // Compute hash code for the entered word.
                    nHashCode = computeHash(pWord);

                    // Check if the word exists in the hash table.
                    pSTemp = findWord(pWord, nHashCode);

                    // If the word already exists.
                    if (pSTemp)
                    {
                        printf("The word %s already exists in the dictionary!\n", pWord);
                        continue;
                    }
                    
                    break; // End the loop.
                }

                // In case the list is empty.
                if (!pHashClassNodes[nHashCode])
                {
                    // Retrieve the newly created node. This node is the head node.
                    pHashClassNodes[nHashCode] = insertWord(pWord, nHashCode);

                    // In case of any problem.
                    if (!pHashClassNodes[nHashCode])
                    {
                        printf("Sorry! The program has crashed :(!\n");
                        return;
                    }   
                }    
                else if (!insertWord(pWord, nHashCode)) // In case of any problem.
                {
                    printf("Sorry! The program has crashed :(!\n");
                    return;
                }

                break;
            case 2:
                pWord = (char *) malloc(sizeof(char) * 101); // Allocate a 100 bytes string.

                // Accept an alphabetic string from the user.
                readAlphabeticString(pWord);   

                // Compute hash code for the entered word.
                nHashCode = computeHash(pWord);

                // Check if the word exists in the hash table.
                pSTemp = findWord(pWord, nHashCode);

                // If the searched student exists in the record.
                if (pSTemp)
                {
                    printf("The searched word exists in the dictionary!\n");
                    printf("Hash code of the searched word: %d\n", nHashCode);
                    printf("The searched word: %s\n", pWord);
                }
                else
                    printf("The given word %s is not in the dictionary.\n", pWord);
                
                // Free the memory space allocated for the string.
                free(pWord);
                break;
            case 3:
                pWord = (char *) malloc(sizeof(char) * 101); // Allocate a 100 bytes string.
                
                // Accept an alphabetic string from the user.
                readAlphabeticString(pWord);

                // Compute hash code for the entered word.
                nHashCode = computeHash(pWord);

                // Check if the word exists in the hash table.
                pSTemp = findWord(pWord, nHashCode);

                if (!pSTemp)
                {
                    printf("The %s does not exist in the dictionary.\n", pWord);
                    free(pWord);
                    break;
                }

                char* pWordNew = (char *) malloc(sizeof(char) * 101); // Allocate a 100 bytes string.

                // Ensure proper input.
                while(1)
                {
                    // Accept new word.
                    readAlphabeticString(pWordNew);

                    // Compute hash code for the entered word.
                    nHashCode = computeHash(pWordNew);

                    // Check if the word exists in the hash table.
                    SHashTableDataNode* pSTempNew = findWord(pWordNew, nHashCode);

                    // In case the new word already exists in the dictionary.
                    if (pSTempNew && (strcmp(pWord, pWordNew)))
                    {
                        printf("The word %s already exists in the dictionary.\n", pWordNew);
                        continue;
                    }

                    break; // End the loop.
                }

                free(pSTemp->pStrVal); // Release the previously allocated memory.

                // Edit the details stored in the node of the previous word.
                pSTemp->nHashCode = nHashCode;
                pSTemp->pStrVal = pWordNew;
                
                free(pWord); // Release the pointer.
                break;
            case 4:
                pWord = (char *) malloc(sizeof(char) * 101); // Allocate a 100 bytes string.
                
                // Accept an alphabetic string from the user.
                readAlphabeticString(pWord);

                // Compute hash code for the entered word.
                nHashCode = computeHash(pWord);

                // Search.
                // Check if the word exists in the hash table.
                pSTemp = findWord(pWord, nHashCode);

                if (!pSTemp)
                {
                    printf("The %s does not exist in the dictionary.\n", pWord);
                    free(pWord); // Release the pointer.
                    break;
                }

                // Delete the word from the hash table. Retrieve the modified list from the function.
                pHashClassNodes[nHashCode] = deleteWord(pSTemp);

                free(pWord); // Release the pointer.
                break;
            case 5:
                displayTable();
                break;
            case 6:
                return;
                break;
        default:
            printf("Your input is not recognised! Please try again!\n");
        }
    }
}
