//
// Created by luax2 on 26/11/2021.
//
#include "raylib.h"

#ifndef SLITHERIO_LISTS_H
#define SLITHERIO_LISTS_H
typedef struct node Node;
typedef struct list List;

List *newList();
void addElement(List *list,void* value);
void removeLastElement(List *list);
void* getElement(List* list,int index);
int getSize(List *gusano);

Node *getHead(List *list);
Node *getNext(Node* focusNode);
void *getValue(Node *focusNode);

void updateListaP(List* posiciones, Vector2 mouse);
#endif //SLITHERIO_LISTS_H
