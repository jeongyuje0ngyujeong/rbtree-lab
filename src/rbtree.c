#include "rbtree.h"

#include <stdlib.h>

//////////////////////////////////////////////////////////////////
void printTree(rbtree *t, node_t *node)
{
  if (t == NULL || node == t->nil)
    return;

  printf("%d(%d) ", node->key, node->color);
  printTree(t, node->left);
  printTree(t, node->right);
}
//////////////////////////////////////////////////////////////////

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil_node = (node_t *)malloc(sizeof(node_t));
  nil_node->color = RBTREE_BLACK;
  nil_node->key = 0;
  nil_node->left = nil_node;
  nil_node->right = nil_node;
  nil_node->parent = nil_node;

  p->root = nil_node;
  p->nil = nil_node;

  return p;
}

void delete_rbtree(rbtree *t)
{
  recursive_delete(t, t->root);
  free(t->nil);
  free(t); 
}

// 재귀로 후위순회하며 삭제
void recursive_delete(rbtree *t, node_t *cur)
{
  if (cur->left == t->nil && cur->right == t->nil)
  {
    if (cur->parent->left == cur)
    {
      cur->parent->left = t->nil;
    
  } else {
      cur->parent->right = t->nil;
  }

    free(cur);
    return;
  }

  recursive_delete(t, cur->left);
  recursive_delete(t, cur->right);
  if (cur->parent->left == cur)
    {
      cur->parent->left = t->nil;
    
  } else {
      cur->parent->right = t->nil;
  }

  free(cur);
  return;
}

// insert 함수
node_t *rbtree_insert(rbtree *t, const key_t key)
{
  node_t *insertHere = t->nil;
  node_t *cur = t->root;

  while (cur != t->nil)
  {
    insertHere = cur;
    if (key < cur->key)
      cur = cur->left;
    else
      cur = cur->right;
  }

  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  newNode->parent = insertHere;
  newNode->key = key;
  newNode->left = t->nil;
  newNode->right = t->nil;
  newNode->color = RBTREE_RED;

  if (insertHere == t->nil)
  {
    t->root = newNode;
  }
  else if (key < insertHere->key)
  {
    insertHere->left = newNode;
  }
  else
  {
    insertHere->right = newNode;
  }

  rbtree_insert_fixup(t, newNode);

  return t->root;
}

// insert 후 속성 위반 확인하여 재조정하는 함수
node_t *rbtree_insert_fixup(rbtree *t, node_t *cur) {
  while (cur->parent->color == RBTREE_RED) {
    node_t *parent = cur->parent;
    node_t *grandParent = parent->parent;
    node_t *uncle;

    if (parent == grandParent->left) {
      uncle = grandParent->right;

      if (uncle->color == RBTREE_RED) {
        parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        grandParent->color = RBTREE_RED;
        cur = grandParent;
      
      } else {
        if (cur == parent->right) {
          cur = cur->parent;
          left_rotate(t, cur);  
        }

        cur->parent->color = RBTREE_BLACK;
        cur->parent->parent->color = RBTREE_RED;
        right_rotate(t, cur->parent->parent);

      }

    } else {
      uncle = grandParent->left;
      if (uncle->color == RBTREE_RED) {
        parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        grandParent->color = RBTREE_RED;
        cur = grandParent;

      } else {
        if (cur == parent->left) {
          cur = cur->parent;
          right_rotate(t, cur);  
        }

        cur->parent->color = RBTREE_BLACK;
        cur->parent->parent->color = RBTREE_RED;
        left_rotate(t, cur->parent->parent);

      }
    }
  }
  
  t->root->color = RBTREE_BLACK;
  return t->root;
}

  void left_rotate(rbtree * t, node_t * std)
  {
    node_t *target = std->right;

    std->right = target->left;

    if (target->left != t->nil) target->left->parent = std;

    target->parent = std->parent;

    if (std->parent == t->nil) t->root = target;
    else if (std->parent->left == std) std->parent->left = target;
    else std->parent->right = target;

    target->left = std;
    std->parent = target;
  }

  void right_rotate(rbtree * t, node_t * std) {
    node_t *target = std->left;

    std->left = target->right;

    if (target->right != t->nil) target->right->parent = std;

    target->parent = std->parent;

    if (std->parent == t->nil) t->root = target;
    else if (std->parent->left == std) std->parent->left = target;
    else std->parent->right = target;

    target->right = std;
    std->parent = target;
  }

  int checkPlace(node_t * parent, node_t * cur)
  {
    int parentPlace = parent->parent->left == parent ? -1 : 1;
    int curPlace = cur->parent->left == cur ? -1 : 1;
    return parentPlace == curPlace;
  }

  node_t *rbtree_find(const rbtree *t, const key_t key)
  {
    // TODO: implement find
    return t->root;
  }

  node_t *rbtree_min(const rbtree *t)
  {
    // TODO: implement find
    return t->root;
  }

  node_t *rbtree_max(const rbtree *t)
  {
    // TODO: implement find
    return t->root;
  }

  int rbtree_erase(rbtree * t, node_t * p)
  {
    // TODO: implement erase
    return 0;
  }

  int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
  {
    // TODO: implement to_array
    return 0;
  }
