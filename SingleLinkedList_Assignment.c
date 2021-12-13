// Single Linked List program...
// Student Name: Amitabha Roy.
// Roll No.: 19012.
// Major: Mathematics.

#include<stdio.h>
#include<stdlib.h>

// Linked List structure...
typedef struct _SLinkedList
{
    int nNodeValue;
    struct _SLinkedList* pNextNode;
} SLinkedList;

// Linked list replication function.
SLinkedList* createReplica(SLinkedList* pLList)
{
    SLinkedList* pNode = pLList; // Points to the present node in control in the original list.
    
    // First we need to go to the last node..
    while(pNode->pNextNode) pNode = pNode->pNextNode;

    SLinkedList* pNewList = (SLinkedList*) malloc(sizeof(SLinkedList)); // Points to the new list's first node.
    SLinkedList* pCurNode; // Node pointer during iteration for the replica list. 

    // Check if allocation has failed.
    if (!pNewList)
    {
        // Display message...
        printf("Memory allocation has failed! The program has crashed!\n");
        return NULL;
    }

    // Set the pointer to the beginning of the new list.
    pCurNode = pNewList;

    // Replication loop.    
    while(pNode)
    {
        SLinkedList* pPrevNode = pLList; // Will store the previous node to pNode in the original list.

        // Find the previous node to this node (pNode)..
        if (pNode != pLList) // Check that we are not in the first node itself.
            while(pPrevNode->pNextNode != pNode) pPrevNode = pPrevNode->pNextNode;

        // Copy the values from pNode onto pCurNode.
        *pCurNode = *pNode;
        
        // Are we at the first node of the original list?
        if (pNode != pLList)
        { 
            // Allocate a new next node...
            pCurNode->pNextNode = (SLinkedList*) malloc(sizeof(SLinkedList));
        
            if (!pCurNode->pNextNode)
            {
                // Display message...
                printf("Memory allocation has failed! The program has crashed!\n");
                return NULL;
            }

            pCurNode = pCurNode->pNextNode; // Set the pointer to the next node in the replica list.
            pNode = pPrevNode; // Set the pointer to the parent of this node.
        }
        else // Yes..Then this is the last iteration.
        {
            pCurNode->pNextNode = NULL; // Set the next node of the last node to NULL.
            pNode = NULL;
        }
    }

    return pNewList;
}

// Entry point Main...
void main()
{
    int nSize; // Stores the number of elements to be entered by the user.

    // Ensure that nSize >= 7.
    do
    {
        printf("Enter number of elements: ");
        scanf("%d", &nSize); // Accept value from the user.

        if (nSize >= 7) break; // Break the loop.

        // Display error.
        printf("The list must contain atleast seven nodes!\n");
    } while(1); 

    SLinkedList* pNode; // Points to the current node in control in the original list.
    SLinkedList* *pLList = (SLinkedList *) malloc(sizeof(SLinkedList)); // Pointer to first node in the list...

    // Check if allocation has failed.
    if (!pLList)
    {
        // Display message...
        printf("Memory allocation has failed! The program has crashed!\n");
        return;
    }

    // Point to the first node in the list.
    pNode = pLList;

    // Create the list by accepting values from the user...
    for(int i = 0; i < nSize;i++)
    {
        int nValue; // Stores the value entered by the user...
        printf("Enter the value at index [%d]: ", i + 1);
        scanf("%d", &pNode->nNodeValue);

        // If we are not at the last iteration.
        if (i < (nSize - 1))
        {
            // Create a new node linkage with the present node.
            pNode->pNextNode = (SLinkedList* ) malloc(sizeof(SLinkedList));

            // Check if allocation has failed.
            if (!pNode->pNextNode)
            {
                // Display message...
                printf("Memory allocation has failed! The program has crashed!\n");
                return;
            }
            
            pNode = pNode->pNextNode; // Set the pointer to the new node.
        }
        else
        {
            pNode->pNextNode = NULL; // Set the node pointer to null.
        }
    }

    SLinkedList* pRepList = createReplica(pLList); // Create a replica of the new list...

    // Has the allocation been successfull?..If no, then exit the program.
    if (!pRepList) return;

    // Display all the elements in both the lists..
    printf("Displaying all the elements in the list.\n");
    
    SLinkedList* pRNode = pRepList; // Set the pointer to the first node of the replica list.
    
    pNode = pLList; // Set the pointer to the first node of the original list.

    // Iterate over the nodes..
    while(pRNode) // Appropriate since both the nodes must end together.
    {
        // Display the values.
        printf("%d\t%d\n", pNode->nNodeValue, pRNode->nNodeValue);

        // Set the pointers to the next nodes respectively.
        pRNode = pRNode->pNextNode;
        pNode = pNode->pNextNode;
    }
}
