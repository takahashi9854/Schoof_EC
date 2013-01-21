#include <stdio.h>
#include <stdlib.h>

// #define p 3
const int p = 5;

typedef struct{
  int Degree; //order of the polynominl.
  int *Coeff; // coefficients of polynomial.
  
} Polynomial;

int inv_mod(int a, int b){
  // long long xa, ya, r, q, x, y, ra;
  int xa,ya,r,q,x,y,ra;
  x=a; y=b; xa=1; ya=0;
  while(x<0) x+=b;
  while(y<0) y+=b;
  while(y>0){
    r=x%y;
    q=x/y;
    ra=xa-q*ya;
    x=y;
    xa=ya;
    y=r;
    ya=ra;
  }
  while(xa<0) xa+=b;
  if(x==1){
    return xa%b;
  }else{
    printf("cannot find inverse module %d.\n",p);
    exit(1);
    return 0;
  }
}

int initPolynomial(Polynomial* P, const int D, const int* C){
  int i;
  if(P!=NULL && C!= NULL){
    P->Degree = D;
    P->Coeff = malloc(sizeof(int) * (P->Degree + 1));
    if(P->Coeff == NULL){
      puts("could't allocate memory.");
      exit(1);
    }
    memset(P->Coeff,0,P->Degree + 1);
    
    for(i=0;i<=P->Degree;i++){
      P->Coeff[i] = C[i];
    }
    return 1; //true;
  }else{
    return -1; //false;
  }
}


/*
Division of Polynominals.

Given two polynominals A and B in K[X] with B \neq 0,
this algorithm finds Q and R such that A = BQ + R and deg(R) < deg(B).

deg(Q) = deg(a) - deg(B)
deg(R) < deg(Q)

1.[Initialize]
Set R \lefttarrow A, Q \leftarrow 0.
2.[Finished?]
If deg(R) < deg(B) then terminate the algorithm.
3.[Find coefficient]
Set
S \leftarrow \ell(R)/\ell(B) X^{deg(R) - deg(B)}
then, Q \leftarrow Q+S, R \leftarrow R-S \times B and go to step 2.

(Recall that \ell(Z) is the leading coefficient of Z.)

 */
int main(){
  int c[3] = {-2,1,1};
  int D = 2;
  Polynomial P;
  initPolynomial(&P,D,c);
  
  printf("%lu\n",sizeof(P.Coeff)/sizeof(P.Coeff[0]));
  return 0;
}
  
  
