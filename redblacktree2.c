#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "redblacktree2.h"

static const bool RED = true;
static const bool BLACK = false;

struct LinkedString {
  char * str;
  struct LinkedString * next;
};

//void putToLinkedTreeMap(int count, char * word);

//void printAllOrderedByCountDesc();


struct rbNode{
  int key;
  struct LinkedString * value;
  struct rbNode *left, *right;
  bool color;
  int N;  
};

static struct rbNode *root;

static struct rbNode* put_node(struct rbNode* h, int keyP, struct LinkedString * valueP);
static void printTree(struct rbNode* h);

static bool isRed(struct rbNode *node){
  if (node == NULL) {
    return false;
  }
  return node->color == RED;
}

static void flipColors(struct rbNode *node){
  node->color = RED;
  node->left->color = BLACK;
  node->right->color = BLACK;  
}

static int size_node(struct rbNode *node){
  if (node == NULL){
    return 0;
  } else {
    return node -> N;
  }
}


int countOfKeys(){
  return size_node(root);
}

static struct rbNode * rotateLeft(struct rbNode *h){
  struct rbNode *x = h -> right;
  h -> right = x -> left;
  x -> left = h;
  x -> color = h -> color;
  h -> color = RED;
  x -> N = h -> N;
  h -> N = 1 + size_node(h->left) + size_node(h-> right);   
  return x;
}

static struct rbNode * rotateRight(struct rbNode *h){
  struct rbNode *x = h -> left;
  h -> left = x -> right;
  x -> right = h;
  x -> color = h -> color;
  h -> color = RED;
  x -> N = h -> N;
  h -> N = 1 + size_node(h->left) + size_node(h-> right);   
  return x;
}


void putCountForString(int key, char * str){
  struct LinkedString * value = (struct LinkedString *) malloc(sizeof(struct LinkedString));
  value -> str = str;
  value -> next = NULL;
  root = put_node(root, key, value);  
  root -> color = BLACK;
}

static struct rbNode* put_node(struct rbNode* h, int keyP, struct LinkedString * valueP) {  
  if (h == NULL){
    struct rbNode* result = (struct rbNode*) malloc(sizeof(struct rbNode));
    result -> key = keyP;
    result -> value = valueP;
    result -> N = 1;
    result -> color = RED;     
    return result;
  }

  int cmp = keyP - (h -> key);
  if (cmp < 0) {
    h -> left = put_node(h -> left, keyP, valueP);
  } else if (cmp > 0){
    h -> right = put_node(h -> right, keyP, valueP);
  } else {
    //h -> value = valueP;
    //h -> value++;
    struct LinkedString * temp = h -> value;
    h -> value = valueP;
    h -> value -> next = temp;
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
void printAllOrderedByCountDesc() {
    printTree(root);
}

static void printTree(struct rbNode* h) {
    if (h == NULL){
        return;
    }

    printTree(h -> right);
    printf("%d:\n", h -> key);
    struct LinkedString * currentNodePointer = h -> value;
    while(currentNodePointer != NULL) {
      printf("    %s\n", currentNodePointer -> str);
      currentNodePointer = currentNodePointer -> next;
    }
    printTree(h -> left);    
}

/*
void main() {
  
  putCountForString(42, "sdsdfghhghsd");
  putCountForString(32, "sdsdfsd");
  putCountForString(22, "sddfhsdfsd");
  putCountForString(22, "sdsdsdfsd");

  printAllOrderedByCountDesc();
}
*/


