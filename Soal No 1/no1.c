#include <stdio.h>
//#include <conio.h>
#include <pthread.h>

int num;
pthread_t t[100];
void *factorial(void *args) {
	int fac=1;
	char* temp = (char*)args;
	int argc = temp[0] - '0';
	for(int a=1; a<=argc;a++){
		fac=fac*a;
	}
	printf("Factorial of Given Number is = %d\n",fac);
}
int main(int argc,char *argv[])
{
    int i;
    if( argc >= 2 )
    {
        printf("The arguments supplied are:\n");
        for(i = 1; i < argc; i++)
        {
            printf("%s\t", argv[i]);
        }
    }
    else
    {
        printf("argument list is empty.\n");
    }
   int k,j;
for(k = 1; k < argc; k++) {
	for(j = k + 1; j < argc; j++) {
		int angka1 = argv[k][0] - '0';
		int angka2 = argv[j][0] - '0';
		if(angka2 < angka1){
			char *temp = argv[j];
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
