#ifndef ___INFO_H___
#define ___INFO_H___

typedef struct info{
  char * product_code;
  int unitsSold;
}*Info;

typedef struct aux{
  char * product_code;
  int * totalClients;
  int * unitsSold;
}*Aux;


typedef struct money{
  char * product_code;
  double moneySpent;
}*Money;

#endif
