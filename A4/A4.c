/*---------------------------------------------
NAME: AHMAD SAWAN
STUDENT ID: 1205875
DATE: 29/11/2022
TITLE: Heaps
---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int sum_key;
    int key[3];
    int content[7];
} node;

node tree[20]; //initializing a node called tree to store info in it

//function prototype
void heapify(); //function to preform minHeap to the tree whilst updating and swaping contents


int main(){

    FILE *fp1 = fopen("f.dat", "r"); //opening the f.dat file in read mode
    int tempArray[20][10]; //creating a tempArray to store the [20][10] contents from the f.dat file
    int pNode; //initializing the parent node
    int lChild; //initialzing the left child node
    int rChild; //initialzing the right child node

    printf("\n");

    // nested for loop to scan the contents starting from the row then the elements in that row
    for (int j = 0; j < 20; ++j) {
        for (int i = 0; i < 10; ++i){ 
            fscanf(fp1, "%d", &tempArray[j][i]);
        }

        //storing the the first three elements into the variable node sum_key
        tree[j].sum_key = tempArray[j][0] + tempArray[j][1] + tempArray[j][2];

        //for loop to store the first three elements into the node's key element
        for (int i = 0; i < 3; i++){
            tree[j].key[i] = tempArray[j][i];
        }

        //for loop to store the remaing 7 content elements into the node's content element
        for (int i = 0; i < 7; i++){
            tree[j].content[i] = tempArray[j][i + 3];
        }
    }


    for (int i = 0; i < 20; i++)
    {
        pNode = (i - 1) / 2; // the parent node equals (i - 1) / 2 to find the parent node from a given i point
        lChild = i - 1; // the left child is calculated by subtracting a given i point by 1
        rChild = i; // the right child is simply just i

        // an if condition to check that the tree has no children that are less than the parent node
        if (tree[pNode].sum_key < tree[lChild].sum_key && tree[pNode].sum_key < tree[rChild].sum_key){
            heapify(); //calling the function heapify to preform minHeap
        }
    }


    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 3; j++){ // for loop that prints out the first three contents of the row
            printf("%.2d ", tree[i].key[j]);
        }
        for (int z = 0; z < 7; z++){ // for loop that prints out the remaining 7 elements in the row
            printf("%.2d ", tree[i].content[z]); 
        }
        printf("\n");
    }

    fclose(fp1); //closing the file to avoid memory clogs
    printf("\n");
    return 0;
}

void heapify(){

    int pNode; // initializing a parent node with type int
    int lChild; // initializing a left child node with type int
    int rChild; // initializing a right child node with type int
    node tempNode; // initializing a tempNode with type struct node

    // if condition that checks if the left 20th left child is less than the its parent node which is index 9
    if (tree[19].sum_key < tree[9].sum_key){
        tempNode.sum_key = tree[19].sum_key; //storing the contents of the child's into a temp variable
        tree[19].sum_key = tree[9].sum_key; // swaping the child with the parent
        tree[9].sum_key = tempNode.sum_key; // replacing the content of the parent with the child

        // for loop that swaps the content of the remaing 7 elements of the row
        for (int j = 0; j < 7; j++){
            tempNode.content[j] = tree[19].content[j];
            tree[19].content[j] = tree[9].content[j];
            tree[9].content[j] = tempNode.content[j];
        }

        // for loop that swaps the first three elements in that row
        for (int j = 0; j < 3; j++){
            tempNode.key[j] = tree[19].key[j];
            tree[19].key[j] = tree[9].key[j];
            tree[9].key[j] = tempNode.key[j];
        }
    }

    // for loop that goes through every child node and subtracts 2 everytime it loops to go to the next subtree
    for (int i = 18; i > 0; i = i - 2){

        pNode = (i - 1) / 2; // the parent node equals (i - 1) / 2 to find the parent node from a given i point
        lChild = i - 1; // the left child is calculated by subtracting a given i point by 1
        rChild = i; // the right child is simply just i

        // if condtions that checks if the parent node is not 0 and if the right child is less than the left child and the right child is less than parent node
        if (tree[pNode].sum_key != 0 && tree[rChild].sum_key < tree[lChild].sum_key && tree[rChild].sum_key < tree[pNode].sum_key){
            //if the condition is met then swap the parent node with the right child
            tempNode.sum_key = tree[rChild].sum_key;
            tree[rChild].sum_key = tree[pNode].sum_key;
            tree[pNode].sum_key = tempNode.sum_key;

            // for loop to swap its array contents 
            for (int j = 0; j < 7; j++){
                tempNode.content[j] = tree[rChild].content[j];
                tree[rChild].content[j] = tree[pNode].content[j];
                tree[pNode].content[j] = tempNode.content[j];
            }

            // for loop to swap its array contents 
            for (int j = 0; j < 3; j++){
                tempNode.key[j] = tree[rChild].key[j];
                tree[rChild].key[j] = tree[pNode].key[j];
                tree[pNode].key[j] = tempNode.key[j];
            }
        }
        // else if condition that checks if the parent node is not 0 and if the left child is less than the parent node
        else if (tree[pNode].sum_key != 0 && tree[lChild].sum_key < tree[pNode].sum_key){
            // if that condition is met than swap the left child with the parent node
            tempNode.sum_key = tree[lChild].sum_key;
            tree[lChild].sum_key = tree[pNode].sum_key;
            tree[pNode].sum_key = tempNode.sum_key;

            // for loop that swaps its array contents
            for (int j = 0; j < 7; j++){
                tempNode.content[j] = tree[lChild].content[j];
                tree[lChild].content[j] = tree[pNode].content[j];
                tree[pNode].content[j] = tempNode.content[j];
            }

            // for loop that swaps its array contents
            for (int j = 0; j < 3; j++){
                tempNode.key[j] = tree[lChild].key[j];
                tree[lChild].key[j] = tree[pNode].key[j];
                tree[pNode].key[j] = tempNode.key[j];
            }
        }
    }
}

