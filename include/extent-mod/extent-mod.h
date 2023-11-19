#ifndef _EXTENT_MOD_
#define _EXTENT_MOD_

#include <linux/rbtree.h>

typedef struct extent_node {
	unsigned long start_pfn;
	unsigned long end_pfn;
	struct rb_node node;
} extent_node;

static inline struct extent_node *extent_node_search_start(struct rb_root *root, int value)
{
	struct rb_node *node = root->rb_node;  /* top of the tree */

	while (node)
	{
		extent_node *exnode = rb_entry(node, extent_node, node);

		if (exnode->start_pfn > value)
			node = node->rb_left;
		else if (exnode->start_pfn < value)
			node = node->rb_right;
		else
			return exnode;  /* Found it */
	}
	return NULL;
}

static inline void insert_extent_node(struct rb_root *root, extent_node *ex_node) {
	struct rb_node **newN = &root->rb_node, *parent = NULL;
	unsigned long value = ex_node->start_pfn;
	extent_node *node;
	while (*newN) {
		parent = *newN;
		node = rb_entry(*newN, struct extent_node, node);
		if (node->start_pfn > value) {
			newN = &((*newN)->rb_left);
		} else {
			newN = &((*newN)->rb_right);
		}
	}
	rb_link_node(&ex_node->node, parent, newN);
	rb_insert_color(&ex_node->node, root);
}

static inline struct extent_node *extent_node_search_end(struct rb_root *root, int value)
{
	struct rb_node *node = root->rb_node;  /* top of the tree */

	while (node)
	{
		extent_node *exnode = rb_entry(node, extent_node, node);

		if (exnode->end_pfn > value)
			node = node->rb_left;
		else if (exnode->end_pfn < value)
			node = node->rb_right;
		else
			return exnode;  /* Found it */
	}
	return NULL;
}

static inline long get_my_rb_count (struct rb_node *node)
{
	if(!node) {
		return 0;
	} else {
		return get_my_rb_count(node->rb_left) + get_my_rb_count(node->rb_right) + 1;
	}
}
#endif 