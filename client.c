#include <rpc/rpc.h>
#include "global.h"
#include "msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int global_num_nodes;
char** global_nodes;
int mynode;

int main(int argc, char* argv[]){

	int num_nodes = 3;	
	char* nodes[100];
	nodes[0] = "130.203.16.31";
	nodes[1] = "130.203.16.32";
	nodes[2] = "130.203.16.56";
	
	if(argc < 2){
		printf("Input Error! Please use \" ./client #number \" to denote the client node number\n");
		return 0;	
	}
	mynode = strtol(argv[1],NULL,10);
	
	
	psu_init_lock(nodes, num_nodes);
	psu_mutex_lock(0);

	sleep(8);
	psu_mutex_unlock(0);

}