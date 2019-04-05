#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <termios.h>

int *food_stock;

char getch();
void *menu(void * argv);

int main(){
  key_t key = 1234;

  int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
  food_stock = shmat(shmid, NULL, 0);

  *food_stock = 0;

  //thread creation
  pthread_t tid;
  pthread_create(&tid, NULL, menu, NULL);

  while (1) {
    printf("Shop\n");
    printf("Food stock : %d\n", *food_stock);
    printf("Choices\n");
    printf("1. Restock\n");
    printf("2. Exit\n");
    sleep(1);
    system("clear");
  }

  //
  //
  // printf("Program 1: %d\n", *food_stock);
  // shmdt(food_stock);
  // shmctl(shmid, IPC_RMID, NULL);
}

void *menu(void * argv){
  int in;
  while (1) {
    in = getch();
    if (in == '1') {
      printf("tambah 1\n");
      *food_stock+=1;
    }else if(in == '2'){
      exit(0);
    }
  }
}

char getch() {
  char buf = 0;
  struct termios old = {0};
  if (tcgetattr(0, &old) < 0)
    perror("tcsetattr()");
  old.c_lflag &= ~ICANON;
  old.c_lflag &= ~ECHO;
  old.c_cc[VMIN] = 1;
  old.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSANOW, &old) < 0)
    perror("tcsetattr ICANON");
  if (read(0, &buf, 1) < 0)
    perror ("read()");
  old.c_lflag |= ICANON;
  old.c_lflag |= ECHO;
  if (tcsetattr(0, TCSADRAIN, &old) < 0)
    perror ("tcsetattr ~ICANON");
  return (buf);
}
