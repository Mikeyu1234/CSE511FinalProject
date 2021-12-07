/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _MSG_H_RPCGEN
#define _MSG_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif


struct InitInp {
	int mynode;
	int mypid;
};
typedef struct InitInp InitInp;

struct RequestRet {
	int size;
	int valid;
};
typedef struct RequestRet RequestRet;

struct MallocInp {
	char *name;
	int size;
};
typedef struct MallocInp MallocInp;

struct RegisterInp {
	char *psu_ds_start;
	int psu_ds_size;
};
typedef struct RegisterInp RegisterInp;

struct RemoteInp {
	char *name;
	int IsRead;
};
typedef struct RemoteInp RemoteInp;

struct NetworkInp {
	char *name;
	int NetOp;
	int mynode;
};
typedef struct NetworkInp NetworkInp;

#define DSM 0x2ffffff
#define SERVICE_V1 1

#if defined(__STDC__) || defined(__cplusplus)
#define INIT 1
extern  enum clnt_stat init_1(InitInp *, void *, CLIENT *);
extern  bool_t init_1_svc(InitInp *, void *, struct svc_req *);
#define MALLOC 2
extern  enum clnt_stat malloc_1(MallocInp *, int *, CLIENT *);
extern  bool_t malloc_1_svc(MallocInp *, int *, struct svc_req *);
#define REQUEST 3
extern  enum clnt_stat request_1(char **, RequestRet *, CLIENT *);
extern  bool_t request_1_svc(char **, RequestRet *, struct svc_req *);
#define REMOTERDWR 4
extern  enum clnt_stat remoterdwr_1(RemoteInp *, int *, CLIENT *);
extern  bool_t remoterdwr_1_svc(RemoteInp *, int *, struct svc_req *);
#define NETWORKOP 5
extern  enum clnt_stat networkop_1(NetworkInp *, char **, CLIENT *);
extern  bool_t networkop_1_svc(NetworkInp *, char **, struct svc_req *);
#define FREE 6
extern  enum clnt_stat free_1(char **, int *, CLIENT *);
extern  bool_t free_1_svc(char **, int *, struct svc_req *);
extern int dsm_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define INIT 1
extern  enum clnt_stat init_1();
extern  bool_t init_1_svc();
#define MALLOC 2
extern  enum clnt_stat malloc_1();
extern  bool_t malloc_1_svc();
#define REQUEST 3
extern  enum clnt_stat request_1();
extern  bool_t request_1_svc();
#define REMOTERDWR 4
extern  enum clnt_stat remoterdwr_1();
extern  bool_t remoterdwr_1_svc();
#define NETWORKOP 5
extern  enum clnt_stat networkop_1();
extern  bool_t networkop_1_svc();
#define FREE 6
extern  enum clnt_stat free_1();
extern  bool_t free_1_svc();
extern int dsm_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_InitInp (XDR *, InitInp*);
extern  bool_t xdr_RequestRet (XDR *, RequestRet*);
extern  bool_t xdr_MallocInp (XDR *, MallocInp*);
extern  bool_t xdr_RegisterInp (XDR *, RegisterInp*);
extern  bool_t xdr_RemoteInp (XDR *, RemoteInp*);
extern  bool_t xdr_NetworkInp (XDR *, NetworkInp*);

#else /* K&R C */
extern bool_t xdr_InitInp ();
extern bool_t xdr_RequestRet ();
extern bool_t xdr_MallocInp ();
extern bool_t xdr_RegisterInp ();
extern bool_t xdr_RemoteInp ();
extern bool_t xdr_NetworkInp ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_MSG_H_RPCGEN */
