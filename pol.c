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
  while(x<0) x+=p;
  while(y<0) y+=p;
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
    // printf("cannot find inverse module %d.\n",p);
    exit(1);
    return 0;
  }
}

void div_pol(POL *q,POL *r,const POL *a, const POL *b){
}

int init_pol(POL *a,int size){
  //size in paramator is the order of polynominal.
  a->order = size;
  a->n = a->order + 1;
  a->co = (int *)malloc(sizeof(int) * a->n);
  if(a->co != 0) return 1;
  else return -1;
}

void print_pol(POL *a){
  int i;
  for(i=0;i<(a->n);i++) printf("%d:%d ",i,a->co[i]);
  printf("\n");
}

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

int main(){
  POL a,b,c;

  if(init_pol(&a,2) && init_pol(&b,2)) printf("success. the order of a is %d.\n",a.order);
  print_pol(&a);
  print_pol(&b);
  a.co[0]=-2;
  a.co[1]=1;
  a.co[2]=4;
  b.co[0]=2;
  b.co[1]=3;
  b.co[2]=1;
  //b.co[3]=3;

  printf("a\n");
  print_pol(&a);
  printf("b\n");
  print_pol(&b);
  mul_pol(&c,&a,&b);
  print_pol(&c);
  
  return 0;
}
  
  
