#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_SEATS 20

/* =========================================================
   STUDENT NODE - LINKED LIST
   ========================================================= */

struct Student
{
    int id;
    char name[50];
    char department[30];
    int seat;
    struct Student *next;
};


/* =========================================================
   WAITING NODE - QUEUE
   ========================================================= */

struct WaitingStudent
{
    int id;
    char name[50];
    char department[30];
    struct WaitingStudent *next;
};


/* =========================================================
   CANCELLED NODE - STACK
   ========================================================= */

struct CancelledStudent
{
    int id;
    char name[50];
    int seat;
    struct CancelledStudent *next;
};


/* =========================================================
   GLOBAL POINTERS
   ========================================================= */

struct Student *studentHead = NULL;

struct WaitingStudent *queueFront = NULL;
struct WaitingStudent *queueRear = NULL;

struct CancelledStudent *stackTop = NULL;

int occupiedSeats[TOTAL_SEATS + 1] = {0};


/* =========================================================
   FIND AVAILABLE SEAT
   ========================================================= */

int findAvailableSeat()
{
    int i;

    for (i = 1; i <= TOTAL_SEATS; i++)
    {
        if (occupiedSeats[i] == 0)
        {
            return i;
        }
    }

    return -1;
}


/* =========================================================
   COUNT ALLOCATED STUDENTS
   ========================================================= */

int countStudents()
{
    int count = 0;

    struct Student *temp = studentHead;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}


/* =========================================================
   SEARCH STUDENT - LINKED LIST
   ========================================================= */

struct Student *searchStudent(int id)
{
    struct Student *temp = studentHead;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}


/* =========================================================
   ADD STUDENT - LINKED LIST
   ========================================================= */

void addStudent(int id, char name[], char department[], int seat)
{
    struct Student *newNode;

    newNode = (struct Student *)malloc(sizeof(struct Student));

    newNode->id = id;

    strcpy(newNode->name, name);

    strcpy(newNode->department, department);

    newNode->seat = seat;

    newNode->next = NULL;


    if (studentHead == NULL)
    {
        studentHead = newNode;
    }
    else
    {
        struct Student *temp = studentHead;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}


/* =========================================================
   DELETE STUDENT - LINKED LIST
   ========================================================= */

struct Student *deleteStudent(int id)
{
    struct Student *temp = studentHead;
    struct Student *previous = NULL;


    while (temp != NULL)
    {
        if (temp->id == id)
        {
            if (previous == NULL)
            {
                studentHead = temp->next;
            }
            else
            {
                previous->next = temp->next;
            }

            temp->next = NULL;

            return temp;
        }

        previous = temp;

        temp = temp->next;
    }

    return NULL;
}


/* =========================================================
   ENQUEUE - QUEUE
   ========================================================= */

void enqueue(int id, char name[], char department[])
{
    struct WaitingStudent *newNode;

    newNode =
        (struct WaitingStudent *)
        malloc(sizeof(struct WaitingStudent));


    newNode->id = id;

    strcpy(newNode->name, name);

    strcpy(newNode->department, department);

    newNode->next = NULL;


    if (queueRear == NULL)
    {
        queueFront = newNode;
        queueRear = newNode;
    }
    else
    {
        queueRear->next = newNode;

        queueRear = newNode;
    }
}


/* =========================================================
   DEQUEUE - QUEUE
   ========================================================= */

struct WaitingStudent *dequeue()
{
    struct WaitingStudent *temp;


    if (queueFront == NULL)
    {
        return NULL;
    }


    temp = queueFront;

    queueFront = queueFront->next;


    if (queueFront == NULL)
    {
        queueRear = NULL;
    }


    temp->next = NULL;

    return temp;
}


/* =========================================================
   QUEUE EMPTY CHECK
   ========================================================= */

int isQueueEmpty()
{
    if (queueFront == NULL)
    {
        return 1;
    }

    return 0;
}


/* =========================================================
   PUSH - STACK
   ========================================================= */

void push(int id, char name[], int seat)
{
    struct CancelledStudent *newNode;

    newNode =
        (struct CancelledStudent *)
        malloc(sizeof(struct CancelledStudent));


    newNode->id = id;

    strcpy(newNode->name, name);

    newNode->seat = seat;

    newNode->next = stackTop;

    stackTop = newNode;
}


/* =========================================================
   POP - STACK
   ========================================================= */

struct CancelledStudent *pop()
{
    struct CancelledStudent *temp;


    if (stackTop == NULL)
    {
        return NULL;
    }


    temp = stackTop;

    stackTop = stackTop->next;

    temp->next = NULL;

    return temp;
}


/* =========================================================
   DISPLAY STUDENTS - LINKED LIST
   ========================================================= */

void displayStudents()
{
    struct Student *temp = studentHead;


    printf("\n");
    printf("===============================================================\n");
    printf("                 ALLOCATED STUDENTS\n");
    printf("===============================================================\n");


    if (temp == NULL)
    {
        printf("No students currently allocated.\n");
        return;
    }


    printf("%-10s %-20s %-15s %-10s\n",
           "ID",
           "NAME",
           "DEPARTMENT",
           "SEAT");


    printf("---------------------------------------------------------------\n");


    while (temp != NULL)
    {
        printf("%-10d %-20s %-15s A-%02d\n",
               temp->id,
               temp->name,
               temp->department,
               temp->seat);

        temp = temp->next;
    }


    printf("===============================================================\n");
}


/* =========================================================
   DISPLAY WAITING QUEUE
   ========================================================= */

void displayQueue()
{
    struct WaitingStudent *temp = queueFront;


    printf("\n");
    printf("===============================================================\n");
    printf("                     WAITING QUEUE\n");
    printf("===============================================================\n");


    if (temp == NULL)
    {
        printf("Waiting queue is empty.\n");
        return;
    }


    printf("Front -> ");


    while (temp != NULL)
    {
        printf("[%d - %s]", temp->id, temp->name);

        if (temp->next != NULL)
        {
            printf(" -> ");
        }

        temp = temp->next;
    }


    printf(" <- Rear\n");

    printf("===============================================================\n");
}


/* =========================================================
   DISPLAY CANCELLED STACK
   ========================================================= */

void displayStack()
{
    struct CancelledStudent *temp = stackTop;


    printf("\n");
    printf("===============================================================\n");
    printf("                  CANCELLED STACK\n");
    printf("===============================================================\n");


    if (temp == NULL)
    {
        printf("No cancelled records.\n");
        return;
    }


    printf("TOP\n");


    while (temp != NULL)
    {
        printf("| ID: %d | %s | Seat: A-%02d |\n",
               temp->id,
               temp->name,
               temp->seat);

        printf("-------------------------------\n");

        temp = temp->next;
    }
}


/* =========================================================
   DISPLAY SEAT MAP
   ========================================================= */

void displaySeats()
{
    int i;


    printf("\n");
    printf("===============================================================\n");
    printf("                       SEAT MAP\n");
    printf("===============================================================\n");


    for (i = 1; i <= TOTAL_SEATS; i++)
    {
        if (occupiedSeats[i] == 1)
        {
            printf("[A-%02d X] ", i);
        }
        else
        {
            printf("[A-%02d _] ", i);
        }


        if (i % 5 == 0)
        {
            printf("\n");
        }
    }


    printf("\n");
    printf("X = Occupied    _ = Available\n");
}


/* =========================================================
   ALLOCATE FROM WAITING QUEUE
   ========================================================= */

void allocateFromQueue()
{
    struct WaitingStudent *waiting;

    int seat;


    if (isQueueEmpty())
    {
        return;
    }


    seat = findAvailableSeat();


    if (seat == -1)
    {
        return;
    }


    waiting = dequeue();


    addStudent(
        waiting->id,
        waiting->name,
        waiting->department,
        seat
    );


    occupiedSeats[seat] = 1;


    printf("\n");
    printf(">>> WAITING QUEUE UPDATE\n");

    printf("Student %s moved from waiting queue.\n",
           waiting->name);

    printf("Seat A-%02d allocated successfully.\n",
           seat);


    free(waiting);
}


/* =========================================================
   REGISTER STUDENT
   ========================================================= */

void registerStudent()
{
    int id;

    char name[50];

    char department[30];

    int seat;


    printf("\n");
    printf("===============================================================\n");
    printf("                    STUDENT REGISTRATION\n");
    printf("===============================================================\n");


    printf("Enter Student ID: ");
    scanf("%d", &id);


    if (searchStudent(id) != NULL)
    {
        printf("\nStudent ID already registered.\n");
        return;
    }


    printf("Enter Student Name: ");

    scanf(" %[^\n]", name);


    printf("Enter Department: ");

    scanf(" %[^\n]", department);


    seat = findAvailableSeat();


    if (seat != -1)
    {
        addStudent(
            id,
            name,
            department,
            seat
        );


        occupiedSeats[seat] = 1;


        printf("\n");
        printf("========================================\n");
        printf("        SEAT ALLOCATION SUCCESS\n");
        printf("========================================\n");

        printf("Student     : %s\n", name);

        printf("Department  : %s\n", department);

        printf("Seat        : A-%02d\n", seat);

        printf("Status      : CONFIRMED\n");

        printf("========================================\n");
    }
    else
    {
        enqueue(
            id,
            name,
            department
        );


        printf("\n");
        printf("========================================\n");
        printf("          WAITING QUEUE\n");
        printf("========================================\n");

        printf("All seats are currently occupied.\n");

        printf("Student %s added to waiting queue.\n",
               name);

        printf("Status : WAITING\n");

        printf("========================================\n");
    }
}


/* =========================================================
   CANCEL REGISTRATION
   ========================================================= */

void cancelRegistration()
{
    int id;

    struct Student *removed;


    printf("\n");
    printf("Enter Student ID to cancel: ");

    scanf("%d", &id);


    removed = deleteStudent(id);


    if (removed == NULL)
    {
        printf("\nStudent not found.\n");

        return;
    }


    occupiedSeats[removed->seat] = 0;


    push(
        removed->id,
        removed->name,
        removed->seat
    );


    printf("\n");
    printf("========================================\n");
    printf("       REGISTRATION CANCELLED\n");
    printf("========================================\n");

    printf("Student : %s\n",
           removed->name);

    printf("Seat    : A-%02d\n",
           removed->seat);

    printf("Status  : CANCELLED\n");

    printf("========================================\n");


    free(removed);


    allocateFromQueue();
}


/* =========================================================
   SEARCH MENU
   ========================================================= */

void searchMenu()
{
    int id;

    struct Student *student;


    printf("\n");
    printf("Enter Student ID to search: ");

    scanf("%d", &id);


    student = searchStudent(id);


    if (student == NULL)
    {
        printf("\nStudent not found.\n");
        return;
    }


    printf("\n");
    printf("========================================\n");
    printf("           STUDENT FOUND\n");
    printf("========================================\n");

    printf("ID          : %d\n",
           student->id);

    printf("Name        : %s\n",
           student->name);

    printf("Department  : %s\n",
           student->department);

    printf("Seat        : A-%02d\n",
           student->seat);

    printf("========================================\n");
}


/* =========================================================
   DASHBOARD
   ========================================================= */

void dashboard()
{
    int allocated;

    int available;


    allocated = countStudents();

    available = TOTAL_SEATS - allocated;


    printf("\n\n");

    printf("===============================================================\n");
    printf("             CAMPUS EVENT SEAT ALLOCATION SYSTEM\n");
    printf("===============================================================\n");

    printf("                  TECHFEST 2026\n");

    printf("===============================================================\n");

    printf("Total Seats       : %d\n",
           TOTAL_SEATS);

    printf("Allocated Seats   : %d\n",
           allocated);

    printf("Available Seats   : %d\n",
           available);

    printf("Waiting Students  : ");

    /* Count queue */
    {
        int count = 0;

        struct WaitingStudent *temp = queueFront;

        while (temp != NULL)
        {
            count++;

            temp = temp->next;
        }

        printf("%d\n", count);
    }

    printf("===============================================================\n");
}


/* =========================================================
   MAIN MENU
   ========================================================= */

int main()
{
    int choice;


    do
    {
        dashboard();


        printf("\n");
        printf("1. Register Student\n");
        printf("2. Cancel Registration\n");
        printf("3. Search Student\n");
        printf("4. Display Allocated Students\n");
        printf("5. Display Waiting Queue\n");
        printf("6. Display Cancelled Stack\n");
        printf("7. Display Seat Map\n");
        printf("8. Exit\n");


        printf("\nEnter your choice: ");

        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
                registerStudent();
                break;


            case 2:
                cancelRegistration();
                break;


            case 3:
                searchMenu();
                break;


            case 4:
                displayStudents();
                break;


            case 5:
                displayQueue();
                break;


            case 6:
                displayStack();
                break;


            case 7:
                displaySeats();
                break;


            case 8:
                printf("\n");
                printf("Thank you for using Campus Event Seat Allocation System!\n");
                printf("Goodbye!\n");
                break;


            default:
                printf("\nInvalid choice. Please try again.\n");
        }


        if (choice != 8)
        {
            printf("\nPress ENTER to continue...");

            getchar();
            getchar();
        }


    } while (choice != 8);


    return 0;
}