#include <rpc/rpc.h>
#include "msg.h"
#include "global.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


#define MAX_NODE_NAME 20

void* remote_request(void* arg)
{
    input* inpp =(input*)arg;
    CLIENT *client;
    client = clnt_create(global_nodes[inpp->you], DISLOCK, LOCK_V1,"tcp");
    if (client == NULL)
    {
        printf("clnt_create error\n");
        exit(1);
    }

    output outp;
    enum clnt_stat ret;
    ret = request_1(inpp, &outp, client);
    if (ret != RPC_SUCCESS)
    {
        printf("request_1 error\n");
        exit(1);
    }

    return;
}

void psu_init_lock(char** nodes, int lockno){
    /*This function will create the lock specified by lockno. Here you can assume that all nodes will participate in the locking mechanism.*/
    global_nodes = (char **)malloc(sizeof(char *)*lockno);
    for ( int i = 0; i < lockno; i++)
    {
        global_nodes[i] = (char *)malloc(sizeof(char)*MAX_NODE_NAME);
        strcpy(global_nodes[i], nodes[i]);
    }
    global_num_nodes = lockno;
    return ;

}

void psu_mutex_lock(lockno){
    CLIENT *client;
    client = clnt_create(global_nodes[mynode], DISLOCK, LOCK_V1,"tcp");
    if (client == NULL)
    {
        printf("clnt_create error\n");
        exit(1);
    }
    input inp;
    inp.you = mynode;
    inp.me = mynode;
    inp.num_nodes = global_num_nodes;
    inp.lockno = lockno;
    inp.release = 0;
    output outp;
    enum clnt_stat ret;
    ret = request_1(&inp, &outp, client);
    if (ret != RPC_SUCCESS)
    {
        printf("request_1 error\n");
        exit(1);
    }

    int seq = outp.seq;
    pthread_t* tid = (pthread_t*)malloc(sizeof(pthread_t)*global_num_nodes);
    input* inpp = (input*)malloc(sizeof(input)*global_num_nodes);
    for (int i = 0; i < global_num_nodes; i++)
    {
        /* code */
        if (i != mynode)
        {
            /* code */
            inpp[i].you = i;
            inpp[i].me = mynode;
            inpp[i].num_nodes = global_num_nodes;
            inpp[i].lockno = lockno;
            inpp[i].seq = seq;
            pthread_create(&tid[i], NULL, remote_request, (void*)&inpp[i]);
        }
        
    }
    for (int i = 0; i < global_num_nodes; i++)
    {
        /* code */
        if (i != mynode)
        {
            /* code */
            pthread_join(tid[i], NULL);
        }
    }
    printf("Client %d get lock %d now", mynode, lockno);

}

void psu_mutex_unlock(lockno){

    CLIENT *client;
    client = clnt_create(global_nodes[mynode], DISLOCK, LOCK_V1,"tcp");
    if (client == NULL)
    {
        printf("clnt_create error\n");
    }

    input inp;
    inp.you = mynode;
    inp.me = mynode;
    inp.num_nodes = global_num_nodes;
    inp.lockno = lockno;
    inp.release = 1;
    output outp;
    enum clnt_stat ret;
    ret = request_1(&inp, &outp, client);
    if (ret != RPC_SUCCESS)
    {
        printf("request_1 error\n");
        exit(1);
    }
    printf("Client %d release lock %d now", mynode, lockno);


}