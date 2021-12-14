// Program implementing a double linked list.
// Written by Amitabha Roy, Roll-No: 19012
// Note: Name entries with white-spaces are not supported by the program.

#include<stdio.h>
#include<stdlib.h>

// List structure...
typedef struct _SLinkedList
{
    int nStudentRollNo;
    char* sStudentName;
    struct _SLinkedList* pPrevNode;
    struct _SLinkedList* pNextNode;
} SLinkedList;

// Inserts a student in the linked list.
SLinkedList* fInsertStudent(SLinkedList* pList, int nSRoll, char* sSName)
{
    // Variable for iteration purposes.
    SLinkedList* pStudent = pList;

    // Allocate the first node if the list is empty.
    if (!pStudent)
    {
        pStudent = (SLinkedList *) malloc(sizeof(SLinkedList));

        // In case of allocation failure.
        if (!pStudent) return 0;

        pStudent->nStudentRollNo = nSRoll; // Assign values to the new node...
        pStudent->sStudentName = sSName;
        pStudent->pNextNode = NULL;
        
        return pStudent; // Return the pointer to the first node.
    }

    // Reach to the end of the list...
    while(pStudent->pNextNode) 
        pStudent = pStudent->pNextNode;
    
    // Allocate a new student object.
    SLinkedList* pNewStudent = (SLinkedList *) malloc(sizeof(SLinkedList));

    // In case of allocation failure.
    if (!pNewStudent) return 0;    

    // Assign values to the new node...
    pNewStudent->nStudentRollNo = nSRoll;
    pNewStudent->sStudentName = sSName;
    pNewStudent->pPrevNode = pStudent; // The tail of the linked list is the parent of the new node.
    pNewStudent->pNextNode = NULL;

    // Connect the new node with the tail of the linked list.
    pStudent->pNextNode = pNewStudent;

    // Return as success flag.
    return pNewStudent;
}

// Finds a student in the linked list on the basis of roll number.
SLinkedList* fFindStudent(SLinkedList* pList, int nSRoll)
{
    SLinkedList* pStudent = pList;

    // In case the tree is empty.
    if (!pList) 
        return NULL;

    // Reach to the end of the list...
    while(pStudent)
    {
        // Check for match with given roll number.
        if (pStudent->nStudentRollNo == nSRoll) 
            return pStudent;

        // Go to the next node.     
        pStudent = pStudent->pNextNode;
    }

    return NULL; // Search failed..
}

// Deletes a particular student in the linked list.
SLinkedList* fDeleteStudent(SLinkedList* pList, SLinkedList* pStudent)
{
    // If the list contains only one element.
    if (pList->pNextNode == NULL)
    {
        free(pList); // Free the first node itself.
        return NULL;
    }
    else if (pStudent == pList) // If the first node is to be deleted.
    {
        pList = pList->pNextNode; // Take the next node as the starting node.
        pList->pPrevNode = NULL; // The head node has no parent node.
        free(pStudent); // Release the first node.
        return pList;
    }

    // The parent node of pStudent can be accessed directly. This is where we have an advantage in case of double linked list over single linked list.
    // Connect the parent of pStudent with the child of pStudent child.
    pStudent->pPrevNode->pNextNode = pStudent->pNextNode;

    // In case the child of pStudent exists, then connnect it with the parent of pStudent.  
    if (pStudent->pNextNode) pStudent->pNextNode->pPrevNode = pStudent->pPrevNode;

    free(pStudent); // Release the given node...
    return pList; // Return the first node pointer.
}

// Displays the linked list to the user.
void fDisplayList(SLinkedList* pList)
{
    SLinkedList* pStudent = pList;

    if (!pStudent) return;

    // Display messages...
    printf("Displaying list contents.\n");
    printf("Student Name--Roll-No\n");

    int nCounter = 1;

    // Reach to the end of the list...
    while(pStudent)
    {
        printf("%d) %s--%d\n", nCounter, pStudent->sStudentName, pStudent->nStudentRollNo); // Display student details.
        pStudent = pStudent->pNextNode;
        nCounter++;
    }
}

// Main.
void main()
{
    SLinkedList* pList = NULL; // Linked list pointer.

    printf("Welcome to double linked list program!\n");

    // Start an infinite for loop.
    while(1)
    {
        // Display the choices to the user.
        printf("1. Insert student in the list.\n");
        printf("2. Find a student in the list.\n");
        printf("3. Change a student's details in the list.\n");
        printf("4. Delete a stuedent from the list.\n");
        printf("5. Display the list.\n");
        printf("6. Exit.\n");

        int nChoice = 0; // Stores the user's choice.

        // Accept input from the user...
        printf("Enter your choice: ");
        scanf("%d", &nChoice);

        // Global declarations relative to the switch block...
        SLinkedList* pStudent = NULL;
        char* pName = NULL;
        int nRollNo = 0;

        switch(nChoice)
        {
            case 1:
                pName = (char *) malloc(sizeof(char) * 101); // Allocate a 100 bytes string.
                nRollNo = 0;

                // Accept student name.
                printf("Enter student name (upto 100 characters only): ");
                scanf("%s", pName);

                // Ensure uniqueness of roll no. of each student.
                while(1)
                {
                    // Accept student roll no.
                    printf("Enter new student roll no.: ");
                    scanf("%d", &nRollNo);

                    SLinkedList* pSTemp = fFindStudent(pList, nRollNo);

                    // If some other student is in the record with the same roll no.
                    if (pSTemp)
                    {
                        printf("A student already exists with the given roll no.! Please enter something different!\n");
                        continue;
                    }
                    
                    break; // End the loop.
                }

                // In case the list is empty.
                if (!pList)
                {
                    // Retrieve the newly created node. This node is the head node.
                    pList = fInsertStudent(pList, nRollNo, pName);

                    // In case of any problem.
                    if (!pList)
                    {
                        printf("Sorry!The program has crashed :(!\n");
                        return;
                    }   
                }    
                else if (!fInsertStudent(pList, nRollNo, pName)) // In case of any problem.
                {
                    printf("Sorry!The program has crashed :(!\n");
                    return;
                }

                break;
            case 2:
                nRollNo = 0;

                // Accept student roll no.
                printf("Enter new student roll no.: ");
                scanf("%d", &nRollNo);

                // Search.
                SLinkedList* pSTemp = fFindStudent(pList, nRollNo);

                // If the searched student exists in the record.
                if (pSTemp)
                {
                    printf("Match found in the list!\n");
                    printf("Name of the searched student: %s\n", pSTemp->sStudentName);
                    printf("Roll number of the searched student: %d\n", pSTemp->nStudentRollNo);
                }
                else
                    printf("No student found with the roll number %d in the list.\n", nRollNo);
                
                break;
            case 3:
                pName = (char *) malloc(sizeof(char) * 101); // Allocate a 100 bytes string.
                nRollNo = 0;

                printf("Enter student roll no.: ");
                scanf("%d", &nRollNo);

                // Search for the student with the given roll number.
                pStudent = fFindStudent(pList, nRollNo);

                if (!pStudent)
                {
                    printf("No student found with the roll no. %d in the record.\n", nRollNo);
                    break;
                }

                // Accept student name.
                printf("Enter new student name (upto 100 characters only): ");
                scanf("%s", pName);

                // Ensure uniqueness of roll no. of each student.
                while(1)
                {
                    // Accept student roll no.
                    printf("Enter new student roll no.: ");
                    scanf("%d", &nRollNo);

                    SLinkedList* pSTemp = fFindStudent(pList, nRollNo);

                    // In case the roll number entered is the same, then we can just skip the check.
                    // Otherwise we should ensure uniqueness.
                    if ((pSTemp) && (pSTemp != pStudent))
                    {
                        printf("A student already exists with the given roll no.! Please enter something different!\n");
                        continue;
                    }

                    break; // End the loop.
                }

                free(pStudent->sStudentName); // Release the previously allocated memory.

                // Edit the student details.
                pStudent->sStudentName = pName;
                pStudent->nStudentRollNo = nRollNo;

                break;
            case 4:
                nRollNo = 0;

                // Accept student roll no.
                printf("Enter student roll no.: ");
                scanf("%d", &nRollNo);

                // Search.
                SLinkedList* pStudent = fFindStudent(pList, nRollNo);

                // In case not found.
                if (!pStudent)
                {
                    printf("No student found with the roll no. %d in the list.\n", nRollNo);
                    break;
                }

                // Delete the student from the list. Retrieve the modified list from the function.
                pList = fDeleteStudent(pList, pStudent);

                break;
            case 5:
                fDisplayList(pList);
                break;
            case 6:
                return;
                break;
        default:
            printf("Your input was not recognised! Please try again!\n");
        }
    }
}