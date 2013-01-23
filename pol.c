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

int initPolynomial(Polynomial *P,int size){
  //size in paramator is the order of polynominal.
  int i,n;
  P->Degree = size;
  n = (P->Degree + 1); // the number of coefficients.
  P->Coeff = malloc(sizeof(int) * n);
  memset(P->Coeff,0,n);
  return 1;
}

void delPolynomial(Polynomial *P){
  free(P->Coeff);
  free(P);
}
  

void printPolynomial(Polynomial *P){
  int i;
  for(i=P->Degree;i>=0;i--) printf("[%d]:%d ",i,P->Coeff[i]);
  printf("\n");
}

void printDegree(Polynomial *P){
  printf("order:%d.\n",P->Degree);
}

void addPolynomial(Polynomial *C, const Polynomial *A,const Polynomial *B){
  // c = a + b
  int i,least_n,least_Degree;
  
  if(A->Degree > B->Degree){
    initPolynomial(C,A->Degree);
    least_Degree = B->Degree;
    for(i=least_Degree+1;i<=(A->Degree);i++){
      // c->Coeff[i]=a->Coeff[i];
      C->Coeff[i]=(A->Coeff[i])%p;
      while(C->Coeff[i] < 0) (C->Coeff[i])+=p;
    }    
  }else{
    initPolynomial(C,B->Degree);
    least_Degree = A->Degree;
    for(i=least_Degree+1;i<=(B->Degree);i++){
      // c->Coeff[i]=b->Coeff[i];
      C->Coeff[i]=(B->Coeff[i])%p;
      while(C->Coeff[i] < 0) (C->Coeff[i])+=p;
    }
  }
  for(i=0;i<=least_Degree;i++){
    // c->co[i] = a->co[i] + b->co[i];
    C->Coeff[i] = (A->Coeff[i] + B->Coeff[i])%p;
  }
}

void subPolynomial(Polynomial *c, const Polynomial *a,const Polynomial *b){
  // c = a-b;
  int i,least_n,least_Degree;
  
  if(a->Degree > b->Degree){
    initPolynomial(c,a->Degree);
    least_Degree = b->Degree;
    for(i=least_Degree+1;i<=(a->Degree);i++){
      // c->Coeff[i]=a->Coeff[i];
      c->Coeff[i]=(a->Coeff[i])%p;
      while(c->Coeff[i] < 0) (c->Coeff[i])+=p;
    }    
  }else{
    initPolynomial(c,b->Degree);
    least_Degree = a->Degree;
    for(i=least_Degree+1;i<=(b->Degree);i++){
      // c->Coeff[i]= -b->Coeff[i];
      c->Coeff[i]= (-1 * b->Coeff[i])%p;
      while(c->Coeff[i] < 0) (c->Coeff[i])+=p;
    }
  }
  for(i=0;i<=least_Degree;i++){
    // c->Coeff[i] = a->Coeff[i] -  b->Coeff[i];
    c->Coeff[i] = (a->Coeff[i] -  b->Coeff[i])%p;
    while(c->Coeff[i] < 0) (c->Coeff[i])+=p;
  }
}

void mulPolynomial(Polynomial *c, const Polynomial *a,const Polynomial *b){
  // c = a*b;
  int i,j;
  c->Degree = a->Degree + b->Degree;
  c->Coeff = malloc(sizeof(int)*(c->Degree+1));
  // initPolynomial(c,a->Degree + b->Degree);
  memset(c->Coeff,0,c->Degree+1);
  if(c->Coeff == NULL) exit(-1);

  if(a->Degree == 0){
    for(i=0;i<=b->Degree;i++) c->Coeff[i]=a->Coeff[0]*b->Coeff[i];
    return;
  }

  if(b->Degree == 0){
    for(i=0;i<=a->Degree;i++) c->Coeff[i]=b->Coeff[0]*a->Coeff[i];
    return;
  }

  for(i=0;i<=(a->Degree);i++){
    for(j=0;j<=(b->Degree);j++){
      // c->Coeff[i+j] += a->Coeff[i]*b->Coeff[j];
      c->Coeff[i+j] += (a->Coeff[i]*b->Coeff[j])%p;
      c->Coeff[i+j]%=p;
      while(c->Coeff[i+j] < 0) (c->Coeff[i+j])+=p;
    }
  }
}

void copyPolynomial(Polynomial *x, const Polynomial *y){
  int i;
  // here is initialize the polynomial.
  // the degree of x is equall to the degree of y.
  x->Degree = y->Degree;
  x->Coeff = malloc(sizeof(int) *(x->Degree + 1));
  memset(x->Coeff,0,x->Degree + 1);
  // this is the end of initialize.
  // printf("the Degree of x Polynomial is %d.\n",x->Degree);
  // printf("the Degree of y Polynomial is %d.\n",y->Degree);
  if(x->Coeff == NULL){
    printf("cannnot allocate memory\n");
    exit(-1);
  }else{
    for(i=0;i<=(x->Degree);i++) x->Coeff[i]=y->Coeff[i];
  }
}

void resizePolynomial(Polynomial *P){
  Polynomial *TMP = malloc(sizeof(Polynomial));
  int i;
  int newDegree = P->Degree;
  while(P->Coeff[newDegree--] == 0 && newDegree >=0 );// find the biggest degree which coefficient is not equall to zero.
  if(newDegree<0){
    return;   
  }
  TMP->Degree = newDegree+1;
  TMP->Coeff = malloc(sizeof(int) * (TMP->Degree + 1));
  if(TMP->Coeff == NULL) exit(-1);
  for(i=0;i<=TMP->Degree;i++) TMP->Coeff[i] = P->Coeff[i];
  P->Degree = TMP->Degree;
  P->Coeff = malloc(sizeof(int) * (P->Degree+1));
  if(P->Coeff == NULL) exit(-1);
  for(i=0;i<=TMP->Degree;i++) P->Coeff[i] = TMP->Coeff[i];
  // free(TMP->Coeff);
  // free(TMP);
  delPolynomial(TMP);
}

/*
  Division of Polynominals.

  Given two polynominals A and B in K[X] with B \neq 0,
  this algorithm finds Q and R such that A = BQ + R and deg(R) < deg(B).

  deg(Q) = deg(A) - deg(B)
  deg(R) < deg(Q)

  1.[Initialize]
  Set R \lefttarrow A, Q \leftarrow 0.

  2.[Finished?]
  If deg(R) < deg(B) then terminate the algorithm.

  3.[Find coefficient]
  Set
  S \leftarrow (\ell(R)) / (\ell(B)) X^{deg(R) - deg(B)}
  then, Q \leftarrow Q+S, R \leftarrow R-S \times B and go to step 2.

  (Recall that \ell(Z) is the leading coefficient of Z.)
*/

int getLeadCoeff(const Polynomial *P){
  if(P == NULL || P->Coeff == NULL) exit(-1);
  else return P->Coeff[P->Degree];
}

void divPolynomial(Polynomial *Q,Polynomial *R,const Polynomial *A, const Polynomial *B){
  int i,degree;
  int condition; // condition to stop the loop.
  Polynomial *SB,*QS,*RSB;
  // S = malloc(sizeof(Polynomial));
  SB = malloc(sizeof(Polynomial));
  QS = malloc(sizeof(Polynomial));
  RSB = malloc(sizeof(Polynomial));
  /*
    S is used for temporary Polynomial.
    SB is used for S \times B.
    QS is used for Q + S.
    
  */

  Q->Degree = (A->Degree - B->Degree);
  Q->Coeff = malloc(sizeof(int) * (Q->Degree + 1));
  if(Q->Coeff == NULL) exit(-1);

  copyPolynomial(R,A);
  // printf("R: ");
  // printPolynomial(R); // for debug.

  degree = R->Degree - B->Degree;
  // printf("%d\n",degree);
    
  // SB = S \times B, QS = Q \times S.
  // In this case, the conditon to stop the loop is when deg(R) < deg(B)
  while(R->Degree >= B->Degree){
    //
    Polynomial *S = malloc(sizeof(Polynomial));
    S->Degree = (R->Degree - B->Degree);
    S->Coeff = malloc(sizeof(int) * (S->Degree + 1));
    if(S->Coeff == NULL) exit(-1);

    S->Coeff[R->Degree - B->Degree] = (getLeadCoeff(R) * inv_mod(getLeadCoeff(B),p))%p;
    // printPolynomial(S);

    addPolynomial(QS,S,Q);
    // printPolynomial(QS);
    copyPolynomial(Q,QS);
    resizePolynomial(Q);
    // printf("Q:");
    // printPolynomial(Q);

    mulPolynomial(SB,B,S);

    //printPolynomial(SB);
    resizePolynomial(SB);
    //printPolynomial(SB);
    
    subPolynomial(RSB,R,SB);
    //printPolynomial(RSB);
    resizePolynomial(RSB);
    //printPolynomial(RSB);
    
    copyPolynomial(R,RSB);

    //printPolynomial(R);
    resizePolynomial(R);
    //printPolynomial(R);

    //printf("the Degree of R is %d\n",R->Degree);
    //printf("the Degree of B is %d\n",B->Degree);
    
    free(S->Coeff);
    free(S);
  }
  // delPolynomial(S);
  delPolynomial(SB);
  delPolynomial(QS);
  delPolynomial(RSB);
  // So while deg(R) - deg(B) >= 0, then th loop has continued.
}

int main(){
  // Polynomial a,b,c,d;
  Polynomial *A,*B,*P,*Q,*R;
  A = malloc(sizeof(Polynomial));
  B = malloc(sizeof(Polynomial));
  P = malloc(sizeof(Polynomial));
  Q = malloc(sizeof(Polynomial));
  R = malloc(sizeof(Polynomial));

  initPolynomial(A,4);
  A->Coeff[0]=2;
  A->Coeff[1]=4;
  A->Coeff[2]=1;
  A->Coeff[3]=2;
  A->Coeff[4]=3;
  printf("A: ");
  printPolynomial(A);
  
  initPolynomial(B,3);
  B->Coeff[0]=0;
  B->Coeff[1]=1;
  B->Coeff[2]=0;
  B->Coeff[3]=1;
  printf("B: ");
  printPolynomial(B);
  
  divPolynomial(Q,R,A,B);

  printf("Q: ");
  printPolynomial(Q);
  printf("R: ");
  printPolynomial(R);
  
  delPolynomial(A);
  delPolynomial(B);
  delPolynomial(P);
  delPolynomial(Q);

  return 0;
  
}

  
  
