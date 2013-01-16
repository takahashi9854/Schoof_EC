#include <stdio.h>
#include <stdlib.h>

// #define p 3
const int p = 5;

typedef struct{
  int *co; // coefficient
  int order; //order of the polynominal
  int n; // the number of terms in polynominal which is order + 1.
} POL;

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

int init_pol(POL *a,int size){
  //size in paramator is the order of polynominal.
  a->order = size;
  a->n = a->order + 1;
  a->co = (int *)malloc(sizeof(int) * a->n);
  if(a->co != 0) return 1;
  else return -1;
}

void del_pol(POL *a){
  free(a);
}
  

void print_pol(POL *a){
  int i;
  for(i=0;i<(a->n);i++) printf("%d:%d ",i,a->co[i]);
  printf("\n");
}

void copy_pol(POL *x, const POL *a){
  int i;
  init_pol(x,a->order);
  for(i=0;i<a->n;i++) x[i]=a[i];
}

/*
int resize_pol(POL *obj,POL *a){
  int i=a->order;
  int top=a->order;
  while(i>=0){
    if(a->co[i]==0) break;
    i--;
  }
  if(i==0){
    printf("cannot resize this polynominal.\n");
    return -1;
  }else{
    init_pol(obj,i);
    for(i=0;i<=(obj->n);i++) obj->co[i] = a->co[i];
  }
  return 1;
}
*/

void add_pol(POL *c, const POL *a,const POL *b){
  // c = a + b
  int i,least_n,least_order;
  
  if(a->order > b->order){
    init_pol(c,a->order);
    least_n = b->n;
    least_order = b->order;
    for(i=least_n;i<(a->n);i++){
      // c->co[i]=a->co[i];
      c->co[i]=(a->co[i])%p;
    }    
  }else{
    init_pol(c,b->order);
    least_n = a->n;
    least_order = a->order;
    for(i=least_n;i<(b->n);i++){
      // c->co[i]=b->co[i];
      c->co[i]=(b->co[i])%p;
    }
  }
  for(i=0;i<least_n;i++){
    // c->co[i] = a->co[i] + b->co[i];
    c->co[i] = (a->co[i] + b->co[i])%p;
  }
}

void sub_pol(POL *c, const POL *a,const POL *b){
  // c = a-b;
  int i,least_n,least_order;
  
  if(a->order > b->order){
    init_pol(c,a->order);
    least_n = b->n;
    least_order = b->order;
    for(i=least_n;i<(a->n);i++){
      // c->co[i]=a->co[i];
      c->co[i]=(a->co[i])%p;
    }    
  }else{
    init_pol(c,b->order);
    least_n = a->n;
    least_order = a->order;
    for(i=least_n;i<(b->n);i++){
      // c->co[i]= -b->co[i];
      c->co[i]= (-b->co[i])%p;
      while(c->co[i] < 0) (c->co[i])+=p;
    }
  }
  for(i=0;i<least_n;i++){
    // c->co[i] = a->co[i] -  b->co[i];
    c->co[i] = (a->co[i] -  b->co[i])%p;
    while(c->co[i] < 0) (c->co[i])+=p;
  }
}

void mul_pol(POL *c, const POL *a,const POL *b){
  // c = a*b;
  int i,j;
  init_pol(c,a->order + b->order);

  for(i=0;i<(a->n);i++){
    for(j=0;j<(b->n);j++){
      // c->co[i+j] += a->co[i]*b->co[j];
      c->co[i+j] += (a->co[i]*b->co[j])%p;
      while(c->co[i+j] < 0) c->co[i+j]+=p;
    }
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

void div_pol(POL *q,POL *r,const POL *a, const POL *b){
  int i;
  int condition; // condition to stop the loop.
  // In this case, the conditon to stop the loop is when deg(R) < deg(B)
  copy_pol(r,a); // R \leftarrow A
  init_pol(q,a->order - b->order); // Q \leftarrow 0
  while(r->order >= b->order ){
    
  }
}


int main(){
  POL a,b,c,d;
  int i;

  if(init_pol(&a,2) && init_pol(&b,2)) printf("success. the order of a is %d.\n",a.order);
  print_pol(&a);
  print_pol(&b);
  a.co[0]=-2;
  a.co[1]=1;
  a.co[2]=4;
  b.co[0]=2;
  b.co[1]=3;
  b.co[2]=0;
  //b.co[3]=3;

  printf("a\n");
  print_pol(&a);
  printf("b\n");
  print_pol(&b);
  mul_pol(&c,&a,&b);
  print_pol(&c);

  copy_pol(&d,&a);
  print_pol(&d);

  return 0;
}
  
  
