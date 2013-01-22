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
  if(P->Coeff == NULL) return -1;
  P->Coeff = malloc(sizeof(int) * n);
  memset(P->Coeff,0,n);
  return 1;
}

void delPolynomial(Polynomial *P){
  free(P->Coeff);
}
  

void printPolynomial(Polynomial *P){
  int i;
  for(i=0;i<=(P->Degree);i++) printf("[%d]:%d ",i,P->Coeff[i]);
  printf("\n");
}

void printDegree(Polynomial *P){
  printf("order:%d.\n",P->Degree);
}

/*
int resize_pol(POL *obj,POL *a){
  int i=a->order;
x  int top=a->order;
  while(i>=0){
    if(a->co[i]==0) break;
    i--;
  }
  if(i==0){
    printf("cannot resize this polynominal.\n");
    return -1;
  }else{
    init_pol(obj,i);
    for(i=0;i<=(obj->n);i++) obj->Coeff[i] = a->Coeff[i];
  }
  return 1;
}
*/

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
  initPolynomial(c,a->Degree + b->Degree);

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

void divPolynomial(Polynomial *Q,Polynomial *R,const Polynomial *A, const Polynomial *B){
  int i,degree;
  int condition; // condition to stop the loop.
  Polynomial S,ADD,MUL,SUB,SB,QS; // SB = S \times B, QS = Q \times S.
  // In this case, the conditon to stop the loop is when deg(R) < deg(B)
  copyPolynomial(R,A); // R \leftarrow A

  // Initialize the S of degree (deg(A) - deg(B)) for temporary polynomial.
  S.Degree = A->Degree - B->Degree;
  S.Coeff = malloc(sizeof(int) * (S.Degree + 1));
  if(S.Coeff == NULL) exit(-2);
  memset(S.Coeff,0,S.Degree + 1);
  // Here is the end of initialize.
  // Initialize the ADD of degree (deg(A) - deg(B)) for temporary polynomial.
  ADD.Degree = A->Degree - B->Degree;
  ADD.Coeff = malloc(sizeof(int) * (ADD.Degree + 1));
  if(ADD.Coeff == NULL) exit(-2);
  memset(ADD.Coeff,0,ADD.Degree + 1);
  // Here is the end of initialize.
  // Initialize the S of degree (deg(A) - deg(B)) for temporary polynomial.
  SUB.Degree = A->Degree - B->Degree;
  SUB.Coeff = malloc(sizeof(int) * (SUB.Degree + 1));
  if(SUB.Coeff == NULL) exit(-2);
  memset(SUB.Coeff,0,SUB.Degree + 1);
  // Here is the end of initialize.
  // Initialize the S of degree (deg(A) - deg(B)) for temporary polynomial.
  MUL.Degree = A->Degree - B->Degree;
  MUL.Coeff = malloc(sizeof(int) * (MUL.Degree + 1));
  if(MUL.Coeff == NULL) exit(-2);
  memset(MUL.Coeff,0,MUL.Degree + 1);
  // Here is the end of initialize.
  // Initialize the SB of degree (deg(A) - deg(B)) for temporary polynomial.
  SB.Degree = A->Degree - B->Degree;
  SB.Coeff = malloc(sizeof(int) * (SB.Degree + 1));
  if(SB.Coeff == NULL) exit(-2);
  memset(SB.Coeff,0,SB.Degree + 1);
  // Here is the end of initialize.
  // Initialize the QS of degree (deg(A) - deg(B)) for temporary polynomial.
  QS.Degree = A->Degree - B->Degree;
  QS.Coeff = malloc(sizeof(int) * (QS.Degree + 1));
  if(QS.Coeff == NULL) exit(-2);
  memset(QS.Coeff,0,QS.Degree + 1);
  // Here is the end of initialize.

  // So while deg(R) - deg(B) >= 0, then th loop has continued.
  degree = R->Degree;
  for(i=0;i<condition;i++){
    S.Coeff[i] = R->Coeff[degree] * inv_mod(B->Coeff[degree],p);
    
  }
}

int main(){
  Polynomial a,b,c,d;
  int i;

  initPolynomial(&a,3);
  printf("the degree of a is %d.\n",a.Degree);
  a.Coeff[0]=-2;
  a.Coeff[1]=3;
  a.Coeff[2]=4;
  a.Coeff[3]=5;
  printPolynomial(&a);
  copyPolynomial(&b,&a);
  printPolynomial(&b);

  divPolynomial(&d,&c,&a,&b);
  printPolynomial(&c);
    
  return 0;
}
  
  
