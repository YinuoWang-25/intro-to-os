#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h> 

#define STUDENT_NUM 200
#define HEKP_DESK_NUM 1
#define WAITING_CHAIR_NUM 3
#define STUDENT_SLEEP_MAX 5 

sem_t chair_sem;
pthread_mutex_t office_mutex;

int waiting_student = 0;
int chairs[3]; 
int next_seat = 0; 
int next_teach = 0; 

// simulate student and ta using pthread
void *simulate_student(void *param);
void *simulate_ta(void *param);

void rand_sleep(void); 

int main(void) {
    // initial locks
    pthread_mutex_init(&office_mutex, NULL);
    sem_init(&chair_sem, 0, WAITING_CHAIR_NUM);

    // create students thread and join them
    pthread_t student_pid[STUDENT_NUM];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for (int i = 0 ; i < STUDENT_NUM; i++) {
        pthread_create(&student_pid[i], &attr, simulate_student, NULL);
        pthread_join(student_pid[i], NULL);
    }
    return 0;
}


void *simulate_student(void *param) {
    // 1. generate a random number as the initial sleep time


    // 2. simulate go to ta office: check mutex lock for chairs 

    // 3. while chairs are full, sleep at a random time again and have another try

    // 4. if chairs are not full, go check whether can get help now
        // 4.1 if can, just get help
        // 4.2 else put in waiting queue
}

void *simulate_ta(void *param) {
    // mutex lock on office

    // counting samephore on chairs
}

 void rand_sleep(void){ 
 	int time = rand() % STUDENT_SLEEP_MAX + 1; 
 	sleep(time); 
 }