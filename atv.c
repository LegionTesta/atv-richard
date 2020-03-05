#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void atv1() {

    /*
    entrada recebe primeiro o tamanho dos vetores (ambos terao o mesmo tamanho),
    depois salva nos vetores seus valores, um vetor por vez
    */

  int s;

  while(scanf("%d", &s) != EOF){
      //inicializa os vetores com o size
        int e1[s];
        int e2[s];
        int r[s];
        //le as entrys 1 e 2
        for(int x = 0; x < s; x++){
            scanf("%d", &e1[x]);
        }
        for(int x = 0; x < s; x++){
            scanf("%d", &e2[x]);
        }
        #pragma omp parallel
        {
            //for para fazer a distribuicao das threads pelo vetor
            #pragma omp for
            for(int x = 0; x < s; x++){
                r[x] = e1[x] + e2[x];
            }
        }
        for(int x = 0; x < s; x++){
            printf("%d\n", r[x]);
        }
  }

}

void atv2(){
 
  int s;

  while(scanf("%d", &s) != EOF){
      double v[s];
      double r = 0;
      double desvio = 0;
      double media;
      double t = 0;
      for(int x = 0; x < s; x++){
          scanf("%lf", &v[x]);
      }
      
    #pragma pragma omp parallel for reduction(+:r)
    {
        for(int x = 0; x < s; x++){
            r += v[x];
        }
    }
    media = r / s;
    printf("%lf\n", media);
    #pragma pragma omp parallel for reduction(+:t)
    {
        for(int x = 0; x < s; x++){
            t += pow((v[x] - media), 2);
        }
    }
    desvio = sqrt(t/s);
    printf("%lf\n", desvio);  
  }   
}

void main() {
    atv2();
}
