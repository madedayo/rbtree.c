#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rbtree.h"
 
int main(int argc, char const *argv[])
{
	double duration;
	double room;
 
	rbtree_t t = {};
	rbtree_node_t s = {};
	rbtree_init(&t, &s, rbtree_insert_value);
 
	const int cnt = 1<<20;
	const int max_len = 15;
 
#define TEST_VALUES {"apple", "banana", "cherry", "grape", "lemon", "mango", "pear", "pineapple", "strawberry", "watermelon"}
 
	/* for gcc */
	char* v[] = TEST_VALUES;
	/* for g++ */
	// char v[][max_len] = TEST_VALUES;
 
	/* Default stack size in Ubuntu Kylin 14.04 is 8MB. */
	/* It's not enough. So I use memory in heap which offers a lot larger room. */
	rbtree_node_t* n = (rbtree_node_t*)calloc(cnt, sizeof(rbtree_node_t));
	int i;
 
	long time1 = clock();
 
	for (i = 0; i < cnt; i++)
	{
		n[i].key = i+1;
		n[i].value = v[i%10];
		n[i].node_cnt = 1;
		rbtree_insert(&t, &n[i]);
	}
 
	srand( (unsigned int)time(0) );
	int no = rand()%cnt;
	printf("n[%d]->key = %d\n", no, rbtree_index(&t, no)->key);
 
	long time2 = clock();
	room = 48.0*cnt/(1<<20);
	duration = (double)(time2 - time1) / CLOCKS_PER_SEC;
	printf("Inserting %d nodes costs %.2fMB and spends %f seconds.\n", cnt, room, duration);
 
	const int search_cnt = 1<<10;
	for( i = 0 ; i < search_cnt ; i++ )
	{
		rbtree_find(&t, (rand()%cnt)+1);
	}
 
	long time3 = clock();
	duration = (double)(time3 - time2) / CLOCKS_PER_SEC;
	printf("Searching %d nodes among %d spends %f seconds.\n", search_cnt, cnt, duration);
 
	const int index_cnt = 1<<10;
	for( i = 0 ; i < index_cnt ; i++ )
	{
		rbtree_index(&t, (rand()%cnt));
	}
 
	long time4 = clock();
	duration = (double)(time4 - time3) / CLOCKS_PER_SEC;
	printf("Indexing %d nodes among %d spends %f seconds.\n", index_cnt, cnt, duration);
 
	const int delete_cnt = 1<<10;
	int nums[delete_cnt];
	int num;
	/* Let's hash! */
	char* mark = (char*)calloc(cnt, sizeof(char));
	memset(mark, 0, cnt*sizeof(char));
	for(i = 0; i < delete_cnt; i++)
	{
		for(;;)
		{
			num = rand()%cnt;
			if (mark[num] == 0)
			{
				mark[num] = 1;
				nums[i] = num;
				break;
			}
		}
	}
 
	long time5 = clock();
	duration = (double)(time5 - time4) / CLOCKS_PER_SEC;
	printf("Hash %d times spends %f seconds.\n", delete_cnt, duration);
 
	for(i = 0; i < delete_cnt; i++)
	{
		rbtree_delete(&t, &n[nums[i]]);
	}
 
	long time6 = clock();
	duration = (double)(time6 - time5) / CLOCKS_PER_SEC;
	printf("Deleting %d nodes among %d spends %f seconds.\n", delete_cnt, cnt, duration);
	free(mark);
 
	int h = rbtree_height(&t, t.root);
	long time7 = clock();
	duration = (double)(time7 - time6) / CLOCKS_PER_SEC;
	printf("The height of the tree is %d. Getting it spends %f seconds.\n", h, duration);
 
	rbtree_traversal(&t, t.root, rbtree_visit);
	long time8 = clock();
	duration = (double)(time8 - time7) / CLOCKS_PER_SEC;
	printf("Traversal the tree spends %f seconds.\n", duration);
 
	printf("Count of nodes in the tree is %d.\n", rbtree_count(&t));
 
	free(n);
 
	return 0;
}

