/*
Instituto Politecnico Nacional
Escuela Superior de Cómputo
Analisis de algoritmos
Grupo: 3CV2
Alumnos: Garcia Tello Axel
		 Rodríguez Acosta Alan
Profesor: Benjamin Luna Benoso
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
Strassen

Fecha: 29 de abril de 2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Función para imprimir la matriz
void imprimirMatriz(int *a, int tamanio){
  int x,
      y;
  for(y=0; y<tamanio; y++){
    for(x=0; x<tamanio; x++){
      printf("%d\t", *(a+(tamanio*y)+x));
    }
    printf("\n");
  }
  printf("\n\n");
}

//Función para la resta de 2 matrices
void restaMatriz(int *a, int *b, int *c, int tamanio, int *contador){
  int x;
  for(x=0; x<(tamanio*tamanio); x++){
    *contador+=1;
    *(c+x)=(*(a+x))-(*(b+x));
  }
  *contador+=1;
}

//Función para la suma de 2 matrices
void sumaMatriz(int *a, int *b, int *c, int tamanio, int *contador){
    int x;
    for(x=0; x<(tamanio*tamanio); x++){
      *contador+=1;
      *(c+x)=(*(a+x))+(*(b+x));
    }
    *contador+=1;
}

//Función del Strassen para la multplicación de matrices
void strassen(int *a, int *b, int *c, int tamanio, int *contador){
    int mitad=0,
        x,
        y,
        z,
        *s[10],
        *p[7],
        *ap[4],
        *bp[4],
        *cp[4];
        *contador += 9;
    if(tamanio==1){
      //Si la matrices son de tamaño 1
      *c=(*a)*(*b);
      *contador +=2;
    }
    else{
      *contador+=1;
      mitad=tamanio/2; *contador+=1;
      /*Creación de los espacios de memoria correspondientes para
      realizar los calculos*/
      for(x=0; x<10; x++){
        *contador+=1;
        s[x]=(int *) malloc((sizeof(int)*tamanio*tamanio)/4);
        *contador+=1;
        if(x<7){
          p[x]=(int *) malloc((sizeof(int)*tamanio*tamanio)/4);
          *contador+=1;
        }
        if(x<4){
          ap[x]=(int *) malloc((sizeof(int)*tamanio*tamanio)/4);
          *contador+=1;
          bp[x]=(int *) malloc((sizeof(int)*tamanio*tamanio)/4);
          *contador+=1;
          cp[x]=(int *) malloc((sizeof(int)*tamanio*tamanio)/4);
          *contador+=1;
        }
      }
      *contador+=1;
      //Division de las matrices en submatrices
      for(z=0; z<4; z++){
        *contador+=1;
        for(y=0; y<mitad; y++){
          *contador+=1;
          for(x=0; x<mitad; x++){
            *contador+=1;
            switch(z){
              case 0:
                *(ap[0]+(mitad*y)+x)=*(a+(tamanio*y)+x); *contador+=1;
                *(bp[0]+(mitad*y)+x)=*(b+(tamanio*y)+x); *contador+=1;
              break;
              case 1:
                *(ap[1]+(mitad*y)+x)=*(a+(tamanio*y)+x+mitad);
                *contador+=1;
                *(bp[1]+(mitad*y)+x)=*(b+(tamanio*y)+x+mitad);
                *contador+=1;
              break;
              case 2:
                *(ap[2]+(mitad*y)+x)=*(a+(tamanio*(y+mitad))+x);
                *contador+=1;
                *(bp[2]+(mitad*y)+x)=*(b+(tamanio*(y+mitad))+x);
                *contador+=1;
              break;
              case 3:
                *(ap[3]+(mitad*y)+x)=*(a+(tamanio*(y+mitad))+x+mitad);
                *contador+=1;
                *(bp[3]+(mitad*y)+x)=*(b+(tamanio*(y+mitad))+x+mitad);
                *contador+=1;
              break;
            }
          }
          *contador+=1;
        }
        *contador+=1;
      }
      *contador+=1;
      //Operaciones del algoritmo de Strassen
      restaMatriz(bp[1], bp[3], s[0], mitad, contador);
      sumaMatriz(ap[0], ap[1], s[1], mitad, contador);
      sumaMatriz(ap[2], ap[3], s[2], mitad, contador);
      restaMatriz(bp[2], bp[0], s[3], mitad, contador);
      sumaMatriz(ap[0], ap[3], s[4], mitad, contador);
      sumaMatriz(bp[0], bp[3], s[5], mitad, contador);
      restaMatriz(ap[1], ap[3], s[6], mitad, contador);
      sumaMatriz(bp[2], bp[3], s[7], mitad, contador);
      restaMatriz(ap[0], ap[2], s[8], mitad, contador);
      sumaMatriz(bp[0], bp[1], s[9], mitad, contador);
      strassen(ap[0], s[0], p[0], mitad, contador);
      strassen(s[1], bp[3], p[1], mitad, contador);
      strassen(s[2], bp[0], p[2], mitad, contador);
      strassen(ap[3], s[3], p[3], mitad, contador);
      strassen(s[4], s[5], p[4], mitad, contador);
      strassen(s[6], s[7], p[5], mitad, contador);
      strassen(s[8], s[9], p[6], mitad, contador);
      sumaMatriz(p[4], p[3], cp[0], mitad, contador);
      restaMatriz(cp[0], p[1], cp[0], mitad, contador);
      sumaMatriz(cp[0], p[5], cp[0], mitad, contador);
      sumaMatriz(p[0], p[1], cp[1], mitad, contador);
      sumaMatriz(p[2], p[3], cp[2], mitad, contador);
      sumaMatriz(p[4], p[0], cp[3], mitad, contador);
      restaMatriz(cp[3], p[2], cp[3], mitad, contador);
      restaMatriz(cp[3], p[6], cp[3], mitad, contador);
      //Unión de las submatrices en la matriz de respuesta
      for(z=0; z<4; z++){
        *contador+=1;
        for(x=0; x<mitad; x++){
          *contador+=1;
          for(y=0; y<mitad; y++){
            *contador+=1;
            switch(z){
              case 0:
                *(c+(tamanio*y)+x)=*(cp[0]+(mitad*y)+x); *contador+=1;
              break;
              case 1:
                *(c+(tamanio*y)+x+mitad)=*(cp[1]+(mitad*y)+x);
                *contador+=1;
              break;
              case 2:
                *(c+(tamanio*(y+mitad))+x)=*(cp[2]+(mitad*y)+x);
                *contador+=1;
              break;
              case 3:
                *(c+(tamanio*(y+mitad))+x+mitad)=*(cp[3]+(mitad*y)+x);
                *contador+=1;
              break;
            }
          }
          *contador+=1;
        }
        *contador+=1;
      }
      *contador+=1;
      //Liberación del espacio de memoria
      for(x=0; x<10; x++){
        free(s[x]); *contador+=1;
        if(x<7){
          free(p[x]); *contador+=1;
        }
        if(x<4){
          free(ap[x]); *contador+=1;
          free(bp[x]); *contador+=1;
          free(cp[x]); *contador+=1;
        }
      }
    }
}

//Inicio del programa
int main(void){
  int *a,
      *b,
      *c,
      tamanio=1,
      x=0,
      y=0,
      contador=0;
  srand(time(NULL)); //Función para crear números random
  for(x=0; x<4; x++){
    //Asignación del tamaño y espacio de las matrices
    tamanio*=2;
    a=(int *) malloc(sizeof(int)*tamanio*tamanio);
    b=(int *) malloc(sizeof(int)*tamanio*tamanio);
    c=(int *) malloc(sizeof(int)*tamanio*tamanio);
    //Colocación de valores
    for(y=0; y<(tamanio*tamanio); y++){
      *(a+y)=rand()%5+1;
      *(b+y)=rand()%5+1;
    }
    imprimirMatriz(a, tamanio);
    imprimirMatriz(b, tamanio);
    strassen(a, b, c, tamanio, &contador);
    imprimirMatriz(c, tamanio);
    printf("Tamaño de la matriz: %d\n", tamanio);
    printf("Numeros de lineas ejecutadas: %d\n",contador);
    //Liberación de memoria
    free(a);
    free(b);
    free(c);
  }
}
