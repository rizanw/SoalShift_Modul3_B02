#include <stdio.h>
//#include <conio.h>
#include <pthread.h>
#include <stdlib.h>
int num[100];
pthread_t t[100];
int status=0;
int j=1;
void *factorial(void *args) {
  int fac=1;
  for(int a=1; a<=num[j];a++){
    fac=fac*a;
  }
  printf("%d! = %d \n",num[j],fac);
  j++;
  status=1;
}
//void display(){
//  int argc;
//  for(int i=1; i<argc;i++){
//    printf("%d,%s",factorial(fac),argv[1]);
//}}
int main(int argc,char *argv[])
{
    int i=1;
  int a;
    int k,j;
   while(argv[i] != NULL){
  num[i]=atoi(argv[i]);
  i++;}
   for(k=1;k<argc;k++){
  for(j=k+1;j<argc;j++){
    int angka1=atoi(argv[k]);
    int angka2=atoi(argv[j]);
    if(angka2<angka1){
      char *temp = argv[j];
      int temp2 = num[j];
      num[j] = num[k];
      num[k] = temp2;
      argv[j] = argv[k];
      argv[k] = temp;
    }
  }
  }   
   for (k=1;k<argc;k++){
   pthread_create (&t[k-1],NULL,factorial,(void*) argv[k]) ;
   pthread_join(t[k-1], NULL);}

    return 0;
}
