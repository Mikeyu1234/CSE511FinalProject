#define  _POSIX_C_SOURCE 200809L
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "msg.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <signal.h>

#include "psu_dsm.h"

void handler_invalid (int signal, siginfo_t *info, ucontext_t* ctx);
void hangler_server (int signal, siginfo_t* info, ucontext_t* ctx);

void initializeDSM(){
    struct sigaction act;
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = handler_invalid;
    sigemptyset(&act.sa_mask);
    sigaction(SIGSEGV, &act, NULL);

    
}

void psu_dsm_register_datasegment(void* psu_ds_start, size_t psu_ds_size){
    
}
