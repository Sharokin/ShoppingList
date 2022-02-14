#define _CRT_SECURE_NO_WARNINGS
#include"ShoppingList.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


void addItem(struct ShoppingList *list)
{
    struct GroceryItem *temp = allocate(list->length+1, list->itemList);
    if(temp == NULL)
        printf("Error");
    else
    {
        list->itemList = temp;
        while(getchar()!='\n');
        
        printf("Enter the name of the product: ");
        fgets(list->itemList[list->length].productName,MAX_NAME,stdin);
        list->itemList[list->length].productName[strlen(list->itemList[list->length].productName)-1] = '\0'; //Tar bort \n för utskriften

        printf("Enter the amount: ");
        do
        {
            scanf("%f", &list->itemList[list->length].amount);
            if(list->itemList[list->length].amount <= 0)
            {
                printf("Negative numbers not allowed");
            }
        }while(list->itemList[list->length].amount <= 0);

        printf("Enter what unit: ");
        while(getchar()!='\n');
        fgets(list->itemList[list->length].unit,MAX_UNIT,stdin);
        
        list->itemList[list->length].firstLetter = list->itemList[list->length].productName[0]; /*EXAMINATION 1*/
        list->itemList[list->length].firstLetter = toupper(list->itemList[list->length].firstLetter); /*EXAMINATION 1*/
        list->itemList[list->length].randNum = rand()%900+100; /*EXAMINATION 1*/
        
        list->length++;
    }
}

void printList(struct ShoppingList *list)
{
if(list->length > 0)
    for(int i = 0; i < list->length; i++)
    {
        printf("%d.(%c%d) %-20s %.1f %s", i+1, list->itemList[i].firstLetter, list->itemList[i].randNum, list->itemList[i].productName, list->itemList[i].amount, list->itemList[i].unit); /*EXAMINATION 1*/
    }
    else
        printf("No items in list\n");
}

void editItem(struct ShoppingList *list)
{
    int editer = 0;
    if(list->length > 0) //Kör bara om det finns varor
    {
        for(int i = 0; i < list->length; i++)
        {
            printf("%d.(%c%d) %-20s %.1f %s", i+1, list->itemList[i].firstLetter, list->itemList[i].randNum, list->itemList[i].productName,
                   list->itemList[i].amount, list->itemList[i].unit); /*EXAMINATION 1*/
        }
        printf("What product do you want to edit? ");
        do
        {
            scanf("%d", &editer);
            if(editer <= 0 || editer > list->length)
                printf("Enter valid number\n");
        }
        while(editer <= 0 || editer > list->length); //Hindrar användaren från att välja vara som ej finns
        if(editer <= list->length && editer > 0)
        {
            printf("Enter the new amount: ");
            do
            {
                scanf("%f", &list->itemList[editer - 1].amount); //Ändrar amount
                if(list->itemList[editer - 1].amount <= 0)
                {
                    printf("Enter positive number: ");
                }
            }while(list->itemList[editer - 1].amount <= 0);
        }
    }
    else
        printf("No items in list\n");
}

void removeItem(struct ShoppingList *list)
{
    int remover = 0;
    if(list->length > 0)
    {
        for(int i = 0; i < list->length; i++)
        {
            printf("%d.(%c%d) %-20s %.1f %s", i+1, list->itemList[i].firstLetter, list->itemList[i].randNum, list->itemList[i].productName, list->itemList[i].amount, list->itemList[i].unit); /*EXAMINATION 1*/
        }
        printf("What product do you want to remove? ");
        do
        {
            scanf("%d", &remover);
            if(remover <= 0 || remover > list->length) //Kontrollera att varan finns
                printf("Enter valid number\n");
        }
        while(remover <= 0 || remover > list->length);
        if(remover <= list->length && remover > 0)
        {
            for(int i = remover - 1; i<list->length; i++)
                {
                    list->itemList[i].firstLetter = list->itemList[i+1].firstLetter; /*EXAMINATION 1*/
                    list->itemList[i].randNum = list->itemList[i+1].randNum; /*EXAMINATION 1*/
                    strcpy(list->itemList[i].productName, list->itemList[i+1].productName);
                    list->itemList[i].amount = list->itemList[i+1].amount; 
                    strcpy(list->itemList[i].unit,list->itemList[i+1].unit);
                }
            list->length--; //Pga borttagning måste vi minska length
        }
    }
    else
        printf("No items in list\n");
}


void saveList(struct ShoppingList *list)
{
    while(getchar()!='\n');
    char fileName[25];
    int length = list->length;
    FILE *fp;
    printf("Enter the name of the file: ");
    scanf("%[^\n]s", fileName);
    fp = fopen(fileName, "wb");
    if (fp != NULL)
    {
        struct GroceryItem *temp = list->itemList;
        fwrite(&length, sizeof(int), 1, fp);
        fwrite(temp, sizeof(struct GroceryItem), length, fp);
        printf("List saved\n");
        fclose(fp);
    }
    else
    {
        printf("Error");
        return;
    }
}

void loadList(struct ShoppingList* list)
{
    while(getchar()!='\n');
    char name[25];
    printf("Enter the name of the file you want to open: ");
    scanf("%[^\n]s", name);
    FILE *fp = fopen(name, "rb");
    
    if(fp == NULL)
    {
        printf("File not found");
        return;
    }
    fread(&list->length, sizeof(int), 1, fp);
    struct GroceryItem *temp = allocate(list->length, list->itemList);
    list->itemList = temp;
    fread(list->itemList, sizeof(struct GroceryItem), list->length, fp);
    
}

struct GroceryItem * allocate (int size, struct GroceryItem *pList)
{
    struct GroceryItem *temp = (struct GroceryItem*)realloc(pList, sizeof(struct GroceryItem)*size);
    
    if(temp==NULL)
    {
        printf("Error");
        return NULL;
    }
    else
    {
        pList = temp;
        return pList;
    }
}

void searchItem(struct ShoppingList *list) //HELA DENNA FUNKTION /*EXAMINATION UPPGIFT 2*/
{
    int checker = 101;
    char searchName[25];
    if(list->length > 0)
    {
        for(int i = 0; i < list->length; i++)
        {
            printf("%d.(%c%d) %-20s %.1f %s", i+1, list->itemList[i].firstLetter, list->itemList[i].randNum, list->itemList[i].productName, list->itemList[i].amount, list->itemList[i].unit); /*EXAMINATION 1*/
        }
            
        printf("What item are you searching for? ");
        while(getchar()!='\n');
        scanf("%[^\n]s", searchName);
        
        for(int i = 0; i < list->length; i++)
        {
            if(strcmp(searchName, list->itemList[i].productName)==0)
            {
                printf("%d.(%c%d) %-20s %.1f %s", i+1, list->itemList[i].firstLetter, list->itemList[i].randNum, list->itemList[i].productName, list->itemList[i].amount, list->itemList[i].unit); /*EXAMINATION 1*/
                checker++;
            }
        }
        if(checker==101)
            printf("No item in list with this name\n");
    }
else
    printf("No items in the list\n");
}
