#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<windows.h>
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
typedef struct nodo
{
    int n_reserva;
    char nombre[20];
    char destino[20];
    
    struct nodo *izq;
    struct nodo *der;
}NODO;
int global = 0;
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/

void pdc();
void res_creada();
void finprogram();
void treefree(NODO *rarbol);
void Color(int Background, int Text);
int buscar_destino(NODO *raiz, char viaje[], int cont);
void mostrar_mayor(NODO *raiz);

int sser(NODO *raiz,int numero, int cont);
NODO *Buscar(NODO *raiz);
int buscar_reserva(NODO *raiz, int numero, int cont);
NODO *Cancelar(NODO *raiz, int reserva);

NODO *CrearArbol(NODO *nuevo, int reserva);
void mostrar_menu(char flecha[]);
int menu();
void inicio();

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*DECORACION*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/

void pdc()
{
    system("cls");
    printf("                            ,--.\n");
    printf("                          {    }\n");
    printf("                          K,   }\n");
    printf("                         /  `Y`\n");
    printf("                    _   /   /\n");
    printf("                   {_'-K.__/\n");
    printf("                     `/-.__L._\n");
    printf("                     /  ' /`\\_}\n");
    printf("                    /  ' /    -RESERVA CANCELADA-\n");
    printf("            ____   /  ' /\n");
    printf("     ,-'~~~~    ~~/  ' /_\n");
    printf("   ,'             ``~~~%%',\n");
    printf("  (                     %%  Y\n");
    printf(" {                      %% I\n");
    printf("{      -                 %%  `.\n");
    printf("|       ',                %%  )\n");
    printf("|        |   ,..__      __. Y\n");
    printf("|    .,_./  Y ' / ^Y   J   )|\n");
    printf("\\           |' /   |   |   ||\n");
    printf(" \\          L_/    . _ (_,.'(\n");
    printf("  \\,   ,      ^^\"\"' / |      )\n");
    printf("    \\_  \\          /,L]     /\n");
    printf("      '-_`-,       ` `   ./`\n");
    printf("         `-(            )\n");
    printf("            ^^\\..___,.--`\n");
}
enum Colors { // Listado de colores (La letra "L" al inicio, indica que es un color m�s claro que su antecesor).
 BLACK = 0,
 BLUE = 1,
 GREEN = 2,
 CYAN = 3,
 RED = 4,
 MAGENTA = 5,
 BROWN = 6,
 LGREY = 7,
 DGREY = 8,
 LBLUE = 9,
 LGREEN = 10,
 LCYAN = 11,
 LRED = 12,
 LMAGENTA = 13,
 YELLOW = 14,
 WHITE = 15
};
void Color(int Background, int Text){ // Funci�n para cambiar el color del fondo y/o pantalla

 HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.

 // Para cambiar el color, se utilizan n�meros desde el 0 hasta el 255.
 // Pero, para convertir los colores a un valor adecuado, se realiza el siguiente c�lculo.
 int    New_Color= Text + (Background * 16);

 SetConsoleTextAttribute(Console, New_Color); // Guardamos los cambios en la Consola.

}
void res_creada()//FUNCION AL CREAR RESERVA
{
    printf("\n_*_*_*_*_*_*_*_*_*_*_*_*_*_*__*_*VIAJE CREADO CON EXITO_*_*_*_*_*_*_*_*_*_*_*_*_*_*_\n");
    printf("                             ==(W{==========-      /===-                        \n");
    printf("                              ||  (.--.)         /===-_---~~~~~~~~~------____  \n");
    printf("                              | \\_,|**|,__      |===-~___                _,-' ` \n");
    printf("                 -==\\\\        `\\ ' `--'   ),    `//~\\\\   ~~~~`---.___.-~~      \n");
    printf("             ______-==|        /`\\_. .__/>\\ \\    | |  \\\\           _-~`         \n");
    printf("       __--~~~  ,-/-==\\\\      (   | .  |~~~~|   | |   `\\        ,'             \n");
    printf("    _-~       /'    |  \\\\     )__/==0==-\\<>\\   / /      \\      /               \n");
    printf("  .'        /       |   \\\\      /~\\___/~~\\/  /' /        \\   /'                \n");
    printf(" /  ____  /         |    \\\\`.\\__/-~~   \\  |_/'  /          \\\\/'                 \n");
    printf("/-'~    ~~~~~---__  |     ~-/~         ( )   /'        _--~`                    \n");
    printf("                  \\_|      /        _) | ;  ),   __--~~                        \n");
    printf("                    '~~--_/      _-~/- |/ \\   '-~ \\                            \n");
    printf("                   {\\__--_/}    / \\\\_>-|)<__\\      \\                           \n");
    printf("                   /'   (_/  _-~  | |__>--<__|      |                          \n");
    printf("                  |   _/) )-~     | |__>--<__|      |                          \n");
    printf("                  / /~ ,_/       / /__>---<__/      |                          \n");
    printf("                 o-o _//        /-~_>---<__-~      /                           \n");
    printf("                 (^(~          /~_>---<__-      _-~                            \n");
    printf("                ,/|           /__>--<__/     _-~                               \n");
    printf("             ,//('(          |__>--<__|     /                  .----_          \n");
    printf("            ( ( '))          |__>--<__|    |                 /' _---_~\\        \n");
    printf("         `-)) )) (           |__>--<__|    |               /'  /     ~\\`\\      \n");
    printf("        ,/,'//( (             \\__>--<__\\    \\            /'  //        ||      \n");
    printf("      ,( ( ((, ))              ~-__>--<_~-_  ~--____---~' _/'/        /'       \n");
    printf("    `~/  )` ) ,/|                 ~-_~>--<_/-__       __-~ _/                  \n");
    printf("  ._-~//( )/ )) `                    ~~-'_/_/ /~~~~~~~__--~                    \n");
    printf("   ;'( ')/ ,)(                              ~~~~~~~~~~                         \n");
}
void finprogram()//FUNCION AL TERMINAR EL PROGRAMA
{
    printf("         ,     \\    /      ,        \n");
    printf("       / \\    )\\__/(     / \\       \n");
    printf("      /   \\  (_\\  /_)   /   \\      \n");
    printf(" ____/_____\\__\\@  @/___/_____\\____ \n");
    printf("|             |\\../|              |\n");
    printf("|              \\VV/               |\n");
    printf("|         Fin del programa        |\n");
    printf("|_________________________________|\n");
    printf(" |    /\\ /      \\\\       \\ /    | \n");
    printf(" |  /   V        ))       V   \\  | \n");
    printf(" |/     `       //        '     \\| \n");
    printf(" `              V                ' \n");
}
void mostrar_menu(char flecha[])//MENU BONITO QUE HICE
{
    char a = 175;
    Color(BLACK, DGREY);
    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    Color(BLACK, LGREY);
    printf("Bienvenido al sistema de transportes por dragon mas rapido del mundo\n");
    if (flecha[0] == a)Color(BLACK, YELLOW);
    else Color(BLACK, LGREY);
    printf("\n%c Realizar reserva", flecha[0]);
    if (flecha[1] == a)Color(BLACK, YELLOW);
    else Color(BLACK, LGREY);
    printf("\n%c Cancelar reserva", flecha[1]);
    if (flecha[2] == a)Color(BLACK, YELLOW);
    else Color(BLACK, LGREY);
    printf("\n%c Buscar vuelo por numero de reserva", flecha[2]);
    if (flecha[3] == a)Color(BLACK, YELLOW);
    else Color(BLACK, LGREY);
    printf("\n%c Buscar reservas por destino", flecha[3]);
    if (flecha[4] == a)Color(BLACK, YELLOW);
    else Color(BLACK, LGREY);
    printf("\n%c Mostrar listado de reservas", flecha[4]);
    Color(BLACK, RED);
    printf("\n%c Salir\n", flecha[5]);
    Color(BLACK, DGREY);
    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}
void inicio()//MENSAJE DE INTRO
{
    printf("\n*-*-*-*-**-*-*-* Bienvenido a *-*-*-**-*-*-*-*");
    Color(BLACK, RED);
    printf("\n     (                                   ");
    printf("\n     )\\ )                                ");
    printf("\n     (()/(   (       )  (  (              ");
    printf("\n     /(_))  )(   ( /(  )\\))(  (    (     ");
    printf("\n     (_)_)  (()\\  )(_))((_))\\  )\\   )\\ )  ");
    printf("\n     |   \\ (_(_)((_)_  ((_)((_) _(_/(  ");
    Color(BLACK, YELLOW);
    printf("\n     | |) || '_|/ _\\ |/ _ | / _ \\| ' \\)) ");
    printf("\n     (___/ |_|  \\__,_|\\__,| \\___/|_||_|  ");
    Color(BLACK, RED);
    printf("\n     )\\ )  (          |___/ )     )      ");
    printf("\n    (()/(  )\\ (   (  (   ( /(  ( /(      ");
    printf("\n     )_(_))((_))\\  )\\))(  )\\()) )\\())     ");
    printf("\n    ( ___| _ ((_)((_))  _  )\\(_))/      ");
    Color(BLACK, YELLOW);
    printf("\n    | |_  | | (_) ((_) | |_( | |_       ");
    printf("\n    | __| | | | |/ _ | |   \\ |  _|      ");
    printf("\n    |_|   |_| |_|\\__,| |_||_| \\__|      ");
    printf("\n                 |___/                   ");
    Color(BLACK, WHITE);
    printf("\n*-*-*-*-**-*-*-*-*-*-**-*-*-*-*-*-*-**-*-*-*-*\n");
}

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_UTILIDADES*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/

void treefree(NODO *rarbol){//LIBERAR MEMORIA/ARBOL
	if(rarbol!=NULL){
		treefree(rarbol->izq);
		treefree(rarbol->der);
		free(rarbol);
	}
}

int sser(NODO *raiz, int numero ,int cont)
{
    if(raiz!=NULL){
        if (raiz->n_reserva == numero) cont = cont + 1;
        buscar_reserva(raiz->izq, numero, cont);
        buscar_reserva(raiz->der, numero, cont);
	}
    return cont;
}
NODO *Buscar(NODO *raiz){//RETORNA EL ULTIMO NODO VACIO A LA IZQUIERDA
    NODO *actual = raiz;
    while (actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual;
}
NODO *Cancelar(NODO *raiz, int reserva) {//ELIMINACION INORDEN
    if (reserva < raiz->n_reserva) raiz->izq = Cancelar(raiz->izq, reserva);//recorre el lado izquierdo
    else if (reserva > raiz->n_reserva) raiz->der = Cancelar(raiz->der, reserva);//recorre el lado derecho
    else// Nodo encontrado, procedemos a eliminarlo
    {
        if (raiz->izq == NULL) // Caso 1: No tiene hijos o solo tiene un hijo
        {
            NODO* temp = raiz->der;
            free(raiz);
            Color(BLACK, YELLOW);
            pdc();
            Color(BLACK, DGREY);
            return temp;
        } else if (raiz->der == NULL) // Caso 1: No tiene hijos o solo tiene un hijo
        {
            NODO* temp = raiz->izq;
            Color(BLACK, YELLOW);
            free(raiz);
            Color(BLACK, DGREY);
            pdc();
            return temp;
        }
        // Caso 2: Tiene dos hijos, sucesor inorden
        NODO* aux = Buscar(raiz->der);
        raiz->n_reserva = aux->n_reserva;
        raiz->der = Cancelar(raiz->der, aux->n_reserva);
    }
    return raiz;
}

int buscar_destino(NODO *raiz, char viaje[], int cont){
	if(raiz!=NULL){
		cont = buscar_destino(raiz->izq, viaje, cont);
        if (strcmp(viaje, raiz->destino) == 0)
        {
            cont = cont + 1;
            Color(BLACK, YELLOW);
            if (cont == 1) printf("+--------+--------------------+--------------------+\n| Boleto |     Aventurero     |      Destino       |\n+--------+--------------------+--------------------+");
            printf("\n|"), Color(BLACK, DGREY), printf("%*d",-8,raiz->n_reserva), Color(BLACK, YELLOW), printf("|");
            Color(BLACK, DGREY), printf("%*s",-20,raiz->nombre), Color(BLACK, YELLOW), printf("|");
            Color(BLACK, DGREY), printf("%*s",-20,raiz->destino), Color(BLACK, YELLOW), printf("|");
            printf("\n+--------+--------------------+--------------------+");
        }
		cont = buscar_destino(raiz->der, viaje, cont);
	}
    return cont;
}

void mostrar_mayor(NODO *raiz){//MUESTRA VUELOS EN INORDEN O DE MENOR A MAYOR
	if(raiz!=NULL){
		mostrar_mayor(raiz->izq);
        Color(BLACK, YELLOW);
        printf("\n|"), Color(BLACK, DGREY), printf("%*d",-8,raiz->n_reserva), Color(BLACK, YELLOW), printf("|");
        Color(BLACK, DGREY), printf("%*s",-20,raiz->nombre), Color(BLACK, YELLOW), printf("|");
        Color(BLACK, DGREY), printf("%*s",-20,raiz->destino), Color(BLACK, YELLOW), printf("|");
        printf("\n+--------+--------------------+--------------------+");
		mostrar_mayor(raiz->der);
	}
}

int buscar_reserva(NODO *raiz, int numero, int cont)//BUSCA RESERVA POR NUMERO DE VUELO
{
    if(raiz!=NULL){
        cont = buscar_reserva(raiz->izq, numero, cont);
        if (raiz->n_reserva == numero)
        {
            cont = cont + 1;
            Color(BLACK, YELLOW);
            if (cont == 1) printf("+--------+--------------------+--------------------+\n| Boleto |     Aventurero     |      Destino       |\n+--------+--------------------+--------------------+");
            printf("\n|"), Color(BLACK, DGREY), printf("%*d",-8,raiz->n_reserva), Color(BLACK, YELLOW), printf("|");
            Color(BLACK, DGREY), printf("%*s",-20,raiz->nombre), Color(BLACK, YELLOW), printf("|");
            Color(BLACK, DGREY), printf("%*s",-20,raiz->destino), Color(BLACK, YELLOW), printf("|");
            printf("\n+--------+--------------------+--------------------+\n");
            Color(BLACK, DGREY);
        }
        cont = buscar_reserva(raiz->der, numero, cont);
	}
    return cont;
}

NODO *CrearArbol(NODO *nuevo, int reserva)// CREA EL ARBOL E INSERTA NODOS
{
	if(nuevo == NULL)
    {//SI EL NODO ES NULO SE CREA CON EL DATO INGRESADO
		nuevo = (NODO*)malloc(sizeof(NODO));
        Color(BLACK, YELLOW);
        printf("\nIngrese nombre del pasajero: ");
        Color(BLACK, DGREY);
        fgets(nuevo->nombre, sizeof(nuevo->nombre), stdin);
        nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0';
        //scanf("%s", nuevo->nombre);
        fflush(stdin);
        Color(BLACK, YELLOW);
        printf("\nElija su destino: ");
        Color(BLACK, DGREY);
        fgets(nuevo->destino, sizeof(nuevo->destino), stdin);
        fflush(stdin);
        nuevo->destino[strcspn(nuevo->destino, "\n")] = '\0';
		nuevo->n_reserva = reserva;//ingresa numero de RESERVA
		nuevo->der = NULL;
		nuevo->izq = NULL;
        Color(BLACK, YELLOW);
        system("cls");
        res_creada();
        Color(BLACK, DGREY);
        system("pause");
	}
    else if (nuevo->n_reserva < reserva) nuevo->der = CrearArbol(nuevo->der, reserva);//SI ES MAYOR EL DATO INGRESADO AL NODO ACTUAL, EL DATO SE MANDA AL NODO DERECHO
	else if(nuevo->n_reserva > reserva) nuevo->izq = CrearArbol(nuevo->izq, reserva);//SI ES MENOR EL DATO INGRESADO AL NODO ACTUAL, EL DATO SE MANDA AL NODO IZQUIERDO
	else if(reserva == nuevo->n_reserva) printf("\nValor repetido o incorrecto\n"), system("pause");//SI HAY UN VALOR QUE ESTA REPETIDO SE LE DICE AL USUARIO QUE INGRESE OTRO VALOR
	return nuevo;//RETORNA EL ARBOL POR COMPLETO
}

int menu()
{
    char flecha[6] = {175,32,32,32,32,32};
    int i = 0;
    do
    {
        system("cls");
        mostrar_menu(flecha);
        switch (tolower(getch()))
        {
        case 'w':
            if (i > 0)
            {
                flecha[i] = 32;
                i = i - 1;
                flecha[i] = 175;
            }
            
            break;
        case 's':
            if (i < 5)
            {
                flecha[i] = 32;
                i = i + 1;
                flecha[i] = 175;
            }        
            break;
        case 13:
            return i;
            break;
        default:
            break;
        }
    } while (1);
}

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
int main()
{
    srand(time(NULL));
    NODO *raiz = NULL;
    int reserva, flag;
    char destino[20];
    inicio();
    system("pause");
    do
    {
        switch (menu())
        {
        case 0://AGREGAR RESERVA
            Color(BLACK, YELLOW);
            printf("\nIngrese numero de boleto: ");
            Color(BLACK, DGREY);
            scanf("%d", &reserva);
            fflush(stdin);
            raiz = CrearArbol(raiz, reserva);
            break;
        case 1://CANCELAR UNA RESERVA
            if (raiz != NULL)
            {
                flag = 0;
                Color(BLACK, YELLOW);
                printf("\nIngrese reserva a cancelar: ");
                Color(BLACK, DGREY);
                scanf("%d", &reserva);
                fflush(stdin);
                flag = sser(raiz, reserva, 0);
                if (flag != 0)
                {
                    raiz = Cancelar(raiz, reserva);
                }else
                {
                    Color(BLACK, YELLOW);
                    printf("\nRESERVA NO ENCONTRADA");
                    Color(BLACK, DGREY);
                }
                printf("\n");
                system("pause");
            }else Color(BLACK, YELLOW), printf("\nNO EXISTEN RESERVAS ACTUALMENTE\n"), Color(BLACK, DGREY), system("pause");
            
            break;
        case 2://BUSCAR REGISTRO DE RESERVA
            if (raiz != NULL)
            {
                flag = 0;
                Color(BLACK, YELLOW);
                printf("\nIngrese numero de reserva a buscar: ");
                Color(BLACK, DGREY);
                scanf("%d", &reserva);
                fflush(stdin);
                flag = buscar_reserva(raiz, reserva, 0);
                if (flag == 0)printf("\nDESTINO NO ENCONTRADO\n");
                system("pause");
            }else Color(BLACK, YELLOW), printf("\nNO EXISTEN RESERVAS ACTUALMENTE\n"), Color(BLACK, DGREY), system("pause");
            break;
        case 3://BUSCAR POR DESTINO
            if (raiz != NULL)
            {
                flag = 0;
                Color(BLACK, YELLOW);
                printf("\nIngrese destino a buscar: ");
                Color(BLACK, DGREY);
                fgets(destino, sizeof(destino), stdin);
                fflush(stdin);
                destino[strcspn(destino, "\n")] = '\0';
                flag = buscar_destino(raiz, destino, 0);
                if (flag == 0) printf("\nDESTINO NO ENCONTRADO\n");
                printf("\n");
                Color(BLACK, DGREY);
                system("pause");
            }else Color(BLACK, YELLOW), printf("\nNO EXISTEN RESERVAS ACTUALMENTE\n"), Color(BLACK, DGREY), system("pause");
            break;
        case 4:
            if (raiz != NULL)//MOSTRAR RESERVAS ORDENADAS
            {
                Color(BLACK, YELLOW);
                printf("+--------+--------------------+--------------------+\n| Boleto |     Aventurero     |      Destino       |\n+--------+--------------------+--------------------+");
                mostrar_mayor(raiz);
                printf("\n");
                Color(BLACK, DGREY);
                system("pause");
            }else Color(BLACK, YELLOW), printf("\nNO EXISTEN RESERVAS ACTUALMENTE\n"), Color(BLACK, DGREY), system("pause");
            break;
        case 5:
            system("cls");
            Color(BLACK, RED);
            finprogram();
            printf("Fin Del Programa.");
            treefree(raiz);
            exit(0);
            break;
        default:
            break;
        }
    } while (1);
}
