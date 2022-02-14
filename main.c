#define _CRT_SECURE_NO_WARNINGS
#include "ShoppingList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main(void)
{
    srand((unsigned int)time(NULL)); /*EXAMINATION 1*/
    struct ShoppingList shoppingList;
    shoppingList.length = 0;
    shoppingList.itemList = NULL;

    int option;

    do
    {
        printf("\n\nWelcome to the shopping list manager!\n");
        printf("=====================================\n\n");

        printf("1. Add an item\n");
        printf("2. Display the shopping list\n");
        printf("3. Remove an item\n");
        printf("4. Change an item\n");
        printf("5. Save list\n");
        printf("6. Load list\n");
        printf("8. Search list\n"); /*EXAMINATION UPPGIFT 2*/
        printf("7. Exit\n");

        printf("What do you want to do? ");
        scanf("%d", &option);

        switch (option)
        {
        case 1: addItem(&shoppingList); break;
        case 2: printList(&shoppingList); break;
        case 3: removeItem(&shoppingList); break;
        case 4: editItem(&shoppingList); break;
        case 5: saveList(&shoppingList); break;
        case 6: loadList(&shoppingList); break;
        case 8: searchItem(&shoppingList); break; /*EXAMINATION UPPGIFT 2*/
        case 7: free(shoppingList.itemList); break;
        default:
            printf("Please enter a number between 1 and 7");
        }
    } while (option != 7);
    
    
    return 0;
}

