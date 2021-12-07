#define Read_Only 0
#define Read_Write 1
#define Invalid 2

extern char myip[20];

extern int mynode;

void initializeDSM();

typedef void* psu_dsm_ptr_t; 

psu_dsm_ptr_t psu_dsm_malloc(char* name, size_t size); 

void psu_dsm_free(char* name); 

void psu_dsm_register_datasegment(void* psu_ds_start, size_t psu_ds_size);

void * psu_ds_start();
size_t psu_ds_size();

typedef struct{
	void* shm_base;
	int size;
	char name[20];
	int shm_fd;
} Page_Table;

extern Page_Table page_table[100];
extern int page_num;