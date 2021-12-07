#include "msg.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>



int Our_Sequence_Number[100]; // the sequence number chosen by a request originating at this node
int Highest_Sequence_Number[100]; //the highest sequence number seen in any REQUEST message sent or received
int Outstanding_Reply_Count[100]; // the number of REPLY messages still expected

bool Requesting_Critical_Section[100]; //TRUE when this node is requesting access to its critial section
bool* Reply_Deferred[100]; //Reply_Deferred [j] is TRUE when this node is deferring a REPLY to j's REQUEST message

pthread_mutex_t Shared_vars[100]; // Interlock access to the above shared variables when necessary

int Lock_Exists[100] = {0}; //TRUE if a lock exists for this node

bool_t request_1_svc(input *inp, output *outp, struct svc_req *rqstp)
{
    if (inp->you == inp->me && inp->release==0 ){
        //request from local client
        int me = inp->you;
        int N = inp->num_nodes;
        int locknum = inp->lockno;

        if ( Lock_Exists[locknum] == 0 ){
            //create a lock
            Highest_Sequence_Number[locknum] = 0;
            Our_Sequence_Number[locknum] = 0;
            Reply_Deferred[locknum] = (bool*) malloc(sizeof(bool)*N);
            for (int i=0; i<N; i++){
                Reply_Deferred[locknum][i] = false;
            }
            Lock_Exists[locknum] = 1;
            pthread_mutex_init(&Shared_vars[locknum], NULL);
            printf("Lock %d created in node %d\n", locknum,me);
        }

        pthread_mutex_lock(&Shared_vars[locknum]);
        Requesting_Critical_Section[locknum] = true;
        Our_Sequence_Number[locknum] = Highest_Sequence_Number[locknum] + 1;
        pthread_mutex_unlock(&Shared_vars[locknum]);

        outp->seq = Our_Sequence_Number[locknum];
        return true;
        
        
    } else if (inp->you != inp->me && inp->release == 1){
        //request from remote client
        int me = inp->you;
        int N = inp->num_nodes;
        int locknum = inp->lockno;
        
        Requesting_Critical_Section[locknum] = false;

        for (int j=0; j<N; j++){
            if (Reply_Deferred[locknum][j]){
                Reply_Deferred[locknum][j] = false;
        }}
        return true;
    } else {
        int me = inp->you;
        int N = inp->num_nodes;
        int locknum = inp->lockno;
        int seq_num = inp->seq;
        int you = inp->me;

        if (Lock_Exists[locknum] == 0){
            //create a lock
            Highest_Sequence_Number[locknum] = 0;
            Requesting_Critical_Section[locknum] = false;
            Reply_Deferred[locknum] = (bool*) malloc(sizeof(bool)*N);
            for (int i=0; i<N; i++){
                Reply_Deferred[locknum][i] = false;
            }
            Lock_Exists[locknum] = 1;
            pthread_mutex_init(&Shared_vars[locknum], NULL);
            printf("Lock %d created in node %d\n", locknum,me);
        }

        if (seq_num > Highest_Sequence_Number[locknum]){
            Highest_Sequence_Number[locknum] = seq_num;
        }
        pthread_mutex_lock(&Shared_vars[locknum]);
        bool defer = Requesting_Critical_Section[locknum] & ((seq_num > Our_Sequence_Number[locknum]) | (seq_num == Highest_Sequence_Number[locknum])&& you > me);
        pthread_mutex_unlock(&Shared_vars[locknum]);
        if (defer){
            Reply_Deferred[locknum][you] = true;\
        }
        while (Reply_Deferred[locknum][you]){
            sleep(1);
        }
        printf("node %d reply to node %d for lock %d.\n",me, you, locknum);
        return true;
        
    }
    return true;
    
}

int dislock_1_freeresult(SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
    xdr_free(xdr_result, result);
    return 1;
}