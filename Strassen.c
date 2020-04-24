#include <stdio.h>
#include <stdlib.h>

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

void restaMatriz(int *a, int *b, int *c, int tamanio){
  int x;
  for(x=0; x<(tamanio*tamanio); x++){
    *(c+x)=(*(a+x))-(*(b+x));
  }
}

void sumaMatriz(int *a, int *b, int *c, int tamanio){
    int x;
    for(x=0; x<(tamanio*tamanio); x++){
      *(c+x)=(*(a+x))+(*(b+x));
    }
  }

void strassen(int *a, int *b, int *c, int tamanio){
    int mitad=0,
        x,
        y,
        z,
        *s[10],
        *p[7],
        *ap[4],
        *bp[4],
        *cp[4];
    if(tamanio==1){
      *c=(*a)*(*b);
    }
    else{
      mitad=tamanio/2;
      for(x=0; x<10; x++){
        s[x]=(int *) malloc((sizeof(int)*tamanio*tamanio)/4);
        if(x<7){
          p[x]=(int *) malloc((sizeof(int)*tamanio*tamanio)/4);
        }
        if(x<4){
          ap[x]=(int *) malloc((sizeof(int)*tamanio*tamanio)/4);
          bp[x]=(int *) malloc((sizeof(int)*tamanio*tamanio)/4);
          cp[x]=(int *) malloc((sizeof(int)*tamanio*tamanio)/4);
        }
      }
      for(z=0; z<4; z++){
        for(y=0; y<mitad; y++){
          for(x=0; x<mitad; x++){
            switch(z){
              case 0:
                *(ap[0]+(mitad*y)+x)=*(a+(tamanio*y)+x);
                *(bp[0]+(mitad*y)+x)=*(b+(tamanio*y)+x);
              break;
              case 1:
                *(ap[1]+(mitad*y)+x)=*(a+(tamanio*y)+x+mitad);
                *(bp[1]+(mitad*y)+x)=*(b+(tamanio*y)+x+mitad);
              break;
              case 2:
                *(ap[2]+(mitad*y)+x)=*(a+(tamanio*(y+mitad))+x);
                *(bp[2]+(mitad*y)+x)=*(b+(tamanio*(y+mitad))+x);
              break;
              case 3:
                *(ap[3]+(mitad*y)+x)=*(a+(tamanio*(y+mitad))+x+mitad);
                *(bp[3]+(mitad*y)+x)=*(b+(tamanio*(y+mitad))+x+mitad);
              break;
            }
          }
        }
      }
      restaMatriz(bp[1], bp[3], s[0], mitad);
      sumaMatriz(ap[0], ap[1], s[1], mitad);
      sumaMatriz(ap[2], ap[3], s[2], mitad);
      restaMatriz(bp[2], bp[0], s[3], mitad);
      sumaMatriz(ap[0], ap[3], s[4], mitad);
      sumaMatriz(bp[0], bp[3], s[5], mitad);
      restaMatriz(ap[1], ap[3], s[6], mitad);
      sumaMatriz(bp[2], bp[3], s[7], mitad);
      restaMatriz(ap[0], ap[2], s[8], mitad);
      sumaMatriz(bp[0], bp[1], s[9], mitad);
      strassen(ap[0], s[0], p[0], mitad);
      strassen(s[1], bp[3], p[1], mitad);
      strassen(s[2], bp[0], p[2], mitad);
      strassen(ap[3], s[3], p[3], mitad);
      strassen(s[4], s[5], p[4], mitad);
      strassen(s[6], s[7], p[5], mitad);
      strassen(s[8], s[9], p[6], mitad);
      sumaMatriz(p[4], p[3], cp[0], mitad);
      restaMatriz(cp[0], p[1], cp[0], mitad);
      sumaMatriz(cp[0], p[5], cp[0], mitad);
      sumaMatriz(p[0], p[1], cp[1], mitad);
      sumaMatriz(p[2], p[3], cp[2], mitad);
      sumaMatriz(p[4], p[0], cp[3], mitad);
      restaMatriz(cp[3], p[2], cp[3], mitad);
      restaMatriz(cp[3], p[6], cp[3], mitad);
      for(z=0; z<4; z++){
        for(x=0; x<mitad; x++){
          for(y=0; y<mitad; y++){
            switch(z){
              case 0:
                *(c+(tamanio*y)+x)=*(cp[0]+(mitad*y)+x);
              break;
              case 1:
                *(c+(tamanio*y)+x+mitad)=*(cp[1]+(mitad*y)+x);
              break;
              case 2:
                *(c+(tamanio*(y+mitad))+x)=*(cp[2]+(mitad*y)+x);
              break;
              case 3:
                *(c+(tamanio*(y+mitad))+x+mitad)=*(cp[3]+(mitad*y)+x);
              break;
            }
          }
        }
      }
      for(x=0; x<10; x++){
        free(s[x]);
        if(x<7){
          free(p[x]);
        }
        if(x<4){
          free(ap[x]);
          free(bp[x]);
          free(cp[x]);
        }
      }
    }
}

int main(void){
  int *a,
      *b,
      *c;
  a=(int *) malloc(sizeof(int)*16);
  b=(int *) malloc(sizeof(int)*16);
  c=(int *) malloc(sizeof(int)*16);
  *a=*b=1;
  *(a+1)=*(b+1)=2;
  *(a+2)=*(b+2)=3;
  *(a+3)=*(b+3)=4;
  *(a+4)=*(b+4)=5;
  *(a+5)=*(b+5)=1;
  *(a+6)=*(b+6)=2;
  *(a+7)=*(b+7)=3;
  *(a+8)=*(b+8)=4;
  *(a+9)=*(b+9)=5;
  *(a+10)=*(b+10)=1;
  *(a+11)=*(b+11)=2;
  *(a+12)=*(b+12)=3;
  *(a+13)=*(b+13)=4;
  *(a+14)=*(b+14)=5;
  *(a+15)=*(b+15)=1;
  imprimirMatriz(a, 4);
  imprimirMatriz(b, 4);
  strassen(a, b, c, 4);
  imprimirMatriz(c, 4);
}
