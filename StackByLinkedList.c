// Implementation of a stack of integers using linked list.
// Written by Amitabha Roy, Roll No.: 19012.
#include<stdio.h>
#include<stdlib.h>

// Structure to define the stack of integers.
typedef struct _TSStack
{
    int nValue; // Stores the value associated with this node.
    struct _TSStack* pPrev; // Stores the reference to the previous element in the stack.
    struct _TSStack* pNext; // Stores the reference to the next element in the stack.
} SStack;

SStack* pStackTop = NULL; // Pointer to the top node in the stack.
int nStackTop = -1; // Position marker for data in the top of the stack.

// Function to insert an element into the stack.
int push(int nVal)
{
    // Allocate a new stack node in the memory.
    SStack* pNewNode = (SStack *) malloc(sizeof(SStack));

    if (!pNewNode) return 0; // Error return.
    
    // Assign the values to the node elements.
    pNewNode->nValue = nVal;
    pNewNode->pPrev = pStackTop;
    pNewNode->pNext = NULL;
    
    // Increment the values of the position markers.
    nStackTop++;

    if (pStackTop != NULL) pStackTop->pNext = pNewNode; // Connect the new node to the present top node.

    pStackTop = pNewNode; // This new node is the new top node of the stack.

    return 1; // Success return.
}

// Function to remove an element from the front end of the stack.
int pop(int* pVal)
{
    // Check if the stack is empty.
    if (nStackTop == -1) return 0; // Error return.
    
    // Store reference to the penultimate node of the top node.
    SStack* pTemp = pStackTop->pPrev;

    // Return the value to the caller function via a pointer.
    *pVal = pStackTop->nValue;
    free(pStackTop);  // Free the top node.
    if (pTemp) pTemp->pNext = NULL; // Nullify the pointer since the previous top node has been freed.
    
    pStackTop = pTemp; // Set the penultimate node as the new top node.

    // Decrement the stack top position.
    nStackTop--;

    return 1; // Success return.
}

// Function to display the elements in the stack.
void display()
{
    // Check if the stack is non-empty.
    if (pStackTop != NULL)
    {
        // Message.
        printf("Displaying the stack contents:-\n");
        
        // Display the top position of the stack.
        printf("Top position: %d\n", nStackTop);

        int nCnt = nStackTop; // Counter variable.
        
        // Display all the elements.
        for(SStack* pCurNode = pStackTop; pCurNode; pCurNode = pCurNode->pPrev, nCnt--) 
            printf("Position: %d, Value: %d\n", nCnt, pCurNode->nValue);
    }
    else
    {
        printf("The stack is empty!\n");
    }
}

// Entry point for the program.
void main()
{
    // Menu-based system via an infinite loop.
    do
    {
        // Display choices to the user.
        printf("1. Insert an element in the stack.\n");
        printf("2. Pop an element from the stack.\n");
        printf("3. Display elements in the stack.\n");
        printf("4. Exit\n");
        
        int nUsrChoice = 0, // Stores the user choice.
            nTmp = 0;    // Variable for multipurpose storage.

        // Accept a choice from the user.
        printf("Enter your choice: ");
        scanf("%d", &nUsrChoice);

        switch(nUsrChoice)
        {
            case 1:
                // Accept input from the user.
                printf("Enter a value: ");
                scanf("%d", &nTmp);

                // Check if push operation succeeds or not.
                if (!push(nTmp))
                {
                    printf("Sorry! Insertion operation failed to memory failure!"); // Display error.
                    return; // Exit program.
                }

                break;
            case 2:
                if (!pop(&nTmp))
                {
                    printf("The stack is empty!\n");
                    break;
                }

                // Display the value to the user.
                printf("The value at the top was %d\n", nTmp);
                break;
            case 3:
                display(); // Invoke the display function.
                break;
            case 4:
                return; // Exit the program directly.
            default:
                printf("Please enter a proper choice value!\n");
        }
    } while(1); 
}