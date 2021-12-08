extern char** global_nodes;

extern int global_num_nodes;

extern int mynode;

char* read_node_name(int lockno);

void psu_init_lock( int num_nodes); 

void psu_mutex_lock(int lock_number);

void psu_mutex_unlock(int lock_number);