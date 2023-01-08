#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tree
{
    char num[10];
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree *parseEquation(char *equation);

//function to preorder the expresion
void preOrder(Tree *root);
//function to postorder the expersion
void postOrder(Tree *root);

void inOrder(Tree *root);

int main(int argc, char **argv)
{

    int code;
    char input[100];        // VARAIABLE USED TO STORE USER INPUT FROM CONSOLE
    strcpy(input, argv[1]); // COPY THE CONTENTS FROM THE CONSOLE TO THE CHAR VARIALBE
    Tree *root;
    root = parseEquation(input);

    do
    {
        printf("\n----------------------------------------------------------------------\n");
        printf("Please select from the following options:\n");
        printf("1: Preorder\n");
        printf("2: Postorder\n");
        printf("3: Inorder\n");
        printf("4: Exit\n");
        printf("----------------------------------------------------------------------\n");

        printf("> ");
        scanf("%d", &code);

        switch (code)
        {
        case 1:
        {
            printf("\n");
            preOrder(root);
            printf("\n");
            break;
        }

        case 2:
        {
            printf("\n");
            postOrder(root);
            printf("\n");
            break;
        }

        case 3:
        {
            printf("\n");
            inOrder(root);
            printf("\n");
            break;
        }

        case 4:
        {
            break;
        }
        }

    } while (code != 4);

    return (0);
}

// .      ((2.00*(x1-1.00))+(x2/3.00))

// FUNCTION TO PARSE THE GIVEN EQUATION INTO A TREE
Tree *parseEquation(char *equation)
{

    Tree *node;
    node = (Tree *)malloc(sizeof(Tree)); // ALLOCATING SIZE FOR THE NODE
    int numBrackets = 0;
    int position = 0;
    int root = 0;
    int length = strlen(equation); // GETTING THE LENGTH OF THE EQUATION AND STORE IT INTO VARIABLE CALLED LENGTH

    for (int i = 0; i < length; i++)
    {
        // IF AN OPEN BRACKET IS FOUND '(' THEN ADD ONE TO numBrackets
        if (equation[i] == '(')
        {
            numBrackets += 1;
        }
        // IF A CLOSE BRACKET IS FOUND ')' THEN SUBTRACT ONE FROM numBrackets
        if (equation[i] == ')')
        {
            numBrackets -= 1;
        }
        // IF THE NUMBER OF BRACKETS IS 1 AND THERES IS NO ROOT THEN STORE ITS APPROPRIATE OPERATOR IN THE ROOT
        if (numBrackets == 1 && root == 0 && (equation[i] == '*' || equation[i] == '/' || equation[i] == '-' || equation[i] == '+'))
        {

            sprintf(node->num, "%c", equation[i]);
            root = 1;     // SET THE ROOT TO 1
            position = i; // FETCHING THE CURRENT num OF i AND STORING IT INTO POSITION SO WE CAN COMPLETE THE TREE
        }
    }

    char bContent[100] = "";
    // STORE ALL THE CONTENTS BEFORE THE ROOT INTO VARIABLE bContent
    for (int i = 1; i < position; i++)
    {
        char temp[100] = "";
        sprintf(temp, "%c", equation[i]); // CONVERTING A CHAR INTO A STRING
        strcat(bContent, temp);           // COMBINES THE CONTENTS FROM TEMP WITH bCONTENT
    }
    char aContent[100] = "";
    // STORE ALL THE CONTENTS AFTER THE ROOT INTO VARIABLE aContent
    for (int i = position + 1; i < length - 1; i++)
    {
        char temp[10] = "";
        sprintf(temp, "%c", equation[i]); // CONVERTING A CHAR INTO A STRING
        strcat(aContent, temp);           // COMBINES THE CONTENTS FROM TEMP WITH bCONTENT
    }
    // IF ROOT IS FOUND THEN CALL ITS CHILDREN BY USING RECURSION
    if (root == 1)
    {
        node->left = parseEquation(bContent);
        node->right = parseEquation(aContent);
    }
    // IF THERE IS NO ROOT AND IF THE ORGINAL EQUATION IS NOT EQUAL TO THOSE BEFORE AND AFTER THE OPERAND THEN ADD LEAF NODE numS
    else if (root == 0 && strcmp(equation, bContent) != 0 && strcmp(equation, aContent) != 0)
    {
        sprintf(node->num, "%s", equation); // CONVERTING A CHAR INTO A STRING
        node->left = NULL;
        node->right = NULL;
    }
    else
    {
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

// FUNCTION PRINTS EQUATION IN PREORDER FORM
void preOrder(Tree *root)
{
    if (root == NULL)
    {
        return;
    }
    if (!(strcmp(root->num, "") == 0))
    {
        printf(" %s", root->num);
        if (strcmp(root->num, "x1") == 0 ||
            strcmp(root->num, "x2") == 0 ||
            strcmp(root->num, "x3") == 0 ||
            strcmp(root->num, "x4") == 0 ||
            strcmp(root->num, "x5") == 0 ||
            strcmp(root->num, "x6") == 0 ||
            strcmp(root->num, "x7") == 0 ||
            strcmp(root->num, "x8") == 0 ||
            strcmp(root->num, "x9") == 0)
        {
            printf("[0.00]");
        }
    }

    preOrder(root->left);
    preOrder(root->right);
}

// FUNCTION PRINTS EQUATION IN POST ORDER FORM
void postOrder(Tree *root)
{
    if (root == NULL)
    {
        return;
    }

    postOrder(root->left);
    postOrder(root->right);

    if (!(strcmp(root->num, "") == 0))
    {
        printf(" %s", root->num);
        if (strcmp(root->num, "x1") == 0 ||
            strcmp(root->num, "x2") == 0 ||
            strcmp(root->num, "x3") == 0 ||
            strcmp(root->num, "x4") == 0 ||
            strcmp(root->num, "x5") == 0 ||
            strcmp(root->num, "x6") == 0 ||
            strcmp(root->num, "x7") == 0 ||
            strcmp(root->num, "x8") == 0 ||
            strcmp(root->num, "x9") == 0)
        {
            printf("[0.00]");
        }
    }
}

// FUNCTION PRINTS EQUATION INORDER FROM
void inOrder(Tree *root){

   
    if(root ==NULL )
    {
        return;
    }

    if(root->left != NULL && root->right !=NULL)
    printf(" (");
    inOrder(root->left);

    if(strcmp(root->num,"") != 0){
        printf(" %s",root->num);
        if (strcmp(root->num, "x1") == 0 ||
            strcmp(root->num, "x2") == 0 ||
            strcmp(root->num, "x3") == 0 ||
            strcmp(root->num, "x4") == 0 ||
            strcmp(root->num, "x5") == 0 ||
            strcmp(root->num, "x6") == 0 ||
            strcmp(root->num, "x7") == 0 ||
            strcmp(root->num, "x8") == 0 ||
            strcmp(root->num, "x9") == 0)
        {
            printf("[0.00]");
        }
    }

    inOrder(root->right);
    //IF IT WAS LEAF THEN DO NOT PRINT "("
    if(root->left != NULL && root->right !=NULL){
        printf(" )");
    }



}