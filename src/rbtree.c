#include "rbtree.h"

#include <stdlib.h>

#define SENTINEL
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

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *nil_node = (node_t *)malloc(sizeof(node_t));
  nil_node->color = RBTREE_BLACK;
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
  if(cur == t->nil) return;

  recursive_delete(t, cur->left);
  recursive_delete(t, cur->right);
  free(cur);

  // if (cur->left != t->nil) recursive_delete(t, cur->left);  
  // if (cur->right != t->nil) recursive_delete(t, cur->right);    
  // if (cur != t->nil) free(cur);
  // return;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  node_t *insertHere = t->nil;
  node_t *cur = t->root;

  while (cur != t->nil)
  {
    insertHere = cur;
    if (key < cur->key) cur = cur->left;
    else cur = cur->right;
  }

  node_t *newNode = (node_t *)malloc(sizeof(node_t));
  newNode->parent = insertHere;
  newNode->key = key;
  newNode->left = t->nil;
  newNode->right = t->nil;
  newNode->color = RBTREE_RED;

  if (insertHere == t->nil) t->root = newNode;
  else if (key < insertHere->key) insertHere->left = newNode;
  else insertHere->right = newNode;
  
  rbtree_insert_fixup(t, newNode);

  return t->root;
}

// insert 후 속성 위반 확인하여 재조정하는 함수
node_t *rbtree_insert_fixup(rbtree *t, node_t *cur)
{
  while (cur->parent->color == RBTREE_RED)
  {
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

void left_rotate(rbtree *t, node_t *std) {
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

void right_rotate(rbtree *t, node_t *std) {
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

int checkPlace(node_t *parent, node_t *cur) {
  int parentPlace = parent->parent->left == parent ? -1 : 1;
  int curPlace = cur->parent->left == cur ? -1 : 1;
  return parentPlace == curPlace;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *check = t->root;

  // while (check != t->nil) {
  //   if (check->key == key) return check;
  
  //   if (check->key < key) check = check->right; 
  //   else check = check->left;
  
  // }
  // return NULL;

  if (check == t->nil) return NULL; 
  
  while (check->key != key) { //40056
    // if(check->key == key) return check; - 60084

    if (check->key < key) check = check->right;
    else check = check->left;

    if (check == t->nil) return NULL; 
  }
  
  return check;
}

node_t *rbtree_min(const rbtree *t) {
  node_t *cur = t->root;

  while (cur->left != t->nil) {
    cur = cur->left;
  }
  
  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *cur = t->root;

  while (cur->right != t->nil) {
    cur = cur->right;
  }
  
  return cur;
}

int rbtree_erase(rbtree *t, node_t *p) {
  node_t *x, *y;
  y = p;
  color_t deleteColor = y->color;
  if (p->left == t->nil) {
    x = p->right;
    transPlnat(t, p, p->right);

  } else if (p->right == t->nil) {
    x = p->left;
    transPlnat(t, p, p->left);
  
  } else {
    y = sub_tree_min(t, p->right);
    deleteColor = y->color;
    x = y->right;

    if (y->parent == p) x->parent = y;
    else {
      transPlnat(t, y, y->right);
      y->right = p->right;
      y->right->parent = y;
    }

    transPlnat(t, p, y);
    y->left = p->left;
    y->left->parent = y;
    y->color = p->color;
  }
  free(p);

  if (deleteColor == RBTREE_BLACK) delete_fixup(t, x);
  return 0;
}

void delete_fixup(rbtree *t, node_t *doublyBlack) {
  node_t *brother;
  while (doublyBlack != t->root && doublyBlack->color == RBTREE_BLACK) {
    if (doublyBlack == doublyBlack->parent->left) {
      brother = doublyBlack->parent->right;

      if (brother->color == RBTREE_RED) {
        brother->color = RBTREE_BLACK;
        doublyBlack->parent->color = RBTREE_RED;
        left_rotate(t, doublyBlack->parent);
        brother = doublyBlack->parent->right;
      }

      if (brother->left->color == RBTREE_BLACK && brother->right->color == RBTREE_BLACK) {
        brother->color = RBTREE_RED;
        doublyBlack = doublyBlack->parent;

      } else {
        if (brother->right->color == RBTREE_BLACK) {
          brother->left->color = RBTREE_BLACK;
          brother->color = RBTREE_RED;
          right_rotate(t, brother);
          brother = doublyBlack->parent->right;
        }

        brother->color = doublyBlack->parent->color;
        doublyBlack->parent->color = RBTREE_BLACK;
        brother->right->color = RBTREE_BLACK;
        left_rotate(t, doublyBlack->parent);
        doublyBlack = t->root;
    }
      

    } else {
      brother = doublyBlack->parent->left;

      if (brother->color == RBTREE_RED) {
        brother->color = RBTREE_BLACK;
        doublyBlack->parent->color = RBTREE_RED;
        right_rotate(t, doublyBlack->parent);
        brother = doublyBlack->parent->left;
      }

      if (brother->right->color == RBTREE_BLACK && brother->left->color == RBTREE_BLACK) {
        brother->color = RBTREE_RED;
        doublyBlack = doublyBlack->parent;

      } else {
        if (brother->left->color == RBTREE_BLACK) {
          brother->right->color = RBTREE_BLACK;
          brother->color = RBTREE_RED;
          left_rotate(t, brother);
          brother = doublyBlack->parent->left; 
        }

        brother->color = doublyBlack->parent->color;
        doublyBlack->parent->color = RBTREE_BLACK;
        brother->left->color = RBTREE_BLACK;
        right_rotate(t, doublyBlack->parent);
        doublyBlack = t->root;
      } 
    }
  }
  doublyBlack->color = RBTREE_BLACK;
}

node_t *sub_tree_min(rbtree *t, node_t *check) {
  node_t *cur = check;

  while (cur->left != t->nil) {
    cur = cur->left;
  }
  
  return cur;
}

void transPlnat(rbtree *t, node_t *target, node_t *source) {
  if (target->parent == t->nil) t->root = source;
  else if (target == target->parent->left) target->parent->left = source;
  else target->parent->right = source;

  source->parent = target->parent;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  recursive_find_node(t, t->root, &arr, arr+n);
  return 0;
}

//중위순회로 값 넣기 left - root - right
void recursive_find_node(const rbtree *t, node_t *cur, key_t **arr, key_t *last_address) {
  if (cur == t->nil || last_address == *arr) return;
  
  recursive_find_node(t, cur->left, arr, last_address);
  **arr = cur->key;
  (*arr)++;
  recursive_find_node(t, cur->right, arr, last_address);
}
