READ ME:

Assignment 3
Name: Ahmad Sawan
Email : asawan@uoguelph.ca
Student ID: 1205875

For q1:
When you compile and run you will be presented with the table of transactions. Pick a command and follow the instructions.

Example: 
        ----------------------------------------------------------------------
        Please select from the following options:
        1: Preorder
        2: Postorder
        3: Inorder
        4: Exit
        ----------------------------------------------------------------------
        > 


To complite the program :-

    1. make
    2. ./q1 '(expression)' for example, ./q1 '(((x1+5.12)*(x2-7.68))/x3)'

To operate this program, a menu will appear with instructions such as preorder, postorder, inorder, and exit
                                
                                *I did the Inorder function for bonus marks*




An example output follows :-

        ----------------------------------------------------------------------
        Please select from the following options:
        1: Preorder
        2: Postorder
        3: Inorder
        4: Exit
        ----------------------------------------------------------------------
        > 1

        / * + x1[0.00] 5.12 - x2[0.00] 7.68 x3[0.00]

        ----------------------------------------------------------------------
        Please select from the following options:
        1: Preorder
        2: Postorder
        3: Inorder
        4: Exit
        ----------------------------------------------------------------------
        > 2

        x1[0.00] 5.12 + x2[0.00] 7.68 - * x3[0.00] /

        ----------------------------------------------------------------------
        Please select from the following options:
        1: Preorder
        2: Postorder
        3: Inorder
        4: Exit
        ----------------------------------------------------------------------
        > 3

        ( ( ( x1[0.00] + 5.12 ) * ( x2[0.00] - 7.68 ) ) / x3[0.00] )

        ----------------------------------------------------------------------
        Please select from the following options:
        1: Preorder
        2: Postorder
        3: Inorder
        4: Exit
        ----------------------------------------------------------------------
        > 4




