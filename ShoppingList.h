/*EXAMINATION UPPGIFT 2, Jag skapade en ny funktion som med hjälp av strcmp jämför de två strängarna (den angivna och de i listan) om de två strängarna är likadana returneras 0. Med hjälp av min checker kan jag 1: veta om jag returneras 0. 2: Veta om jag ska inte haft en enda strcmp som returnerat 0. 3: Veta om 1 eller flera strcmp returnerat 0. */

/*EXAMINATION 1, Jag lagrade ett random number i en int i structen groceryItem och en char som jag gjorde toUpper på också i strukten. Denna char fick jag genom att ta första bokstaven i indexet, eftersom det var en sträng. Binärfilerna gjorde så att jag ej behövde lägga några extra rader kod i save och load funktioneran. Sedan var det bara att fixa utskriften gemom att använda både variablerna istället för att slå ihop dem som komplicerar i onödan. */


#ifndef SHOPPING_LIST_H
#define SHOPPING_LIST_H
#define MAX_NAME 20
#define MAX_UNIT 10

struct GroceryItem
{
    char productName[MAX_NAME];
    float amount;
    char unit[MAX_UNIT];
    char firstLetter; /*EXAMINATION 1*/
    int randNum; /*EXAMINATION 1*/
    
};

struct ShoppingList
{
    struct GroceryItem *itemList;
    int length;
    
};


void addItem(struct ShoppingList *list);
void printList(struct ShoppingList *list);
void editItem(struct ShoppingList *list);
void removeItem(struct ShoppingList *list);
void saveList(struct ShoppingList *list);
void loadList(struct ShoppingList* list);
void searchItem(struct ShoppingList* list); /*EXAMINATION UPPGIFT 2*/
struct GroceryItem * allocate(int, struct GroceryItem *);

#endif

