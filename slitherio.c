//
// Created by luax2 on 20/11/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "slitherio.h"
#include "lists.h"


struct bloque{
    Color color;
    Vector2 posicion;
    float alpha;
    float radio;
};


Bloque *newBloque(Color color,int n){
    Bloque* new=malloc(sizeof(Bloque));
    new->color=color;
    new->alpha=1;
    new->posicion=(Vector2){ 100+5*n, 100+5*n};
    new->radio=20;
    return new;
}

Vector2 *newPos(float x, float y){
    Vector2 *new=malloc(sizeof (Vector2));
    new->x=x;
    new->y=y;
    return new;
}




Vector2 getRandomPosTodo(){
    Vector2 n;
    do{
        n.x = GetRandomValue((-1)*worldSize, worldSize);
        n.y=GetRandomValue((-1)*worldSize, worldSize);
    }
    while ((n.x * n.x) + (n.y * n.y) > (worldSize * worldSize));
    return n;
} //toda la pantalla

Vector2 getRandomPosCentro(){
    Vector2 n = {GetRandomValue(worldSize*0.707*(-1),worldSize*0.707), GetRandomValue(worldSize*0.707*(-1),worldSize*0.707)};
    return n;
}//centro

Color getRandomColor(){
    Color random1=(Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
    return random1;
}




Bloque* getBloque(List* list,int index){
    Node *focusNode = getHead(list);//index 0
    for (int i = 0; i < index; i++) {
        focusNode = getNext(focusNode);
    }
    Bloque *ptr = getValue(focusNode);
    return ptr;
}

Color getColor(List* gusano){
    Bloque *ptr = getValue(getHead(gusano));
    return ptr->color;
}

float getRadio(List* gusano){
    Bloque *ptr = getValue(getHead(gusano));
    return ptr->radio;
}

Vector2 getPosicion(List* gusano,int index){
    Node *focusNode = getHead(gusano);//index 0
    for (int i = 0; i < index; i++) {
        focusNode = getNext(focusNode);
    }
    Bloque *ptr = getValue(focusNode);
    return ptr->posicion;
}

void setPosicion(List* gusano, int index,Vector2 pos){
    Node *focusNode = getHead(gusano);//index 0
    for (int i = 0; i < index; i++) {
        focusNode = getNext(focusNode);
    }
    Bloque *ptr = getValue(focusNode);
    ptr->posicion=pos;
}



void inicializarBloque(Vector2 initialPositions[valorInicial], List *gusano){
    Color random1=(Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
    for(int i = 0; i<valorInicial;i++){//inicializar bloque
        addElement(gusano, newBloque(random1,i));
    }
}

void inicializarPosiciones(List *posiciones, Vector2 initialPositions[valorInicial],  Vector2 pInicial){
    for(int i = 0; i<valorInicial;i++){//inicializar posiciones
        initialPositions[i].x = pInicial.x + i;
        initialPositions[i].y = pInicial.y + i;
        addElement(posiciones, initialPositions+i);
    }

}


void inicializarFakeGusanos(List *fakeGusanos[],List *posicionesFakeGusanos[],Vector2 randomPos[nGusanos][valorInicial]){
    for(int i = 0; i<nGusanos;i++){
        randomPos[i][0]=getRandomPosTodo();
        fakeGusanos[i]=newList();
        inicializarBloque(randomPos[i],fakeGusanos[i]);
        posicionesFakeGusanos[i]=newList();
        inicializarPosiciones(posicionesFakeGusanos[i],randomPos[i],randomPos[i][0]);
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
    return Vector2Scale(resultado,speed);
}

void updateGusano(List *gusano,List *posiciones){
    for(int i =0; i< getSize(gusano);i++){
        setPosicion(gusano,i,*(Vector2*)getElement(posiciones,i));
    }
}


Vector2 updatePosFakeGusano(List* posiciones, Vector2 *pos){
    Vector2* posGusano = (Vector2*)getValue(getHead(posiciones));
    *posGusano= Vector2Add(*posGusano, Vector2Scale(Vector2Normalize(Vector2Subtract(*pos,*posGusano)),speed));
    if(compareVector2(*pos, *posGusano)){
        *pos=getRandomPosTodo();
    }
    return *posGusano;
}

int compareVector2(Vector2 a, Vector2 b){
    if ((b.x>=a.x-7 && b.x<=a.x+7) && (b.y>=a.y-7 && b.y<b.y+7)){
        return 1;
    }
    return 0;
}


void checkCollisionFood(List *gusano, List *posiciones, List* fakeGusanos[], List *fakeGusanosPos[],Vector2 randomPosTodo[],Vector2 randomPosCentro[],Color random[]){
    for(int i =0; i<nFood;i++){//recorre toda la comida
        for(int j=0; j<nGusanos;j++){//recorrer a todos los gusanos fake
            //1° checa si hay colision entre uno de los fake y comida de todoel mapa
            if(CheckCollisionCircles(getPosicion(fakeGusanos[j],0), getRadio(fakeGusanos[j]),randomPosTodo[i],10)){
                addElement(fakeGusanos[j], newBloque(getColor(fakeGusanos[j]),1));
                addElement(fakeGusanosPos[j], newPos(getPosicion(fakeGusanos[j], 1).x,getPosicion(fakeGusanos[j], 1).y));
                randomPosTodo[i]=getRandomPosTodo();

            }
            //2° checa si hay colisión entre uno de los fake y comida del centro
            if(CheckCollisionCircles(getPosicion(fakeGusanos[j],0), getRadio(fakeGusanos[j]),randomPosCentro[i],10)){
                addElement(fakeGusanos[j], newBloque(getColor(fakeGusanos[j]),1));
                addElement(fakeGusanosPos[j], newPos(getPosicion(fakeGusanos[j], 1).x,getPosicion(fakeGusanos[j], 1).y));
                randomPosCentro[i]=getRandomPosCentro();
            }
        }
        //checa si gusano original colision con circulos en todoel mapa
        if(CheckCollisionCircles(getPosicion(gusano,0), getRadio(gusano),randomPosTodo[i],10)){
            addElement(gusano, newBloque(getColor(gusano),1));
            addElement(posiciones, newPos(getPosicion(gusano, 1).x,getPosicion(gusano, 1).y));
            randomPosTodo[i]=getRandomPosTodo();
        }
        //checa si gusano original colisión con circulos en el centro
        if(CheckCollisionCircles(getPosicion(gusano,0), getRadio(gusano),randomPosCentro[i],10)){
            addElement(gusano, newBloque(getColor(gusano),1));
            addElement(posiciones, newPos(getPosicion(gusano, 1).x,getPosicion(gusano, 1).y));
            randomPosCentro[i]=getRandomPosCentro();
        }
        //dibuja la comida
        DrawCircleV(randomPosTodo[i], 10, random[i]);
        DrawCircleV(randomPosCentro[i], 10, random[i]);
    }
}


void foodPrep(Color foods[],Vector2 positionsCentro[], Vector2 positionsAll[],int n){
    for(int i=0;i<n;i++){
        foods[i]=getRandomColor();
        positionsCentro[i]=getRandomPosCentro();
        positionsAll[i]=getRandomPosTodo();
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
    DrawText(TextFormat("Score: %d", getSize(gusano)-10),50,640,30,RED);

    //MAPA
    DrawCircle(120, 780, 110, BLACK);
    DrawCircle(120, 780, 107, RAYWHITE);
    DrawLine(15, 780, 225, 780, BLACK);//linea horizontal
    DrawLine(120, 675, 120, 885, BLACK);//linea vertical
    DrawCircle(((getPosicion(gusano,0).x)/(worldSize/100))+120,((getPosicion(gusano,0).y)/(worldSize/100))+780,5,RED);
}