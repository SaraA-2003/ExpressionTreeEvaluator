/*Name: Sara Adnan Mahmoud Allahaleh
ID:1211083
Section:1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>


#define MAX 200 //maximum size of array
/** @brief Define a structure "StackRecord" ,that consist of two integers and pointer of type char.
*This structure is a Stack built using array implementation.It is designed to depict a stack of characters specifically utilized
*for infix-to-postfix conversion
*
*  @param Top integer,it denotes the latest addition to the stack and simultaneously signifies the total count of elements present in the stack.
*  @param MaxSize integer,it denotes the maximum size of the stack.
*  @param Array pointer of type char,Head of an array that will be used to store characters of the stack in it.
*/
struct StackRecord
{
    int Top;
    int MaxSize;
    char* Array;
};
typedef struct StackRecord *Stack;//another name of the stack structure


/** @brief Define a structure "node" ,that consist of two characters and two pointers of type struct node.
*This structure is designed to depict a tree node of characters specifically utilized for postfix evaluation.
*
*  @param data char,where the character will be stored
*  @param sign char,it denotes sign of the number(char) that will be stored in the node.
*  @param left pointer of type Treeptr.
*  @param right pointer of type Treeptr.
*/
struct node;
typedef struct node *Treeptr;
struct node
{
    char data;
    char sign;
    Treeptr left;
    Treeptr right;
};

/** @brief Define a structure "treeStack" ,that consist of two integers and one pointer of type Treeptr.
*This structure is designed to depict a tree stack of characters specifically utilized for postfix evaluation.
*
*  @param Top integer.
*  @param MaxSize integer.
*  @param Array pointer of type Treeptr,Head of an array that will be used to store elements of the stack in it
*/

struct treeStack;
struct treeStack
{
    int Top;
    int MaxSize;
    Treeptr *Array;
};
typedef struct treeStack *Tree;//another name of the treeStack structure

/////////Global variables/////////

//2D array(equations) used to store infix equations from input file
char Equations[MAX][MAX];//Declares a global array to store maximum 200 equations of length 200

int counter;//Stores the count of equations in file

//2D array (postfixEqs) used to store postfix expression of equations
char postfixEqs[MAX][MAX];//Declares a global array to store maximum 200 equations of length 200

//1D array (results) used to store the results of the equations evaluation
int results[MAX];//Declares a global array to store maximum 200 numbers

int isRead=0;//checks if the input file has been read or not
int isEqEvaluated=0;//checks if the equations has been evaluated or not



/////////Functions/////////

Stack CreateStack (int capacity);
int isEmpty(Stack S);
int isFull(Stack S);
void disposeStack(Stack S);
void push(Stack S,char value);
void pop(Stack S);
char Top (Stack S);

Tree CreateTree(int capacity);
int isTFull(Tree T);
void popT (Tree T);
Treeptr TopT (Tree T);
void pushT (Tree S, Treeptr value);
int isTEmpty(Tree T);
void disposeTree(Tree T);
Treeptr createNode(char value);

int isOperator(char oper);
int opPriority(char oper);
void InfixToPostfix(Stack S, char eq[MAX], int pos);

int equationLength (char eq[MAX]);
int isEqValid(char eq[MAX], int index, int count);
int checkEqStruct(char eq[MAX], int index, int count);

void readInputFile();
void deleteSpaces_specialChar(char eq[MAX]);

Treeptr TreeCreation(char postfixEq[MAX], int index);
int countRight(Treeptr root);
int EvaluateTreeExpression(Treeptr root);


void displayMenu();
void printToOutputFile();



int main()
{



    int op;
    displayMenu();
    scanf("%d",&op);

    while (op != 6)
    {
        switch(op)
        {
        case 1:
        {
            if(isRead==1)// checks if the input file has been read
            {

                printf("\nThe input file has been already processed.\nPlease select a different operation to perform.\n\n");

                break;
            }

            readInputFile();
            printf("\n<<<<The file has been effectively loaded, and the strings are now ready for use.>>>>>>\n\n");

            isRead=1;//the file has been read

            break;
        }

        case 2: //print the infix equations
        {

            if(isRead==0)  // checks if the input file has been read  or not
            {

                printf("\nThe Equations are not currently loaded from the file.\nPlease execute operation 1 to load them before proceeding.\n\n");
                break;
            }

            printf("\n<<<<< INFIX EQUATIONS >>>>>\n\n\n");


            int i;
            for(i=0; i<counter; i++)
            {

                printf("Equation NO.{%d} : %s\n\n", i+1, Equations[i]);
            }


            break;
        }

        case 3://Evaluate infix equations by utilizing an expression tree.
        {
            if(isRead==0)
            {

                printf("\nThe Equations are not currently loaded from the file.\nPlease execute operation 1 to load them before proceeding.\n\n");

                break;
            }

            printf("\n<<<<<<The evaluation of postfix equations is in progress...>>>>>>\n\n");

            Stack S= CreateStack(MAX);
            int i;

            for(i=0; i<counter; i++)
            {

                InfixToPostfix(S, Equations[i], i);//Convert an infix expression to its postfix equivalent.

            }

            int Eqresult=0;

            Treeptr tree;


            for(i=0; i<counter; i++)
            {


                tree=TreeCreation(postfixEqs[i], i);//create tree node for the evaluation



                Eqresult=EvaluateTreeExpression(tree);//evaluate the postfix expression of the equation
                results[i]=Eqresult;//Store the evaluation result in an array named "results"

                if(Eqresult==INT_MIN)//If the result comes from dividing by zero
                {

                    printf("\nInvalid evaluation for equation NO.{%d} : Division by zero error detected!\n\n",i+1);
                    continue;
                }

                printf("\nEvaluation of equation NO.{%d} : %d\n\n",i+1,Eqresult);
            }

            isEqEvaluated=1;//the equation has been evaluated
            disposeStack(S);


            break;
        }

        case 4://print postfix expression of equations
        {

            if(isRead==0)
            {

                printf("\nThe Equations are not currently loaded from the file.\nPlease execute operation 1 to load them before proceeding.\n\n");

                break;
            }

            printf("\n<<<<< POSTFIX EQUATIONS >>>>>\n\n\n");

            Stack S1= CreateStack(MAX);
            int i;

            for(i=0; i<counter; i++)
            {


                InfixToPostfix(S1, Equations[i], i);


                printf("Postfix equation NO.{%d} : %s\n\n", i+1, postfixEqs[i]);

            }


            disposeStack(S1);

            break;
        }

        case 5://print the evaluation & postfix expression to the output file
        {
            if(isRead==0)
            {

                printf("\nThe Equations are not currently loaded from the file.\nPlease execute operation 1 to load them before proceeding.\n\n");

                break;
            }
            if(isEqEvaluated==0)//checks if the equations have been evaluated or not before print them in the output file
            {
                printf("\nThe equations have not yet been evaluated for printing their results to the output file.\nPlease select operation '3' first.\n\n");
                break;
            }


            printToOutputFile();
            printf("The postfix expression and its evaluation for the equations have been saved in the 'output.txt' file.\n\n");


            break;
        }
        default :
            printf("The operation entered is not valid. Please choose again..\n\n");//if the user input non valid op
        }

        displayMenu();
        scanf("%d",&op);

    }
    //if (op==6)
    printf("\n<<<<< You have exited my program. Thank you for using it!! >>>>>\n");




    return 0;
}


//////////displayMenu//////////
/** @brief This function presents a menu of operations.
 *
 *  @return Void.
 */
void displayMenu()
{
    printf("\n\nPlease select the option number for the action you wish to perform:\n\n");
    printf("1- Read equations from input file\n");
    printf("2- Print equations (Infix expression)\n");
    printf("3- Evaluate equations using expression tree\n");
    printf("4- Print equations (postfix expression)\n");
    printf("5- Save the postfix expression of equations and their results to output file\n");
    printf("6- Exit\n\n");
    printf("Enter:\t");

}

//////////CreateStack//////////
/** @brief This Function creates a stack using array implementation .
 *
 *it creates the head using malloc ,then it checks if the head is exist.
 *then we assign the size of the stack array , and -1 to the top(indicates it is empty),also we create the array using
 *dynamic memory allocation.
 *
 *  @param S  pointer of type Stack ,it will be the head of the stack.
 *  @return  pointer of type Stack .
 */
Stack CreateStack (int capacity)
{

    Stack S;


    S=(Stack)malloc (sizeof(struct StackRecord));

    if(S == NULL)
    {
        printf("The creation of a stack is not possible due to insufficient memory space..\n");
        return S;
    }
    S->MaxSize=capacity;
    S->Top=-1;

    S->Array = (char*)malloc (sizeof(char)*S->MaxSize);//Dynamic memory allocation for the stack array

    if(S->Array == NULL)
    {
        printf("The creation of an array is not possible due to insufficient memory space..\n");
        return NULL;
    }
    return(S);

}
//////////CreateTree//////////
/** @brief This Function creates a Tree Stack.
 *
 *it creates the head using malloc ,then it checks if the head is exist.
 *then we assign the size of the stack array , and -1 to the top(indicates it is empty),also we create the array using
 *dynamic memory allocation.
 *
 *  @param T pointer of type Tree ,it will be the head of the Tree stack.
 *  @return  pointer of type Tree .
 */
Tree CreateTree(int capacity)
{
    Tree T= (Tree)malloc(sizeof(struct treeStack));

    if(T==NULL) //memory out of space
        return NULL;


    T->MaxSize=capacity;
    T->Top=-1;

    T->Array=(Treeptr)malloc( sizeof(struct node)* T->MaxSize);//Dynamic memory allocation for the stack array

    return T;

}
//////////isEmpty//////////
/** @brief This boolean Function checks if stack is empty.
 *
 *it checks if the Top is pointing to -1 , if it points to
 *-1 then it's empty and return 1 ,otherwise it's not and return 0 .

 *  @return int.
 */
int isEmpty(Stack S)
{

    return (S->Top == -1);//no elements in the array
}

//////////isTEmpty//////////
/** @brief This boolean Function checks if tree stack is empty.
 *
 *it checks if the Top is pointing to -1 , if it points to
 *-1 then it's empty and return 1 ,otherwise it's not and return 0 .

 *  @return int.
 */
int isTEmpty(Tree T)
{
    return (T->Top==-1);
}

//////////isFull//////////
/** @brief This boolean Function checks if  stack is full.
 *
 *it checks if the Top is pointing to (MaxSize -1) (because we start from zero) , if it points to
 *it then it's full and return 1 ,otherwise it's not and return 0 .

 *  @return int.
 */
int isFull(Stack S)
{

    return (S->Top == (S->MaxSize -1));

}

//////////isTFull//////////
/** @brief This boolean Function checks if  tree is full.
 *
 *it checks if the Top is pointing to (MaxSize -1) (because we start from zero) , if it points to
 *it then it's full and return 1 ,otherwise it's not and return 0 .

 *  @return int.
 */
int isTFull(Tree T)
{

    return (T->Top == (T->MaxSize -1));
}

//////////disposeStack//////////
/** @brief This Function dispose the created stack.
 *
 *it checks if the stack is exist,then disposes of the created array associated
 *with the specified stack, and then disposes of the remaining stack structure.
 *
 *  @return void.
 */
void disposeStack(Stack S)
{
    if(S != NULL)
    {
        free(S->Array);
        free(S);
    }
}

//////////disposeTree//////////
/** @brief This Function dispose the created tree stack.
 *
 *it checks if the tree stack is exist,then disposes of the created array associated
 *with the specified tree stack, and then disposes of the remaining tree stack structure.
 *
 *  @return void.
 */
void disposeTree(Tree T)
{
    if(T != NULL)
    {
        free(T->Array);
        free(T);
    }
}

//////////push//////////
/** @brief This Function inserts element at top of the stack.
 *
 *it checks if the stack is full or not,then if it is not full it inserts the specified value at the top
 *of the stack
 *
 *  @return void.
 */
void push(Stack S,char value  )
{

    if (isFull(S))
    {
        printf("Error: Stack overflow!\n");
        return;
    }
    S->Top++;
    S->Array[S->Top]= value;

}

//////////pushT//////////
/** @brief This Function inserts element at top of the tree stack.
 *
 *it checks if the tree stack is full or not,then if it is not full it inserts the specified value at the top
 *of the tree stack
 *
 *  @return void.
 */
void pushT (Tree T, Treeptr value)
{

    if(isTFull(T)) //Tree stack is full
        return;

    T->Top++;
    T->Array[T->Top]=value;

}

//////////pop//////////
/** @brief This Function delete the most recently added element from the stack.
 *
 *it checks if the stack is empty or not,then if it is not empty it deletes the top value of the stack
 *
 *  @return void.
 */
void pop(Stack S)
{
    if (isEmpty(S))
    {
        printf("Error: Stack underflow!\n");
        return INT_MIN;
    }

    S->Top--;

}
//////////popT//////////
/** @brief This Function delete the most recently added element from the tree stack.
 *
 *it checks if the tree stack is empty or not,then if it is not empty it deletes the top value of the tree stack
 *
 *  @return void.
 */
void popT (Tree T)
{

    if (isTEmpty(T))
        return INT_MIN;

    T->Top--;

}
//////////pop//////////
/** @brief This Function returns the most recently added element to the stack.
 *
 *it checks if the stack is empty or not,then if it is not empty it returns the top value of the stack
 *
 *  @return char.
 */
char Top (Stack S)
{
    if(isEmpty(S))
    {
        return CHAR_MIN;
    }

    return S->Array[S->Top];

}

//////////TopT//////////
/** @brief This Function returns the most recently added element to the tree stack.
 *
 *it checks if the tree stack is empty or not,then if it is not empty it returns the top value of the tree stack
 *
 *  @return char.
 */
Treeptr TopT (Tree T)
{

    if (isTEmpty(T))
        return CHAR_MIN;

    return T->Array[T->Top];

}

//////////createNode//////////
/** @brief This Function creates a tree node.
 *
 *it creates a node of type Treeptr .We assign value to data,and
 * we assign NULL to its left and right pointers.
 *
 *  @param newNode pointer of type Treeptr.
 *  @return Treeptr.
 */
Treeptr createNode(char value)
{

    Treeptr newNode = (Treeptr)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////isOperator//////////
/** @brief This Boolean Function checks if the specified is an operator or not.
 *
 *if the specified char is an operator the function returns 1,other wise it returns 0.
 *
 *  @return int.
 */
int isOperator(char oper)
{
    if(oper=='+')
        return 1;
    else if(oper=='-')
        return 1;
    else if(oper=='*')
        return 1;
    else if(oper=='/')
        return 1;
    else if(oper=='%')
        return 1;
    else
        return 0;

}

//////////opPriority//////////
/** @brief This Function assign the priority of the specified operator .
 *
 *  @return int
 */
int opPriority(char oper)
{
    if(oper=='+' || oper=='-')
        return 1;
    else if(oper=='/' || oper=='*'|| oper=='%')
        return 2;//higher priority
    else
        return 0;

}

//////////InfixToPostfix//////////
/** @brief This Function converts the equations from infix expression to its postfix equivalent .
 *
 *it takes the stack that will be used to convert the equations , the array of equations, and the
 *index of the specified equation to be converted
 *  @param postfix array of char , used to store the postfix expression of the specified equation
 *  @return void.
 */
void InfixToPostfix(Stack S, char eq[MAX], int pos)
{

    char postfix[MAX]="";
    char insertedChar;


    int length=0,i=0;
    length=equationLength(eq);//get the length of the specified equation

    strcpy(postfixEqs[pos],"");//sets the string at that position to an empty string

    if(eq[i]=='-' || eq[i]=='+')  //if the first char is positive or negative
    {
        insertedChar=eq[i];
        strncat(postfix, &insertedChar, 1);//append a single character
        i++;
    }


    for(i; i<length; i++)
    {


        if(!isOperator(eq[i]) && !isdigit(eq[i])&& eq[i]!='(' && eq[i]!=')')
        {

            i++;
            continue;
        }
        if(eq[i]==' ')
        {

            i++;
            continue;
        }

        if(isdigit(eq[i]))//if the char is number
        {

            while(isdigit(eq[i]))
            {
                insertedChar=eq[i];
                strncat(postfix, &insertedChar, 1);
                i++;
            }
            insertedChar=' ';
            strncat(postfix, &insertedChar, 1);
            i--;

        }
        else if(isOperator(eq[i]))  //if the char is operator
        {


            if(eq[i+1]=='+'||eq[i+1]=='-')
            {
                while(isEmpty(S)==0 && opPriority(eq[i]) <= opPriority(Top(S)))
                {
                    insertedChar=Top(S);
                    strncat(postfix, &insertedChar, 1);
                    pop(S);


                }
                push(S,eq[i]);
                insertedChar=eq[i+1];
                strncat(postfix, &insertedChar, 1);
                i++;



            }

            else
            {

                while(isEmpty(S)==0 && opPriority(eq[i]) <= opPriority(Top(S)))
                {

                    insertedChar=Top(S);
                    strncat(postfix, &insertedChar, 1);
                    pop(S);
                    insertedChar=' ';//spaces between char
                    strncat(postfix, &insertedChar, 1);

                }

                push(S, eq[i]);

            }


        }

        else if(eq[i]=='(')
        {

            if(eq[i+1]=='+'||eq[i+1]=='-')
            {
                push(S,eq[i]);
                insertedChar=eq[i+1];
                strncat(postfix, &insertedChar, 1);
                i++;

            }
            else
            {

                push(S, eq[i]);

            }

        }
        else if(eq[i]==')')
        {


            while(Top(S) != '(')
            {
                insertedChar=Top(S);
                strncat(postfix, &insertedChar, 1);
                pop(S);

            }

            pop(S); //to remove '('


        }

    }

    while(!isEmpty(S))
    {
        insertedChar=Top(S);
        strncat(postfix, &insertedChar, 1);
        pop(S);

    }


    strcpy(postfixEqs[pos], postfix);//copy the content of array postfix to the global array posfixEqs at the specified position


}


//////////readInputFile//////////
/** @brief This Function read the equations line by line that are inside the file and store them in array.
 *
 *it also checks if the file is exist or not.
 *

 *  @param in pointer to input file.
 *  @param fileName[100] String to store file name.
 *  @param eq[Max] string with maximum length 200 , stores the equations from the file
 *  @return void.
 */
void readInputFile()
{

    FILE* in; // pointer to input file
    char fileName[100]; // string to store file name
    printf("\nPlease provide the name of the input file:\t");
    scanf("%s",fileName);
    in= fopen(fileName,"r");

    while(in==NULL)//If the file does not exist
    {

        printf("\nUnable to open the file. The file does not exist.\n\n");
        printf("\nPlease provide the name of the input file:\t");
        scanf("%s",fileName);
        in= fopen(fileName,"r");

    }

    char eq[MAX];//maximum length of equation equal MAX
    int i=0;

    while(fgets(eq,sizeof(eq),in))//Read lines one by one and store each string in array 'Equations'
    {

        deleteSpaces_specialChar(eq);//ignores spaces and special characters

        strcpy(Equations[i],eq);
        i++;
    }


    counter=i; //counts the number of equations that are in the file

    int EqTemp=0, j=0, count=0;


    while(j<counter)//checks the structure of the equations
    {
        count++;
        EqTemp=checkEqStruct(Equations[j],j, count);



        if(EqTemp==0)//valid
        {
            j++;
        }

    }


    EqTemp=0, j=0, count=0;

    while(j<counter)////checks if the equations are valid or not
    {
        count++;
        EqTemp=isEqValid(Equations[j], j, count);



        if(EqTemp==0)//valid
        {
            j++;
        }

    }

    fclose(in);

}
//////////deleteSpaces_specialChar//////////
/** @brief This function removes white spaces and special characters
 *it takes the array that have the equations to be cleaned from them.
 *
 *  @param index integer,act as the index of the array
 *  @param i integer , used in the for loop.
 *  @param i integer ,to use it in the for loop
 *  @return Void.
 */

void deleteSpaces_specialChar(char eq[MAX])
{

    int index = 0;
    int i;


    for(i=0; eq[i]!='\0'; i++)
    {
        if(eq[i] != ' ')//if it is not white space
        {
            if(isOperator(eq[i]) || eq[i]=='(' || eq[i]==')' || isdigit(eq[i]))
                eq[index++] = eq[i];
        }
    }
    eq[index]='\0'; // Terminate the modified string with a null character.


}

//////////printToOutputFile//////////
/** @brief This Function print the postfix expression of equations and their evaluation to the output file.
*
*The function utilized the global array `postfixEqs` to display the postfix expression and the global array `results`,
*which stores the evaluated results of the equations, to print them into the output file.
*
*  @param out pointer to input file.
*  @param i integer , used in the for loop
*  @return Void.
*/
void printToOutputFile()
{
    FILE * out;
    out=fopen("output.txt","w");
    int i=0;


    while(i<counter)
    {
        fprintf(out,"\n");
        fflush(out);


        fprintf(out,"Postfix equation NO.{%d} : %s\n\n", i+1, postfixEqs[i]);//print the postfix expression into the output file

        if(results[i] == INT_MIN)//checks if one of the results is a division by zero to display a message in the output file
        {

            fprintf(out,"Invalid evaluation for equation NO.{%d} : Division by zero error detected!\n\n", i+1);
            fflush(out);
            i++;
            continue;
        }

        fprintf(out,"Evaluation of equation NO.{%d} : %d\n\n", i+1, results[i]);//print the results into the output file
        i++;
        fflush(out);
    }
}
//////////isEqValid//////////
/** @brief This Boolean Function checks if the specified equation is valid or not.
*
*This function takes the equations array and the index of the specified equation to be checked,and the number
*of equation
*
*  @param length integer , used to store the length of the specified equation
*  @param i ,j integer , used in the for loop
*  @param inValid integer,flag to check if the specified equation is invalid or not
*  @param S pointer of type Stack,used in the process of checking the validation of the specified equation
*  @return int.
*/

int isEqValid(char eq[MAX], int index, int count)
{
    int i,j,length=0,inValid=0;

    length= equationLength(eq);

    Stack S=CreateStack(MAX);

    for(i=0; i<length; i++)
    {

        if(eq[i]=='(')//check parentheses
        {

            push(S,eq[i]);

            if(i>0 && eq[i-1]!='('&& isdigit(eq[i-1]))//checks if the equation has a missing operators
            {

                inValid=1;
                printf("\nError: Line %d has an invalid equation. Missing operator: '%c%c%c'.\n\n", count, eq[i-1], eq[i], eq[i+1]);

                for(j=index; j<counter; j++)//remove the invalid equation from the global array 'Equations' that stores the equation from the file
                {
                    strcpy(Equations[j],Equations[j+1]);
                }
                counter--;//modify the number of the equations
                disposeStack(S);
                return index;

            }


            else if (i<length-2 && (eq[i+1]=='%' || eq[i+1]=='*' || eq[i+1]=='/' ))//checks if the equation has a missing operators
            {

                printf("\nError: Line %d has an invalid equation. Missing operand: '%c%c'\n\n", count, eq[i], eq[i+1]);
                inValid=1;
                for(j=index; j<counter; j++)
                {
                    strcpy(Equations[j],Equations[j+1]);
                }
                counter--;
                disposeStack(S);
                return index;

            }

        }

        else if(eq[i]==')')
        {


            if(isEmpty(S))//checks for  unopened parentheses
            {

                printf("\nError: Line %d contains an invalid equation. Unopened '%c'.\n\n", count, eq[i]);
                inValid=1;
                for(j=index; j<counter; j++)
                {
                    strcpy(Equations[j],Equations[j+1]);
                }
                counter--;
                disposeStack(S);
                return index;

            }

            else
            {

                char top=Top(S);
                pop(S);

                if((top=='(' && eq[i]==')')==0)
                {

                    inValid=1;
                    printf("\nError: Line %d contains an invalid equation.Missing opening '%c' or unclosed '%c'.\n\n", count, top, eq[i]);
                    for(j=index; j<counter; j++)
                    {
                        strcpy(Equations[j],Equations[j+1]);
                    }
                    counter--;
                    disposeStack(S);
                    return index;

                }

            }


            if (i>0 && isOperator(eq[i-1]))// checks for  missing operands
            {

                inValid=1;
                printf("\nError: Line %d contains an invalid equation.Missing operand '%c%c'.\n\n", count, eq[i-1], eq[i]);

                for(j=index; j<counter; j++)
                {
                    strcpy(Equations[j],Equations[j+1]);
                }
                counter--;
                disposeStack(S);
                return index;

            }


            else if (i<length-2 && eq[i+1]!=')' && !isOperator(eq[i+1]))//checks for missing operator after a closing parentheses
            {

                inValid=1;
                printf("\nError: Line %d contains an invalid equation.Missing operator '%c%c'.\n\n", count, eq[i], eq[i+1]);
                for(j=index; j<counter; j++)
                {
                    strcpy(Equations[j],Equations[j+1]);
                }
                counter--;
                disposeStack(S);
                return index;

            }

        }



        else if(i==0 && ((eq[i]) == '%' || eq[i]== '*' || eq[i]=='/'))//checks for equations begins with an operator
        {

            printf("\nError: Line %d contains an invalid equation. Equations cannot begin with an operator.\n\n", count);

            inValid=1;
            for(j=index; j<counter; j++)
            {
                strcpy(Equations[j],Equations[j+1]);
            }
            counter--;
            disposeStack(S);
            return index;

        }

        else if(i>0 && i<length-2  && isOperator(eq[i-1]) && isOperator(eq[i]) && isOperator(eq[i+1]))//checks for cascading operators
        {

            inValid=1;
            printf("\nError: Line %d contains an invalid equation.Cascading operators '%c%c%c'.\n\n", count, eq[i-1], eq[i], eq[i+1]);
            for(j=index; j<counter; j++)
            {
                strcpy(Equations[j],Equations[j+1]);
            }
            counter--;
            disposeStack(S);
            return index;

        }


        else if(isOperator(eq[i]) && (eq[i+1]=='%' || eq[i+1]=='*' || eq[i+1]=='/'))//checks for cascading operators
        {

            inValid=1;
            printf("\nError: Line %d contains an invalid equation.Cascading operators '%c%c'.\n\n", count, eq[i], eq[i+1]);
            for(j=index; j<counter; j++)
            {
                strcpy(Equations[j],Equations[j+1]);
            }
            counter--;
            disposeStack(S);
            return index;

        }


        else if(i==length-1 && isOperator(eq[i]))//checks for equations that end with operator and not followed by operand
        {

            inValid=1;
            printf("\nError: Line %d contains an invalid equation.Ends with operator '%c' ,and no operand .\n\n", count, eq[i]);
            for(j=index; j<counter; j++)
            {
                strcpy(Equations[j],Equations[j+1]);
            }
            counter--;
            disposeStack(S);
            return index;

        }

    }// end of the for loop

    if(!isEmpty(S))//checks for unclosed parentheses
    {

        char topChar;
        inValid=1;
        while(!isEmpty(S))
        {

            topChar=Top(S);
            pop(S);

        }

        printf("\nError: Line %d contains an invalid equation.Opening '%c' without a corresponding closing one .\n\n", count, topChar);
        for(j=index; j<counter; j++)
        {
            strcpy(Equations[j],Equations[j+1]);
        }
        counter--;
        disposeStack(S);
        return index;

    }

    disposeStack(S);
    return inValid;
}

//////////checkEqStruct//////////
/** @brief This function checks if the specified equation contains only numbers.
*
*This function takes the equations array and the index of the specified equation to be checked,and the number
*of equation
*
*  @param length integer , used to store the length of the specified equation
*  @param i ,j integer , used in the for loop
*  @param isValid integer,flag to check if the specified equation is valid or not
*  @return int.
*/
int checkEqStruct(char eq[MAX], int index, int count)
{

    int length=0, i,j, isValid=0;

    length=equationLength(eq);



    for(i=0; i<length; i++)
    {
        if(eq[i]=='(' || eq[i]==')' || isOperator(eq[i]))
        {
            isValid=1;//valid
            break;


        }
    }
    if(isValid==0)//invalid
    {

        printf("\nError: Line %d contains an invalid equation.Equation must include specified operators.\n\n", count);

        for(j=index; j<counter; j++)
        {
            strcpy(Equations[j],Equations[j+1]);

        }

        counter--;
        return index;
    }

    return 0;


}

//////////TreeCreation//////////
/** @brief This function constructs the expression tree from a postfix expression of the equation.
*
*This function takes array that stores the postfix expression and the index of the specified equation to be created.
*
*  @param tree pointer of type Tree,points at created tree stack
*  @param i  integer , used in the for loop
*  @param result ,opNode,p pointer of type Treeptr
*  @return pointer of type Treeptr
*/

Treeptr TreeCreation(char postfixEq[MAX], int index)
{

    Tree tree=CreateTree(MAX);
    Treeptr result;
    int i;
    Treeptr opNode;
    Treeptr p;

    for (i=0; postfixEq[i]!='\0'; i++)
    {


        if(postfixEq[i]=='+' && isdigit(postfixEq[i+1]))
        {

            opNode = createNode(postfixEq[i+1]);
            opNode->sign='+';//positive number
            pushT(tree, opNode);
            i++;

        }

        else if(postfixEq[i]=='-' && isdigit(postfixEq[i+1]))
        {

            opNode = createNode(postfixEq[i+1]);
            opNode->sign='-';//negative number
            pushT(tree, opNode);
            i++;

        }

        else if(postfixEq[i]==' ')
        {

            continue;

        }
        else if(isdigit(postfixEq[i]))
        {

            if(i==0)
            {

                opNode = createNode(postfixEq[i]);
                pushT(tree, opNode);


            }


            else if(isdigit(postfixEq[i-1]) && !isdigit(postfixEq[i+1]))
            {

                opNode = createNode(postfixEq[i]);
                p =tree->Array[tree->Top];

                while(p->right!=NULL)
                {
                    p=p->right;//add to the right side of the tree node
                }
                p->right=opNode;

            }

            else if(isdigit(postfixEq[i-1]) && isdigit(postfixEq[i+1]))//if the number is more than one digit
            {

                opNode = createNode(postfixEq[i]);

                p=tree->Array[tree->Top];

                while(p->right!=NULL)
                {
                    p=p->right;//add to the right side of the tree node
                }
                p->right=opNode;
            }

            else if(!isdigit(postfixEq[i-1]) && !isdigit(postfixEq[i+1]))
            {

                opNode = createNode(postfixEq[i]);
                pushT(tree, opNode);

            }

            else if(!isdigit(postfixEq[i-1]) && isdigit(postfixEq[i+1]))
            {

                opNode = createNode(postfixEq[i]);
                pushT(tree, opNode);

            }

        }
        else   //if it is operator
        {

            opNode = createNode(postfixEq[i]);
            opNode->right = TopT(tree);
            popT(tree);
            opNode->left = TopT(tree);
            popT(tree);
            pushT(tree, opNode);


        }
    }

    result = TopT(tree);

    popT(tree);
    disposeTree(tree);
    return result; //contains the expression tree
}


//////////EvaluateTreeExpression//////////
/** @brief This function evaluates the postfix expression of equation.
*
*This function takes the root of the tree nodes. Also this function act as a recursion function.
*
*  @param p pointer of type Tree,points at created tree stack
*  @param Eqresult,count integer

*  @return int
*/
int EvaluateTreeExpression(Treeptr root)
{
    if(root)
    {

        if(isdigit(root->data))
        {
            int Eqresult=0, count=0;
            Treeptr p=root;
            count=countRight(root);

            if(count!=0)
            {
                while(p!=NULL)
                {

                    Eqresult += (p->data - '0') * pow(10,count--);//for multi-digit numbers
                    p=p->right;
                }

                return Eqresult;

            }
            else

                return root->data - '0';  // Convert char to int

        }
        else   //operator
        {
            int rightOp, leftOp;

            rightOp = EvaluateTreeExpression(root->right);

            if(root->right->sign=='-')//negative numbers
            {

                rightOp=rightOp * -1;
            }

            leftOp= EvaluateTreeExpression(root->left);

            if(root->left->sign=='-')
            {

                leftOp=leftOp * -1;
            }

            if(rightOp == INT_MIN || leftOp == INT_MIN)  //non valid operation (division by zero)
            {
                return INT_MIN;
            }

            switch (root->data) //operation
            {

            case '+':
                return  rightOp + leftOp;
            case '-':
                return leftOp - rightOp;

            case '%':
            {
                if(rightOp==0)//division by zero
                {

                    return INT_MIN;
                }

                return leftOp % rightOp;
            }
            case '*':
                return  rightOp * leftOp;

            case '/':
            {
                if(rightOp==0)//division by zero
                {

                    return INT_MIN;
                }
                return leftOp / rightOp;
            }

            default://any other characters

                break;
            }
        }
    }

    return 0; // Default return value
}

//////////countRight//////////
/** @brief This Function for counting the occurrences of multi-digit numbers.
*
*This function takes a root from the tree stack
*  @param p pointer of type Tree,points at created tree stack
*  @param count integer, counts the number of digits

*  @return int
*/
int countRight(Treeptr root)
{
    Treeptr p =root;
    int count=0;
    while(p->right!=NULL)
    {
        count++;
        p=p->right;
    }
    return count;
}

//////////equationLength//////////
/** @brief This Function compute the length of the specified equation
*
*This function takes a array of char (one string)

*  @param count integer, counts the number of digits
*  @param i integer, used in the while loop
*  @return int
*/
int equationLength (char eq[MAX])
{
    int i=0, count=0;
    while(isOperator(eq[i]) || eq[i]=='(' || eq[i]==')' || isdigit(eq[i]))
    {
        count++;
        i++;
    }
    return count;
}
