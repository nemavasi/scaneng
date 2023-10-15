#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "redblacktree.h"

static const bool RED = true;
static const bool BLACK = false;

struct tNode{

  KeyType key;
  ValueType value;
  struct tNode *left, *right;
  bool color;
  int N;  
};

static struct tNode *root;

static struct tNode* put_node(struct tNode* h, KeyType keyP, ValueType valueP);
static void printTree(struct tNode* h);
static void transferTree(struct tNode* h, void (*fp)(int, char *));

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


void put(KeyType key, ValueType value){
  root = put_node(root, key, value);
  root -> color = BLACK;
}

static struct tNode* put_node(struct tNode* h, KeyType keyP, ValueType valueP) {  
  if (h == NULL){
    struct tNode* result = (struct tNode*) malloc(sizeof(struct tNode));
    result -> key = keyP;
    result -> value = valueP;
    result -> N = 1;
    result -> color = RED;     
    return result;
  }

  int cmp = strcmp(keyP, h -> key);
  if (cmp < 0) {
    h -> left = put_node(h -> left, keyP, valueP);
  } else if (cmp > 0){
    h -> right = put_node(h -> right, keyP, valueP);
  } else {
    //h -> value = valueP;
    h -> value++;
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

  return h;  
}

void printSorted() {
    printTree(root);
}

static void printTree(struct tNode* h) {
    if (h == NULL){
        return;
    }
    printTree(h -> left);
    printf("\"%s\" - %d\n", h -> key, h -> value);
    printTree(h -> right);
}

void transfer(void (*fp)(int, char *)) {
  transferTree(root, fp);
}

static void transferTree(struct tNode* h, void (*fp)(int, char *)) {
    if (h == NULL){
        return;
    }
    transferTree(h -> left, fp);
    (*fp)(h -> value, h -> key);
    transferTree(h -> right, fp);
}



