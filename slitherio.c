//
// Created by luax2 on 20/11/2021.
//
#include "raylib.h"
#include "raymath.h"
#include "slitherio.h"
#include <stdio.h>
#include <stdlib.h>

#include "slitherio.h"

struct node{
    void* value;
    struct node *next;
};

struct list{
    Node* head;
    int size;
};


//crea una lista
List *newList(){
    List *newHead= malloc(sizeof(List));
    newHead->size=0;
    newHead->head=NULL;
    return newHead;
}



void* getElement(List* list, int index){
    Node *focusNode=list->head;
    for(int i=0;i<index;i++){
        focusNode=focusNode->next;
    }
    return focusNode->value;
}


//añade elementos a una lista
void addElement(List *list,void* value){
    Node *new =malloc(sizeof(Node));
    new->value=value;
    new->next=list->head;
    list->head=new;
    list->size++;
}


//quita el ulitmo elemento de una lista
void removeLastElement(List *list){
    Node *focusNode = list->head;
    while (focusNode->next->next!= NULL) {
        focusNode = focusNode->next;
    }
    Node *elementDelete = focusNode->next;
    focusNode->next = NULL;
    free(elementDelete);
    list->size--;
}

//devuelve el tamaño de una lista
int getSize(List *list) {
    return list->size;
}


struct bloque{
    Color color;
    Vector2 posicion;
    float alpha;
    float radio;
};

// crea un nuevo bloque de gusano
Bloque *newBloque(Color color,int n){
    Bloque* new=malloc(sizeof(Bloque));
    new->color=color;
    new->alpha=1;
    new->posicion=(Vector2){ 100+5*n, 100+5*n};
    new->radio=20;
    return new;
}


//genera una posicion random
Vector2 *newPos(float x, float y){
    Vector2 *new=malloc(sizeof (Vector2));
    new->x=x;
    new->y=y;
    return new;
}


Vector2 getRandomPos1(){
    Vector2 n = {GetRandomValue(-3100,4900), GetRandomValue(-3550,4450)};
    return n;
} //toda la pantalla

Vector2 getRandomPos2(){
    Vector2 n = {GetRandomValue(-1100,2900), GetRandomValue(-1550,2450)};
    return n;
}//centro


//obtiene un color random para los gusanos
Color getRandomColor(){
    Color random1=(Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
    return random1;
}


//devuelve en cual bloque del gusano se encunetra
Bloque* getBloque(List* list,int index){
    Node *focusNode = list->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr;
}

//obitene el color
Color getColor(List* gusano, int index){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr->color;
}


float getRadio(List* gusano,int index){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr->radio;
}

Vector2 getPosicion(List* gusano,int index){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr->posicion;
}

void setPosicion(List* gusano, int index,Vector2 pos){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    ptr->posicion=pos;
}

//inicializa un gusano, a partir de una longitud incial predeterminada
void inicializarBloque(Vector2 initialPositions[valorInicial], List *gusano){
    Color random1=(Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
    for(int i = 0; i<valorInicial;i++){//inicializar bloque
        addElement(gusano, newBloque(random1,i));
    }
}

//se agregan a una lista las posciones de cada bloque del gusano del jugador
void inicializarPosiciones(List *posiciones, Vector2 initialPositions[valorInicial],  Vector2 pInicial){
    for(int i = 0; i<valorInicial;i++){//inicializar posiciones
        initialPositions[i].x = pInicial.x + i;
        initialPositions[i].y = pInicial.y + i;
        addElement(posiciones, initialPositions+i);
    }
}


//actualiza las posciones de cada bloque para que estas puedan ser seguidasp por el mouse
void updateListaP(List* posiciones,Vector2 mouse){
    Node* focus=posiciones->head;
    Vector2 *vec=focus->value;
    Vector2 tmp1=*vec;
    Vector2 tmp2;
    *vec=mouse;
    while(focus->next!=NULL){
        focus=focus->next;
        vec=focus->value;
        tmp2=*vec;
        *vec=tmp1;
        if(focus->next==NULL){
            break;
        }
        focus=focus->next;
        vec=focus->value;
        tmp1=*vec;
        *vec=tmp2;
    }
}


Vector2 mouseMovement(Vector2 mouse,List *posiciones){
    Vector2 direction= Vector2Add(Vector2Transformacion(mouse),*((Vector2*)getElement(posiciones,0)));
    return direction;
}


Vector2 Vector2Transformacion(Vector2 n){
    n.x=n.x-900;
    n.y=n.y-400;
    Vector2 resultado = {n.x/ Vector2Length(n),n.y/ Vector2Length(n)};//calcular unitario
    return Vector2Scale(resultado,7);
}


void updateGusano(List *gusano,List *posiciones){
    for(int i =0; i<gusano->size;i++){
        setPosicion(gusano,i,*(Vector2*)getElement(posiciones,i));
    }
}


void food1(List *gusano,List *posiciones,Vector2 *randomPos, Color randomColor){
    if(CheckCollisionCircles(getPosicion(gusano,0), getRadio(gusano,0),*randomPos,10)){
        addElement(gusano, newBloque(getColor(gusano,0),1));
        addElement(posiciones, newPos(getPosicion(gusano, 1).x,getPosicion(gusano, 1).y));
        *randomPos=getRandomPos2();
    }
    else{
        DrawCircleV(*randomPos,10,randomColor);
    }

}


void food2(List *gusano,List *posiciones,Vector2 *randomPos, Color randomColor){
    if(CheckCollisionCircles(getPosicion(gusano,0), getRadio(gusano,0),*randomPos,10)){
        addElement(gusano, newBloque(getColor(gusano,0),1));
        addElement(posiciones, newPos(getPosicion(gusano, 1).x,getPosicion(gusano, 1).y));
        *randomPos=getRandomPos1();
    }
    else{
        DrawCircleV(*randomPos,10,randomColor);
    }
}


void foodPrep(Color foods[],Vector2 positionsCentro[], Vector2 positionsAll[],int n){
    for(int i=0;i<n;i++){
        foods[i]=getRandomColor();
        positionsCentro[i]=getRandomPos2();
        positionsAll[i]=getRandomPos1();
    }
}



void gameplayer(List *gusano){
    Vector2 mostrar={getPosicion(gusano, 1).x,getPosicion(gusano, 1).y};
    DrawText("VALE",mostrar.x,mostrar.y,20,BLACK);
}


void gameState(List *gusano)
{
    //TITULO
    DrawText("Slither.io Prueba 626", 100, 100, 40, BLACK);

    //SCORE
    DrawText(TextFormat("Score: %d", getSize(gusano)),50,640,30,RED);

    //MAPA
    DrawCircle(120, 780, 103, BLACK);
    DrawCircle(120, 780, 100, RAYWHITE);
    DrawLine(20, 780, 220, 780, BLACK);//linea vertical
    DrawLine(120, 680, 120, 880, BLACK);//linea horizontal
    DrawCircle(((getPosicion(gusano,0).x)/40)+97.5,((getPosicion(gusano,0).y)/40)+768.75,5,RED);
}

