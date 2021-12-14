// Program implementing a circular linked list.
// Written by Amitabha Roy, Roll-No: 19012.
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
    // Allocate the first node if the list is empty.
    if (!pList)
    {
        pList = (SLinkedList *) malloc(sizeof(SLinkedList));

        // In case of allocation failure.
        if (!pList) return 0;

        pList->nStudentRollNo = nSRoll; // Assign values to the new node...
        pList->sStudentName = sSName;
        pList->pPrevNode = pList;
        pList->pNextNode = pList;
        
        return pList; // Return the pointer to the first node.
    }

    // Allocate a new student object.
    SLinkedList* pNewStudent = (SLinkedList *) malloc(sizeof(SLinkedList));

    // In case of allocation failure.
    if (!pNewStudent) return 0;    

    // Assign values to the new node...
    pNewStudent->nStudentRollNo = nSRoll;
    pNewStudent->sStudentName = sSName;
    pNewStudent->pPrevNode = pList->pPrevNode; // The tail of the linked list is the parent of the new node.
    pNewStudent->pNextNode = pList; // The head node of the linked list is the child of the new node.
    pNewStudent->pPrevNode->pNextNode = pNewStudent; // Connect the new node with the tail of the linked list.

    pList->pPrevNode = pNewStudent; // Connect the new node with the head of the linked list.
    
    // Return as success flag.
    return pNewStudent;
}

// Finds a student in the linked list on the basis of roll number.
SLinkedList* fFindStudent(SLinkedList* pList, int nSRoll)
{
    // In case the list is empty.
    if (!pList) 
        return NULL;

    // In case the list has only one element.
    if (pList->pNextNode == pList)
    {
        if (pList->nStudentRollNo == nSRoll)
            return pList;
        else
            return NULL;
    }

    SLinkedList* pStudent = pList;

    // For the case where there are more than one element.
    do
    {
        // Check for match with given roll number.
        if (pStudent->nStudentRollNo == nSRoll) 
            return pStudent;

        // Go to the next node.     
        pStudent = pStudent->pNextNode;
    } while (pStudent != pList);

    return NULL; // Search failed..
}

// Deletes a particular student in the linked list.
SLinkedList* fDeleteStudent(SLinkedList* pList, SLinkedList* pStudent)
{
    // If the list contains only one element.
    if (pList->pNextNode == pList)
    {
        free(pList); // Free the first node itself.
        return NULL;
    }
    
    // In case the reference node of the list is to be deleted. We consider the child of this node as the new reference node for the list.
    if (pStudent == pList) 
        pList = pList->pNextNode;

    // The parent node of pStudent can be accessed directly. This is where we have an advantage in case of double linked list over single linked list.
    // Connect the parent of pStudent with the child of pStudent child.
    pStudent->pPrevNode->pNextNode = pStudent->pNextNode;

    // Connnect the child of pStudent with the parent of pStudent.  
    pStudent->pNextNode->pPrevNode = pStudent->pPrevNode;

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

    // Reach to the end of the list via an exit controlled loop...
    do
    {
        printf("%d) %s--%d\n", nCounter, pStudent->sStudentName, pStudent->nStudentRollNo); // Display student details.
        pStudent = pStudent->pNextNode;
        nCounter++;
    } while(pStudent != pList);
}

// Main.
void main()
{
    SLinkedList* pList = NULL; // Linked list pointer.

    printf("Welcome to circular linked list program!\n");

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