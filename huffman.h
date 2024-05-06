#define OUT_ERR "hdecode [ ( infile | - ) [ outfile ] ]\n"
#define BUF_SIZE 4096
#define FALSE -1

/* Collection of Nodes that points to the next node "Linked List */
typedef struct DataNode
{	
	short int data;	
	unsigned int value;
	struct DataNode *next;
	struct DataNode *left;
	struct DataNode *right;
}DataNode;


DataNode *create_node();
DataNode *build_tree(DataNode *);
short int *link_to_array(DataNode *);
char *dfs(DataNode *, short);
short dfs_traversal(DataNode *, char *, short int, int);
void insert_node(unsigned char, DataNode *);
void sort_list(DataNode *);
void free_list(DataNode *);
void free_string(short int *);


