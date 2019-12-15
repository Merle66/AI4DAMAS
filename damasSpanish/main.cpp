#include<iostream>//Lib. que maneja entrada y salida cout/cin
#include<exception> //Lib. que me permite abortar el juego
using namespace std;
#define NO_JUGAR 0
#define ESPACIO_VACIO 1
#define FICHAS_BLANCAS 2
#define FICHAS_NEGRAS 3
#define DAMA_BLANCA 4
#define DAMA_NEGRA 5
#define FILAS 8
#define COLUMNAS 8

int intro();// Funcion que pinta y colorea a la Universidad Europea
void intercambio(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino);//Intercambia fichas
int turno(int matrix[][COLUMNAS], int jugador,int filaOrigen,int colOrigen,int filaDestino,int colDestino);//Gestiona los turno y movimientos
char simbolos(int i);//Me ayuda a rellenar mi matrix, convierte los numeros en simbolos
void tablero(int matrix[FILAS][COLUMNAS]);//Dibuja el tablero

int intro(){
    int op=0;
    cout << "\033[2J\033[1;1H";
    do{
        do{
            cout<<"\t\t_____________________________________________________________________"<<endl;
            cout<<"\t\t                                                                    "<<endl;
            cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISENO"<<endl;
            cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
            cout<<"\t\tProf.:Christian Sucuzhanay.                  Alumno : David Merle Sanroman"<<endl<<endl<<endl;
            cout<<"\t\t              << JUEGO DE LAS DAMAS ESPANOLAS >>"<<endl<<endl;
            cout<<"\t\t\t    ** SelepintarColione una opcion del menu [ 0-9] **"<<endl<<endl;
            cout<<"\t\t\t\t  [ 1 ] Ver reglas del juego "<<endl;
            cout<<"\t\t\t\t  [ 2 ] Jugar"<<endl;
            cout<<"\t\t\t\t  [ 0 ] SALIR"<<endl<<endl;
            cout<<"\t\t\t              Ingrese su opcion: ";
            cin>>op;
        } while (op<0||op>2);
        switch (op){
            case 1:
                cout<<"\t\t_____________________________________________________________________"<<endl;
                cout<<"\t\t                                                                    "<<endl;
                cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISENO"<<endl;
                cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
                cout<<"\t\tProf.:Christian Sucuzhanay.                  Alumno: David Merle Sanroman"<<endl<<endl<<endl;
                cout<<"\t\t            << REGLAS DEL JUEGO DE LAS DAMAS ESPANOLAS >>\n";
                cout<<"\t\t           ----------------------------------------------\n\n";
                cout<<"\t\t1.- Inician el juego las fichas blancas por defecto"<<endl<<endl;
                cout<<"\t\t2.- Las fichas SOLO se mueven 1 casilla  hacia ADELANTE (o varias si llega al otro extremo del"
                      "\t\t\t\t\t tablero hacia EN CUALQUIER DIRECCION) y siempre en DIAGONAL excepto al comer FICHA que pueden saltar\n\n";
                cout<<"\t\t3.- Las fichas SALTAN mas de una casilla  SOLO cuando haya una ficha\n ";
                cout<<"\t\t    contaria y la siguiente este vacia\n\n ";
                cout<<"\t\t4.- Gana quien coma mas fichas \n\n";
                cout<<"\t\t5.- Si pasan mas de 2 horas sin que nadie gane se declara EMPATE\n\n\n\n ";
                cout<<"\t\t\t\t PULSE [ 0 ] para SALIR: ";
                cin>>op;
                intro();
            case 2:
                break;
            case 0:
                abort();
        }
        return 0;
    }while(op!=0);
}

int turno(int matrix[FILAS][COLUMNAS], int jugador,int filaOrigen,int colOrigen,int filaDestino,int colDestino)//Gestiona movimientos y turnos
{
    int comerFichaBlancas;
    int comerFichaNegras;

    if((filaOrigen < 0 && FILAS <= filaOrigen)&&(colOrigen < 0 && COLUMNAS <= colOrigen)){ // Comprueba filas y col esten dentro del tablero
        cout<<"\n Estas fuera del tablero...\n";
        return -1;
    }
    if((filaDestino < 0 && FILAS <= filaDestino)&&(colDestino < 0 && COLUMNAS<= colDestino)){// Comprueba filas y col esten dentro del tablero
        cout<<"\n Estas fuera del tablero...\n";
        return -1;
    }

    if(jugador == FICHAS_BLANCAS || jugador == DAMA_BLANCA){//Comprueba que muevas solo donde haya blancas
        if(matrix[filaOrigen][colOrigen] != FICHAS_BLANCAS && matrix[filaOrigen][colOrigen] != DAMA_BLANCA){
            cout<<"\n <<< No tienes fichas ** BLANCAS **  en esa posicion >>>\n";
            return -1;
        }
    } else if(jugador == FICHAS_NEGRAS || jugador == DAMA_NEGRA){
        if(matrix[filaOrigen][colOrigen] != FICHAS_NEGRAS && matrix[filaOrigen][colOrigen] != DAMA_NEGRA){
            cout<<"\n <<< No tienes fichas ** NEGRAS **  en esa posicion >>>\n";
            return -1;
        }
    }

    if(matrix[filaDestino][colDestino] != ESPACIO_VACIO){//Comprueba que muevas solo espacios vacios.
        cout<<"\nSolo puedes mover a un espacio VACIO ( v )";
        return -1;
    }

    if(jugador == FICHAS_BLANCAS && matrix[filaOrigen][colOrigen] == FICHAS_BLANCAS){//Comprueba que el movimiento de las BLANCAS no sea hacia atras
        if(filaOrigen >= filaDestino){
            cout<<"\nNo puedes mover hacia atras o quedarte en el mismo lugar\n";
            return -1;
        }
    } else if(jugador == FICHAS_NEGRAS && matrix[filaOrigen][colOrigen] == FICHAS_NEGRAS){//Comprueba que el movimiento de las NEGRAS no sea hacia atras
        if(filaOrigen <= filaDestino){
            cout<<"\nNo puedes mover hacia atras o quedarte en el mismo lugar\n";
            return -1;
        }
    }
    //Comprueba si es un movimiento normal, una sola posicion
    if(jugador == FICHAS_BLANCAS || jugador == FICHAS_NEGRAS){
        if(filaOrigen - filaDestino == -1 || filaOrigen - filaDestino == 1){
            if(colOrigen - colDestino == 1 || colOrigen - colDestino == -1){
                intercambio(matrix,filaOrigen,colOrigen,filaDestino,colDestino);
                return 0;
            }
        }
    }

    //Comprobamos todos los posibles movimientos que una dama puede realizar
    if(jugador == DAMA_BLANCA || jugador == DAMA_NEGRA){
        if((abs(filaOrigen - filaDestino)) == (abs(colOrigen - colDestino))){
            int posibilidad;//Almacena el identificador que se corresponda al movimiento deseado por el jugador
            if((filaOrigen > filaDestino) && (colOrigen < colDestino)){
                posibilidad = 1;
            }else if((filaOrigen < filaDestino) && (colOrigen < colDestino)){
                posibilidad = 2;
            }else if((filaOrigen > filaDestino) && (colOrigen > colDestino)){
                posibilidad = 3;
            }else if((filaOrigen < filaDestino) && (colOrigen > colDestino)){
                posibilidad = 4;
            }
            if(posibilidad == 1){ //Permite mover la pieza hacia la derecha y hacia arriba
                for(int i = filaOrigen, j= colOrigen; (filaOrigen != filaDestino) && (colOrigen != colDestino);i--,j++){
                    if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMA_BLANCA))&&(matrix[i - 1][j + 1] == 1)){//Comprueba si la siguiente posicion esta vacia
                        matrix[i][j] = 1;//Permite comer la ficha dejando la posicion vacia
                        intercambio(matrix, filaOrigen, colOrigen, i - 1, j + 1);//Intercambia las posiciones
                        return 0;
                    }else if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMA_NEGRA))&&(matrix[i - 1][j + 1] == 1)){
                        matrix[i][j] = 1;
                        intercambio(matrix, filaOrigen, colOrigen, i - 1, j + 1);
                        return 0;
                    }
                }
                /* A PARTIR DE AQUÍ, APLICAMOS LA MISMA LÓGICA QUE EN "IF" ANTERIOR,
                 *       VARIANDO TANTO 'i' COMO 'j', DE MANERA QUE CUBRAMOS
                 *                 LAS TRES COMBINACIONES RESTANTES
                 *  1(Hecho) = (i--, j++), 2 = (i++, j++), 3 = (i--, j--), 4 = (i++, j--)
                 */
            }else if(posibilidad == 2){ //Permite mover la pieza hacia la derecha y hacia abajo
                for(int i = filaOrigen, j= colOrigen; (filaOrigen != filaDestino) && (colOrigen != colDestino);i++,j++){
                    if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMA_NEGRA))&&(matrix[i + 1][j + 1] == 1)){
                        matrix[i][j] = 1;
                        intercambio(matrix, filaOrigen, colOrigen, i + 1, j + 1);
                        return 0;
                    }else if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMA_BLANCA))&&(matrix[i + 1][j + 1] == 1)){
                        matrix[i][j] = 1;
                        intercambio(matrix, filaOrigen, colOrigen, i + 1, j + 1);
                        return 0;
                    }
                }
            }else if(posibilidad == 3){ //Permite mover la pieza hacia la izquierda y hacia arriba
                for(int i = filaOrigen, j= colOrigen; (filaOrigen != filaDestino) && (colOrigen != colDestino);i--,j--){
                    if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMA_NEGRA))&&(matrix[i - 1][j - 1] == 1)){
                        matrix[i][j] = 1;
                        intercambio(matrix, filaOrigen, colOrigen, i - 1, j - 1);
                        return 0;
                    }else if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMA_BLANCA))&&(matrix[i - 1][j - 1] == 1)){
                        matrix[i][j] = 1;
                        intercambio(matrix, filaOrigen, colOrigen, i - 1, j - 1);
                        return 0;
                    }
                }
            }else if(posibilidad == 4){ //Permite mover la pieza hacia la izquierda y hacia abajo
                for(int i = filaOrigen, j= colOrigen; (filaOrigen != filaDestino) && (colOrigen != colDestino);i++,j--){
                    if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMA_NEGRA))&&(matrix[i + 1][j - 1] == 1)){
                        matrix[i][j] = 1;
                        intercambio(matrix, filaOrigen, colOrigen, i + 1, j - 1);
                        return 0;
                    }else if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMA_BLANCA))&&(matrix[i + 1][j - 1] == 1)){
                        matrix[i][j] = 1;
                        intercambio(matrix, filaOrigen, colOrigen, i + 1, j - 1);
                        return 0;
                    }
                }
            }
        }
    }

    //Comprueba si ha comido ficha de adversario
    if(filaOrigen - filaDestino == -2 || filaOrigen - filaDestino == 2){
        if(colOrigen - colDestino == -2 || colOrigen - colDestino == 2){
            // Comprueba si en la posicion del salto hay ficha contraria
            if(filaOrigen < filaDestino){ // Movimiento hacia abajo
                comerFichaBlancas = filaOrigen + 1;
            } else { // Movimiento hacia arriba
                comerFichaBlancas = filaOrigen - 1;
            }
            if(colOrigen < colDestino){ // Movimiento hacia abajo
                comerFichaNegras = colOrigen + 1;
            } else { // Movimiento hacia arriba
                comerFichaNegras = colOrigen - 1;
            }
            if(jugador==FICHAS_BLANCAS && matrix[comerFichaBlancas][comerFichaNegras]!=FICHAS_NEGRAS)
            {
                cout<<"\nSolo puedes saltar si COMES FICHA\n"<<comerFichaBlancas<<comerFichaNegras;
                return -1;
            }
            if(jugador==FICHAS_NEGRAS && matrix[comerFichaBlancas][comerFichaNegras] != FICHAS_BLANCAS){
                cout<<"\nSolo puedes saltar si COMES FICHA\n";
                return -1;
            }
            matrix[comerFichaBlancas][comerFichaNegras] = 1;
            intercambio(matrix,filaOrigen,colOrigen,filaDestino,colDestino);
            return 0;
        }
    }
    cout<<"\nLas fichas solo se pueden mover DIAGONALMENTE\n";
    return -1;

}


void tablero(int matrix[FILAS][COLUMNAS])//Pinta tablero
{
    int pintarFilas, pintarCol;
    cout<<"\t\t_____________________________________________________________________"<<endl;
    cout<<"\t\t                                                                    "<<endl;
    cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISENO"<<endl;
    cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
        cout<<"\t\tProf.: Christian Sucuzhanay                  Alumno: David Merle Sanroman"<<endl<<endl<<endl;
    cout<<"\t\t                << TABLERO DE LAS DAMAS ESPANOLAS >>"<<endl<<endl;
    cout<<"\n\t\t\t\t     b = BLANCAS";
    cout<<"\n\t\t\t\t     n = NEGRAS";
    cout<<"\n\t\t\t\t     B = DAMA BLANCA";
    cout<<"\n\t\t\t\t     N = DAMA NEGRA";
    cout<<"\n\t\t\t\t     v = espacios VACIOS jugables";
    cout<<"\n\n\t\t\t\t   +---+---+---+---+---+---+---+---+\n";
    for (pintarFilas=0; pintarFilas<FILAS; ++pintarFilas)
    {
        cout<<"\t\t\t\t"<<  pintarFilas+1  <<"  | "; // Pinto filas
        for (pintarCol=0; pintarCol<COLUMNAS; ++pintarCol)
        {
            cout<<simbolos(matrix[pintarFilas][pintarCol])<< " | " ;//Rellenamos tablero
        }
        cout<<"\n";
        cout<<"\t\t\t\t   +---+---+---+---+---+---+---+---+\n";
    }
    cout<<"\n\t\t\t\t     a   b   c   d   e   f   g   h\n\n\n";//Imprime leyenda para de colunmnas
}


void intercambio(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino)//Cambia fichas en la matrix
{
    int temp;// Variable auxiliar que permite almacenar coordenadas
    if((filaDestino == 0) && (matrix[filaOrigen][colOrigen] == FICHAS_NEGRAS)) { //Comprueba si llega al limite del tablero para el cambiarlo a dama
        matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino]; //Resetea la posicion inicial
        matrix[filaDestino][colDestino] = DAMA_NEGRA; //Cambia la ficha por una dama
    }
    else if((filaDestino == 7) && (matrix[filaOrigen][colOrigen] == FICHAS_BLANCAS)) {
        matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino];
        matrix[filaDestino][colDestino] = DAMA_BLANCA;
    }
    else {
        temp = matrix[filaOrigen][colOrigen];
        matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino];
        matrix[filaDestino][colDestino] = temp;
    }
}

char simbolos(int i)//Cambia letras por numeros
{
    switch(i)
    {
        case 0:
            return ' ';//no jugable
        case 1:
            return 'v';//espacio vacio
        case 2:
            return 'b';//blancas
        case 3:
            return 'n';//negras
        case 4:
            return 'B';//damas blancas
        case 5:
            return 'N';//damas negras
    }
    return ('?');
}

#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main()//Programa principal
{
    int jugador;
    int filaOrigen, filaDestino;//Para almacernar las filas 1-8
    char colOrigen, colDestino;//Para almacenar el valor de las columnas que son a-h
    int matrix[FILAS][COLUMNAS]={//Matrix de fichas
            {0,2,0,2,0,2,0,2},
            {2,0,2,0,2,0,2,0},
            {0,2,0,2,0,2,0,2},
            {1,0,1,0,1,0,1,0},
            {0,1,0,1,0,1,0,1},
            {3,0,3,0,3,0,3,0},
            {0,3,0,3,0,3,0,3},
            {3,0,3,0,3,0,3,0}};//Tablero 0= vacio, 2=Blancas, 3=Negras
    intro();//Funcion que pinta
    for(;;)
    {//Bucle infinito para captura y validacion de coordenada de ficha
        tablero(matrix);//Dibujo el tablero, TURNO BLANCAS, le paso la matrix d para dibujar el tablero
        while(1){//Mientras no sean validas las coordenadas no sale de este while
            cout<<"\nTURNO de las * BLANCAS *\n \nIngrese una FILA 1-8 y una COLUMNA a-h de la ficha que desea mover --> EJEMPLO: 3b\n";
            cin>>filaOrigen>>colOrigen;//Capturo coordenada de origen Blancas
            colOrigen = tolower(colOrigen);//Permite que el usuario meta las columnas en MAYUSCULAS o minusculas
            cout<<"\nIntroduzca una FILA 1-8 y una COLUMNA a-h del destino de la ficha a mover --> EJEMPLO: 4a\n";
            cin>>filaDestino>>colDestino;//Capturo coordenada de destino Blancas
            colDestino = tolower(colDestino);
            if(matrix[filaOrigen - 1][colOrigen - 'a'] == FICHAS_BLANCAS){
                jugador = FICHAS_BLANCAS;
            }else if(matrix[filaOrigen - 1][colOrigen - 'a'] == DAMA_BLANCA){
                jugador = DAMA_BLANCA;
            }else{
                jugador = -1; //En caso de error
            }
            if(turno(matrix, jugador, filaOrigen - 1, colOrigen - 'a', filaDestino - 1,
                    colDestino - 'a') == 0)//Compruebo que sean validos las coordenadas
                break;
            cout<<"\nINTENTA de nuevo :\n";
        }

        tablero(matrix);//Dibujo el tablero, TURNO NEGRAS, le paso la matrix d para dibujar el tablero
        while(1){//Mientras no sean validas las coordenadas no sale de este while
            cout<<"\nTURNO de las  * NEGRAS *\n  \nIngrese una FILA 1-8 y una COLUMNA a-h de la ficha que desea mover  --> EJEMPLO: 6g\n";
            cin>>filaOrigen>>colOrigen;//Capturo coordenada de origen Negras
            colOrigen = tolower(colOrigen);
            cout<<"\nIntroduzca una FILA 1-8 y una COLUMNA a-h del destino de la ficha a mover --> EJEMPLO: 5h \n";
            cin>>filaDestino>>colDestino;//Capturo coordenada de destino Negras
            colDestino = tolower(colDestino);//Permite que el usuario meta las columnas en MAYUSCULAS o minusculas
            if(matrix[filaOrigen - 1][colOrigen - 'a'] == FICHAS_NEGRAS){
                jugador = FICHAS_NEGRAS;
            }else if(matrix[filaOrigen - 1][colOrigen - 'a'] == DAMA_NEGRA){
                jugador = DAMA_NEGRA;
            }else{
                jugador = -1; //En caso de error
            }
            if(turno(matrix, jugador, filaOrigen-1,colOrigen - 'a',filaDestino-1,
                    colDestino - 'a') == 0)
                break;
            cout<<"\nINTENTA de nuevo :\n)";
        }
    }
}
