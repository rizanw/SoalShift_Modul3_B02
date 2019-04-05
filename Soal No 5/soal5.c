#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[]) {
  char *petname = "";
  int hunger_stat = 200;
  //sekaligus nilai maks, berkurang 5 tiap 10detik, jika 0 = gameover
  //pemain bisa memberi makan
  int food_strg = 0;
  //makanan dibeli di market
  int hygine_stat = 100; //berkurang 10 tiap 30detik
  //bertambah 30 jika dimandikan, cooldown 20detik
  int bath_time = 0;
  int health_stat = 300; //regenerasi 5pt tiap 10detik, ketika standby

  int pet_stat = 0; //0 = standby, 1 = battle, 2 = shop

  int NPC_health = 100; //serangan 20, serangan bergantian.

  if(pet_stat == 0){
    printf("Standby Mode\n");
    printf("Health\t: %d\n", health_stat);
    printf("Hunger\t: %d\n", hunger_stat);
    printf("Hygiene\t: %d\n", hygine_stat);
    printf("Food left\t: %d\n", food_strg);
    printf("Bath will be ready in %ds\n", bath_time);
    printf("Choices\n");
    printf("1. Eat\n");
    printf("2. Bath\n");
    printf("3. Battle\n");
    printf("4. Shop\n");
    printf("5. Exit\n");
    int in;
    while ((in = getchar())) {
      if(in == '1'){
        //Mode makan
        printf("1\n");

      }else if(in == '2'){
        //Mode mandi
        printf("2\n");
      }else if(in == '3'){
        //Mode tarung
        printf("3\n");
        pet_stat = 3;
      }else if(in == '4'){
        //Mode pasar
        printf("4\n");
      }else if(in == '5'){
        //keluar game
        printf("5\n");
      }
    }
  }else if (pet_stat == 1){
    int in;
    while (in = getchar()) {
      if (in == '1') {
        printf("attack\n", );
      }else if(in == '2'){
        printf("run\n");
      }
    }
  }else if(pet_stat == 2){
    printf("Shop Mode\n");
    printf("Shop food stock\t: \n");
    printf("Your food stock\t: \n");
    printf("Choices\n");
    printf("1. Buy\n");
    printf("2. Back\n");
  }

  return 0;
}
