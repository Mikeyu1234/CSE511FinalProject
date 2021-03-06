/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "msg.h"


void
dsm_1(char *host)
{
	CLIENT *clnt;
	enum clnt_stat retval_1;
	void *result_1;
	InitInp  init_1_arg;
	enum clnt_stat retval_2;
	int result_2;
	MallocInp  malloc_1_arg;
	enum clnt_stat retval_3;
	RequestRet result_3;
	char * request_1_arg;
	enum clnt_stat retval_4;
	int result_4;
	RemoteInp  remoterdwr_1_arg;
	enum clnt_stat retval_5;
	char *result_5;
	NetworkInp  networkop_1_arg;
	enum clnt_stat retval_6;
	int result_6;
	char * free_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DSM, SERVICE_V1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	retval_1 = init_1(&init_1_arg, &result_1, clnt);
	if (retval_1 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_2 = malloc_1(&malloc_1_arg, &result_2, clnt);
	if (retval_2 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_3 = request_1(&request_1_arg, &result_3, clnt);
	if (retval_3 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_4 = remoterdwr_1(&remoterdwr_1_arg, &result_4, clnt);
	if (retval_4 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_5 = networkop_1(&networkop_1_arg, &result_5, clnt);
	if (retval_5 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
	retval_6 = free_1(&free_1_arg, &result_6, clnt);
	if (retval_6 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	dsm_1 (host);
exit (0);
}
