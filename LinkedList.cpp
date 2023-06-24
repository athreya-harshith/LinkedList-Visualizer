#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
void dll_display();
void display();
void drawstring(float x, float y, char* string, int col, int drawstringflag);

// NODE structure for linked listS.
struct node
{
    int info;
    struct node* link;
};
struct Dll_node
{
    int info;
    struct Dll_node* link;
    struct Dll_node* prevlink;
};

// Structure to store values for display on visualizer.
struct arr
{
    int p;
    int q;
}ar[20];

// Global Variable section.
typedef struct Dll_node* dll_node;
static dll_node dll_first = NULL; // dll_first dll_node of Linked List.
typedef struct node* NODE;
static NODE first = NULL; // First node of Linked List.
static int count = 0, flag = 1;
int succ = 1, succ1 = 1, ins_succ = 1;
int choice, item, key;
float color[5][3] = { {1.0, 1.0, 1.0}, {0.8, 0.0, 0.0}, {0.0, 0.0, 76.0}, {0.0, 0.0, 0.8},{104.0,0.0,165.0} };
int drawstringflag = 0, printflag = 1, titleflag = 1;

// Allocate memory for node.
NODE getnode()
{
    NODE x;
    x = (NODE)malloc(sizeof(struct node));
    if (x == NULL)
    {
        printf("Insufficient memory!!\n");
        exit(0);
    }
    return x;
}

// Display Linked List.
void lldisplay()//To display Linked list contetnts on the terminal
{
    NODE temp;
    int k;
    if (first == NULL)
    {
        printf("The list is empty!\n");
        return;
    }
    printf("\nContents of Singly Linked List: \n");
    temp = first;
    while (temp != NULL)
    {
        for (k = 0; k < count; k++)
        {
            printf("%d", temp->info);
            temp = temp->link;
            printf("\n");
        }
    }
    printf("\n");
}

// Insert element from Front of Linked list.
NODE  insert_front(int item, NODE first)
{
    NODE temp;
    temp = getnode();
    temp->info = item;
    temp->link = first;
    return temp;
}

// Insert element from Rear of Linked list.
NODE insert_rear(int item, NODE first)
{
    NODE temp;
    NODE cur;
    temp = getnode();
    temp->info = item;
    temp->link = NULL;
    if (first == NULL)
        return temp;
    cur = first;
    while (cur->link != NULL)
        cur = cur->link;
    cur->link = temp;
    return first;
}

// Insert node at a specified position.
NODE insert_specified(int item, NODE first)
{
    NODE next, cur, temp;
    temp = getnode();
    temp->info = item;
    if (first == NULL)
    {
        printf("The list is empty! Inserting node at the front...\n");
        temp->link = NULL;
        first = temp;
        return first;
    }
    printf("Enter the key : "); // Key = Node value after which the new node is to be inserted.
    scanf_s("%d", &key);
    cur = first;
    while (cur != NULL)
    {
        next = cur->link;
        if (cur->info == key)
        {
            printf("Key found!\n");
            cur->link = temp;
            temp->link = next;
            return first;
        }
        cur = cur->link;
    }
    if (cur == NULL)
    {
        printf("Search unsuccessful!\n");
        count--;
        ins_succ = 0;
    }
    return first;
}

// Delete node from Front of Linked List.
NODE delete_front(NODE first)
{
    NODE temp;
    if (first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return first;
    }
    temp = first;
    temp = temp->link;
    printf("Deleted item  =  %d \n", first->info);
    free(first);
    return temp;
}

// Delete node from Rear of Linked List.
NODE delete_rear(NODE first)
{
    NODE cur, prev;
    if (first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return first;
    }
    if (first->link == NULL)
    {
        printf("Item to be deleted is %d \n", first->info);
        free(first);
        return NULL;
    }
    prev = NULL;
    cur = first;
    while (cur->link != NULL)
    {
        prev = cur;
        cur = cur->link;
    }
    printf("Deleted item  =  %d \n", cur->info);
    free(cur);
    prev->link = NULL;
    return first;
}

// Delete a specified node from Linked List.
NODE delete_specified(NODE first)
{
    NODE prev, cur;
    if (first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return NULL;
    }
    printf("Enter the key: ");
    scanf_s("%d", &key);
    if (key == first->info)
    {
        cur = first;
        first = first->link;
        free(cur);
        return first;
    }
    prev = NULL;
    cur = first;
    while (cur != NULL)
    {
        if (key == cur->info)
            break;
        prev = cur;
        cur = cur->link;
    }
    if (cur == NULL)
    {
        printf("Search is unsuccessful!\n");
        count++;
        succ1 = 0;
        succ = 0;
        return first;
    }
    prev->link = cur->link;
    free(cur);
    return first;
}
void sll(int choice)
{
    switch (choice)
    {
    case 1:
        printf("Enter the item to be inserted: ");
        scanf_s("%d", &item);
        first = insert_front(item, first);
        count++;
        lldisplay();
        display();
        drawstring(200.0, 130.0, (char*)"NEW NODE INSERTED", 2, 0);
        break;
    case 2:
        printf("Enter the item to be inserted: ");
        scanf_s("%d", &item);
        first = insert_rear(item, first);
        count++;
        lldisplay();
        display();
        drawstring(200.0, 130.0, (char*)"NEW NODE INSERTED", 2, 0);
        break;
    case 3:
        printf("Enter the item to be inserted: ");
        scanf_s("%d", &item);
        ins_succ = 1;
        first = insert_specified(item, first);
        count++;
        lldisplay();
        display();
        if (!ins_succ)
            drawstring(200.0, 130.0, (char*)"KEY NODE DOESN'T EXIST", 2, 0);
        else
            drawstring(200.0, 130.0, (char*)"NEW NODE INSERTED", 2, 0);
        break;
    case 4:
        succ = 1;
        first = delete_front(first);
        count--;
        lldisplay();
        display();
        if (succ)
            drawstring(200.0, 130.0, (char*)"NODE DELETED", 2, 0);
        break;
    case 5:
        succ = 1;
        first = delete_rear(first);
        count--;
        lldisplay();
        display();
        if (succ)
            drawstring(200.0, 130.0, (char*)"NODE DELETED", 2, 0);
        break;
    case 6:
        succ = succ1 = 1;
        first = delete_specified(first);
        count--;
        lldisplay();
        display();
        if (succ)
            drawstring(200.0, 130.0, (char*)"NODE DELETED", 2, 0);
        if (!succ1)
            drawstring(200.0, 130.0, (char*)"KEY NODE DOESN'T EXIST", 2, 0);
        break;
    case 7:
        exit(0);
    }
}
// Allocate memory for node.
dll_node getdll_node()
{
    dll_node x;
    x = (dll_node)malloc(sizeof(struct Dll_node));
    if (x == NULL)
    {
        printf("Insufficient memory!!\n");
        exit(0);
    }
    return x;
}

// Display Linked List.
void dlldisplay()//To display Linked list contetnts on the terminal
{
    dll_node temp;
    int k;
    if (dll_first == NULL)
    {
        printf("The list is empty!\n");
        return;
    }
    printf("\nContents of Doubly Linked List: \n");
    temp = dll_first;
    while (temp != NULL)
    {
        printf("%d", temp->info);
        temp = temp->link;
        printf("\n");

    }
    printf("\n");
}

// Insert element from Front of Linked list.
dll_node  dll_insert_front(int item, dll_node dll_first)
{
    dll_node temp;
    temp = getdll_node();
    temp->info = item;
    temp->link = dll_first;
    temp->prevlink = NULL;
    if (dll_first == NULL)
        return temp;
    dll_first->prevlink = temp;
    temp->prevlink = NULL;
    return temp;
}

// Insert element from Rear of Linked list.
dll_node dll_insert_rear(int item, dll_node dll_first)
{
    dll_node temp;
    dll_node cur;
    temp = getdll_node();
    temp->info = item;
    temp->link = NULL;
    temp->prevlink = NULL;
    if (dll_first == NULL)
        return temp;
    cur = dll_first;
    while (cur->link != NULL)
        cur = cur->link;
    cur->link = temp;
    temp->prevlink = cur;
    return dll_first;
}

// Insert dll_node at a specified position.
dll_node dll_insert_specified(int item, dll_node dll_first)
{
    dll_node next, cur, temp;
    temp = getdll_node();
    temp->info = item;
    temp->link = NULL;
    temp->prevlink = NULL;
    if (dll_first == NULL)
    {
        printf("The list is empty! Inserting dll_node at the front...\n");
        temp->link = NULL;
        dll_first = temp;
        return dll_first;
    }
    printf("Enter the key : "); // Key = dll_node value after which the new dll_node is to be inserted.
    scanf_s("%d", &key);
    cur = dll_first;
    while (cur != NULL)
    {
        next = cur->link;
        if (cur->info == key)
        {
            printf("Key found!\n");
            cur->link = temp;
            temp->link = next;
            temp->prevlink = cur;
            return dll_first;
        }
        cur = cur->link;
    }
    if (cur == NULL)
    {
        printf("Search unsuccessful!\n");
        count--;
        ins_succ = 0;
    }
    return dll_first;
}

// Delete dll_node from Front of Linked List.
dll_node dll_delete_front(dll_node dll_first)
{
    dll_node temp;
    if (dll_first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return dll_first;
    }
    if (dll_first->link == NULL) {
        free(dll_first);
        return NULL;
    }
    temp = dll_first;
    temp = temp->link;
    temp->prevlink = NULL;
    printf("Deleted item  =  %d \n", dll_first->info);
    free(dll_first);
    return temp;
}

// Delete dll_node from Rear of Linked List.
dll_node dll_delete_rear(dll_node dll_first)
{
    dll_node cur, prev;
    if (dll_first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return dll_first;
    }
    if (dll_first->link == NULL)
    {
        printf("Item to be deleted is %d \n", dll_first->info);
        free(dll_first);
        return NULL;
    }
    prev = NULL;
    cur = dll_first;
    while (cur->link != NULL)
    {
        prev = cur;
        cur = cur->link;
    }
    printf("Deleted item  =  %d \n", cur->info);
    free(cur);
    prev->link = NULL;
    return dll_first;
}

// Delete a specified dll_node from Linked List.
dll_node dll_delete_specified(dll_node dll_first)
{
    dll_node prev, cur;
    if (dll_first == NULL)
    {
        printf("The list is empty, cannot delete!\n");
        count++;
        succ = 0;
        return NULL;
    }
    printf("Enter the key: ");
    scanf_s("%d", &key);
    if (key == dll_first->info)
    {
        cur = dll_first;
        dll_first = dll_first->link;
        dll_first->prevlink = NULL;
        free(cur);
        return dll_first;
    }
    prev = NULL;
    cur = dll_first;
    while (cur != NULL)
    {
        if (key == cur->info)
            break;
        prev = cur;
        cur = cur->link;
    }
    if (cur == NULL)
    {
        printf("Search is unsuccessful!\n");
        count++;
        succ1 = 0;
        succ = 0;
        return dll_first;
    }
    if (cur->link == NULL)
    {
        prev->link = NULL;
        free(cur);
        return dll_first;
    }
    prev->link = cur->link;
    cur->link->prevlink = prev;
    free(cur);
    return dll_first;
}

// Option menu for Linked List operations.
void dll(int choice)
{
    switch (choice)
    {
    case 1:
        printf("Enter the item to be inserted: ");
        scanf_s("%d", &item);
        dll_first = dll_insert_front(item, dll_first);
        count++;
        dlldisplay();
        dll_display();
        drawstring(200.0, 130.0, (char*)"NEW dll_node INSERTED", 2, 0);
        break;
    case 2:
        printf("Enter the item to be inserted: ");
        scanf_s("%d", &item);
        dll_first = dll_insert_rear(item, dll_first);
        count++;
        dlldisplay();
        dll_display();
        drawstring(200.0, 130.0, (char*)"NEW dll_node INSERTED", 2, 0);
        break;
    case 3:
        printf("Enter the item to be inserted: ");
        scanf_s("%d", &item);
        ins_succ = 1;
        dll_first = dll_insert_specified(item, dll_first);
        count++;
        dlldisplay();
        dll_display();
        if (!ins_succ)
            drawstring(200.0, 130.0, (char*)"KEY dll_node DOESN'T EXIST", 2, 0);
        else
            drawstring(200.0, 130.0, (char*)"NEW dll_node INSERTED", 2, 0);
        break;
    case 4:
        succ = 1;
        dll_first = dll_delete_front(dll_first);
        count--;
        dlldisplay();
        dll_display();
        if (succ)
            drawstring(200.0, 130.0, (char*)"dll_node DELETED", 2, 0);
        break;
    case 5:
        succ = 1;
        dll_first = dll_delete_rear(dll_first);
        count--;
        dlldisplay();
        dll_display();
        if (succ)
            drawstring(200.0, 130.0, (char*)"dll_node DELETED", 2, 0);
        break;
    case 6:
        succ = succ1 = 1;
        dll_first = dll_delete_specified(dll_first);
        count--;
        dlldisplay();
        dll_display();
        if (succ)
            drawstring(200.0, 130.0, (char*)"dll_node DELETED", 2, 0);
        if (!succ1)
            drawstring(200.0, 130.0, (char*)"KEY dll_node DOESN'T EXIST", 2, 0);
        break;
    case 7:
        exit(0);
    }
}


// Option menu for Linked List operations.

void dll_title()//To display contents of dll_first Window
{
    glClearColor(192.0, 192.0, 192.0, 1.0);
    drawstring(170.0, 240.0, (char*)"Doubly Linked List Visualizer", 1, 2);
    drawstring(130.0, 200.0, (char*)"Click Right Mouse Button for operations menu", 1, 1);
    drawstring(0.0, 50.0, (char*)"By:", 2, 0);
    drawstring(0.0, 30.0, (char*)"    Harshith P Athreya", 2, 0);
    drawstring(0.0, 10.0, (char*)"    Dheeraj M", 2, 0);
    glFlush();
}

// Display function for visualizer.
void dll_display()
{
    if (titleflag) // Ensure title is printed only once.
    {
        dll_title(); // Render the Title.
        titleflag = 0;
    }
    int i = 0, j = 0, k = 0, b[20];
    dll_node temp;
    glClearColor(192.0, 192.0, 192.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.6);
    drawstring(250.0, 450.0, (char*)"Doubly LINKED LIST", 1, 0);//Second Window Heading
    if (dll_first == NULL)//check for empty linked list
    {
        if (printflag)//check for dll_first time
        {
            printf("\nEmpty List\n");
            printflag = 0;
        }
    }
    temp = dll_first;
    while (temp != NULL)//To Display whole Linked List Every time a new operation is done through menu
    {
        for (k = 0; k < count; k++)
        {
            //y3-y1 dll_node height
            //2*(x2-x3) dll_node width or 2*(x1-x2)
            GLfloat x0 = 20, x1 = 50, y1 = 200, x2 = 80, y2 = 225;
            GLfloat x3 = 110, y3 = 250, x4 = 95, y4 = 225;
            GLfloat x5 = 130, y5 = 210, y6 = 240, x6 = 150;
            int pos = 130; // Constant multiplier for positioning.(initial x pos of the dll_node)
            // if (dll_first->link == NULL)
            // {

             //}
             //X0---x1----x2----x3
             /* y3
             * |
             * |
             * |
             * y1
             */
            if (dll_first->link == NULL)
            {
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // prevlink
                glVertex2i(x0 + k * pos, y1);//bottom left vertex
                glVertex2i(x0 + k * pos, y3);//top left
                glVertex2i(x1 + k * pos, y3);//top right
                glVertex2i(x1 + k * pos, y1);//bottom right
                glEnd();
                glColor3f(0.0, 0.0, 100.0);
                glBegin(GL_POLYGON); // Info box.
                glVertex2i(x1 + k * pos, y1);//bottom left vertex
                glVertex2i(x1 + k * pos, y3);//top left
                glVertex2i(x2 + k * pos, y3);//top right
                glVertex2i(x2 + k * pos, y1);//bottom right
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // Next link box.
                glVertex2i(x2 + k * pos, y1);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINES); // Slash in both pointers to indicate termination of Linked list
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glVertex2i(x0 + k * pos, y3);
                glVertex2i(x1 + k * pos, y1);
                glEnd();

            }
            else if (temp->link == NULL) {
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINES); // Slash to indicate termination of Linked list.(in next link)
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glVertex2i(x0 + k * pos, y3);
                glVertex2i(x1 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // prevlink
                glVertex2i(x0 + k * pos, y1);//bottom left vertex
                glVertex2i(x0 + k * pos, y3);//top left
                glVertex2i(x1 + k * pos, y3);//top right
                glVertex2i(x1 + k * pos, y1);//bottom right
                glEnd();
                glColor3f(0.0, 0.0, 100.0);
                glBegin(GL_POLYGON); // Info box.
                glVertex2i(x1 + k * pos, y1);
                glVertex2i(x1 + k * pos, y3);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x2 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // Next link box.
                glVertex2i(x2 + k * pos, y1);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.0, 0.0);
                if (temp->prevlink != NULL) {
                    glBegin(GL_LINE_STRIP); //Previous link
                    glVertex2i(35 + k * pos, y3);
                    glVertex2i(35 + k * pos, y3 + 35);
                    glVertex2i(-60 + k * pos, y3 + 35);
                    glVertex2i(-60 + k * pos, y3);
                    glEnd();
                    glColor3f(0.0, 0.0, 0.0);
                    glBegin(GL_LINES); //Arrow
                    glVertex2i(-75 + k * pos, y3 + 15);
                    glVertex2i(-60 + k * pos, y3);
                    glVertex2i(-45 + k * pos, y3 + 15);
                    glVertex2i(-60 + k * pos, y3);
                    glEnd();
                }
            }
            else
            {
                //x4 is a little behind x3
                //x4---x5 arrow line
                //y4 is b/w y1 and y3
                glColor3f(0.0f, 0.0f, 0.0f);
                glBegin(GL_LINES); // Line pointing to next dll_node.
                glVertex2i(x4 + k * pos, y4);
                glVertex2i(x6 + k * pos, y4);
                glEnd();
                glColor3f(0.0f, 0.0f, 0.0f);
                glBegin(GL_LINES); // Arrow marks.
                glVertex2i(x5 + k * pos, y6);
                glVertex2i(x6 + k * pos, y4);
                glVertex2i(x6 + k * pos, y4);
                glVertex2i(x5 + k * pos, y5);
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // prevlink
                glVertex2i(x0 + k * pos, y1);//bottom left vertex
                glVertex2i(x0 + k * pos, y3);//top left
                glVertex2i(x1 + k * pos, y3);//top right
                glVertex2i(x1 + k * pos, y1);//bottom right
                glEnd();
                glColor3f(0.0, 0.0, 100.0);
                glBegin(GL_POLYGON); // Info box.
                glVertex2i(x1 + k * pos, y1);
                glVertex2i(x1 + k * pos, y3);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x2 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // Next link box.
                glVertex2i(x2 + k * pos, y1);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.0, 0.0);
                if (temp->prevlink != NULL) {
                    glBegin(GL_LINE_STRIP); //Previous link
                    glVertex2i(35 + k * pos, y3);
                    glVertex2i(35 + k * pos, y3 + 35);
                    glVertex2i(-60 + k * pos, y3 + 35);
                    glVertex2i(-60 + k * pos, y3);
                    glEnd();
                    glColor3f(0.0, 0.0, 0.0);
                    glBegin(GL_LINES); //Arrow
                    glVertex2i(-75 + k * pos, y3 + 15);
                    glVertex2i(-60 + k * pos, y3);
                    glVertex2i(-45 + k * pos, y3 + 15);
                    glVertex2i(-60 + k * pos, y3);
                    glEnd();
                }
            }
            if (temp->link == NULL) {
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINES); // Slash in both pointers to indicate termination of Linked list
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
            }
            if (temp->prevlink == NULL) {
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINES); // Slash in both pointers to indicate termination of Linked list
                glVertex2i(x0 + k * pos, y3);
                glVertex2i(x1 + k * pos, y1);
                glEnd();

            }
            b[j] = temp->info;
            temp = temp->link;
            ar[i].p = b[j] / 10;
            ar[i].q = b[j] % 10;
            ar[i].p = ar[i].p + 48;
            ar[i].q = ar[i].q + 48;
            glColor3f(1.0, 1.0, 0.0);
            glRasterPos2f(55.0 + k * pos, 215.0);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ar[i].p); // Print dll_node value.
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ar[i].q);
            drawstring(50.0 + k * pos, 185, (char*)"INFO", 3, 0);
            drawstring(85.0 + k * pos, 185, (char*)"NEXT", 1, 0);
            drawstring(15.0 + k * pos, 185, (char*)"PREV", 1, 0);
            i++;
            j++;
            glFlush();
        }
    }
}


// Initialize window properties. 
void init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glMatrixMode(GL_MODELVIEW);
}

// Function to print strings on rendered window.
void drawstring(float x, float y, char* string, int col, int drawstringflag)
{
    char* c;
    glColor3fv(color[col]);
    glRasterPos2f(x, y);
    if (drawstringflag == 0)
    {
        for (c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
    else if (drawstringflag == 1)
    {
        for (c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    else
    {
        for (c = string; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

// Delay function.
void delay()
{
    int i, j;
    for (i = 0; i < 5000; i++)
        for (j = 0; j < 5000; j++)
            ;
}

// Title display function.
void title()//To display contents of First Window
{
    glClearColor(192.0, 192.0, 192.0, 1.0);
    drawstring(170.0, 240.0, (char*)"Singly Linked List Visualizer", 1, 2);
    drawstring(130.0, 200.0, (char*)"Click Right Mouse Button for operations menu", 1, 1);
    drawstring(0.0, 50.0, (char*)"By:", 2, 0);
    drawstring(0.0, 30.0, (char*)"    Harshith P Athreya", 2, 0);
    drawstring(0.0, 10.0, (char*)"    Dheeraj M", 2, 0);
    glFlush();
}

// Display function for visualizer.
void display()
{
    if (titleflag) // Ensure title is printed only once.
    {
        title(); // Render the Title.
        titleflag = 0;
    }
    int i = 0, j = 0, k = 0, b[20];
    NODE temp;
    glClearColor(192.0, 192.0, 192.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.6);
    drawstring(250.0, 450.0, (char*)"SINGLY LINKED LIST", 1, 0);//Second Window Heading
    if (first == NULL)//check for empty linked list
    {
        if (printflag)//check for First time
        {
            printf("\nEmpty List\n");
            printflag = 0;
        }
    }
    temp = first;
    while (temp != NULL)//To Display whole Linked List Every time a new operation is done through menu
    {
        for (k = 0; k < count; k++)
        {
            //y3-y1 Node height
            //2*(x2-x3) Node width or 2*(x1-x2)
            GLfloat x1 = 50, y1 = 200, x2 = 80, y2 = 225;
            GLfloat x3 = 110, y3 = 250, x4 = 95, y4 = 225;
            GLfloat x5 = 160, y5 = 210, y6 = 240, x6 = 180;
            int pos = 130; // Constant multiplier for positioning.(initial x pos of the node)
            if (first->link == NULL)
            {
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINES); // Slash to indicate termination of Linked list.
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
            }
            //x1----x2----x3
            /* y3
            * |
            * |
            * |
            * y1
            */
            if (first->link == NULL)
            {
                glColor3f(0.0, 0.0, 100.0);
                glBegin(GL_POLYGON); // Info box.
                glVertex2i(x1 + k * pos, y1);//bottom left vertex
                glVertex2i(x1 + k * pos, y3);//top left
                glVertex2i(x2 + k * pos, y3);//top right
                glVertex2i(x2 + k * pos, y1);//bottom right
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // Next link box.
                glVertex2i(x2 + k * pos, y1);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINES); // Slash to indicate termination of Linked list.s
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
            }
            else if (temp->link == NULL) {
               
                glColor3f(0.0, 0.0, 100.0);
                glBegin(GL_POLYGON); // Info box.
                glVertex2i(x1 + k * pos, y1);
                glVertex2i(x1 + k * pos, y3);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x2 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // Next link box.
                glVertex2i(x2 + k * pos, y1);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_LINES); // Slash to indicate termination of Linked list.s
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
            }
            else
            {
                //x4 is a little behind x3
                //x4---x5 arrow line
                //y4 is b/w y1 and y3
                glColor3f(0.0f, 0.0f, 0.0f);
                glBegin(GL_LINES); // Line pointing to next node.
                glVertex2i(x4 + k * pos, y4);
                glVertex2i(x6 + k * pos, y4);
                glEnd();
                glColor3f(0.0f, 0.0f, 0.0f);
                glBegin(GL_LINES); // Arrow marks.
                glVertex2i(x5 + k * pos, y6);
                glVertex2i(x6 + k * pos, y4);
                glVertex2i(x6 + k * pos, y4);
                glVertex2i(x5 + k * pos, y5);
                glEnd();
                glColor3f(0.0, 0.0, 100.0);
                glBegin(GL_POLYGON); // Info box.
                glVertex2i(x1 + k * pos, y1);
                glVertex2i(x1 + k * pos, y3);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x2 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.60, 0.80);
                glBegin(GL_POLYGON); // Next link box.
                glVertex2i(x2 + k * pos, y1);
                glVertex2i(x2 + k * pos, y3);
                glVertex2i(x3 + k * pos, y3);
                glVertex2i(x3 + k * pos, y1);
                glEnd();
                glColor3f(0.0, 0.0, 0.0);
            }
            b[j] = temp->info;
            temp = temp->link;
            ar[i].p = b[j] / 10;
            ar[i].q = b[j] % 10;
            ar[i].p = ar[i].p + 48;
            ar[i].q = ar[i].q + 48;
            glColor3f(1.0, 1.0, 0.0);
            glRasterPos2f(55.0 + k * pos, 215.0);
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ar[i].p); // Print Node value.
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ar[i].q);
            drawstring(50.0 + k * pos, 185, (char*)"INFO", 3, 0);
            drawstring(85.0 + k * pos, 185, (char*)"LINK", 1, 0);
            i++;
            j++;
            glFlush();
        }
    }
}

int main(int argc, char** argv)
{
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 120; i++) {
            printf("*");
        }
        printf("\n");
    }
    printf("\t\t\t\t\t\tEnter your choice\n");
    printf("\t\t\t\t\t\t1.Singly Linked List\n\t\t\t\t\t\t2.Doubly Linked List\n\t\t\t\t\t\tPress any other key to exit...\n");
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 120; i++) {
            printf("*");
        }
        printf("\n");
    }
    int ch;
    scanf_s("%d", &ch);
    switch (ch) {
    case 1: {
            printf("                     SINGLY LINKED LIST                       \n\n");
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowSize(640, 480);
            glutInitWindowPosition(0, 0);
            glutCreateWindow("Singly Linked List Visualizer");
            glutCreateMenu(sll);
            //int sub_id=glutCreateMenu(sll);//Create a submenu and store the identifier
            glutAddMenuEntry("Insert Front", 1);//Sll submenu entries
            glutAddMenuEntry("Insert Rear", 2);
            glutAddMenuEntry("Insert Specified", 3);
            glutAddMenuEntry("Delete Front", 4);
            glutAddMenuEntry("Delete Rear", 5);
            glutAddMenuEntry("Delete Specified", 6);
            glutAddMenuEntry("Exit", 7);
            glutAttachMenu(GLUT_RIGHT_BUTTON);
            glutDisplayFunc(display);
            init();
            glutMainLoop();
    }
            break;
    case 2: {
            printf("                     DOUBLY LINKED LIST                       \n\n");
            glutInit(&argc, argv);
            glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
            glutInitWindowSize(640, 480);
            glutInitWindowPosition(0, 0);
            glutCreateWindow("Doubly Linked List Visualizer");
            glutCreateMenu(dll);
            //int sub_id=glutCreateMenu(sll);//Create a submenu and store the identifier
            glutAddMenuEntry("Insert Front", 1);//Sll submenu entries
            glutAddMenuEntry("Insert Rear", 2);
            glutAddMenuEntry("Insert Specified", 3);
            glutAddMenuEntry("Delete Front", 4);
            glutAddMenuEntry("Delete Rear", 5);
            glutAddMenuEntry("Delete Specified", 6);
            glutAddMenuEntry("Exit", 7);
            glutAttachMenu(GLUT_RIGHT_BUTTON);
            glutDisplayFunc(dll_display);
            init();
            glutMainLoop();
        }
            break;
        default:exit(0);
    }
    return 0;
}