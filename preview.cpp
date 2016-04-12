/*************************************************************
 * Project name: HRA2016
 * File: preview.cpp
 * Last change: 12.04.2016 23:51
 *
 * Authors: Molnar Ondrej xmolna05@stud.fit.vutbr.cz
 *          Jelen Vilem   xjelen09@stud.fit.vutbr.cz
 *
 * Description: Methods for built-in functions.
 *
 ***********************************************************/
/**
 * @file preview.cpp
 *
 * @brief Methods for main program
 * @author Vilem Jelen
 * @todo Substring search method, Heap sort, Symbol table - BST (Binary Search Tree)
 */

#include <stdio.h>

int findSubString();

int main(void)
{
    int a = 0;
    a = getchar() - 97;
    if (a == 0)        printf ("%s", "Je to 'a'");
    else
        printf ("%s", "Neni to 'a'");

return 0;
}

/**
 * Method searches for substring in a string
 *
 * @bug Console app crashes when searching for #$%^ characters
 * @todo Fix bugs and finish method
 * @return position of substring
 */
int findSubString()
{
    //SOME CODE

} // int findSubString()

/*** End of file ial.c ***/
