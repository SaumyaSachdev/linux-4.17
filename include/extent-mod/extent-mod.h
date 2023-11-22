#ifndef _EXTENT_MOD_
#define _EXTENT_MOD_

#include <linux/rbtree.h>

typedef struct extent_node {
	unsigned long start_pfn;
	unsigned long end_pfn;
	struct rb_node node;
} extent_node;

// check if the new pfn matches the start_pfns of existing nodes
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

// create new node in rbtree
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

// check if the new pfn matches the end_pfns of existing nodes
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

// recursively call this function to get count of all nodes
static inline long get_my_rb_count (struct rb_node *node)
{
	if(!node) {
		return 0;
	} else {
		return get_my_rb_count(node->rb_left) + get_my_rb_count(node->rb_right) + 1;
	}
}

// test to verify the value of extent
static inline long get_extent_pages_count (struct rb_node *node)
{
	if(!node) {
		return 0;
	} else {
		extent_node *exnode = rb_entry(node, extent_node, node);
		// printk(KERN_ERR " exnode->start_pfn  %ld exnode->end_pfn  %ld\n",  exnode->start_pfn, exnode->end_pfn);
		long totalPages = exnode->end_pfn - exnode->start_pfn;
		return  totalPages + get_extent_pages_count(node->rb_left) + get_extent_pages_count(node->rb_right) + 1;
	}
}

static inline void delete_all_extent_nodes (struct rb_root *root)
{	
	while(root->rb_node)
		rb_erase(root->rb_node, root);

}


static inline void insert_and_merge_extent_node(struct rb_root *root, unsigned long pagepfn) {
	
	extent_node* left = NULL, *right = NULL;
	extent_node *new = (extent_node*) kmalloc(sizeof(extent_node), GFP_KERNEL);


	new->start_pfn = pagepfn;
	new->end_pfn = pagepfn;
	left = extent_node_search_end(root, pagepfn - 1);
	right = extent_node_search_start(root, pagepfn + 1);

	if(left)
	{
		new->start_pfn = left->start_pfn;
		rb_erase(&left->node, root);
	}
	if(right)
	{
		new->end_pfn = right->end_pfn;
		rb_erase(&right->node, root);
	}
	insert_extent_node(root, new);


}


#endif 