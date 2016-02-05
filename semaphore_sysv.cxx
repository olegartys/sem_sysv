/*
 * semaphore_sysv.cxx
 * 
 * Copyright 2016 olegartys <olegartys@olegartys-HP-Pavilion-15-Notebook-PC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define N 16

int main(int argc, char **argv)
{
	key_t key_id = ftok("/tmp/sem.temp", 1);
	if (key_id < 0) {
		perror("ftok");
		exit(errno);
	}
	
	int semid = semget(key_id, N, (IPC_CREAT | IPC_EXCL | 0666));
	if (semid < 0) {
		perror("semid");
		exit(errno);
	}
	
	struct sembuf sops[N];
	for (int i = 0; i < N; ++i) {
		sops[i].sem_num = i;
		sops[i].sem_op = 1;
		sops[i].sem_flg = /*SEM_UNDO*/0;
	}
	
	semop(semid, sops, N);
	
	return 0;
}

