#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

typedef struct avRent
{

  int mileage;
  char plateNumber[8];
  struct avRent *next; // dynamic connection to the next car in the list
  struct avRent *previous;

} avRent;

typedef struct rented
{

  int mileage;
  char plateNumber[8];
  int returnDate;
  struct rented *next; // dynamic connection to the next car in the list
  struct rented *previous;

}rented;

typedef struct repair
{

  int mileage;
  char plateNumber[8];
  struct repair *next; // dynamic connection to the next car in the list
  struct rented *previous;

} repair;

//prototypes
void addCarNode(avRent **carList, avRent *node);
void addRentedNode(rented **rentList, rented *node);
void addRepairNode(repair **repairList, repair *node);

avRent *addNewCar(avRent *carList);

void tran1(avRent **carList, rented **rentList);
void tran2(repair **repairList, rented **rentList);
void tran3(avRent **carList, repair **repairList);
void tran4(avRent **carList, rented **rentList);

void removeCar(avRent **carList);

void displayLists(avRent *carList, rented *rentList, repair *rapirList);

void loadFromFile( avRent **carList,  rented **rentList,  repair **repairList);

void saveToFiles(avRent *carList, rented *rentList, repair *repairList);

//void sortList(avRent **carList, rented **rentList);

bool search(struct rented* rentList, char *plateNumber);

bool search1(struct rented* rentList, char *plateNumber);

bool search2(struct repair* repairList, char *plateNumber);

void sortAVRentList(avRent **carList);

void sortRentedtList(rented **rentList);

int ifPlateExists(avRent *carList, char *tempPlate);



int main(){
  avRent **carList;
  avRent *carNode;
  carList = NULL;
  carList = (avRent **)malloc(sizeof(avRent *));

  rented **rentList;
  //rented *rentNode;
  rentList = NULL;
  rentList = (rented **)malloc(sizeof(rented *));

  repair **repairList;
  //repair *repairNode;
  repairList = NULL;
  repairList = (repair **)malloc(sizeof(repair *));

  int code;

  loadFromFile(carList, rentList, repairList);



  do{

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

    sortAVRentList(carList);
    sortRentedtList(rentList);


    switch(code){

      case 1:{
        carNode = addNewCar(*carList);
        addCarNode(carList, carNode);
        break;
      }

      case 2:{
        tran1(carList, rentList);
        break;
      }

      case 3:{
        tran2(repairList, rentList);
        break;
      }
      
      case 4:{
        tran3(carList, repairList);
        break;
      }

      case 5:{
        tran4(carList, rentList);
        break;
      }

      case 6:{
        displayLists(*carList, *rentList, *repairList);
        break;
      }
      
      case 7:{
        saveToFiles(*carList, *rentList, *repairList);
        break;
      }
        
    }

  }while(code != 7);

  return(0);
}


void addCarNode(avRent **carList, avRent *node) {

  avRent *temp;
  temp = *carList;

  if (*carList == NULL) {
    *carList = node;
  } else {

    while (temp->next != NULL) {
      temp = temp->next;
    }//while

    temp->next = node;
  }//else
}//addCarNode

void addRentedNode(rented **rentList, rented *node) {

  rented *temp;
  temp = *rentList;

  if (*rentList == NULL) {
    *rentList = node;
  } else {

    while (temp->next != NULL) {
      temp = temp->next;
    }//while

    temp->next = node;
  }//else
}//addRentedNode

void addRepairNode(repair **repairList, repair *node) {

  repair *temp;
  temp = *repairList;

  if (*repairList == NULL) {
    *repairList = node;
  } else {

    while (temp->next != NULL) {
      temp = temp->next;
    }//while

    temp->next = node;
  }//else
}//addRepairNode


//1.
avRent *addNewCar(avRent *carList){

  avRent *ptr = NULL;
  ptr = (avRent *)malloc(sizeof(avRent));
  //avRent *tempptr = carList;

  char tempPlate [7] = "";
  char tempMileage [10] = "";
  int result;

  printf("Please enter a plate number (7-Charecters Long): ");
  scanf("%s", tempPlate);



  while(strlen(tempPlate) != 7){
    printf("\nInvalid Plate Length!\n");
    printf("Please enter a plate number (7-Charecters Long): ");
    scanf("%s", tempPlate);
  }

  // result = ifPlateExists(carList, tempPlate);

  

  // while(result == 1){
  //   printf("\nPlate already exists\n");
  //   printf("Please enter a plate number (7-Charecters Long): ");
  //   scanf("%s", tempPlate);
  //   result = ifPlateExists(carList, tempPlate);
  // }


  printf("Please enter a mileage: ");
  scanf("%s", tempMileage);

  ptr->mileage = atoi(tempMileage);

  strcpy(ptr->plateNumber, tempPlate);

  printf("\nYou have succesfully added plate number:- %s with a mileage of:- %d\n", ptr->plateNumber, ptr->mileage);
  return ptr;

}//addNewCar


void displayLists(avRent *carList, rented *rentList, repair *repairList){

    printf("\nAvailable For Rent Cars:-\n\n");
    avRent *av = carList;
    rented *rented = rentList;
    repair *repair = repairList;

    while (av != NULL){
        printf("%s | %d\n", av->plateNumber, av->mileage);
        av = av->next;
    }

    printf("\nRented Cars:-\n\n");

    while (rented != NULL){
        printf("%s | %d | %d\n", rented->plateNumber, rented->mileage, rented->returnDate);
        rented = rented->next;
    }

    printf("\nCars In Repair:-\n\n");

    while (repair != NULL){
        printf("%s | %d\n", repair->plateNumber, repair->mileage);
        repair = repair->next;
    }
}//displayLists


void loadFromFile( avRent **carList,  rented **rentList,  repair **repairList){

  FILE *file1 = fopen("availableForRentYY.txt", "r");
  FILE *file2 = fopen("rentedYY.txt", "r");
  FILE *file3 = fopen("inRepairYY.txt", "r");

  char tempPlate[10];
  int tempMileage;
  int rDate;

  if(file1 == NULL){
    printf("carList file unable to open \n");
    exit(0);
  }

    //LOADING IN carList
  while (fscanf(file1, "%s %d", tempPlate, &tempMileage) != EOF){

    avRent *tempNode = (avRent *)malloc(sizeof(avRent));

    strcpy(tempNode->plateNumber, tempPlate);
    tempNode->mileage = tempMileage;
    tempNode->next = NULL;

    addCarNode(carList, tempNode);

  }

  if(file1 == NULL){
    printf("rentList file unable to open \n");
    exit(0);
  }

    //LOADING IN rentList
  while (fscanf(file2, "%s %d %d", tempPlate, &tempMileage, &rDate) != EOF){

    rented *tempNode = (rented *)malloc(sizeof(rented));

    strcpy(tempNode->plateNumber, tempPlate);
    tempNode->mileage = tempMileage;
    tempNode->returnDate = rDate;
    tempNode->next = NULL;

    addRentedNode(rentList, tempNode);

  }

  if(file1 == NULL){
    printf("repairList file unable to open \n");
    exit(0);
  }

   //LOADING IN repairList 
  while (fscanf(file3, "%s %d", tempPlate, &tempMileage) != EOF){

    repair *tempNode = (repair *)malloc(sizeof(repair));

    strcpy(tempNode->plateNumber, tempPlate);
    tempNode->mileage = tempMileage;
    tempNode->next = NULL;

    addRepairNode(repairList, tempNode);

  }



  fclose(file1);
  fclose(file2);
  fclose(file3);


}//loadFromFile


void saveToFiles(avRent *carList, rented *rentList, repair *repairList){

  FILE *file1 = fopen("availableForRentYY.txt", "w");
  FILE *file2 = fopen("rentedYY.txt", "w");
  FILE *file3 = fopen("inRepairYY.txt", "w");


  avRent *arent = carList; 
  repair *repair = repairList;
  rented *rented = rentList;

  while (arent != NULL) {
    fprintf(file1, "%s\n%d", arent->plateNumber, arent->mileage);
    // add a new line if it is not the last car
    if (arent->next != NULL) {
      fprintf(file1, "\n\n");
    }
    arent = arent->next;
  }

  while (rented != NULL) {
    fprintf(file2, "%s\n%d\n%d", rented->plateNumber, rented->mileage, rented->returnDate);
    // add a new line if it is not the last car
    if (rented->next != NULL) {
      fprintf(file2, "\n\n");
    }
    rented = rented->next;
  }

  while (repair != NULL) {
    fprintf(file3, "%s\n%d", repair->plateNumber, repair->mileage);
    // add a new line if it is not the last car
    if (repair->next != NULL) {
      fprintf(file3, "\n\n");
    }
    repair = repair->next;
  }


    fclose(file1);
    fclose(file2);
    fclose(file3);



}//saveToFile

//make free list

//2.
void tran1(avRent **carList, rented **rentList){

  char *tempPlate = malloc(sizeof(char) * 10);
  int updatedMileage;
  bool result;
  int count = 1;

  rented *tmp ;
  
  rented *previous = NULL;
  rented *rented = *rentList;

  avRent *carNode = (avRent *)malloc(sizeof(avRent));

  printf("Enter a plate number you wish to return: ");
  scanf("%s", tempPlate);
  fflush(stdin);

  while(strlen(tempPlate) != 7){
    printf("\nInvalid Plate Length!\n");
    printf("Enter a plate number you wish to return: ");
    scanf("%s", tempPlate);
  }



  while(rented != NULL && result != true){
    result = search(rented, tempPlate);
    if(count == 1 && result == true){
      tmp = *rentList;
      *rentList = (*rentList)->next;
      free(previous);
    }else if(rented->next == NULL && result == true){
      previous->next = NULL;
      free(rented);
      rented = NULL;
    }else{
      if(result == true){
        previous->next = rented->next;
        free(rented);
        rented = NULL;
      }else{
        previous = rented;
        rented = rented->next;
      }
    }

    count++;
    
  }

    if(result != true){
      printf("Plate number does not exist\n");
      exit(0);
    }


  printf("Please enter the updated mileage: ");
  scanf("%d", &updatedMileage);
  
  strcpy(carNode->plateNumber, tempPlate);
  carNode->mileage = updatedMileage;

  addCarNode(carList, carNode);

  printf("\nYou have succesfully transfered plate number | %s | from the rented cars into the available for rent cars.\n", carNode->plateNumber);

}//tran1


//problem in this part of code
bool search(struct rented* rentList, char *plateNumber)
{
    printf("test is %s_%s\n", rentList->plateNumber, plateNumber);
    // if current node is empty, return false
    if (rentList == NULL)
        return false;
 
    // If plate is present in current node, return true
    if (strcmp(rentList->plateNumber, plateNumber) == 0)
        return true;

    return false;
}

//3.
//TRANSFER A CAR FROM THE RENTED LL TO THE CARS IN REPAIR LL
void tran2(repair **repairList, rented **rentList){

  char *tempPlate = malloc(sizeof(char) * 10);
  int updatedMileage;
  bool result;
  int count = 1;

  rented *tmp;
  
  rented *previous = NULL;
  rented *rented = *rentList;

  repair *repairNode = (repair *)malloc(sizeof(repair));

  printf("Enter a plate number you wish to return: ");
  scanf("%s", tempPlate);
  fflush(stdin);

  while(strlen(tempPlate) != 7){
    printf("\nInvalid Plate Length!\n");
    printf("Enter a plate number you wish to return: ");
    scanf("%s", tempPlate);
  }



  while(rented != NULL && result != true){
    result = search1(rented, tempPlate);
    if(count == 1 && result == true){
      tmp = *rentList;
      *rentList = (*rentList)->next;
      free(previous);
    }else if(rented->next == NULL && result == true){
      previous->next = NULL;
      free(rented);
      rented = NULL;
    }else{
      if(result == true){
        previous->next = rented->next;
        free(rented);
        rented = NULL;
      }else{
        previous = rented;
        rented = rented->next;
      }
    }

    count++;
}

  if(result != true){
      printf("Plate number does not exist\n");
      exit(0);
    }


  printf("Please enter the updated mileage: ");
  scanf("%d", &updatedMileage);
  
  strcpy(repairNode->plateNumber, tempPlate);
  repairNode->mileage = updatedMileage;

  addRepairNode(repairList, repairNode);

  printf("\nYou have succesfully transfered plate number | %s | from rented cars into the repair cars.\n", repairNode->plateNumber);


}//tran 2

bool search1(struct rented* rentList, char *plateNumber)
{
    printf("test is %s_%s\n", rentList->plateNumber, plateNumber);
    // if current node is empty, return false
    if (rentList == NULL)
        return false;
 
    // If plate is present in current node, return true
    if (strcmp(rentList->plateNumber, plateNumber) == 0)
        return true;

    return false;
}

//4.
//TRANSFERING A CAR FROM THE REPAIR LL TO THE AVAILABLE-FOR-RENT LL
void tran3(avRent **carList, repair **repairList){

  char *tempPlate = malloc(sizeof(char) * 10);
  int updatedMileage;
  bool result;
  int count = 1;

  repair *tmp;
  repair *previous = NULL;
  repair *repairN = *repairList;

  avRent *carNode = (avRent *)malloc(sizeof(avRent));

  printf("Enter a plate number you wish to return: ");
  scanf("%s", tempPlate);
  fflush(stdin);

  while(strlen(tempPlate) != 7){
    printf("\nInvalid Plate Length!\n");
    printf("Enter a plate number you wish to return: ");
    scanf("%s", tempPlate);
  }



  while(repairN != NULL && result != true){
    result = search2(repairN, tempPlate);
    if(count == 1 && result == true){
      tmp = *repairList;
      *repairList = (*repairList)->next;
      free(previous);
    }else if(repairN->next == NULL && result == true){
      previous->next = NULL;
      free(repairN);
      repairN = NULL;
    }else{
      if(result == true){
        previous->next = repairN->next;
        free(repairN);
        repairN = NULL;
      }else{
        previous = repairN;
        repairN = repairN->next;
      }
    }

    count++;
    
  }

    if(result != true){
      printf("Plate number does not exist\n");
      exit(0);
    }


  printf("Please enter the updated mileage: ");
  scanf("%d", &updatedMileage);
  
  strcpy(carNode->plateNumber, tempPlate);
  carNode->mileage = updatedMileage;

  addCarNode(carList, carNode);

  printf("\nYou have succesfully transfered plate number | %s | from cars in repair into the available for rent.\n", carNode->plateNumber);


}

bool search2(struct repair* repairList, char *plateNumber)
{
    printf("test is %s_%s\n", repairList->plateNumber, plateNumber);
    // if current node is empty, return false
    if (repairList == NULL)
        return false;
 
    // If plate is present in current node, return true
    if (strcmp(repairList->plateNumber, plateNumber) == 0)
        return true;

    return false;
}

//5.
//TRANSFER FROM AVAILABLE-FOR-RENT LL to RENTED LL
void tran4(avRent **carList, rented **rentList){
  char *returnDate = malloc(sizeof(char) * 10);  

  avRent *previous = NULL;
  avRent *avail = *carList;

  rented *rentNode = (rented *)malloc(sizeof(rented));

  printf("Please enter the expected return date: ");
  scanf("%s", returnDate);
  fflush(stdin);

  while(strlen(returnDate) != 6){
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

  printf("\nYou have succesfully transfered plate number | %s | from cars available for rent to the rented cars.\n", rentNode->plateNumber);

}



//SORT AVAILABLE FOR RENT LL FROM LEAST TO GREATEST MILEAGES
void sortAVRentList(avRent **carList)
{

  avRent *tempNode = (avRent *)malloc(sizeof(avRent));
  tempNode = *carList;
  avRent *ptr = NULL;
  int temp;
  char *tempPlate = malloc(sizeof(char) * 10);

 
  
    while (tempNode != NULL)
    {
      // Node index will point to node next to current
      ptr = tempNode->next;
      while (ptr != NULL)
      {
        // If current node's data is greater than index's node data, swap the data between them
        if (tempNode->mileage > ptr->mileage)
        {
          temp = tempNode->mileage;
          strcpy(tempPlate, tempNode->plateNumber);

          //printf("test is _%s_\n", &charTemp);


          tempNode->mileage = ptr->mileage;
          strcpy(tempNode->plateNumber, ptr->plateNumber);


          ptr->mileage = temp;
          strcpy(ptr->plateNumber, tempPlate);

          //printf("test is _%s_\n", &charTemp);


        }
        ptr = ptr->next;
      }
      tempNode = tempNode->next;
    }
  }


//SORTING THE RENTED LINKED LIST FROM EARLIEST TO LATEST DATES
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
      // Node index will point to node next to current
      ptr = tempNode->next;
      while (ptr != NULL)
      {
        // If current node's data is greater than index's node data, swap the data between them
        if (tempNode->returnDate > ptr->returnDate)
        {
          temp = tempNode->mileage;
          strcpy(tempPlate, tempNode->plateNumber);
          tempDate = tempNode->returnDate;

          //printf("test is _%s_\n", &charTemp);


          tempNode->mileage = ptr->mileage;
          strcpy(tempNode->plateNumber, ptr->plateNumber);
          tempNode->returnDate = ptr->returnDate;


          ptr->mileage = temp;
          strcpy(ptr->plateNumber, tempPlate);
          ptr->returnDate = tempDate;

          //printf("test is _%s_\n", &charTemp);


        }
        ptr = ptr->next;
      }
      tempNode = tempNode->next;
    }
  }


  int ifPlateExists(avRent *carList, char *tempPlate){

    int result;

    //avRent *carNode = (avRent *)malloc(sizeof(avRent));
    
    avRent *carNode = carList;

    while(carNode != NULL && result != 1){

      printf("_%s_ _%s_\n", tempPlate, carNode->plateNumber);

      if(strcmp(tempPlate, carNode->plateNumber) == 0){
        result = 1;
      }
      else{
        result = 0;
      }

      carNode = carNode->next;
    }

    return result;
  }


