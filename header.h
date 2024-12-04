#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>

using namespace std;

typedef char infotype;
typedef struct elmList *address;

struct elmList {
    infotype info;
    address next;
    address prev;
};

struct List {
    address first;
    address last;
    address cursor;
};

void createList(List &L);
address alokasi(infotype x);
void insertChar(List &L, infotype x);

void removeChar(List &L);
int count_words(List L);
void displayText(List L);
void displayFinalText(List L);
void moveCursorLeft(List &L);
void moveCursorRight(List &L);
void handleInput(List &L);


#endif // HEADER_H_INCLUDED
