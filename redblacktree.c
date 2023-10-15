#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "redblacktree.h"

static const bool RED = true;
static const bool BLACK = false;

struct tNode{

  KeyPointer key;
  ValuePointer value;
  struct tNode *left, *right;
  bool color;
  int N;  
};

struct tNode *root;


static struct tNode* put_node(struct tNode* h, KeyPointer keyP, ValuePointer valueP);

static bool isRed(struct tNode *node){
  if (node == NULL) {
    return false;
  }
  return node->color == RED;
}

static void flipColors(struct tNode *node){
  node->color = RED;
  node->left->color = BLACK;
  node->right->color = BLACK;  
}

static int size_node(struct tNode *node){
  if (node == NULL){
    return 0;
  } else {
    return node -> N;
  }
}


int size(){
  return size_node(root);
}

static struct tNode * rotateLeft(struct tNode *h){
  struct tNode *x = h -> right;
  h -> right = x -> left;
  x -> left = h;
  x -> color = h -> color;
  h -> color = RED;
  x -> N = h -> N;
  h -> N = 1 + size_node(h->left) + size_node(h-> right);   
  return x;
}

static struct tNode * rotateRight(struct tNode *h){
  struct tNode *x = h -> left;
  h -> left = x -> right;
  x -> right = h;
  x -> color = h -> color;
  h -> color = RED;
  x -> N = h -> N;
  h -> N = 1 + size_node(h->left) + size_node(h-> right);   
  return x;
}


void put (KeyPointer key, ValuePointer value){
  printf("put key \"%s\" with root %s\n", key, root != NULL? root-> key : "NULL");
  root = put_node(root, key, value);
  root -> color = BLACK;
}

static struct tNode* put_node(struct tNode* h, KeyPointer keyP, ValuePointer valueP) {  
  if (h == NULL){
    struct tNode* result = (struct tNode*) malloc(sizeof(struct tNode));
    printf("malloc for key \"%s\"\n", keyP);
    result -> key = keyP;
    result -> value = valueP;
    result -> N = 1;
    result -> color = RED;     
    return result;
  } else {
    printf("keyP= %s h->key=%s\n", keyP, h -> key);
  }

  int cmp = strcmp(keyP, h -> key);
  printf("cmp = %d  %s %s\n", cmp, keyP, h -> key);
  if (cmp < 0) {
    h -> left = put_node(h -> left, keyP, valueP);
  } else if (cmp > 0){
    h -> right = put_node(h -> right, keyP, valueP);
  } else {
    h -> value = valueP;
  }

  if (isRed(h -> right) && !isRed(h -> left)) {
    h = rotateLeft(h);
  }
  if (isRed(h -> left) && isRed(h -> left -> left)) {
    h = rotateRight(h);
  }
  if (isRed(h -> left) && isRed(h -> right)) {
    flipColors(h);
  }
  h -> N = size_node(h -> left) + size_node(h -> right) + 1;

  printf("root word is \"%s\"\n", root -> key);
  return h;  
}



