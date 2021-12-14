// Implementation of a binary search tree.
// Written by Amitabha Roy, Roll No.: 19012.
// Motivation taken from Gopi's sir code on binary search tree implementation.
// Repeatiton of elements not allowed in this tree implementation.
#include<stdio.h>
#include<stdlib.h>

typedef struct _STreeNode
{
    int nKeyValue;  // The value stored at this node.
    struct _STreeNode* pParentNode; // Parent node.
    struct _STreeNode* pLeftNode; // Left child.
    struct _STreeNode* pRightNode; // Right child.
} STreeNode;

// Creates a new node by taking all its parameters.
// This function is defined to make the code shorter.
STreeNode* createNewNode(int nKeyVal, STreeNode* pParentNode, STreeNode* pLeftNode, STreeNode* pRightNode)
{
    // Allocate a new node.
    STreeNode* pNewNode = (STreeNode *) malloc(sizeof(STreeNode));
            
    // In case of allocation failure.
    if (!pNewNode)
        return NULL;

    // Assign the values.
    pNewNode->nKeyValue = nKeyVal;
    pNewNode->pParentNode = pParentNode;
    pNewNode->pLeftNode = pLeftNode;
    pNewNode->pRightNode = pRightNode;

    return pNewNode;
}

// Insert a node in the tree.
// It is assumed that the head node of the tree exists before this function is called.
STreeNode* insert(int nVal, STreeNode* pCurNode)
{
    // This situaton only arises when the head node has not been created.
    if (!pCurNode)
        return createNewNode(nVal, NULL, NULL, NULL);
    
    // Note that uniquess of the inserted key is ensured before the function has been called. So it has not been checked here
    if (pCurNode->nKeyValue > nVal) // Smaller than this node.
    {
        // In case no left child exists.
        if (!pCurNode->pLeftNode)
        {
            // Allocate a new node.
            STreeNode* pNewNode = createNewNode(nVal, pCurNode, NULL, NULL);
            
            // In case of allocation failure.
            if (!pNewNode)
                return NULL;
            
            // Connect pCurNode with pNewNode.
            pCurNode->pLeftNode = pNewNode;

            return pNewNode; // Success code.
        }
        else
            return insert(nVal, pCurNode->pLeftNode); // Go down to the left child for insertion.
    }
    else // Larger than this node.
    {
        // In case no right child exists.
        if (!pCurNode->pRightNode)
        {
            // Allocate a new node.
            STreeNode* pNewNode = createNewNode(nVal, pCurNode, NULL, NULL);
            
            // In case of allocation failure.
            if (!pNewNode)
                return NULL;
            
            // Connect pCurNode with pNewNode.
            pCurNode->pRightNode = pNewNode;

            return pNewNode; // Success code.
        }
        else
            return insert(nVal, pCurNode->pRightNode); // Go down to the right child for insertion.
    }
}

// Search for a node in the tree.
STreeNode* search(int nVal, STreeNode* pCurNode)
{
    // The searched key does not exist in the tree.
    if (!pCurNode)
        return NULL;

    if (pCurNode->nKeyValue == nVal) // Required key found.
        return pCurNode;
    else if (pCurNode->nKeyValue > nVal) // Smaller than this node.
        return search(nVal, pCurNode->pLeftNode); // Go down to the left child for insertion.
    else // Larger than this node.
        return search(nVal, pCurNode->pRightNode); // Go down to the right child for insertion.
}

// Find the maximum key.
// It can determine the maximum key of any subtree.
STreeNode* findMaximum(STreeNode* pCurNode)
{
    return (pCurNode->pRightNode) ? findMaximum(pCurNode->pRightNode) : pCurNode; 
}

// Find the minimum key.
// It can determine the minimum key of any subtree.
STreeNode* findMinimum(STreeNode* pCurNode)
{
    return (pCurNode->pLeftNode) ? findMinimum(pCurNode->pLeftNode) : pCurNode; 
}

// Delete the passed node in the tree.
STreeNode* delete(int nVal, STreeNode* pCurNode)
{
    STreeNode* pRetNode = NULL; // Node to be return by the function.

    // If the node has no child nodes.
    if (!pCurNode->pLeftNode && !pCurNode->pRightNode)
    {   
        // If the current node is not the head node.
        if (pCurNode->pParentNode)
        {
            if (pCurNode->pParentNode->pLeftNode == pCurNode)
                pCurNode->pParentNode->pLeftNode = NULL;
            else 
                pCurNode->pParentNode->pRightNode = NULL;
        }
    }
    else if (!pCurNode->pLeftNode) // Right node exists.
    {
        // If the current node is not the head node.
        if (pCurNode->pParentNode) 
        {
            if (pCurNode->pParentNode->pLeftNode == pCurNode)
                pCurNode->pParentNode->pLeftNode = pCurNode->pRightNode;
            else 
                pCurNode->pParentNode->pRightNode = pCurNode->pRightNode;
        }

        pCurNode->pRightNode->pParentNode = pCurNode->pParentNode;   

        // In case the root node is being deleted, return the pointer to the new root node.
        if (!pCurNode->pParentNode)
            pRetNode = pCurNode->pRightNode;
    }
    else if (!pCurNode->pRightNode) // Left node exists.
    {
        // If the current node is not the head node.
        if (pCurNode->pParentNode) 
        {
            if (pCurNode->pParentNode->pLeftNode == pCurNode)
                pCurNode->pParentNode->pLeftNode = pCurNode->pLeftNode;
            else 
                pCurNode->pParentNode->pRightNode = pCurNode->pLeftNode;
        }

        pCurNode->pLeftNode->pParentNode = pCurNode->pParentNode;

        // In case the root node is being deleted, return the pointer to the new root node.
        if (!pCurNode->pParentNode)
            pRetNode = pCurNode->pLeftNode;
    }
    else // Both node exists.
    {
        // Find the left-most child of the right subtree of the current node.
        STreeNode* pMinNode = findMinimum(pCurNode->pRightNode);

        // Check how pMinNode is connected to it's parent and accordingly nullify the connection.
        if (pMinNode->pParentNode->pLeftNode == pMinNode)
            pMinNode->pParentNode->pLeftNode = NULL;
        else 
            pMinNode->pParentNode->pRightNode = NULL;

        // pMinNode replaces pCurNode in the tree. The parent of pMinNode is now the parent of pCurNode.
        pMinNode->pParentNode = pCurNode->pParentNode; 

        // pMinNode replaces pCurNode in the tree. So the node connections need to be revised accordingly.
        // Connect pMinNode with its new child nodes. 
        pMinNode->pLeftNode = pCurNode->pLeftNode;
        pMinNode->pRightNode = pCurNode->pRightNode;
        // Connect the new child nodes of pMinNode with pMinNode.
        pCurNode->pLeftNode->pParentNode = pMinNode; 
        pCurNode->pRightNode->pParentNode = pMinNode;

        // In case the root node is being deleted, return the pointer to the new root node.
        if (!pCurNode->pParentNode)
            pRetNode = pMinNode;
    }

    // Delete this node.
    free(pCurNode);
    return pRetNode;
}

// Display all the keys in the tree.
// Prints the keys in descending order.
void displayTree(STreeNode* pCurNode)
{
    // In case there is a right subtree, print it first.
    if (pCurNode->pRightNode)
        displayTree(pCurNode->pRightNode);

    char* pNodeTypeStr = ""; // Stores some information related to the type of node.
    
    if (pCurNode->pParentNode)
    {
        if (pCurNode->pParentNode->pLeftNode == pCurNode)
            pNodeTypeStr = "left child of ";
        else
            pNodeTypeStr = "right child of ";
    }

    // Print the current node.
    printf("%d at address %p, %sparent at address: %p.\n", pCurNode->nKeyValue, pCurNode, pNodeTypeStr, pCurNode->pParentNode);

    // In case there is a left subtree, print it.
    if (pCurNode->pLeftNode)
        displayTree(pCurNode->pLeftNode);
}

// Main function.
void main()
{
    STreeNode* pHeadNode = NULL; // Pointer to head node of the tree.

    printf("Welcome to binary search tree program!\n");

    // Menu loop.
    do
    {
        // Display the choices to the user.
        printf("1. Insert a key in the tree.\n");
        printf("2. Find a key in the tree.\n");
        printf("3. Delete a key in the tree.\n");
        printf("4. Display the maximum key in the tree.\n");
        printf("5. Display the minimum key in the tree.\n");
        printf("6. Display all keys in the tree.\n");
        printf("7. Exit.\n");

        // Temporary variables used throughout the switch block.
        int nUsrChoice = 0,
            nTmp = 0;
        STreeNode* pTempNode;
        
        // Accept user choice.
        printf("Enter your choice: ");
        scanf("%d", &nUsrChoice);

        switch(nUsrChoice)
        {
            case 1:
                printf("Enter key value: ");
                scanf("%d", &nTmp);

                // Search for the given node.
                pTempNode = search(nTmp, pHeadNode);

                // In case the inserted key already exists.
                if (pTempNode)
                {
                    printf("%d key already exists in the tree at address %p! Please enter a different value!\n", nTmp, pTempNode);
                    continue;
                }

                // Insert the key into the tree.
                pTempNode = insert(nTmp, pHeadNode);
                
                // In case the insertion operation failed.
                if (!pTempNode)
                {
                    printf("Sorry! The program has crashed due to memory failure!\n");
                    return;
                }

                // In case the head node has not been created.
                if (!pHeadNode)
                    pHeadNode = pTempNode;

                printf("%d key node created at address %p.\n", nTmp, pTempNode);
                break;
            case 2:
                // In case the tree is empty.
                if (!pHeadNode)
                {
                    printf("The tree is empty! Nothing to search!\n");
                    break;
                }

                // Accept search key value.
                printf("Enter search key value: ");
                scanf("%d", &nTmp);

                pTempNode = search(nTmp, pHeadNode);

                // In case the inserted key already exists.
                if (pTempNode)
                    printf("%d key found in the tree at address %p.\n", nTmp, pTempNode);
                else
                    printf("%d key does not exist in the tree.\n", nTmp);

                break;
            case 3:
                // In case the tree is empty.
                if (!pHeadNode)
                {
                    printf("The tree is empty! Nothing to search!\n");
                    break;
                }

                // Accept search key value.
                printf("Enter key value: ");
                scanf("%d", &nTmp);

                pTempNode = search(nTmp, pHeadNode);

                // In case the inserted key does not exist.
                if (!pTempNode)
                    printf("%d key does not exist in the tree.\n", nTmp);
                else
                {
                    pTempNode = delete(nTmp, pTempNode);

                    // In case the root node has been deleted, the function returns the new root node of the tree.
                    if (pTempNode)
                        pHeadNode = pTempNode;
                }
                   
                break;
            case 4:
                // In case the tree is empty.
                if (!pHeadNode)
                {
                    printf("The tree is empty! Nothing to search!\n");
                    break;
                }

                pTempNode = findMaximum(pHeadNode);
                printf("The maximum key value in the tree is %d at %p.\n", pTempNode->nKeyValue, pTempNode);

                break;
            case 5:
                // In case the tree is empty.
                if (!pHeadNode)
                {
                    printf("The tree is empty! Nothing to search!\n");
                    break;
                }

                pTempNode = findMinimum(pHeadNode);
                printf("The minimum key value in the tree is %d at %p.\n", pTempNode->nKeyValue, pTempNode);
                break;
            case 6:
                printf("Displaying all keys in descending order:-\n");
                displayTree(pHeadNode);
                break;
            case 7:
                return;
            default:
                printf("Your input was not recognised! Please re-enter properly!\n");
                break;
        }
    } while (1);   
}