#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include <ctype.h>
#include<time.h>
#include<windows.h>
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
typedef struct nodo
{
    int n_reserva;
    char nombre[15];
    char destino[20];
    
    struct nodo *izq;
    struct nodo *der;
}NODO;
int global = 0;
/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/

void Color(int Background, int Text);
int buscar_destino(NODO *raiz, char viaje[], int cont);
void mostrar_mayor(NODO *raiz);

NODO *Buscar(NODO *node);
void buscar_reserva(NODO *raiz, int numero);
NODO *Cancelar(NODO *raiz, int reserva);

NODO *CrearArbol(NODO *nuevo, int reserva);
void mostrar_menu(char flecha[]);
int menu();
void inicio();

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/


NODO *Buscar(NODO *node) {
    NODO *actual = node;
    while (actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual;
}

NODO *Cancelar(NODO *raiz, int reserva) {
    if (raiz == NULL) return raiz;
    if (reserva < raiz->n_reserva) 
    {
        raiz->izq = Cancelar(raiz->izq, reserva);
    } else if (reserva > raiz->n_reserva) 
    {
        raiz->der = Cancelar(raiz->der, reserva);

    } else // Nodo encontrado, procedemos a eliminarlo
    {
        if (raiz->izq == NULL) // Caso 1: No tiene hijos o solo tiene un hijo
        {
            NODO* temp = raiz->der;
            free(raiz);
            return temp;
        } else if (raiz->der == NULL) 
        {
            NODO* temp = raiz->izq;
            free(raiz);
            return temp;
        }
        // Caso 2: Tiene dos hijos, buscamos el sucesor inorden
        NODO* aux = Buscar(raiz->der);
        raiz->n_reserva = aux->n_reserva;
        raiz->der = Cancelar(raiz->der, aux->n_reserva);
    }
    return raiz;
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

int buscar_destino(NODO *raiz, char viaje[], int cont){
	if(raiz!=NULL){
		buscar_destino(raiz->izq, viaje, cont);
        if (strcmp(viaje, raiz->destino) == 0)
        {
            cont = cont + 1;
            printf("\n%d ",raiz->n_reserva);
            printf("%s ", raiz->nombre);
            printf("%s ", raiz->destino);
        }
		buscar_destino(raiz->der, viaje, cont);
	}
    return cont;
}

void mostrar_mayor(NODO *raiz){
	if(raiz!=NULL){
		mostrar_mayor(raiz->izq);
		printf("\n%d ",raiz->n_reserva);
        printf("%s ", raiz->nombre);
        printf("%s ", raiz->destino);
		mostrar_mayor(raiz->der);
	}
}

void buscar_reserva(NODO *raiz, int numero)//FALTA
{
    if(raiz!=NULL){
        buscar_reserva(raiz->izq, numero);
        if (raiz->n_reserva == numero)
        {
            printf("\n%d ",raiz->n_reserva);
            printf("%s ", raiz->nombre);
            printf("%s ", raiz->destino);
            exit(0);
        }
        buscar_reserva(raiz->der, numero);
	}else if (raiz == NULL)
    {
        printf("\nRESERVA NO ENCONTRADA");
        return;
    }
}


NODO *CrearArbol(NODO *nuevo, int reserva)
{
	if(nuevo == NULL)
    {//SI EL NODO ES NULO SE CREA CON EL DATO INGRESADO
		nuevo = (NODO*)malloc(sizeof(NODO));
        printf("\nIngrese nombre del pasajero: ");
        scanf("%s", nuevo->nombre);
        fflush(stdin);
        printf("\nElija su destino: ");
        scanf("%s", nuevo->destino);
        fflush(stdin);
		nuevo->n_reserva = reserva;

		nuevo->der = NULL;
		nuevo->izq = NULL;
        printf("\nVIAJE CREADO CON EXITO");
        system("pause");
	}
    else if (nuevo->n_reserva < reserva) nuevo->der = CrearArbol(nuevo->der, reserva);//SI ES MAYOR EL DATO INGRESADO AL NODO ACTUAL, EL DATO SE MANDA AL NODO DERECHO
	else if(nuevo->n_reserva > reserva) nuevo->izq = CrearArbol(nuevo->izq, reserva);//SI ES MENOR EL DATO INGRESADO AL NODO ACTUAL, EL DATO SE MANDA AL NODO IZQUIERDO
	else if(reserva == nuevo->n_reserva) printf("\nIngrese valor no repetido\n"), system("pause");//SI HAY UN VALOR QUE ESTA REPETIDO SE LE DICE AL USUARIO QUE INGRESE OTRO VALOR
	return nuevo;//RETORNA EL ARBOL POR COMPLETO
}

void mostrar_menu(char flecha[])
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

void inicio()
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

/*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/
int main()
{
    srand(time(NULL));
    NODO *raiz = NULL;
    int reserva, flag = 0;
    char destino[20];
    inicio();
    system("pause");
    do
    {
        switch (menu())
        {
        case 0:
            printf("\nIngrese numero de boleto: ");
            scanf("%d", &reserva);
            fflush(stdin);
            raiz = CrearArbol(raiz, reserva);
            break;
        case 1://CANCELAR UNA RESERVA
            if (raiz != NULL)
            {
                printf("\nIngrese reserva a cancelar:");
                scanf("%d", &reserva);
                raiz = Cancelar(raiz, reserva);
            }else printf("\nNO EXISTEN RESERVAS ACTUALMENTE\n"), system("pause");
            
            break;
        case 2://BUSCAR REGISTRO DE RESERVA
            if (raiz != NULL)
            {
                printf("\nIngrese reserva a buscar: ");
                scanf("%d", &reserva);
                fflush(stdin);
                buscar_reserva(raiz, reserva);
                printf("\n");
                system("pause");
            }else printf("\nNO EXISTEN RESERVAS ACTUALMENTE\n"), system("pause");
            break;
        case 3://BUSCAR POR DESTINO
            if (raiz != NULL)
            {
                printf("\nIngrese destino a buscar: ");
                scanf("%s", destino);
                fflush(stdin);
                flag = buscar_destino(raiz, destino, 0);
                if (flag == 0)printf("\nDESTINO NO ENCONTRADO");
                
                system("pause");
            }else printf("\nNO EXISTEN RESERVAS ACTUALMENTE\n"), system("pause");
            break;
        case 4:
            if (raiz != NULL)//MOSTRAR RESERVAS ORDENADAS
            {
                mostrar_mayor(raiz);
                system("pause");
            }else printf("\nNO EXISTEN RESERVAS ACTUALMENTE\n"), system("pause");
            break;
        case 5:
            system("cls");
            Color(BLACK, RED);
            printf("Fin Del Programa.");
            exit(0);
            break;
        default:
            break;
        }
    } while (1);
    

}
