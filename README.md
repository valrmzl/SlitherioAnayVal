# SlitherioAnayVal

Implementaci贸n en C del juego de internet Slither.io, usando librer铆a gr谩fica Raylib. 
## Comenzando 馃殌

### Pre-requisitos 馃搵
Tener la librer铆a gr谩fica de Raylib instalada y un compilador de C, en nuestro caso usamos Visual Studio. 

## Wiki 馃摉
Constantes | Descripci贸n 
--- | --- 
valorInicial | Tama帽o inicial de gusanos, default 10.
nFood | Cantidad de comida durante el juego, considere que es el doble ya que hay dos arreglos de comida. 
nGusanos | Cantidad de gusanos de I.A. en el juego, recomendamos entre 10-50 pero funciona perfectamente hasta con 80
worldSize | Radio (en pixeles) del mundo en el que se podra jugar.
speed | Velocidad (en pixeles por frame) a la que se mueven los gusanos.
screenWidth | Ancho de la pantalla (en pixeles) recomendamos 1800.
screenHeight | Alto de la pantalla (en pixeles) recomendamos 900.
maxInputChars | Cantidad de caracteres disponible para el nombre de jugador.
growth  | Crecimiento del radio del gusano (en pixeles) recomendamos 1.
radioInicial | Radio inicial de los gusanos (en pixeles) recomendamos 20.
radioFindFood | Radio de deteccion de comida (en pixeles) recomendamos 100. 
radioAvoidGusano | Radio de detecci贸n y evasi贸n entre gusanos I.A. (en pixeles) recomendamos 30.



Estructuras | Descripci贸n 
--- | --- 
Bloque | Elementos que componen el gusano, cada uno tiene color, posici贸n, radio. 



Funciones | Descripci贸n 
--- | --- 
void starScreen(int sw,int* letterCount,char player[]); | Funci贸n que permite visualizar la pantalla principal, se recibe el nombre del jugador.
void initCamera(Camera2D* camera, List* gusano); | Funci贸n que inicializar la c谩mara 2D.
void inicializarBloque(Vector2 initialPositions[valorInicial], List* gusano); | Recibe un arreglo de posiciones y lista din谩mica del cuerpo de gusano original, inicializa bloque del cuerpo del gusano con las posiciones del arreglo, color random y radioInicial. 
void inicializarPosiciones(List* posiciones,Vector2 initialPositions[valorInicial],Vector2 pInicial);| Inicializa posiciones para gusano original.
void inicializarFakeGusanos(List* fakeGusanos[],List* posicionesFakeGusanos[],Vector2 randomPos[nGusanos][valorInicial]);| Inicializa cuerpo de gusanos I.A. y sus posiciones con listas din谩micas.
void inicializarFood(Color foods[],Vector2 positionsCentro[], Vector2 positionsAll[],int n); | Funci贸n que inicializa 2 arreglos de comida de tama帽o nFood cada uno.
Vector2 getRandomPosTodo(); | Funci贸n que permite posicionar gusanos o comida en todo el worldSize.
void gameState(List* gusano); | Funci贸n que muestra el score de la longitud del gusano y el mapa de ubicaci贸n.
void gameplayer(List* gusano, char player[]); | Funci贸n que muestra el nombre del jugador a un costado del gusano.
void drawGusano(List* gusano); | Funci贸n que se encarga de dibujar gusano.
void updateGusano(List* gusano,List* posiciones);  | Funci贸n que actualiza las posici贸nes que el mouse debe de seguir.
Vector2 updatePosFakeGusano(List* posiciones, Vector2* target);  | Funci贸n que permite los movimientos de gusanos de IA.
Vector2 getPosicionGusano(List* gusano,int index); | Recibe lista din谩mica del cuerpo del gusano y 铆ndice para seleccionar el elemento que regresar谩 la posici贸n. 
Vector2 mouseMovement(Vector2 mouse, List* posiciones);  |Funci贸n que permite que el gusano siga la direcci贸n del mouse.
void checkBoundaries(List* posiciones, List* gusano, int* play);  | Si el gusano tiene colisi贸n con los limites del wordlSize el gusano muere, se reincia partida.
void checkCollisionGusanos(List* gusano, List* posiciones, List* fakeGusanos[], List* fakeGusanosPos[],int* play,int* count,Vector2 foodPosTodo[]);  | Funci贸n que revisa si hay alg煤n tipo de colisi贸n, ya sea entre gusanos de IA, o del gusano con uno de IA.
void checkCollisionFood(List* gusano, List* posiciones, List* fakeGusanos[], List* fakeGusanosPos[],Vector2 randomPosTodo[],Vector2 randomPosCentro[],Color random[]); | Fucni贸n que detecta si hay colisiones entre cualquier tipo de gusano y comida en el mundo.
void fakeGusanoFollowFood(List* fakeGusanos,Vector2 randomPosTodo[],Vector2 randomPosCentro[],Vector2* target);  | Funci贸n que se encarga que un gusano de IA busque comida cercana.
void fakeGusanoAvoidGusanos(List* fakeGusanos[],List* fakeGusano, Vector2* target,int i, List* gusano,int* flag);  | Funci贸n que se encarga de que un gusano de IA evite colisionar con otro gusano a partir de un cambio de posici贸n.



## Versionado 馃搶

Para todas las versiones disponibles, mira los [commits en este repositorio](https://github.com/anamariaag/experiments/commits/master).

## Autores 鉁掞笍

* **Valeria Ram铆rez** - *Developer* - [valrmzl](https://github.com/valrmzl)
* **Ana Mar铆a Anaya** - *Developer* - [anamariaag](https://github.com/anamariaag)


## Licencia 馃搫
Si nos van a copiar m铆nimo pidan permiso, grax.

## Expresiones de Gratitud 馃巵

* Gracias Josean por ayudarnos este semestre y debuggearnos todo el proyecto, vales mil. 
* Agradecimientos adicionales a nuestros compa帽eros @sebas, @pablito. @iker, @tia, @chris, @lolo por no dejarnos morir este semestre los tqm.


---
鈱笍 con 鉂わ笍 por [anamariaag7](https://www.instagram.com/anamariaag7/) &&  [valrmzl](https://www.instagram.com/valrmzl/) 馃槉
