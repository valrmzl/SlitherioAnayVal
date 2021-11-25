//
// Created by luax2 on 24/11/2021.
//

#ifndef SLITHERIO_SLITHERIO_H
#define SLITHERIO_SLITHERIO_H

#include <stdio.h>
#include <stdlib.h>

#define valorInicial 10



typedef struct node Node;
typedef struct list List;


List *newList();
void* getElement(List* list, int index);
void addElement(List *list,void* value);
void removeLastElement(List *list);
int getSize(List *list);

typedef struct bloque Bloque;
Bloque *newBloque(Color color,int n);


Vector2 *newPos(float x, float y);
Vector2 getRandomPos1();
Vector2 getRandomPos2();
Color getRandomColor();



Bloque* getBloque(List* list,int index);
Color getColor(List* gusano, int index);
float getRadio(List* gusano,int index);
Vector2 getPosicion(List* gusano,int index);
void setPosicion(List* gusano, int index,Vector2 pos);



void inicializarBloque(Vector2 initialPositions[valorInicial], List *gusano);
void inicializarPosiciones(List *posiciones, Vector2 initialPositions[valorInicial],  Vector2 pInicial);
void updateListaP(List* posiciones,Vector2 mouse);


Vector2 mouseMovement(Vector2 mouse,List *posiciones);
Vector2 Vector2Transformacion(Vector2 n);
void updateGusano(List *gusano,List *posiciones);





void food1(List *gusano,List *posiciones,Vector2 *randomPos, Color randomColor);
void food2(List *gusano,List *posiciones,Vector2 *randomPos, Color randomColor);
void foodPrep(Color foods[],Vector2 positionsCentro[], Vector2 positionsAll[],int n);


void gameplayer(List *gusano);
void gameState(List *gusano);

#endif //SLITHERIO_SLITHERIO_H
