// Implementation of heap of positive integers.
// Both min-max modes are implemented.
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Amortized constant complexity.
int* pHeapArr = NULL; // Pointer to data stored in the heap memory.
int nNumElem = 0; // Stores the number of elements in the heap.
int nHeapSize = 0; // Stores the number of maximum possible elements in the heap.
char cHeapMode = 0; // Stores the mode of operation of the heap, i.e, either minimum or maximum.

// Function to search for an element in the heap. Returns the node index of the required key.
int search(int nKeyVal)
{
    // Loop over all the element in the heap.
    for(int i = 0;i < nNumElem;i++)
    {   
        if (pHeapArr[i] == nKeyVal)
            return i;
    }

    // Search failure indicator return.
    return -1;
}

// Function to recursive swap nodes upwards until the heap condition is established.
void swapUpwards(int nNodeIndex)
{
    // In case the root node has been reached, stop.
    if (nNodeIndex <= 0) return;    

    // Compute the index of the parent node.
    int nParIndex = ((nNodeIndex % 2) == 0) ? (nNodeIndex / 2 - 1) : (nNodeIndex - 1) / 2;
    int nFlag = 0;

    if (cHeapMode == 0)
    {
        // Max-mode.
        if (pHeapArr[nParIndex] < pHeapArr[nNodeIndex]) // Check for violation of heap condition.
            nFlag = 1;
    }
    else
    {
        // Min-mode.
        if (pHeapArr[nParIndex] > pHeapArr[nNodeIndex]) // Check for violation of heap condition.
            nFlag = 1;
    }

    if (nFlag)
    {
        // Swap the node values.
        int nTmp = pHeapArr[nParIndex];
        pHeapArr[nParIndex] = pHeapArr[nNodeIndex];
        pHeapArr[nNodeIndex] = nTmp;
        swapUpwards(nParIndex); // Now perform swapping on the parent node.
    }
}

// Function to recursively swap nodes downwards until the heap condition is established.
void swapDownwards(int nNodeIndex)
{
    // In case the root node has been reached, stop.
    if (nNodeIndex >= nHeapSize) return;    
   
    // Compute the indices of the left and right child.
    int nLefIndex = 2 * nNodeIndex + 1, nRigIndex = 2 * nNodeIndex + 2;
    int nFlag = 0;
    int nTmp = pHeapArr[nNodeIndex];

    // In case the right child index exceeds the heap size, the required layer has not yet been created.
    if (nRigIndex >= nHeapSize) return;

    // In case this node has no child nodes.
    if ((pHeapArr[nLefIndex] == -1) && (pHeapArr[nRigIndex] == -1)) return;

    // Check if one of the childs are absent.
    if (pHeapArr[nLefIndex] == -1)
    {
        if (cHeapMode == 0)
        {
            if (pHeapArr[nRigIndex] > pHeapArr[nNodeIndex])
                nFlag = 1;
        }
        else
        {
            if (pHeapArr[nRigIndex] < pHeapArr[nNodeIndex])
                nFlag = 1;
        }

        if (nFlag)
        {
            // Swap the node values.
            pHeapArr[nNodeIndex] = pHeapArr[nRigIndex];
            pHeapArr[nRigIndex] = nTmp;
            swapDownwards(nRigIndex); // Now perform swapping on the right child node.
        }
    }
    else if (pHeapArr[nRigIndex] == -1)
    {
        if (cHeapMode == 0)
        {
            if (pHeapArr[nLefIndex] > pHeapArr[nNodeIndex])
                nFlag = 1;
        }
        else
        {
            if (pHeapArr[nLefIndex] < pHeapArr[nNodeIndex])
                nFlag = 1;
        }

        if (nFlag)
        {
            // Swap the node values.
            pHeapArr[nNodeIndex] = pHeapArr[nLefIndex];
            pHeapArr[nLefIndex] = nTmp;
            swapDownwards(nLefIndex); // Now perform swapping on the right child node.
        }
    }
    else
    {
        // The case where both the childs are present.
        if (cHeapMode == 0)
        {
            if ((pHeapArr[nLefIndex] > pHeapArr[nNodeIndex]) || (pHeapArr[nRigIndex] > pHeapArr[nNodeIndex])) // Check for violation of heap condition.
                nFlag = 1;
        }
        else
        {
            if ((pHeapArr[nLefIndex] < pHeapArr[nNodeIndex]) || (pHeapArr[nRigIndex] < pHeapArr[nNodeIndex])) // Check for violation of heap condition.
                nFlag = 1;
        }

        if (nFlag)
        {
            if (cHeapMode == 0) 
            {
                // Max-mode.
                // The left child has more key value.
                if (pHeapArr[nLefIndex] > pHeapArr[nRigIndex])
                {
                    // Swap the node values.
                    pHeapArr[nNodeIndex] = pHeapArr[nLefIndex];
                    pHeapArr[nLefIndex] = nTmp;
                    swapDownwards(nLefIndex); // Now perform swapping on the left child node.
                }
                else
                {
                    // Swap the node values.
                    pHeapArr[nNodeIndex] = pHeapArr[nRigIndex];
                    pHeapArr[nRigIndex] = nTmp;
                    swapDownwards(nRigIndex); // Now perform swapping on the right child node.
                }
            }
            else
            {
                // Min-mode.
                // The left child has less key value.
                if (pHeapArr[nLefIndex] < pHeapArr[nRigIndex])
                {
                    // Swap the node values.
                    pHeapArr[nNodeIndex] = pHeapArr[nLefIndex];
                    pHeapArr[nLefIndex] = nTmp;
                    swapDownwards(nLefIndex); // Now perform swapping on the left child node.
                }
                else
                {
                    // Swap the node values.
                    pHeapArr[nNodeIndex] = pHeapArr[nRigIndex];
                    pHeapArr[nRigIndex] = nTmp;
                    swapDownwards(nRigIndex); // Now perform swapping on the right child node.
                }
            }
        }
    }
}

// Function to insert an element (positive integer) into the heap.
int insert(int nKeyVal)
{
    // Check if the heap array does not exist.
    if (!pHeapArr)
    {
        // Allocate an integer array of size 16.
        pHeapArr = (int *) malloc(sizeof(int) * 16);

        // If there is a memory allocation failure.
        if (!pHeapArr) return -1;

        // Initially start with a 16 integers heap.
        nHeapSize = 16;

        // Fill the entries except the first entry with -1.
        for(int i = 0;i < nHeapSize;i++)
            pHeapArr[i] = -1;
    }

    // Check if the heap has reached its bound.
    if (nNumElem == nHeapSize)
    {   
        // Increase the maximum possible elements allowed in the heap to the next power of 2.
        nHeapSize = 2 * nHeapSize + 1;
        int* pTmp = (int *) malloc(sizeof(int) * nHeapSize);

        // If there is a memory allocation failure.
        if (!pTmp) return -1;

        // Copy all elements from the previous heap memory to the new memory space.
        for(int i = 0; i < nNumElem;i++)
            pTmp[i] = pHeapArr[i];

        // Fill the remaining entries with -1.
        for(int i = nNumElem;i < nHeapSize;i++)
            pTmp[i] = -1;

        // Free the previous memory space.
        free(pHeapArr);
        pHeapArr = pTmp; // Reset the heap pointer.
    }

    // Check whether the key already exists.
    if (search(nKeyVal) >= 0)
        return -2;

    // Insert an element in the heap.
    pHeapArr[nNumElem++] = nKeyVal;

    // Start swapping upwards from the node of insertion.
    swapUpwards(nNumElem - 1);

    // Return success indicator.
    return 1;
}

// Returns the root element of the heap and re-shapes the heap. 
int extractRoot()
{
    // If the heap is empty.
    if (nNumElem == 0) return -1;

    // Store the root value.
    int nRootVal = pHeapArr[0];

    // Replace the root node key value with the last entered key value.
    pHeapArr[0] = pHeapArr[nNumElem - 1];
    pHeapArr[nNumElem - 1] = -1;

    nNumElem--; // Decrease the number of elements.
    
    // Start downward swap from the root node.
    swapDownwards(0);

    return nRootVal;
}

// Display all the elements in the heap following the left-to-right convention.
void display()
{
    // In case the heap is empty.
    if (nNumElem == 0)
    {
        printf("The heap is empty!\n"); 
        return;
    }

    printf("Display heap details:---\n");

    // Fill the remaining entries with -1.
    for(int i = 0;i < nNumElem;i++)
    {
        // Display the details of each element.
        printf("%d at node index %d, layer %d.\n", pHeapArr[i], i, ((int) log2f(i + 1) + 1));
    }
}

// Main function.
void main()
{
    // Menu-based system via an infinite loop.
    do
    {
        // Display choices to the user.
        printf("Present mode of operation: %s\n", (cHeapMode == 0) ? "Max-mode." : "Min-mode.");
        printf("1. Insert an element in the heap.\n");
        printf("2. Extract root element from the heap.\n");
        printf("3. Search for an element in the heap.\n");
        printf("4. Display elements in the heap.\n");
        printf("5. Change heap mode of operation.\n");
        printf("6. Exit\n");
        
        int nUsrChoice = 0, // Stores the user choice.
            nTmp = 0,    // Variable for multipurpose storage.
            nRetCode = 0; // Stores return values of functions.

        // Accept a choice from the user.
        printf("Enter your choice: ");
        scanf("%d", &nUsrChoice);

        switch(nUsrChoice)
        {
            case 1:
                do
                {
                    // Accept input from the user.
                    printf("Enter a key value: ");
                    scanf("%d", &nTmp);

                    // Incase non-positive values are entered.
                    if (nTmp <= 0)
                        printf("Please enter positive integers as key values!\n");
                        
                } while(nTmp <= 0);

                // Call insert function.
                nRetCode = insert(nTmp);

                // Check if push operation succeeds or not.
                if (nRetCode == -1)
                {
                    printf("Sorry! Insertion operation failed to memory failure!"); // Display error.
                    return; // Exit program.
                }
                else if (nRetCode == -2)
                    printf("Sorry! The key value %d already exists!\n", nTmp); // Display error.
                
                break;
            case 2:
                nRetCode = extractRoot();

                // Check if the heap is empty...
                if (nRetCode == -1)
                {
                    printf("The heap is empty!\n");
                    break;
                }
                
                // Display the value to the user.
                printf("The value at the root node was %d\n", nRetCode);
                break;
            case 3:
                do
                {
                    // Accept input from the user.
                    printf("Enter a key value: ");
                    scanf("%d", &nTmp);

                    // Incase non-positive values are entered.
                    if (nTmp <= 0)
                        printf("Please enter positive integers as key values!\n");
                        
                } while(nTmp <= 0);

                // Call insert function.
                nRetCode = search(nTmp);

                // Check if push operation succeeds or not.
                if (nRetCode == -1)
                {
                    printf("They given key value %d does not exist in the heap.\n", nTmp); // Display error.
                    break; // Exit the case.
                }
                
                // Display the result to the user.
                printf("The key value %d was found at node index %d, layer %d.\n", nTmp, nRetCode, ((int) log2f(nRetCode + 1) + 1));
                break;
            case 4:
                display(); // Invoke the display function.
                break;
            case 5:
                printf("Enter 0 for max-heap and 1 for min-heap.\n");

                do
                {
                    // Accept input from the user.
                    printf("Enter your choice: ");
                    scanf("%d", &nTmp);

                    // Incase non-positive values are entered.
                    if ((nTmp < 0) || (nTmp > 1))
                        printf("Your choice is not valid!\n");
                        
                } while((nTmp < 0) || (nTmp > 1));

                // Store the choice value in the mode determination variable.
                cHeapMode = (char) nTmp;
                
                // Empty all previous heap memory and reset the heap variables.
                if (pHeapArr) free(pHeapArr);
                nHeapSize = 0;
                nNumElem = 0;
                pHeapArr = NULL;
                
                break;
            case 6:
                return; // Exit the program directly.
            default:
                printf("Please enter a proper choice value!\n");
        }
    } while(1); 
}