#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#define M 124
#define N 10

struct LNode
{
    int id;
    char *manufacturer;
    char *model;
    int year;
    int price;
    float length;
    float width;
    int *memory;
    struct LNode *next;
};

struct LHead
{
    int cnt;
    struct LNode *first;
    struct LNode *last;
};

typedef struct LNode Node;
typedef struct LHead Head;

int menu_main(); // main menu
int menu_intput(); // menu to choose between two numbers
int menu_1(); // redaction menu
int menu_2(); // search menu
int Read_Field(char *); // field selection
void Read_Value(char *); // the value of the selected field
int scanID(int *); // enter an element id by the user
Head *MakeHead(); // create head
Node *MakeNode(); // creating a list element
int ReadFile(Head *, Node *, int *, int *); // read file
Node *ReadNode(char *, int *); // reading a list element from the keyboard
void NodePrint(Node *, int); // output of the list element on the screen
void KartPrint(Head *, int *); // the output table on the screen
void InsertAfter(Head *, Node *, int); // inserting element
void ChangeAfterInsert(Head *, int, int *); // changing numbers and reinstallation of counters in the array memory after insertion
void clearNode(Head *, Node *); // memory clearing
void DeleteNode(Head *, int); // deleting element
void ChangeAfterDelete(Head *, int, int *); // changing numbers and reinstallation of counters in the array memory after deleting
Node *FindNodeById(Head *, int); // search elements by number
int FindNodesByField(Head *, char *(*Fname)(Node *), int, char *, int *); // search elements by field value
int ChangeValue(Node *, char *, int, int); // changing element
char *manufacturer(Node *); // returns the value of the manufacturer field of the current list element
char *model(Node *); // returns the value of the model field of the current list element
char *year(Node *); // returns the value of the year field of the current list element
char *price(Node *); // returns the value of the price field of the current list element
char *length(Node *); // returns the value of the length field of the current list element
char *width(Node *); // returns the value of the width field of the current list element
int Sort1_6(Head *, Node *, char *(*Fname)(Node *), int, int, int *); // sorting
void Sort7(Head *, Node *, int, int *); // sorting memory array
int rewriteFile(FILE *, Head *, int *); // rewriting file

#endif // MAIN_H_INCLUDED
