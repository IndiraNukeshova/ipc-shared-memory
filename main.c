#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


#define MAX_LEN 256
int main() {	
	key_t  key;
	int shmid, semid;
	struct sembuf sops[2];
	
	key = ftok("ipcfile", 5);
	if (key == -1){
		perror("ftok");
		return EXIT_FAILURE;
	}
	
	shmid = shmget(key, MAX_LEN * sizeof(char), IPC_CREAT | 0666);
	if (shmid == -1){
		perror("shmget");
		return EXIT_FAILURE;
	}
	
	semid = semget(key, 2, IPC_CREAT | IPC_EXCL | 0666);
	if (semid == -1){
		perror("semget");
		return EXIT_FAILURE;
	}
	
	
	char* str = shmat(shmid, NULL, 0);
	strcpy(str, "Hello");
	if (str == NULL){
		perror("shmat");
		_exit(EXIT_FAILURE);
	}
	sops[0].sem_num = 0;
	sops[1].sem_num = 0;
	sops[0].sem_flg = 0;
	sops[1].sem_flg = 0;
	semctl(semid, 0, SETVAL, (int) 0);
	
	sops[0].sem_op = 10;
	semop(semid, &sops[0], 1);
	sops[1].sem_op = 1;
	semop(semid, &sops[1], 1);
	while(1){
		if (strcmp(str,"quit") == 0){
			sops[0].sem_op = -10;
			semop(semid, &sops[0], 1);
			sops[1].sem_op = -1;
			semop(semid, &sops[1], 1);
			shmdt(str);
			semctl(semid, 0, IPC_RMID);
			shmctl(shmid, IPC_RMID, NULL);
			return EXIT_SUCCESS;
		}
	}
}
