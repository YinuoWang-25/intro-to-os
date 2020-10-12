#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h> 

#define STUDENT_NUM 5
#define WAITING_CHAIR_NUM 3
#define STUDENT_SLEEP_MAX 5 

sem_t sem_waiting_chairs;
sem_t sem_ta;
pthread_mutex_t mutex_thread;

int chairs[3];
int waiting_student_num = 0;
int next_seating_position = 0;
int next_teaching_position = 0;
int is_ta_sleeping = 0;

// simulate student and ta using pthread
void *simulate_student(void* student_id);
void *simulate_ta();
int isWaiting( int student_id );

int rand_sleep(void); 

int main(void) {

    // initial locks
	sem_init( &sem_waiting_chairs, 0,  WAITING_CHAIR_NUM);
	sem_init( &sem_ta, 0, 1);

    // create students thread and join them
    pthread_t student_pid[STUDENT_NUM];
    pthread_t ta; 
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&ta, NULL, simulate_ta, NULL); 

    int student_ids[STUDENT_NUM];

    for (int i = 0 ; i < STUDENT_NUM; i++) {
        student_ids[i] = i + 1;
        pthread_create(&student_pid[i], &attr, simulate_student,  (void*) &student_ids[i]);
    }
    for (int i = 0; i < STUDENT_NUM; i++) {
        pthread_join(student_pid[i], NULL);
    }
    pthread_join(ta, NULL); 
    return 0;
}


void *simulate_student(void* student_id) {
    
    int id = *(int*)student_id;
    printf( "Student %d registered.\n", id);

    while (1) {
        //if student is waiting, continue waiting
		if ( isWaiting( id ) == 1 ) { continue; }

        // sleep for a random time
        rand_sleep();

        // ask to begin check
        pthread_mutex_lock( &mutex_thread );

        if (waiting_student_num < WAITING_CHAIR_NUM) {
            // student has a seat at waiting chairs
            chairs[next_seating_position] = id;
            waiting_student_num++;
            next_seating_position = ( next_seating_position + 1 ) % WAITING_CHAIR_NUM;

            // free up mutex_thread
            pthread_mutex_unlock( &mutex_thread );
            printf( "Student %d took a seat. Students waiting = %d.\n", id, waiting_student_num );

            //wake TA if sleeping
			sem_wait( &sem_waiting_chairs );
			sem_wait( &sem_ta );
        } else {
            pthread_mutex_unlock( &mutex_thread );
            printf( "Student %d will try later.\n", id);
        }
    }
}

void *simulate_ta(void *param) {
    printf( "TA is here.\n" );
    while (1) {
        if ( waiting_student_num > 0 ) {
            is_ta_sleeping = 0;
            sem_post( &sem_waiting_chairs );

            pthread_mutex_lock( &mutex_thread );

            chairs[waiting_student_num]=0;
			waiting_student_num--;
			next_teaching_position = ( next_teaching_position + 1 ) % WAITING_CHAIR_NUM;
            printf( "student %d get in TA room,  Students waiting = %d.\n", chairs[next_teaching_position], waiting_student_num);
			pthread_mutex_unlock( &mutex_thread );

            //TA helping student.
            int help_time = rand_sleep();
			printf( "Helped student %d for %d seconds.\n", chairs[next_teaching_position], help_time );
            sem_post( &sem_ta );
        } else {
			if ( is_ta_sleeping == 0 ) {
				printf( "No students waiting. Sleeping.\n" );
				is_ta_sleeping = 1;

			}
        }
    }
}

/* util function to make thread sleep for a random period  */
int rand_sleep(void){ 
    int time = rand() % STUDENT_SLEEP_MAX + 1; 
 	sleep(time); 
    return time;
}

/* util function to check whether student is already waiting on chair  */
int isWaiting( int student_id ) {
	for ( int i = 0; i < 3; i++ ) {
		if ( chairs[i] == student_id ) { return 1; }
	}
	return 0;
}