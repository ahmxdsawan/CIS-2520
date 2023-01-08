/*---------------------------------------------
NAME: AHMAD SAWAN
STUDENT ID: 1205875
DATE: 22/10/2022
Stacks
---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//LINKED LIST FOR THE AVAILABLE FOR RENT CARS NAMED avRent
typedef struct avRent
{
	int mileage; //VARIABLE FOR STORING THE MILEAGES
	char plateNumber[8]; //VARIABLE FOR STORING THE PLATE NUMBERS
	struct avRent *next; //DYNAMIC ALLOCATION TO THE NEXT LIST
	struct avRent *previous; //DYNAMIC ALLOCATION TO THE PREVIOUS LIST

} avRent;

//LINKED LIST FOR THE RENTED CARS NAMED rented
typedef struct rented
{
	int mileage; //VARIABLE FOR STORING THE MILEAGES
	char plateNumber[8]; //VARIABLE FOR STORING THE PLATE NUMBERS
	int returnDate; //VARIABLE FOR STORING THE RETURN DATES
	struct rented *next; //DYNAMIC ALLOCATION TO THE NEXT LIST
	struct rented *previous; //DYNAMIC ALLOCATION TO THE PREVIOUS LIST

} rented;

typedef struct repair
{
	int mileage; //VARIABLE FOR STORING THE MILEAGES
	char plateNumber[8]; //VARIABLE FOR STORING THE PLATE NUMBERS
	struct repair *next; //DYNAMIC ALLOCATION TO THE NEXT LIST
	struct rented *previous; //DYNAMIC ALLOCATION TO THE PREVIOUS LIST

} repair;

//FUNCTION PROTOTYPE TO ADD A CARE NODE TO IT'S CORRESPONDING LINKED LIST
void addCarNode(avRent **carList, avRent *node);

//FUNCTION PROTOTYPE TO ADD A RENTED CAR NODE
void addRentedNode(rented **rentList, rented *node);

//FUNCTION PROTOTYPE TO ADD A CAR IN REPAIR NODE
void addRepairNode(repair **repairList, repair *node);

//FUNCTION PROTOTYPE TO ADD A NEW CAR TO THE AVAILABLE FOR RENT LINKED LIST
avRent *addNewCar(avRent *carList);

//FUNCTION PROTOTYPE TO ADD A RETURNED CAR TO THE AVAILABLE FOR RENT LIST
void tran1(avRent **carList, rented **rentList);

//FUNCTION PROTOTYPE TO ADD A RETURNED CAR TO THE REPAUR LIST
void tran2(repair **repairList, rented **rentList);

//FUNCTION PROTOTYPE TO TRANSFER A CAR FROM REPAIUR LIST TO THE AVAILABLE FOR RENT LIST
void tran3(avRent **carList, repair **repairList);

//FUNCTION PROTOTYPE TO RENT THE FIRST AVAILABLE CAR
void tran4(avRent **carList, rented **rentList);

//FUNCTION PROTOTYPE TO REMOVE A CAR FROM THE CAR LIST
void removeCar(avRent **carList);

//FUNCTION PROTOTYPE TO DISPLAY THE 3 LISTS TO THE USER
void displayLists(avRent *carList, rented *rentList, repair *rapirList);

//FUNCTION PROTOTYPE TO LOAD INFORMATION FROM THE TEXT FILES INTO THE LISTS
void loadFromFile(avRent **carList, rented **rentList, repair **repairList);

//FUNCTION PROTOTYPE TO SAVE THE UPDATED LISTS TO THE EXISITING TEXT FILES
void saveToFiles(avRent *carList, rented *rentList, repair *repairList);

//FUNCTION PROTOTYPE TO SEARCH IS A PLATE EXISTS IN THE RENT LIST
bool search(struct rented *rentList, char *plateNumber);

//FUNCTION PROTOTYPE TO SEARCH IS A PLATE EXISTS IN THE RENT LIST
bool search2(struct repair *repairList, char *plateNumber);

//FUNCTION PROTOTPYE TO SORT THE CARS IN THE AVAILABLE FOR RENT CAR LISTS
void sortAVRentList(avRent **carList);

//FUNCTION PROTOTYPE TO SORT THE CARS TO THE RENTED CARS LIST
void sortRentedtList(rented **rentList);

int main()
{
	avRent **carList; //DEFINING A CARLIST NODE OF TYPE AVRENT
	avRent *carNode; //DEFIND A CARNODE OF TYPE AVRENT
	carList = NULL;
	carList = (avRent **)malloc(sizeof(avRent *)); //GIVING THE CARLIST ITS APPROPRIATE SIZE

	rented **rentList;
	rentList = NULL;
	rentList = (rented **)malloc(sizeof(rented *)); //GIVING THE RENTLIST ITS APPROPRIATE SIZE

	repair **repairList;
	repairList = NULL;
	repairList = (repair **)malloc(sizeof(repair *)); //GIVING REPAIR LIST ITS APPROPRIATE SIZE

	int code; //VARIABLE FOR STORING THE USER OPTION
	loadFromFile(carList, rentList, repairList); //CALLING THE FUNCTION TO LOAD DATA FROM TEXT FILES INTO THE LINKED LIST

	//DO WHILE LOOP THE RUNS THROUGH THE PROGRAM UNTIL 7 IS ENTERED
	do
	{
		printf("\n----------------------------------------------------------------------\n");
		printf("1: Add a new car to the available-for-rent list\n");
		printf("2: Add a returned car to the available-for-rent list\n");
		printf("3: Add a returned car to the repair list\n");
		printf("4: Transfer a car from the repair list to the available-for rent list\n");
		printf("5: Rent the first available car\n");
		printf("6: Print all the lists\n");
		printf("7. Quit\n");
		printf("----------------------------------------------------------------------\n\n");

		printf("Please choose a menu option: ");
		scanf("%d", &code);

		switch (code)
		{
		case 1:
		{
			carNode = addNewCar(*carList);
			addCarNode(carList, carNode);
			break;
		}

		case 2:
		{
			tran1(carList, rentList);
			break;
		}

		case 3:
		{
			tran2(repairList, rentList);
			break;
		}

		case 4:
		{
			tran3(carList, repairList);
			break;
		}

		case 5:
		{
			tran4(carList, rentList);
			break;
		}

		case 6:
		{
			sortAVRentList(carList);
			sortRentedtList(rentList);
			displayLists(*carList, *rentList, *repairList);
			break;
		}

		case 7:
		{
			saveToFiles(*carList, *rentList, *repairList);
			break;
		}
		}

	} while (code != 7);

	return (0);
}

//FUNCTION THE ADDS A NEW NODE TO THE AVAILABLE FOR RENT LINKED LIST
void addCarNode(avRent **carList, avRent *node)
{
	avRent *temp; //TEMP STRUCT
	temp = *carList; //GIVING THAT TEMP STRUCT THE CAR LIST

	//IF THERE ARE NO CARS IN THE CAR LUST THIS LET CAR LIST EQUAL THE NODE
	if (*carList == NULL)
	{
		*carList = node;
	}
	//ELSE WHILE THE NEXT NODE IS NOT NULL THEN LET TEMP NODE EQUAL THE NEXT NODE AND GO TO THE NEXT NODE
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = node;
	}
}

//FUNCTION THAT ADDS A RENTED NODE TO THE RENTED LINKED LIST (SAME EXPLANATION AS ADDCARNODE FUNCTION)
void addRentedNode(rented **rentList, rented *node)
{

	rented *temp;
	temp = *rentList;

	if (*rentList == NULL)
	{
		*rentList = node;
	}
	else
	{

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = node;
	}
}

//FUNCTION THAT ADDS A RENTED NODE TO THE RENTED LINKED LIST (SAME EXPLANATION AS ADDCARNODE FUNCTION)
void addRepairNode(repair **repairList, repair *node)
{

	repair *temp;
	temp = *repairList;

	if (*repairList == NULL)
	{
		*repairList = node;
	}
	else
	{

		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		temp->next = node;
	}
}

//FUNCTION THAT ADD A NEW CAR TO THE AVAILABLE FOR RENT LIST
avRent *addNewCar(avRent *carList)
{

	avRent *ptr = (avRent *)malloc(sizeof(avRent));; //CREATE A PTR WITH TYPE AVRENT THAT MALLOCS SIZE OF AVRENT
	

	char tempPlate[10]; //VARIABLE THAT STORES THE TEMP PLATE
	char tempMileage[10] = ""; //VARIABLE THAT STORES THE TEMP MILAGE

	printf("Please enter a plate number (7-Charecters Long): "); //PROMTS THE USER TO INPUT A PLATE NUMBER
	scanf("%s", tempPlate);// STORES IT IN THE TEMPPLATE


  int plateLength = strlen(tempPlate);


	//WHILE THE LENGTH OF THE PLATE DOES NOT EQUAL 7 THEN HAVE THE USER INPUT A VALID ONE
	while (plateLength != 7)
	{
		printf("\nInvalid Plate Length!\n");
		printf("Please enter a plate number (7-Charecters Long): ");
		scanf("%s", tempPlate);
	}

	printf("Please enter a mileage: "); //PROMTS THE USER TO ENTER A MILEAGE
	scanf("%s", tempMileage); //STORING THAT MILEAGE IN A TEMPMILAGE VARIABLE

	ptr->mileage = atoi(tempMileage); //TRANSFER THE TEMPMILEAGE INTO THE MILEAGE NODE USING ATOI TO CONVERT STRING INTO A INT

	strcpy(ptr->plateNumber, tempPlate); //COPY THE CONRENTS FROM TEMPPLATE INTO THE NODES PLATE NUMBER

	printf("\nYou have succesfully added plate number:- %s with a mileage of:- %d\n", ptr->plateNumber, ptr->mileage);
	return ptr; //RETURN PTR SO IT CAN BE ADDED TO THE LIST

}

//FUNCTION THAT DISPLATS ALL 3 LISTS TO THE USER
void displayLists(avRent *carList, rented *rentList, repair *repairList)
{

	printf("\nAvailable For Rent Cars:-\n\n");
	avRent *av = carList;
	rented *rented = rentList;
	repair *repair = repairList;

	while (av != NULL)
	{
		printf("%s | %d\n", av->plateNumber, av->mileage);
		av = av->next;
	}

	printf("\nRented Cars:-\n\n");

	while (rented != NULL)
	{
		printf("%s | %d | %d\n", rented->plateNumber, rented->mileage, rented->returnDate);
		rented = rented->next;
	}

	printf("\nCars In Repair:-\n\n");

	while (repair != NULL)
	{
		printf("%s | %d\n", repair->plateNumber, repair->mileage);
		repair = repair->next;
	}
}

//FUNCTION THE LOADS THE CONTENTS FROM THE TEXT FILES AND STORES THEM IN THEIR CORESPONDING LINKED LISTS
void loadFromFile(avRent **carList, rented **rentList, repair **repairList)
{

	FILE *file1 = fopen("availableForRentYY.txt", "r");
	FILE *file2 = fopen("rentedYY.txt", "r");
	FILE *file3 = fopen("inRepairYY.txt", "r");

	char tempPlate[10];
	int tempMileage;
	int rDate;

	// IF THE FILE COULD NOT BE OPENED TELL THE USER
	if (file1 == NULL)
	{
		printf("availableForRentYY file could not be opened!\n");
		exit(0);
	}

	//WHILE LOOP THAT SCANS THE CONTENTS FROM THE FILES AND UPDATED THE EMPTY LINKED LISTS
	while (fscanf(file1, "%s %d", tempPlate, &tempMileage) != EOF)
	{

		avRent *tempNode = (avRent *)malloc(sizeof(avRent));

		strcpy(tempNode->plateNumber, tempPlate);
		tempNode->mileage = tempMileage;
		tempNode->next = NULL;

		addCarNode(carList, tempNode);
	}

	// IF THE FILE COULD NOT BE OPENED TELL THE USER
	if (file2 == NULL)
	{
		printf("rentedYY file could not be opened!\n");
		exit(0);
	}

	//WHILE LOOP THAT SCANS THE CONTENTS FROM THE FILES AND UPDATED THE EMPTY LINKED LISTS
	while (fscanf(file2, "%s %d %d", tempPlate, &tempMileage, &rDate) != EOF)
	{

		rented *tempNode = (rented *)malloc(sizeof(rented));

		strcpy(tempNode->plateNumber, tempPlate);
		tempNode->mileage = tempMileage;
		tempNode->returnDate = rDate;
		tempNode->next = NULL;

		addRentedNode(rentList, tempNode);
	}

	// IF THE FILE COULD NOT BE OPENED TELL THE USER
	if (file3 == NULL)
	{
		printf("InRepairYY file could not be opened!\n");
		exit(0);
	}

	//WHILE LOOP THAT SCANS THE CONTENTS FROM THE FILES AND UPDATED THE EMPTY LINKED LISTS
	while (fscanf(file3, "%s %d", tempPlate, &tempMileage) != EOF)
	{

		repair *tempNode = (repair *)malloc(sizeof(repair));

		strcpy(tempNode->plateNumber, tempPlate);
		tempNode->mileage = tempMileage;
		tempNode->next = NULL;

		addRepairNode(repairList, tempNode);
	}

	//CLOSE ALL 3 FILES
	fclose(file1);
	fclose(file2);
	fclose(file3);

}

//FUNCTION THAT SAVES THE UPDATES LINKED LISTS INTO THEIR CORESPONDING FILES
void saveToFiles(avRent *carList, rented *rentList, repair *repairList)
{

	FILE *file1 = fopen("availableForRentYY.txt", "w");
	FILE *file2 = fopen("rentedYY.txt", "w");
	FILE *file3 = fopen("inRepairYY.txt", "w");

	avRent *arent = carList;
	repair *repair = repairList;
	rented *rented = rentList;

	//WHILE THE LINKED LIST IS NOT EMPTY PRINT THE CONTENTS FROM THE LINKED LISTS INTO THE FILE
	while (arent != NULL)
	{
		fprintf(file1, "%s\n%d", arent->plateNumber, arent->mileage);
		if (arent->next != NULL)
		{
			fprintf(file1, "\n\n");
		}
		arent = arent->next;
	}

	//WHILE THE LINKED LIST IS NOT EMPTY PRINT THE CONTENTS FROM THE LINKED LISTS INTO THE FILE
	while (rented != NULL)
	{
		fprintf(file2, "%s\n%d\n%d", rented->plateNumber, rented->mileage, rented->returnDate);
		if (rented->next != NULL)
		{
			fprintf(file2, "\n\n");
		}
		rented = rented->next;
	}

	//WHILE THE LINKED LIST IS NOT EMPTY PRINT THE CONTENTS FROM THE LINKED LISTS INTO THE FILE
	while (repair != NULL)
	{
		fprintf(file3, "%s\n%d", repair->plateNumber, repair->mileage);
		if (repair->next != NULL)
		{
			fprintf(file3, "\n\n");
		}
		repair = repair->next;
	}

	//CLOSE ALL 3 FILES
	fclose(file1);
	fclose(file2);
	fclose(file3);

}


// TRANSFER A CAR FROM THE RENTED LL TO THE CARS THAT ARE AVAILABLE FOR RENT LL
void tran1(avRent **carList, rented **rentList)
{

	char *tempPlate = malloc(sizeof(char) * 10); //MALLOCING SIZE TO THE TEMPPLATE OF SIZE 10
	int updatedMileage; //VARIABLE TO STORE THE UPDATEDMILAGE
	bool result = false; //BOOL VARIABLE TO STORE TRUE OR FALSE
	int count = 1;

	rented *previous = NULL; //A NODE CALLED PREVIOUS OF TYPE RENTED
	rented *rented = *rentList; //A NODE CALLED RENTED THAT POINTS TO THE RENTED CAR LIST

	avRent *carNode = (avRent *)malloc(sizeof(avRent)); //MALLOCING MEMORY TO CARNODE OF SIZE AVRENT

	printf("Enter a plate number you wish to return: "); //PROMTS THE USER TO ENTER A PLATE 
	scanf("%s", tempPlate); //STORE THAT PLATE INTO VARIABLE TEMPPLATE
	fflush(stdin); //FLUSH STANDARD INPUT TO CLEAR THE LAST INPUT CHAR FROM THE BUFFER

	//WHILE LOOP THAT CHECK IF THE PLATE ISNT 7 CHARECTERS LONG AND WILL LET THE USER INPUT THE PROPER PLATE
	while (strlen(tempPlate) != 7)
	{
		printf("\nInvalid Plate Length!\n");
		printf("Enter a plate number you wish to return: ");
		scanf("%s", tempPlate);
	}
	
	//WHILE LOOP THAT DOES THE UPDATES TO THE LINKED LIST TO REMOVE THE PLATE THEY ENTERS
	while (rented != NULL && result != true)
	{
		result = search(rented, tempPlate); //RESULT EQUALS TRUE OR FALSE DEPENDING IF THE PLATE WAS FOUND IN THE LIST
		//IF CONDITION THAT CHECK IF THE COUNT IS ONE AND THE RESULT IS TRUE THEN IT DELETES THE FIRST NODE
		if (count == 1 && result == true)
		{
			*rentList = (*rentList)->next;
			free(previous);
		}
		//ANOTHER IF CONDITION TO CHECK IF THE NEXT NODE EQUALS NOTHIN AND IF THERE IS NO EXISTING PLATE
		else if (rented->next == NULL && result == true)
		{
			previous->next = NULL;
			free(rented);
			rented = NULL;
		}
		//ELSE
		else
		{
			//IF THE PLEATE DOES NOT EXISTS THEN LET THE PREVIOUS NODE EQUAL THE NEXT NODE AND FREE THE CONTENTS OF THE NULL
			if (result == true)
			{
				previous->next = rented->next;
				free(rented);
				rented = NULL;
			}
			//ELSE LET PREVIOUS EQUAL RENTED AND LET RENTED NODE EQUAL THE NEXT NODE
			else
			{
				previous = rented;
				rented = rented->next;
			}
		}

		//INCREMENT COUNT TO KEEP TRACK OF THE LISTS CONTENTS
		count++;
	}

	//IF THE PLATE DOES NOT EXISTS THE PROMPT THE USER THAT IT DOESNT EXIST
	if (result != true)
	{
		printf("Plate number does not exist\n");
		exit(0);
	}

	printf("Please enter the updated mileage: "); //PROMTS THE USER TO ENTER AN UPDATED MILEAGE
	scanf("%d", &updatedMileage); //STORES THE MILAGE INTO THE UPDATED MILAGE VARIABLE

	strcpy(carNode->plateNumber, tempPlate); //COPY THE CONTENTS FROM TEMPPLATE INTO THE NODE'S PLATENUMBER
	carNode->mileage = updatedMileage; //LET CAR NODE'S MILEAGE EQUAL THE UPDATE MILEAGE GIVEN FROM THE USER

	//CALL THE FUNCTION THAT ADDS A CAR TO THE AVAIBLE FOR RENT CAR LIST
	addCarNode(carList, carNode);
}

//FUNCTIO THE SEACHES IF THE A PLATE NUMBER ALREADY EXISTS IN THE RENTED CAR LIST
bool search(struct rented *rentList, char *plateNumber)
{
	//IF THE LIST IS EMPTY THEN RETURN FALSE
	if (rentList == NULL)
		return false;
	//IF THE PLATE NUMBER EXISTS THEN RETURN TRUE
	if (strcmp(rentList->plateNumber, plateNumber) == 0)
		return true;

	return false;
}


//-------COMMENTS BELOW APPLY TO THE SAME CONCEPTS THE BEGIN ON LINE 439------------------------//

void tran2(repair **repairList, rented **rentList)
{

	char *tempPlate = malloc(sizeof(char) * 10);
	int updatedMileage;
	bool result = false;
	int count = 1;

	rented *previous = NULL;
	rented *rented = *rentList;

	repair *repairNode = (repair *)malloc(sizeof(repair));

	printf("Enter a plate number you wish to return: ");
	scanf("%s", tempPlate);
	fflush(stdin);

	while (strlen(tempPlate) != 7)
	{
		printf("\nInvalid Plate Length!\n");
		printf("Enter a plate number you wish to return: ");
		scanf("%s", tempPlate);
	}

	while (rented != NULL && result != true)
	{
		result = search(rented, tempPlate);
		if (count == 1 && result == true)
		{
			*rentList = (*rentList)->next;
			free(previous);
		}
		else if (rented->next == NULL && result == true)
		{
			previous->next = NULL;
			free(rented);
			rented = NULL;
		}
		else
		{
			if (result == true)
			{
				previous->next = rented->next;
				free(rented);
				rented = NULL;
			}
			else
			{
				previous = rented;
				rented = rented->next;
			}
		}

		count++;
	}

	if (result != true)
	{
		printf("Plate number does not exist\n");
		exit(0);
	}

	printf("Please enter the updated mileage: ");
	scanf("%d", &updatedMileage);

	strcpy(repairNode->plateNumber, tempPlate);
	repairNode->mileage = updatedMileage;

	addRepairNode(repairList, repairNode);
}

// TRANSFERING A CAR FROM THE REPAIR LL TO THE AVAILABLE-FOR-RENT LL
void tran3(avRent **carList, repair **repairList)
{

	char *tempPlate = malloc(sizeof(char) * 10);
	int updatedMileage;
	bool result = false;
	int count = 1;

	repair *previous = NULL;
	repair *repairN = *repairList;

	avRent *carNode = (avRent *)malloc(sizeof(avRent));

	printf("Enter a plate number you wish to return: ");
	scanf("%s", tempPlate);
	fflush(stdin);

	while (strlen(tempPlate) != 7)
	{
		printf("\nInvalid Plate Length!\n");
		printf("Enter a plate number you wish to return: ");
		scanf("%s", tempPlate);
	}

	while (repairN != NULL && result != true)
	{
		result = search2(repairN, tempPlate);
		if (count == 1 && result == true)
		{
			*repairList = (*repairList)->next;
			free(previous);
		}
		else if (repairN->next == NULL && result == true)
		{
			previous->next = NULL;
			free(repairN);
			repairN = NULL;
		}
		else
		{
			if (result == true)
			{
				previous->next = repairN->next;
				free(repairN);
				repairN = NULL;
			}
			else
			{
				previous = repairN;
				repairN = repairN->next;
			}
		}

		count++;
	}

	if (result != true)
	{
		printf("Plate number does not exist\n");
		exit(0);
	}

	printf("Please enter the updated mileage: ");
	scanf("%d", &updatedMileage);

	strcpy(carNode->plateNumber, tempPlate);
	carNode->mileage = updatedMileage;

	addCarNode(carList, carNode);
}

//FUNCTION THAT SEARCHES IF A PLATE NUMBER EXISTS IN THE CARS IN REPAIR CARLIST
bool search2(struct repair *repairList, char *plateNumber)
{
	if (repairList == NULL)
		return false;

	if (strcmp(repairList->plateNumber, plateNumber) == 0)
		return true;

	return false;
}

// TRANSFER FROM AVAILABLE-FOR-RENT LL to RENTED LL
void tran4(avRent **carList, rented **rentList)
{
	char *returnDate = malloc(sizeof(char) * 10);

	avRent *previous = NULL;
	avRent *avail = *carList;

	rented *rentNode = (rented *)malloc(sizeof(rented));

	printf("Please enter the expected return date: ");
	scanf("%s", returnDate);
	fflush(stdin);

	while (strlen(returnDate) != 6)
	{
		printf("\nInvalid date!\n");
		printf("Enter a new return date: ");
		scanf("%s", returnDate);
	}

	strcpy(rentNode->plateNumber, avail->plateNumber);
	rentNode->mileage = avail->mileage;
	rentNode->returnDate = atoi(returnDate);

	previous = *carList;
	*carList = (*carList)->next;
	free(previous);

	addRentedNode(rentList, rentNode);
}

// SORT AVAILABLE FOR RENT LL FROM LEAST TO GREATEST MILEAGES
void sortAVRentList(avRent **carList)
{

	avRent *tempNode = (avRent *)malloc(sizeof(avRent)); // TEMP NODE WITH TYPE AVRENT MALLOCING SIZE OF AVRENT
	tempNode = *carList; //LET A TEMPNODE POINT THE AVAILABLE FOR RENT CAR LIST
	avRent *ptr = NULL; //LET NODE OF TYPE AVRENT EQUAL NULL
	int temp; //TEMP VARIABLE TO STORE MILAGES
	char *tempPlate = malloc(sizeof(char) * 10); //CHAR TEMP PLATE WITH THE SAME OF 10

	//IF THE TEMP NODE IS NOT EMPTY THEN:
	while (tempNode != NULL)
	{
		ptr = tempNode->next; //LET PTR EQUAL TO THE NEXT NODE
		//WHILE LOOP THAT CHECK IF PTR IS NOT EMPTY THEN TRANSFER CONTENTS FROM THE LIST INTO TEMP VARIABLES
		while (ptr != NULL)
		{
			//IF THE MILAGE OF THE TEMP NODE IS GREATER THAN THE MILAGE IN THE PTR NODE THEN
			if (tempNode->mileage > ptr->mileage)
			{
				temp = tempNode->mileage; //LET TEMP EQUAL THE MILAGE IN THE TEMP NODE
				strcpy(tempPlate, tempNode->plateNumber); // AND COPY THE CONTENTS FROM THE TEMPNODE INTO THE TEMP PLATE

				tempNode->mileage = ptr->mileage; //LET THE MILEAGE FROM THR PTR EQUAL THE TEMO NODE'S MILEAGE
				strcpy(tempNode->plateNumber, ptr->plateNumber); //COPY THE PLATE NUMBER FROM THE PTR NODE IN TO THE TEMP NODE

				ptr->mileage = temp; //LET THE PTR NODE'S MILEAGE EQUAL THE TEMP MILEAGE
				strcpy(ptr->plateNumber, tempPlate); //COPY THE CONTENTS FROM TEMP PLATE INTO THE THE PTR'S PLATE NUMNER NODE
			}
			ptr = ptr->next; //GO TO THE NEXT NODE
		}
		tempNode = tempNode->next; //GO TO THE NEXT NODE
	}
}

//-----------------SAME CONCEPT COMMENTS APPLIES TO THE NEXT FUNCTION FROM LINE 725-------------------//

// SORTING THE RENTED LINKED LIST FROM EARLIEST TO LATEST DATES
void sortRentedtList(rented **rentList)
{

	rented *tempNode = (rented *)malloc(sizeof(rented));
	tempNode = *rentList;
	rented *ptr = NULL;
	int temp;
	char *tempPlate = malloc(sizeof(char) * 10);
	int tempDate;

	while (tempNode != NULL)
	{
		ptr = tempNode->next;
		while (ptr != NULL)
		{
			if (tempNode->returnDate > ptr->returnDate)
			{
				temp = tempNode->mileage;
				strcpy(tempPlate, tempNode->plateNumber);
				tempDate = tempNode->returnDate;

				tempNode->mileage = ptr->mileage;
				strcpy(tempNode->plateNumber, ptr->plateNumber);
				tempNode->returnDate = ptr->returnDate;

				ptr->mileage = temp;
				strcpy(ptr->plateNumber, tempPlate);
				ptr->returnDate = tempDate;
			}
			ptr = ptr->next;
		}
		tempNode = tempNode->next;
	}
}
