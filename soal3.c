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
int i_ptr = 0;
int a_ptr = 0;

void *thread(void *argv);
void *agmal(void *argv);
void *iraj(void *argv);
void *checker(void *argv);

int main(){
    int num_t = 2, i;
    char *cmd = malloc(100);
    char *s1 = "All Status";
    char *s2 = "Agmal Ayo Bangun";
    char *s3 = "Iraj Ayo Tidur";
    
    pthread_t tid_a, tid_i, tid_s;
    pthread_create(&tid_a, NULL, agmal, NULL);
    pthread_create(&tid_i, NULL, iraj, NULL);
    pthread_create(&tid_s, NULL, checker, NULL);

    while(1){
        gets(cmd);
        if(strcasecmp(cmd, s1) == 0){
            printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }else if(strcasecmp(cmd, s2) == 0){
            // printf("agmal\n");
            if(a_stat != 3)
                a_ptr = 1;
        }else if(strcasecmp(cmd, s3) == 0){
            // printf("iraj\n");
            if(i_stat != 3)
                i_ptr = 1;
        }else{
            printf("no cmd\n");
        }
    }

    pthread_join(tid_a, NULL);
    pthread_join(tid_i, NULL);
    pthread_join(tid_s, NULL);
}

void *checker(void *argv){
    while(1){
        if(WakeUp_Status >= 100){
            printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");
            exit(0);
        }
        if(Spirit_Status <= 0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            exit(0);
        }
    }
}

void *agmal(void *argv){
    while (1) {
        if(a_stat == 3){            
            printf("Agmal Ayo Bangun disabled 10 s\n");
            sleep(10);
            // printf("\tagmal sleep selesai\n");
            a_stat = 0;
        }else if(a_ptr == 1 && a_stat != 3){
            a_ptr = 0;
            WakeUp_Status += 15;
            i_stat++;
            // printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            // printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }
    }
    
}

void *iraj(void *argv){
    while (1) {
        if(i_stat == 3){
            printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
            sleep(10);
            // printf("\tiraj sleep selesai\n");
            i_stat = 0;
        }else if(i_ptr == 1 && i_stat != 3){
            i_ptr = 0;
            Spirit_Status -= 20;
            a_stat++;
            // printf("Agmal WakeUp_Status\t= %d\n", WakeUp_Status);
            // printf("Iraj Spirit_Status\t= %d\n", Spirit_Status);
        }
    }
    
}
