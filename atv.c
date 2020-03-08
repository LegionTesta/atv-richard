#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
mudar na main qual a atv quer testar
executar passando uma entrada com <
atv1 < entrada1
atv2, atv3, atv4 < entrada2
atv5 < entrada3
*/

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

    //primeiro elemento da entrada corresponde ao numero de elementos, o resto da entrada sao os elementos
 
  int s;

  while(scanf("%d", &s) != EOF){
      double v[s];
      double r = 0;
      double desvio = 0;
      double media;
      double t = 0;

      //le os elementos
      for(int x = 0; x < s; x++){
          scanf("%lf", &v[x]);
      }
      
    //somatoria para calcular media
    #pragma pragma omp parallel for reduction(+:r)
    {
        for(int x = 0; x < s; x++){
            r += v[x];
        }
    }
    media = r / s;
    printf("media: %lf\n", media);
    //somatoria para calcular desvio
    #pragma pragma omp parallel for reduction(+:t)
    {
        for(int x = 0; x < s; x++){
            t += pow((v[x] - media), 2);
        }
    }
    desvio = sqrt(t/s);
    printf("desvio: %lf\n", desvio);  
  }   
}

void atv3(){
    
    //primeiro elemento da entrada corresponde ao numero de elementos, o resto da entrada sao os elementos
 
    int s;

    while(scanf("%d", &s) != EOF){
        double v[s];
        double si = 0; 
        double mh;

        //le os elementos
        for(int x = 0; x < s; x++){
          scanf("%lf", &v[x]);
        }

        //calculo da somatoria dos valores invertidos
        #pragma pragma omp parallel for reduction(+:r)
        {
            for(int x = 0; x < s; x++){
                si += 1.0/v[x];
            }
        }
        //calculo da media harmonica. cast para nao perder decimal
        mh = (double)s/si;
        printf("media harmonica: %lf\n", mh);
    }

}

void atv4(){
    
    //primeiro elemento da entrada corresponde ao numero de elementos, o resto da entrada sao os elementos
 
    int s;

    while(scanf("%d", &s) != EOF){
        double v[s];
        double menor = 9999;
        double maior = 0;

        //le os elementos
        for(int x = 0; x < s; x++){
          scanf("%lf", &v[x]);
        }

        #pragma pragma omp parallel for reduction(min:r)
        {
            for(int x = 0; x < s; x++){
                menor = min(menor, v[x]);
            }   
        }
        #pragma pragma omp parallel for reduction(max:r)
        {
            for(int x = 0; x < s; x++){
                maior = max(maior, v[x]);
            }  
        }
        printf("maior: %lf\nmenor: %lf\n", maior, menor);

  }  

}

void atv5(){

    //algoritmo para mostrar primos de 0 ate n utilizando crivo de erastoteles
    int n;

    scanf("%d", &n);
     
    //se primos[x] == 1 entao eh primo
    int primos[n+1]; 

    #pragma omp parallel
    {
        
        #pragma omp for
        for(int x = 0; x < n; x++){
            primos[x] = 1;
        }
    }


    #pragma omp parallel
    {
        #pragma omp for
        for (int p = 2; p * p <= n; p++){ 
            
            if (primos[p] == 1) 
            { 
                // atualiza todos os multiplos de p maiores que sua raiz quadrada.
                // numeros multiplos de p menores que sua raiz quadrada ja foram analisados.  
                #pragma omp for
                for (int i = p * p; i <= n; i += p) 
                    primos[i] = 0; 
            } 
        } 
    }

  
    // printa os primos
    for (int p = 2; p <= n; p++) 
       if (primos[p]) 
          printf("%d\n", p); 
} 
  

void main() {
    
}
