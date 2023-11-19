#ifndef _EXTENT_MOD_
#define _EXTENT_MOD_

#include <linux/rbtree.h>

typedef struct header_struct {
	int header_test;
} header_struct;


typedef struct extent_node {
	unsigned long start_pfn;
	unsigned long end_pfn;
	struct rb_node node;
} extent_node;

 
// long get_my_rb_count (rb_node *node)
// {
// 	if(!node)
// 	{
// 		return 0;
// 	}	
// 	else
// 	{
// 		return get_my_rb_count(node->rb_left) + get_my_rb_count(node->rb_right) + 1;
// 	}
// }


// struct my_stuff *my_rb_search(struct rb_root *root, unsigner long value)
// {
// 	struct rb_node *node = root->rb_node;  /* top of the tree */

// 	while (node)
// 	{
// 		extent_node *stuff = rb_entry(node, extent_node, node);

// 		if (stuff->start_pfn >= value)
// 			node = node->rb_left;
// 		else if (stuff->start_pfn < value)
// 			node = node->rb_right;
// 		else
// 		return stuff;  /* Found it */
// 	}
// 	return NULL;
// }

// void insert_extent_node(struct rb_root *root, extent_node *ex_node) {
// 	struct rb_node **newN = &root->rb_node, *parent = NULL;
// 	unsigned long value = ex_node->start_pfn;
// 	extent_node *node;
// 	while (*newN) {
// 		parent = *newN;
// 		node = rb_entry(*newN, struct extent_node, node);
// 		if (node->start_pfn > value) {
// 			newN = &((*newN)->rb_left);
// 		} else {
// 			newN = &((*newN)->rb_right);
// 		}
// 	}
// 	rb_link_node(&ex_node->node, parent, newN);
// 	rb_insert_color(&ex_node->node, root);
// }

// void my_rb_insert(struct rb_root *root, extent_node *new)
// {
// 	struct rb_node **link = &root->rb_node, *parent;
// 	unsigned long value = new->start_pfn;

// 	/* Go to the bottom of the tree */
// 	while (*link)
// 	{
// 		parent = *link;
// 		extent_node *stuff = rb_entry(parent, extent_node, node);

// 		if (stuff->start_pfn > value)
// 			link = &(*link)->rb_left;
// 		else
// 			link = &(*link)->rb_right;
// 	}

// 	/* Put the new node there */
// 	rb_link_node(new, parent, link);
// 	rb_insert_color(new, root);
// }
#endif 