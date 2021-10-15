#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MAX_NOMBRE 26
#define MAX_CEDULA 9
#define MAX_JUEGOS 1000
#define SALDO_INICIAL 2000

using namespace std;

enum resJuego{Acerto,Fallo};

//ESTRCUTURA PARA GUARDAR LA INFO DEL JUGADOR.
struct datos_juego
{
char s_nombre[MAX_NOMBRE];
char s_cedula[MAX_CEDULA];
int s_copa_sorteada;
int s_copa_elegida;
int s_monto_apostado;
enum resJuego res;
};

//ESTRUCTURA PARA TOPE.
typedef struct resultados
{
datos_juego resultado_arr[MAX_JUEGOS];
int tope;
}tipo_resultados;

//DECLARACION DE LAS FUNCIONES.
void opcion1(char nombre[],char cedula[],bool &regDatos);
void opcion2(char nombre[],char cedula[],bool &regDatos, bool &regJuegos,tipo_resultados &resultado,int &mg,int &mp);
void opcion3(tipo_resultados &resultado);
void opcion4(int mg, int mp);

//MAIN
int main(int argc, char *argv[])
{
int opcion=0;//LA INICIALIZO EN CERO PARA QUE NO ACEPTE LETRAS EN LA ENTRADA.
bool regDatos=false;
bool regJuegos=false;
char nombre[MAX_NOMBRE];
char cedula[MAX_CEDULA];
tipo_resultados resultado;
int mg=0;//MONTO GANADO POR LA CASA DE APUESTAS. LO PASAMOS POR REFERENCIA PARA CALCULARLO EN F2.
int mp=0;//MONTO PERDIDO POR LA CASA DE APUESTAS. LO PASAMOS POR REFERENCIA PARA CALCULARLO EN F2.
resultado.tope=0;
printf("\n");
printf(" << BIENVENIDO AL JUEGO DE LA MOSQUETA >>\n\n");
printf(" Por favor marque una de las siguientes opciones:\n");
do{
   printf("\n");
   printf(" MENU OPCIONES.\n");
   printf(" 1 Registrarse como jugador.\n");
   printf(" 2 Jugar.\n");
   printf(" 3 Listar los juegos realizados.\n");
   printf(" 4 Listar el total ganado y el total perdido por la casa de apuestas.\n");
   printf(" 5 Salir del juego.\n\n");
   printf(" OPCION: ");
   fflush stdin;//LIMPIO LA ENTRADA PARA NO CAUSAR ERRORES.
   scanf("%d", &opcion);
   switch(opcion){
                  case 1:
                         opcion1(nombre,cedula,regDatos);
                  break;
                  case 2:
                         if(!regDatos)
                         {
                         printf("\n");
                         printf(" Antes de jugar debe ingresar los datos del juegador en la opcion1.\n");
                         }else
                         opcion2(nombre,cedula,regDatos,regJuegos,resultado,mg,mp);
                  break;
                  case 3:
                         if(!regJuegos)
                         {
                         printf("\n");
                         printf(" No se han realizado juegos.\n");
                         }else
                         {
                         printf("\n");
                         printf(" Historico de juegos realizados.\n");
                         opcion3(resultado);
                         }
                  break;
                  case 4:
                         if(!regJuegos)
                         {
                         printf("\n");
                         printf(" No se han realizado juegos.\n");
                         }else
                         opcion4(mg,mp);
                  break;
                  case 5:
                         if(!regDatos || regDatos)
                         {
                         printf("\n");
                         printf(" Saliendo...\n\n");
                         }
                  break;
                  default:
                          printf("\n");
                          printf(" Error, ingrese una de las 5 opciones.\n");
                  break;
    }
}while((opcion==1 || opcion==2 || opcion==3 || opcion==4) || (opcion!=1 && opcion!=2 && opcion!=3 && opcion!=4 && opcion!=5));
system("PAUSE");
return EXIT_SUCCESS;
}

//FUNCION 1. REGISTRO DEL JUGADOR.
void opcion1(char nombre[],char cedula[],bool &regDatos)
{
int largo_nombre=0;
int largo_cedula=0;
//INGRESO DEL NOMBRE.
do{
   printf("\n");
   printf(" Ingrese su nombre: ");
   printf("\n");
   fflush stdin;
   gets(nombre);
   largo_nombre=strlen(nombre);//LO USO PARA CONTROLAR LA CANTIDAD DE CARACTERES INGRESADAS.
   if(largo_nombre==0 || largo_nombre==' ')
   {
   printf(" El nombre no puede ser vacio.\n");
   }else
        if(largo_nombre>25)//CONTROLO EL MÁXIMO PARA NO PASARME DEL ARRAY Y GENERAR ERRORES EN EL PROG.
        {
        printf("\n");
        printf(" Error, el nombre no puede tener mas de 25 caracteres.\n");
        }
}while(largo_nombre==0 || largo_nombre==' ' || largo_nombre>25);
//INGRESO DE LA CEDULA.
do{
   printf("\n");
   printf(" Ingrese su cedula de identidad: ");
   printf("\n");
   fflush stdin;
   gets(cedula);
   largo_cedula=strlen(cedula);//LO USO PARA CONTROLAR LA CANTIDAD DE CARACTERES INGRESADAS.
   if(largo_cedula==0 || largo_cedula==' ')
   {
   printf(" La cedula no puede ser vacia.\n");
   }else
        if(largo_cedula>8)//CONTROLO EL MÁXIMO PARA NO PASARME DEL ARRAY Y GENERAR ERRORES EN EL PROG.
        {
        printf("\n");
        printf(" Error, la cedula no puede tener mas de 8 caracteres.\n");
        }
}while(largo_cedula==0 || largo_cedula==' ' || largo_cedula>8);
regDatos=true;//LO PONGO EN TRUE, HABILITANDO A ELEGIR LA OPCION 2 LUEGO DE REGISTRARSE.
//LO ARRANCO EN FALSE EN EL MAIN() PARA QUE NO PUEDA JUGAR SIN REGISTRARSE ANTES.
}
//FUNCION 2. JUGAR.
void opcion2(char nombre[],char cedula[],bool &regDatos,bool &regJuegos, tipo_resultados &resultado,int &mg,int &mp)
{
//DECLARACION DE VARIABLES.
srand(time(0));
int pelotita_jugador;
int apuesta;
int saldo=SALDO_INICIAL;
int aciertos=0;
char opcion;
printf("\n");
printf(" < BIENVENIDO > \n\n");
printf(" 1 Debera ingresar en que copa se encuentra la pelotita.\n");
printf(" 2 Luego debera ingresar el monto que desea apostar.\n");
printf(" 3 Su saldo para comenzar a jugar es de: %d\n\n", saldo);
do{
   int i=resultado.tope;
   //SORTEO PELOTITA.
   int pelotita_sistema=rand()%3+1;
   //DECALARACIÓN DE VARIABLE ESTAFA PARA LA PROGRAMACIÓN DE LA MISMA CUANDO LOS ACIERTOS SEAN IGUALES A 2.
   int estafa;
   estafa=aciertos==2;
   //PARA PROBAR QUE LA ESTAFA FUNCIONE DE MANERA CORRECTA IMPRIMIR LA COPA SORTEADA.
   //printf("SORTEO = %d\n\n", pelotita_sistema);
   //COMIENZO DEL JUEGO.
   printf("\n============================================================");
   printf("\n\n");
   printf(" << O O O >>\n");
   printf(" << 1 2 3 >>\n\n");
   //ELECCION DE COPA.
   printf(" Copa?: ");
   pelotita_jugador=0;//INICIALIZO LA VARIABLE EN CERO PARA QUE SOLAMENTE ACEPTE NUMEROS ENTEROS.
   fflush stdin;
   scanf("%d", &pelotita_jugador);
   while(pelotita_jugador!=1 && pelotita_jugador!=2 && pelotita_jugador!=3)
   {
   printf(" Copa invalida, debe elegir 1, 2 o 3.\n");
   printf(" Copa?: ");
   fflush stdin;
   scanf("%d", &pelotita_jugador);
   }
   //APUESTA.
   printf(" Apuesta?: ");
   apuesta=0;//IDEM QUE LA VARIABLE pelotita_jugador.
   fflush stdin;
   scanf("%d", &apuesta);
   while(apuesta>saldo || apuesta==0 || apuesta!=apuesta)
   {
   printf(" Apuesta invalida.\n");
   printf(" Apuesta?: ");
   fflush stdin;
   scanf("%d", &apuesta);
   }
   //POSIBLES CASOS DE ELECCION E IMPRESIONES EN PANTALLA.
   if(pelotita_jugador==pelotita_sistema && !estafa)
   {
   switch(pelotita_sistema){
                            case 1:
                                 printf("\n << _ O O >>\n\n");
                            break;
                            case 2:
                                 printf("\n << O _ O >>\n\n");
                            break;
                            case 3:
                                 printf("\n << O O _ >>\n\n");
                            break;
   }
   printf(" << Acerto >>\n");
   saldo+=apuesta;
   aciertos++;
   mp+=apuesta;//VA SUMANDO SEGUN GANE O PIERDA LA CASA DE APUESTAS.
   resultado.resultado_arr[i].res=Acerto;//COPIA EL RESULTADO DE LA JUGADA A LA ESTRUCTURA.
   }
   else
       if(pelotita_jugador!=pelotita_sistema)
       {
       switch(pelotita_sistema){
                                case 1:
                                     printf("\n << _ O O >>\n\n");
                                break;
                                case 2:
                                     printf("\n << O _ O >>\n\n");
                                break;
                                case 3:
                                     printf("\n << O O _ >>\n\n");
                                break;
       }
       printf(" << Fallo >>\n");
       saldo-=apuesta;
       aciertos=0;
       mg+=apuesta;//VA SUMANDO SEGUN GANE O PIERDA LA CASA DE APUESTAS.
       resultado.resultado_arr[i].res=Fallo;//COPIA EL RESULTADO DE LA JUGADA A LA ESTRUCTURA.
       }
       else//ESTAFA EN EL CASO EN QUE EL JUGADOR ACIERTE 2 VECES CONSECUTIVAS, LA TERCERA LO ESTAFA.
           if(pelotita_jugador==pelotita_sistema && estafa)
           {
           switch(pelotita_jugador){
                                    case 1:
                                         printf("\n << O . O >>\n\n");
                                    break;
                                    case 2:
                                         printf("\n << O O . >>\n\n");
                                    break;
                                    case 3:
                                         printf("\n << . O O >>\n\n");
                                    break;
           }
           printf(" << Fallo >>\n");
           saldo-=apuesta;
           aciertos=0;
           mg+=apuesta;//VA SUMANDO SEGUN GANE O PIERDA LA CASA DE APUESTAS.
           resultado.resultado_arr[i].res=Fallo;//COPIA EL RESULTADO DE LA JUGADA A LA ESTRUCTURA.
           }
   printf(" Su saldo ahora es de: %d\n\n", saldo);
   strcpy(resultado.resultado_arr[i].s_nombre,nombre);//COPIA EL NOMBRE DEL JUGADOR A LA ESTRUCTURA.
   strcpy(resultado.resultado_arr[i].s_cedula,cedula);//COPIA LA CEDULA DEL JUGADOR A LA ESTRUCTURA.
   resultado.resultado_arr[i].s_copa_sorteada=pelotita_sistema;//COPIA LA COPA SORTEADA A LA ESTRUCTURA.
   resultado.resultado_arr[i].s_copa_elegida=pelotita_jugador;//COPIA LA COPA ELEGIDA A LA ESTRUCTURA.
   resultado.resultado_arr[i].s_monto_apostado=apuesta;//COPIA EL MONTO APOSTADO A LA ESTRUCTURA.
   ++resultado.tope;//INCREMENTA EL TOPE DEL JUEGO. LO MAXIMO SON LAS 1000 JUGADAS POR SESION.
   printf("============================================================\n\n");
   //PARA PROBAR LA SUMA DE ACIERTOS AL FINAL DE CADA JUGADA Y PROBAR LA ESTAFA.
   //printf(" Aciertos:%d\n", aciertos);
   //ELECCION SI QUIERE SEGUIR JUGANDO O NO.
   regJuegos=true;
   do{
      printf(" Quiere seguir jugando (S/N)?: ");
      fflush stdin;
      scanf("%c", &opcion);
      if(opcion=='N' || opcion=='n')
      {
      printf("\n");
      printf(" << GRACIAS POR JUGAR >> \n\n");
      regDatos=false;//LO PONGO EN FALSE AL SALIR PARA QUE SOLICITE DATOS ANTE UN NUEVO JUEGO.
      }
      if(opcion!='S' && opcion!='s' && opcion!='N' && opcion!='n')
      {
      printf(" Error, debe elegir S(si) o N(no)\n");
      }
   }while(opcion!='S' && opcion!='s' && opcion!='N' && opcion!='n');
   //EN CASO EN QUE EL SALDO SEA INSUFICIENTE (CERO) IMPRIMIR LO SIGUIENTE Y SALIR
   if(saldo==0)
   {
   printf("\n");
   printf(" << SALDO INSUFICIENTE >>\n\n");
   printf(" << GRACIAS POR JUGAR >> \n\n");
   regDatos=false;//LO PONGO EN FALSE AL SALIR PARA QUE SOLICITE DATOS ANTE UN NUEVO JUEGO.
   }
}while((opcion=='S' || opcion=='s') && (saldo>0));
system("cls");
}

//FUNCION 3. LISTA LOS DATOS COMPLETOS DEL JUGADOR Y SUS JUGADAS.
void opcion3(tipo_resultados &resultado)
{
int i;
for(i=0; i<resultado.tope; i++)
{
printf("\n");
printf(" ==============================\n");
printf(" Nombre jugador: %s\n", resultado.resultado_arr[i].s_nombre);
printf(" Cedula jugador: %s\n", resultado.resultado_arr[i].s_cedula);
printf(" Copa sorteada: %d\n", resultado.resultado_arr[i].s_copa_sorteada);
printf(" Copa elegida: %d\n", resultado.resultado_arr[i].s_copa_elegida);
printf(" Monto apostado: %d\n", resultado.resultado_arr[i].s_monto_apostado);
if(resultado.resultado_arr[i].res==Acerto)
{
printf(" Resultado de apuesta: Acerto\n");
}else 
      if(resultado.resultado_arr[i].res==Fallo)
      {
      printf(" Resultado de apuesta: Fallo\n");
      }
printf(" ==============================\n");
}
}

//FUNCION 4. LISTAR EL MONTO GANADO Y EL MONTO PERDIDO POR LA CASA DE APUESTAS.
void opcion4(int mg, int mp)
{
//YA CALCULADOS DENTRO DEL MAIN().
printf("\n");
printf(" Saldos totales casa de apuestas:\n");
printf(" ==============================\n");
printf(" Monto ganado: %d\n", mg);
printf(" Monto perdido: %d\n", mp);
printf(" ==============================\n\n");
}
