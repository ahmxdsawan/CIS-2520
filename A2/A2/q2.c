/*---------------------------------------------
NAME: AHMAD SAWAN
STUDENT ID: 1205875
DATE: 22/10/2022
Reverse Polish notation (RPN): Łukasiewicz notation
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//REVERSE POLISH NOTATION LINKED LIST
typedef struct rpn
{
	float data; //STORING THE OPERANDS
	struct rpn *next;//DYANMIC ALLOCATION
} rpn;

//FUNCTION TO PUSH NUMBERS TO THE TOP OF THE STACK
void push(struct rpn **top, float data);

//FUNCTION TO POP NUMBERS FROM THE TOP OF THE STACK
float pop(struct rpn **top);

//FUNCTION TO PREFORM THE OPERATION (+,-,/,*)
void doOperation(struct rpn **stack, char oper);

//MAIN
int main(int argc, char **argv)
{
	struct rpn *stack = (struct rpn *)malloc(sizeof(struct rpn)); //GIVING STACK ITS APROPRIATE SIZE
	char input[100]; //VARAIABLE USED TO STORE USER INPUT FROM CONSOLE
	strcpy(input, argv[1]); //COPY THE CONTENTS FROM THE CONSOLE TO THE CHAR VARIALBE

	int length = strlen(input); //GETTING THE LENGTH OF THE INPUT

  //FOR LOOP THAT GOES THROUGH THE INPUT AND IF THERE IS A NUMBER BETWEEN 0-9, PUSH IT INTO THE STACK
  //AND IF THERE ARE ANY OPERANDS (+,-,/,*) CALL THE "DOOPERATION" FUNCTION
	for (int i = 0; i < length; i++)
	{
		if (input[i] >= 48 && input[i] <= 57)
		{
			float num = input[i] - 48; //CONVERTING ASCCI NUMBER INTO ITS ACUTAL DECIMAL NUMBER
			push(&stack, num); //PUSH NUM TO THE STACK
		}
		else if (input[i] == 43 || input[i] == 42 || input[i] == 45 || input[i] == 47)
		{
			doOperation(&stack, input[i]); //CALLING THE PREFORM OPERATION FUNCTION
		}
		else
		{
			printf("\nINVALID INPUT, PLEASE RE-RUN THE PROGRAM!\n");
			exit(1);
		}
	}

	printf("RPN RESULT = %.2f\n", stack->data); //PRINTING THE RESULT TO THE USER AND EXITING THE PROGRAM

	return 0;
}

//A FUNCTION TO CREATE A NEW NODE TO UPDATE THE VALUES IN THE STACK
struct rpn *newNode(float data)
{
	struct rpn *stack = (struct rpn *)malloc(sizeof(struct rpn));
	stack->data = data;
	stack->next = NULL;
	return stack;
}

//FUNCTION TO PUSH A GIVEN FLOAT TYPE INTO THE "TOP" OF THE STACK
void push(struct rpn **top, float data)
{
	struct rpn *stack = newNode(data); //ADDING A NEW NODE IN THE STACK
	stack->next = *top; //LET THE NEXT NODE EQUAL THE TOP OF THE STACK
	*top = stack; //LET THE TOP EQUAL THE STACK
}

//FUNCTION TO POP, REMOVE, THE TOP NUMBER IN THE STACK
float pop(struct rpn **top)
{
	struct rpn *temp = *top; //LET A TEMP NODE EQUAL THE TOP NUMBER IN THE LUST
	*top = (*top)->next; //UPDATE THE POINTED STACK DIRECTLY TO EQUAL THE NEXT ONE IN THE LIST
	float popped = temp->data; //RETRIVE THE POPPED NUMBER INTO A VARIABLE TO STORE IT
	free(temp); //FREE TEMP NODE'S MEMORY
	return popped; // RETURN THE POPPED VARIABLE
}

//FUNCTION THAT PREFORMS OPERATIONS (+,-,/,*)
void doOperation(struct rpn **stack, char oper)
{
	float lNum; //ASSIGNING THE LEFT MOST VARIABLE
	float rNum; //ASSIGNING THE RIGHT MOST VARIABLE

  //SWITCH CASE: -
	switch (oper)
	{
  //IF THE OPERAND IS A '+' THEN POP THE FIRST TWO NUMBERS AND ADD THEM AND RETURN THE NUM THEN BREAK
	case '+':
	{
		rNum = pop(stack);
		lNum = pop(stack);
		push(stack, lNum + rNum);
		break;
	}
  ///IF THE OPERAND IS A '-' THEN POP THE FIRST TWO NUMBERS AND SUBTRACT THEM AND RETURN THE NUM THEN BREAK
	case '-':
	{
		rNum = pop(stack);
		lNum = pop(stack);
		push(stack, lNum - rNum);
		break;
	}
  ///IF THE OPERAND IS A '*' THEN POP THE FIRST TWO NUMBERS AND MULTIPLY THEM AND RETURN THE NUM THEN BREAK
	case '*':
	{
		rNum = pop(stack);
		lNum = pop(stack);
		push(stack, lNum * rNum);
		break;
	}
  ///IF THE OPERAND IS A '/' THEN POP THE FIRST TWO NUMBERS AND DIVIDE THEM AND RETURN THE NUM THEN BREAK
	case '/':
	{
		rNum = pop(stack);
		lNum = pop(stack);
		push(stack, lNum / rNum);
		break;
	}
	}
}