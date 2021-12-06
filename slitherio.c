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

Bloque *newBloque(Color color,int n, float radio){
    Bloque* new=malloc(sizeof(Bloque));
    new->color=color;
    new->alpha=1;
    new->posicion=(Vector2){ 100+5*n, 100+5*n};
    new->radio=radio;
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

Vector2 getRandomPosAfueras() {
    Vector2 n;
    do{
        n.x = GetRandomValue((-1)*worldSize, worldSize);
        n.y=GetRandomValue((-1)*worldSize, worldSize);
    }
    while ((n.x * n.x) + (n.y * n.y) > (worldSize * worldSize) && (n.x * n.x) + (n.y * n.y) > ((worldSize/2) * (worldSize/2)));
    return n;
}

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

void setRadio(List* gusano, float newValue){
    Node *focusNode = getHead(gusano);//index 0
    Bloque *ptr;
    for (int i = 0; i < getSize(gusano)-1; i++) {
        ptr= getValue(focusNode);
        ptr->radio=newValue;
        focusNode = getNext(focusNode);
    }
}

void changeRadio(List *gusano){
    Node *focusNode = getHead(gusano);
    Bloque *ptr;
    if(getSize(gusano)%10==0){
        for (int i = 0; i < getSize(gusano)-1; i++) {
            ptr= getValue(focusNode);
            ptr->radio=(ptr->radio)+growth;
            focusNode = getNext(focusNode);
        }
    }
}

Vector2 getPosicionGusano(List* gusano,int index){
    Node *focusNode = getHead(gusano);//index 0
    for (int i = 0; i < index; i++) {
        focusNode = getNext(focusNode);
    }
    Bloque *ptr = getValue(focusNode);
    return ptr->posicion;
}

Vector2 getPosicion(List* posiciones,int index){
    Node *focusNode = getHead(posiciones);//index 0
    for (int i = 0; i < index; i++) {
        focusNode = getNext(focusNode);
    }
    Vector2 *ptr = getValue(focusNode);
    return *ptr;
}

void setPosicion(List* posiciones, int index,Vector2 pos){
    Node *focusNode = getHead(posiciones);//index 0
    for (int i = 0; i < index; i++) {
        focusNode = getNext(focusNode);
    }
    Vector2* ptr= getValue(focusNode);
    *ptr=pos;
}

void setPosicionGusano(List* posiciones, int index,Vector2 pos){
    Node *focusNode = getHead(posiciones);//index 0
    for (int i = 0; i < index; i++) {
        focusNode = getNext(focusNode);
    }
    Bloque* ptr= getValue(focusNode);
    ptr->posicion=pos;
}




void inicializarBloque(Vector2 initialPositions[valorInicial], List *gusano){
    Color random1=(Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
    for(int i = 0; i<valorInicial;i++){//inicializar bloque
        addElement(gusano, newBloque(random1,i,20));
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
    Vector2 *pos= getElement(posiciones,0);
    Vector2 direction;
    direction= Vector2Add(Vector2Transformacion(mouse),*pos);
    return direction;
}

Vector2 Vector2Transformacion(Vector2 n){
    n.x=n.x-900;
    n.y=n.y-400;
    Vector2 resultado = {n.x/ Vector2Length(n),n.y/ Vector2Length(n)};//calcular unitario
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        return Vector2Scale(resultado,speed*2);
    }
    return Vector2Scale(resultado,speed);
}

void updateGusano(List *gusano,List *posiciones){
    for(int i =0; i< getSize(gusano);i++){
        setPosicionGusano(gusano,i,*(Vector2*)getElement(posiciones,i));
    }
}

Vector2 updatePosFakeGusano(List* posiciones, Vector2 *target){
    Vector2* posGusano = (Vector2*)getValue(getHead(posiciones));
    *posGusano= Vector2Add(*posGusano, Vector2Scale(Vector2Normalize(Vector2Subtract(*target,*posGusano)),speed));
    if(compareVector2(*target, *posGusano)){
        *target=getRandomPosAfueras();
    }
    return *posGusano;
}

void fakeGusanoFollowFood(List* fakeGusanos,Vector2 randomPosTodo[],Vector2 randomPosCentro[],Vector2 *target){
    for (int i = 0; i < nFood; i++) {//recorre toda la comida
        //1° checa si hay colision entre uno de los fake y comida detodo el mapa
        if (CheckCollisionCircles(getPosicionGusano(fakeGusanos, 0), getRadio(fakeGusanos) + radioFindFood, randomPosTodo[i],
                                  10)) {
            *target=randomPosTodo[i];
        }
        //2° checa si hay colisión entre uno de los fake y comida del centro
        if (CheckCollisionCircles(getPosicionGusano(fakeGusanos, 0), getRadio(fakeGusanos) + radioFindFood, randomPosCentro[i],
                                  10)){
            *target=randomPosCentro[i];
        }
    }
}

void fakeGusanoAvoidGusanos(List* fakeGusanos[],List* fakeGusano,Vector2 *target, int i, List *gusano){
    //checar colisiones con otros gusanos fake y evitarlas
    for(int j =0; j<nGusanos;j++){
        if(i!=j){
            for (int k = 0; k < getSize(fakeGusanos[j]) - 1; k++) {
                if (CheckCollisionCircles(getPosicionGusano(fakeGusano, 0), getRadio(fakeGusano)+radioAvoidGusano, getPosicionGusano(fakeGusanos[j], k), getRadio(fakeGusanos[j]))) {
                    *target= getRandomPosAfueras();
                }
            }
        }
    }
    //checar colisiones con gusano original y evitarlo
    for(int j=0;j< getSize(gusano)-1;j++){
        if(CheckCollisionCircles(getPosicionGusano(fakeGusano,0), getRadio(fakeGusano)+radioAvoidGusano, getPosicionGusano(gusano,j),getRadio(gusano))){
            *target=getRandomPosAfueras();
        }
    }
}




int compareVector2(Vector2 a, Vector2 b){
    if ((b.x>=a.x-7 && b.x<=a.x+7) && (b.y>=a.y-7 && b.y<b.y+7)){
        return 1;
    }
    return 0;
}

void checkBoundaries(List *posiciones, List *gusano, int *play){
    Vector2 *pos= getElement(posiciones,0);
    if(((pos->x) * (pos->x)) + ((pos->y) * (pos->y)) >= ((worldSize-10) * (worldSize-10))){
        while(getSize(gusano)!=valorInicial){
            removeLastElement(gusano);
            removeLastElement(posiciones);
        }
        setPosicion(posiciones,0,getRandomPosCentro());
        setRadio(gusano,radioInicial);
        *play=0;
    }
}



void checkCollisionGusanos(List *gusano, List *posiciones, List* fakeGusanos[], List *fakeGusanosPos[],int *play, int *count,Vector2 foodPosTodo[]){
    //CHECAR SI FAKE GUSANOS CHOCAN ENTRE SI
    for(int i=0;i<nGusanos;i++){
        for(int j =0; j<nGusanos;j++){
            if(i!=j) {
                for (int k = 0; k < getSize(fakeGusanos[j]) - 1; k++) {
                    if (CheckCollisionCircles(getPosicionGusano(fakeGusanos[i], 0), getRadio(fakeGusanos[i]),
                                              getPosicionGusano(fakeGusanos[j], k), getRadio(fakeGusanos[j]))) {
                        while (getSize(fakeGusanos[i]) != valorInicial) {
                            removeLastElement(fakeGusanos[i]);
                        }
                        gusanoFoodTrail(foodPosTodo,fakeGusanosPos[i],*count);
                        while (getSize(fakeGusanosPos[i]) != valorInicial) {
                            removeLastElement(fakeGusanosPos[i]);
                        }
                        setPosicion(fakeGusanosPos[i], 0, getRandomPosAfueras());
                        setRadio(fakeGusanos[i],radioInicial);
                    }
                }
            }
        }
    }
    //CHECAR SI GUSANO CHOCA CON FAKE GUSANOS
    for(int i=0;i<nGusanos;i++){
        for(int j=0;j< getSize(fakeGusanos[i])-1;j++){
            if(CheckCollisionCircles(getPosicionGusano(gusano,0), getRadio(gusano), getPosicionGusano(fakeGusanos[i],j), getRadio(fakeGusanos[i]))){
                while(getSize(gusano)!=valorInicial){
                    removeLastElement(gusano);
                    removeLastElement(posiciones);
                }
                setPosicion(posiciones,0,getRandomPosTodo());
                setRadio(gusano,radioInicial);
                *play=0;
            }
        }
    }
    //CHECAR SI FAKE GUSANOS CHOCAN CON GUSANO
    for(int i=0;i<nGusanos;i++){
        for(int j=0;j< getSize(gusano)-1;j++){
            if(CheckCollisionCircles(getPosicionGusano(fakeGusanos[i],0), getRadio(fakeGusanos[i]), getPosicionGusano(gusano,j),getRadio(gusano))){
                while (getSize(fakeGusanos[i]) != valorInicial) {
                    removeLastElement(fakeGusanos[i]);
                }
                gusanoFoodTrail(foodPosTodo,fakeGusanosPos[i],*count);
                while (getSize(fakeGusanosPos[i]) != valorInicial) {
                    removeLastElement(fakeGusanosPos[i]);
                }
                setRadio(fakeGusanos[i],radioInicial);
                setPosicion(fakeGusanosPos[i],0,getRandomPosAfueras());
            }
        }
    }
}



void gusanoFoodTrail(Vector2 foodPosTodo[], List* gusano, int count){
    for(int i=0; i< getSize(gusano);i++){
        if(count==nFood-1){
            count=0;
        }
        foodPosTodo[i+count] = getPosicion(gusano,i);
        count++;
    }

}

void checkCollisionFood(List *gusano, List *posiciones, List* fakeGusanos[], List *fakeGusanosPos[],Vector2 randomPosTodo[],Vector2 randomPosCentro[],Color random[]){
    for(int i =0; i<nFood;i++){//recorre toda la comida
        for(int j=0; j<nGusanos;j++){//recorrer a todos los gusanos fake
            //1° checa si hay colision entre uno de los fake y comida de todoel mapa
            if(CheckCollisionCircles(getPosicionGusano(fakeGusanos[j],0), getRadio(fakeGusanos[j]),randomPosTodo[i],10)){
                addElement(fakeGusanos[j], newBloque(getColor(fakeGusanos[j]),1, getRadio(fakeGusanos[j])));
                changeRadio(fakeGusanos[j]);
                addElement(fakeGusanosPos[j], newPos(getPosicionGusano(fakeGusanos[j], 1).x,getPosicionGusano(fakeGusanos[j], 1).y));
                randomPosTodo[i]=getRandomPosTodo();

            }
            //2° checa si hay colisión entre uno de los fake y comida del centro
            if(CheckCollisionCircles(getPosicionGusano(fakeGusanos[j],0), getRadio(fakeGusanos[j]),randomPosCentro[i],10)){
                addElement(fakeGusanos[j], newBloque(getColor(fakeGusanos[j]),1, getRadio(fakeGusanos[j])));
                addElement(fakeGusanosPos[j], newPos(getPosicionGusano(fakeGusanos[j], 1).x,getPosicionGusano(fakeGusanos[j], 1).y));
                changeRadio(fakeGusanos[j]);
                randomPosCentro[i]=getRandomPosCentro();
            }
        }
        //checa si gusano original colision con circulos en todoel mapa
        if(CheckCollisionCircles(getPosicionGusano(gusano,0), getRadio(gusano),randomPosTodo[i],10)){
            addElement(gusano, newBloque(getColor(gusano),1, getRadio(gusano)));
            addElement(posiciones, newPos(getPosicionGusano(gusano, 1).x,getPosicionGusano(gusano, 1).y));
            changeRadio(gusano);
            randomPosTodo[i]=getRandomPosTodo();
        }
        //checa si gusano original colisión con circulos en el centro
        if(CheckCollisionCircles(getPosicionGusano(gusano,0), getRadio(gusano),randomPosCentro[i],10)){
            addElement(gusano, newBloque(getColor(gusano),1, getRadio(gusano)));
            addElement(posiciones, newPos(getPosicionGusano(gusano, 1).x,getPosicionGusano(gusano, 1).y));
            changeRadio(gusano);
            randomPosCentro[i]=getRandomPosCentro();
        }
        //dibuja la comida
        DrawCircleV(randomPosTodo[i], 10, random[i]);
        DrawCircleV(randomPosCentro[i], 10, random[i]);
    }
}

void inicializarFood(Color foods[],Vector2 positionsCentro[], Vector2 positionsAll[],int n){
    for(int i=0;i<n;i++){
        foods[i]=getRandomColor();
        positionsCentro[i]=getRandomPosCentro();
        positionsAll[i]=getRandomPosTodo();
    }
}




void gameplayer(List *gusano,char player[]){
    Vector2 mostrar={getPosicionGusano(gusano, 1).x,getPosicionGusano(gusano, 1).y};
    DrawText(player ,mostrar.x,mostrar.y,20,BLACK);
}

void gameState(List *gusano)
{
    //TITULO

    //SCORE
    DrawText(TextFormat("Score: %d", getSize(gusano)-valorInicial),50,640,30,RED);

    //MAPA
    DrawCircle(120, 780, 110, BLACK);
    DrawCircle(120, 780, 107, LIGHTGRAY);
    DrawLine(15, 780, 225, 780, BLACK);//linea horizontal
    DrawLine(120, 675, 120, 885, BLACK);//linea vertical
    DrawCircle(((getPosicionGusano(gusano,0).x)/(worldSize/100))+120,((getPosicionGusano(gusano,0).y)/(worldSize/100))+780,5,RED);
}


void initCamera(Camera2D *camera, List *gusano) {
    camera->target = (Vector2) {getPosicionGusano(gusano, 0).x + 20.0f, getPosicionGusano(gusano, 0).y + 20.0f};
    camera->offset = (Vector2) {screenWidth / 2.0f, screenHeight / 2.0f};
    camera->rotation = 0.0f;
    camera->zoom = 0.5f;}

void starScreen(int sw, int* letterCount, char player[]){
    ClearBackground(BLACK);
    DrawText("Slither.io", 500, 190, 180,WHITE);
    DrawText("By Ana & Val", 800, 390, 30,WHITE);
    DrawText("Enter your name", 780, 450, 30,WHITE);
    int framesCounter=0;
    bool mouseOnText=false;
    Rectangle textBox={sw/2.0f-100,500,225,50};
    if(CheckCollisionPointRec(GetMousePosition(),textBox)){
        mouseOnText=true;
    }
    else{
        mouseOnText=false;
    }
    if(mouseOnText){
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key=GetCharPressed();
        while(key>0){
            if((key>=32)&&(key<=125)&&(*letterCount<maxInputChars)){
                player[*letterCount]=(char)key;
                player[*letterCount+1]='\0';
                (*letterCount)++;
            }
            key=GetCharPressed();
        }
        if(IsKeyPressed(KEY_BACKSPACE)){
            (*letterCount)--;
            if(*letterCount<0)
                *letterCount=0;
            player[*letterCount]='\0';
        }
    }
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if(mouseOnText)
        framesCounter++;
    else
        framesCounter=0;

    DrawRectangleRec(textBox,WHITE);
    DrawText(player, (int)textBox.x+5,(int)textBox.y+8,40,BLUE);

    if(mouseOnText){
        if(*letterCount<maxInputChars){
            if (((framesCounter/20)%2) == 0){
                DrawText("_", (int)textBox.x + 8 + MeasureText(player, 40), (int)textBox.y + 12, 40, MAROON);
            }
        }
    }
}

void drawGusano(List *gusano){
    for (int i = getSize(gusano)-1; i>0; i--) {
        DrawCircleV(getPosicionGusano(gusano, i), (getRadio(gusano)) + 2, DARKGRAY);
        DrawCircleV(getPosicionGusano(gusano, i), getRadio(gusano), getColor(gusano));
    }
}