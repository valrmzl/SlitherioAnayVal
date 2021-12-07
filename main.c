#include "raylib.h"
#include "slitherio.h"
#include "lists.h"

int main() {
    int play=0;
    int letter=0;
    int countTrail=0;
    char player[maxInputChars]="\0";
    InitWindow(screenWidth, screenHeight, "Sliter.io -- Ana y Valeria");

    SetTargetFPS(30);
    //--------------------------------------------------------------------------------------

    Color foodsColores[nFood];
    Vector2 randomCirclesCentro[nFood];//centro
    Vector2 randomCirclesTodo[nFood];//toda la pantalla
    inicializarFood(foodsColores,randomCirclesCentro,randomCirclesTodo,nFood);

    Vector2 pInicial = { 100.0f, 100.0f };
    Vector2 initialPositions[valorInicial];
    initialPositions[0] = pInicial;
    List *posiciones = newList();
    List *gusano = newList();
    inicializarBloque(initialPositions,gusano);
    inicializarPosiciones(posiciones,initialPositions,pInicial);

    Vector2 randomPosF[nGusanos][valorInicial];
    List* fGusano[nGusanos];
    List* fGusanoPos[nGusanos];
    int randomSizes[nGusanos];
    inicializarFakeGusanos(fGusano,fGusanoPos,randomPosF);

    Camera2D camera;
    initCamera(&camera,gusano);


    //TARGET HACIA DONDE SE MUEVEN FAKE GUSANOS, DENTRO DE LOS LIMITES DEL MUDNO
    Vector2 fakeGusanoTarget[nGusanos];
    for(int i=0;i<nGusanos;i++){
        fakeGusanoTarget[i]=getRandomPosTodo();
    }

    // Main game loop
    while (!WindowShouldClose())
    {

        //UPDATE GUSANO
        updateListaP(posiciones, mouseMovement(GetMousePosition(),posiciones));
        updateGusano(gusano,posiciones);

        //UPDATE FAKE GUSANOS
        for(int i =0; i<nGusanos;i++){
            updateListaP(fGusanoPos[i],updatePosFakeGusano(fGusanoPos[i],&fakeGusanoTarget[i]));
            updateGusano(fGusano[i],fGusanoPos[i]);
            fakeGusanoFollowFood(fGusano[i], randomCirclesTodo, randomCirclesCentro,&fakeGusanoTarget[i]);
            fakeGusanoAvoidGusanos(fGusano,fGusano[i],&fakeGusanoTarget[i], i,gusano);
        }

        checkCollisionGusanos(gusano, posiciones, fGusano, fGusanoPos,&play,&countTrail,randomCirclesTodo,foodsColores);

        checkBoundaries(posiciones,gusano,&play);
        camera.target = (Vector2){getPosicionGusano(gusano,1).x , getPosicionGusano(gusano,1).y};
        BeginDrawing();

        if(play==0)
            starScreen(screenWidth,&letter, player);

        if(IsKeyPressed(KEY_SPACE)|| IsKeyPressed(KEY_ENTER))
            play=1;

        if(play) {
            ClearBackground(BLACK);
            BeginMode2D(camera);

            //CIRCULO/MAPA DE JUEGO
            DrawCircle(0, 0, worldSize + 70,RED);
            DrawCircle(0, 0, worldSize+20, LIGHTGRAY);

            //CUERPO GUSANO
            drawGusano(gusano);

            //CUERPO GUSANOS FAKE
            for (int j = 0; j < nGusanos; j++) {
                drawGusano(fGusano[j]);
            }

            //COMIDA
            checkCollisionFood(gusano, posiciones, fGusano, fGusanoPos, randomCirclesTodo, randomCirclesCentro,foodsColores);

            //NOMBRE
            gameplayer(gusano,player);

            EndMode2D();

            //MAPA, SCORE
            gameState(gusano);
        }
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
