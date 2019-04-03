//
//  soal3.c created with Xcode.
//
//
//  Created by Rizky Andre Wibisono on 02/04/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <strings.h>

int WakeUp_Status = 0;
int Spirit_Status = 100;
int i_stat = 0;
int a_stat = 0;

void *thread(void *argv);
void *agmal(void *argv);
void *iraj(void *argv);

int main(){
    int num_t = 2, i;
    char *cmd = malloc(100);
    char *s1 = "All Status";
    char *s2 = "Agmal Ayo Bangun";
    char *s3 = "Iraj Ayo Tidur";
    
    pthread_t tid_a, tid_i;
    pthread_create(&tid_a, NULL, agmal, NULL);
    pthread_create(&tid_i, NULL, iraj, NULL);
    
    while(1){
        gets(cmd);
        if(strcasecmp(cmd, s1) == 0){
            printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }else if(strcasecmp(cmd, s2) == 0){
            printf("agmal\n");
        }else if(strcasecmp(cmd, s3) == 0){
            iraj();
        }else{
            printf("no cmd\n");
        }
    }
    

//    for (i=0; i<num_t; i++) {
//        pthread_join(tid[i], NULL);
//    }
}

void *agmal(void *argv){
    while (1) {
        if(a_stat == 3){
            sleep(5);
            printf("\tagmal sleep selesai\n");
        }else{
            Spirit_Status+=20;
            i_stat++;
            printf("Agmal Ayo Bangun disabled 10 s\n");
        }
    }
    
}

void *iraj(void *argv){
    while (1) {
        if(i_stat == 3){
            sleep(5);
            printf("\tiraj sleep selesai\n");
        }else{
            Spirit_Status+=20;
            a_stat++;
            printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
        }
    }
    
}
