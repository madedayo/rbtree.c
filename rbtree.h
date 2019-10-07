# rbtree.h

/*****************
#ifndef _RBTREE_H_INCLUDED_
#define _RBTREE_H_INCLUDED_
 
/* the node structure of the red-black tree */
typedef struct rbtree_node_s rbtree_node_t;
/* Using type int means its range is -0x7fffffff-1~0x7fffffff. */
typedef int rbtree_key_t;
/* Abstract type is complicated to achieve with C so I use char* instead. */
typedef char* rbtree_data_t;
 
struct rbtree_node_s
{
	/* key of the node */
	rbtree_key_t	key;
	/* pointer of the parent of the node */
	rbtree_node_t*	parent;
	/* pointer of the left kid of the node */
	rbtree_node_t*	left;
	/* pointer of the right kid of the node */
	rbtree_node_t*	right;
	/* color of the node */
	unsigned char	color;
	/* pointer of the value of the node corresponding to the key */
	rbtree_data_t	value;
	/* count of nodes in the subtree whose root is the current node */
	int node_cnt;
};
 
/* the tree object stucture of the red-black tree */
typedef struct rbtree_s rbtree_t;
/* foundational insert function pointer */
typedef void (*rbtree_insert_p) (rbtree_t* root, rbtree_node_t* node);
/* foundational visit function pointer */
typedef void (*rbtree_visit_p) (rbtree_node_t* node);
 
struct rbtree_s
{
	/* the pointer of the root node of the tree */
	rbtree_node_t* root;
	/* black leaf nodes as sentinel */
	rbtree_node_t* sentinel;
	/* the polymorphic insert function pointer */
	rbtree_insert_p insert;
};
 
/* macros */
#define rbtree_init(tree, s, i)		\
rbtree_sentinel_init(s);			\
(tree)->root = s;				\
(tree)->sentinel = s;			\
(tree)->insert = i
 
#define rbtree_red(node)	((node)->color = 1)
#define rbtree_black(node)	((node)->color = 0)
#define rbtree_is_red(node)	((node)->color)
#define rbtree_is_black(node)	(!rbtree_is_red(node))
 /* copy n2's color to n1 */
#define rbtree_copy_color(n1, n2)	(n1->color = n2->color)
/* sentinel must be black cuz it's leaf node */
#define rbtree_sentinel_init(node)	\
rbtree_black(node);			\
(node)->node_cnt = 0
 
/* statements of public methods */
void rbtree_insert_value(rbtree_t* tree, rbtree_node_t* node);
void rbtree_insert(rbtree_t* tree, rbtree_node_t* node);
void rbtree_delete(rbtree_t* tree, rbtree_node_t* node);
/* get node by key */
rbtree_node_t* rbtree_find(rbtree_t* tree, rbtree_key_t key);
/* get node by order number */
rbtree_node_t* rbtree_index(rbtree_t* tree, int index);
int rbtree_height(rbtree_t* tree, rbtree_node_t* node);
int rbtree_count(rbtree_t* tree);
void rbtree_visit(rbtree_node_t* node);
void rbtree_traversal(rbtree_t* tree, rbtree_node_t* node, rbtree_visit_p);
 
#endif	/* _RBTREE_H_INCLUDED_ */
