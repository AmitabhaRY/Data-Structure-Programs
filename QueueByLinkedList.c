// Implementation of a queue of integers using linked list.
#include<stdio.h>
#include<stdlib.h>

// Structure to define the queue of integers.
typedef struct _TSQueue
{
    int nValue; // Stores the value associated with this node.
    struct _TSQueue* pPrev; // Stores the reference to the previous element in the queue.
    struct _TSQueue* pNext; // Stores the reference to the next element in the queue.
} SQueue;

SQueue* pQueue = NULL; // Pointer to the first node in the queue.
int nQueueFront = -1, nQueueRear = -1; // Position markers for data in the queue, i.e, the front and the rear ends.

// Function to insert an element into the queue from the rear end.
int push(int nVal)
{
    SQueue* pLsNode = NULL; // Stores the node corresponding to the rear end.
    
    if (pQueue != NULL)
    {
        // Using a loop, reach to the rear end of the list.
        for(pLsNode = pQueue; pLsNode->pNext != NULL; pLsNode = pLsNode->pNext);    
    }

    // Allocate a new queue node in the memory.
    SQueue* pNewNode = (SQueue *) malloc(sizeof(SQueue));

    if (!pNewNode) return 0; // Error return.
    
    // Assign the values to the node elements.
    pNewNode->nValue = nVal;
    pNewNode->pPrev = pLsNode;
    pNewNode->pNext = NULL;
    
    // Increment the values of the position markers.
    if (nQueueRear == -1) nQueueFront = 0;
    nQueueRear++;

    if (pQueue == NULL) pQueue = pNewNode; // This new node is the first node of the queue.
    else pLsNode->pNext = pNewNode; // Connect the new node to the queue.

    return 1; // Success return.
}

// Function to remove an element from the front end of the queue.
int pop(int* pVal)
{
    // Check if the queue is empty.
    if ((nQueueFront == nQueueRear) && (nQueueFront == -1)) return 0; // Error return.
    
    if (nQueueFront == nQueueRear) nQueueFront = nQueueRear = -1; // Restore the position markers to their initial value.
    else nQueueFront++; // Increment the front position marker.
    
    // Store reference to the next node of the front node.
    SQueue* pTemp = pQueue->pNext;

    // Return the value to the caller function via a pointer.
    *pVal = pQueue->nValue;
    free(pQueue);  // Free the front node.
    if (pTemp) pTemp->pPrev = NULL; // Nullify the pointer since the previous node has been freed.
    
    pQueue = pTemp; // Set the reference to the new front end.

    return 1; // Success return.
}

// Function to display the elements in the queue.
void display()
{
    // Check if the queue is non-empty.
    if (pQueue != NULL)
    {
        // Message.
        printf("Displaying the queue contents:-\n");
        
        // Display the position markers of the queue.
        printf("Front position: %d, Rear position: %d\n", nQueueFront, nQueueRear);

        int nCnt = 0; // Counter variable.
        
        // Display all the elements.
        for(SQueue* pCurNode = pQueue; pCurNode; pCurNode = pCurNode->pNext, nCnt++) 
            printf("Position: %d, Value: %d\n", nQueueFront + nCnt, pCurNode->nValue);
    }
    else
    {
        printf("The queue is empty!\n");
    }
}

// Entry point for the program.
void main()
{
    // Menu-based system via an infinite loop.
    do
    {
        // Display choices to the user.
        printf("1. Insert an element in the queue.\n");
        printf("2. Remove an element from the queue.\n");
        printf("3. Display elements in the queue.\n");
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
                    printf("The queue is empty!\n");
                    break;
                }

                // Display the value to the user.
                printf("The value at the front end was %d\n", nTmp);
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