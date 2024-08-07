#ifndef _RBTREE_H_
#define _RBTREE_H_

#include <stddef.h>
#include <stdio.h>


typedef enum { RBTREE_RED, RBTREE_BLACK } color_t;

typedef int key_t;

typedef struct node_t {
  color_t color;
  key_t key;
  struct node_t *parent, *left, *right;
} node_t;

typedef struct {
  node_t *root;
  node_t *nil;  // for sentinel
} rbtree;

rbtree *new_rbtree(void);
void delete_rbtree(rbtree *);

node_t *rbtree_insert(rbtree *, const key_t);
node_t *rbtree_insert_fixup(rbtree *, node_t *);
node_t *rbtree_find(const rbtree *, const key_t);
node_t *rbtree_min(const rbtree *);
node_t *rbtree_max(const rbtree *);
int rbtree_erase(rbtree *, node_t *);

int rbtree_to_array(const rbtree *, key_t *, const size_t);

void printTree(rbtree *t, node_t *node);
void left_rotate(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *y);
int checkPlace(node_t *parent, node_t *cur);
void recursive_delete(rbtree *t, node_t *cur);
void delete_fixup(rbtree *t, node_t *doublyBlack);
node_t *sub_tree_min(rbtree *t, node_t *check);
void transPlnat(rbtree *t, node_t *target, node_t *source);
void recursive_find_node(const rbtree *t, node_t *cur, key_t **arr, key_t *last_address);


////////////////////////////////////////
void printTree(rbtree *t, node_t *node);
////////////////////////////////////////



#endif  // _RBTREE_H_
