// Program implementing a single linked list.
// Written by Amitabha Roy, Roll-No: 19012
#include<stdio.h>
#include<stdlib.h>

// List structure...
typedef struct _SLinkedList
{
    int nStudentRollNo;
    char* sStudentName;
    struct _SLinkedList* pNextNode;
} SLinkedList;

// Inserts a student in the linked list.
SLinkedList* fInsertStudent(SLinkedList* pList, int nSRoll, char* sSName)
{
    SLinkedList* pStudent = pList;

    // Allocate the first node if the list is empty.
    if (!pStudent)
    {
        if (!(pStudent = (SLinkedList *) malloc(sizeof(SLinkedList)))) return 0;   
        pStudent->nStudentRollNo = nSRoll; // Assign values to the new node...
        pStudent->sStudentName = sSName;
        pStudent->pNextNode = NULL;
        return pStudent; // Return the pointer to the first node.
    }

    // Reach to the end of the list...
    while(pStudent->pNextNode) pStudent = pStudent->pNextNode;
    
    // Allocate a new student object.
    if (!(pStudent->pNextNode = (SLinkedList *) malloc(sizeof(SLinkedList)))) return 0;    
    pStudent->pNextNode->nStudentRollNo = nSRoll; // Assign values to the new node...
    pStudent->pNextNode->sStudentName = sSName;
    pStudent->pNextNode->pNextNode = NULL;

    // Return as success flag.
    return pStudent;
}

// Finds a student in the linked list on the basis of roll number.
SLinkedList* fFindStudent(SLinkedList* pList, int nSRoll)
{
    SLinkedList* pStudent = pList;

    if (!pStudent) return NULL;

    // Reach to the end of the list...
    while(pStudent)
    {
        if (pStudent->nStudentRollNo == nSRoll) return pStudent;
        pStudent = pStudent->pNextNode;
    }

    return NULL; // Search failed..
}

// Deletes a particular student in the linked list.
SLinkedList* fDeleteStudent(SLinkedList* pList, SLinkedList* pStudent)
{
    SLinkedList* pSTemp = pList; // Temporary student pointer...

    // If the list contains only one element.
    if (pSTemp->pNextNode == NULL)
    {
        free(pSTemp); // Free the first node itself.
        return NULL;
    }
    else if (pList == pStudent) // If the first node is to be deleted.
    {
        pList = pStudent->pNextNode; // Take the next node as the starting node.
        free(pStudent); // Release the first node.
        return pList;
    }

    // Reach to the previous element of given node...
    while(pSTemp)
    {
        // Break when the required previous node is determined.
        if (pSTemp->pNextNode == pStudent) break;
        pSTemp = pSTemp->pNextNode;
    }

    // Change the next node of this node to the next node of its successor.
    pSTemp->pNextNode = pStudent->pNextNode;
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

    printf("Welcome to single linked list program!\n");

    // Start an infinite for loop.
    while(1)
    {
        // Display the choices to the user.
        printf("1. Insert student in the list.\n");
        printf("2. Change a student's details in the list.\n");
        printf("3. Delete a stuedent from the list.\n");
        printf("4. Display the list.\n");
        printf("5. Exit.\n");

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

                if (!pList)
                {
                    if (!(pList = fInsertStudent(pList, nRollNo, pName)))
                    {
                        printf("Sorry!The program has crashed :(!\n");
                        return;
                    }
                }    
                else if (!fInsertStudent(pList, nRollNo, pName))
                {
                    printf("Sorry!The program has crashed :(!\n");
                    return;
                }

                break;
            case 2:
                pName = (char *) malloc(sizeof(char) * 101); // Allocate a 100 bytes string.
                nRollNo = 0;

                printf("Enter student roll no.: ");
                scanf("%d", &nRollNo);

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
            case 3:
                nRollNo = 0;

                // Accept student roll no.
                printf("Enter student roll no.: ");
                scanf("%d", &nRollNo);

                SLinkedList* pStudent = fFindStudent(pList, nRollNo);

                if (!pStudent)
                {
                    printf("No student found with the roll no. %d in the record.\n", nRollNo);
                    break;
                }

                // Delete the student from the list.
                pList = fDeleteStudent(pList, pStudent);

                break;
            case 4:
                fDisplayList(pList);
                break;
            case 5:
                return;
                break;
        default:
            printf("Your input is not recognised! Please try again!\n");
        }
    }
}