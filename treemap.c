#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
    TreeMap * mapa = (TreeMap *)malloc(sizeof(TreeMap));

    mapa->root = NULL;
    mapa->current = NULL;
    mapa->lower_than = lower_than;
    return mapa;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
  TreeNode* newNode = createTreeNode(key,value);
  TreeNode* aux = tree->root;

  while(aux != NULL)
  {
    tree->current = aux;
    if(tree->lower_than(key, aux->pair->key) == 1)
    {
      aux = aux->left;
      if(aux == NULL)
      {
        tree->current->left = newNode;
        newNode->parent = tree->current;
        tree->current = newNode;
        return;
        }
      }
      else if(tree->lower_than(aux->pair->key, key) == 1)
      {
        aux = aux->right;
        if(aux == NULL) 
        {
          tree->current->right = newNode;
          newNode->parent = tree->current;
          tree->current = newNode;
          return;
          }
        }
        else
        {
            return;
        }
    }
}

TreeNode * minimum(TreeNode * x)
{
    
    if(x->left == NULL) return x;
    
    while (x->left != NULL)
    {
        if(x->left != NULL)
        {
            x = x->left;
        }
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
    /*if (searchTreeMap(tree, node->pair->key) == NULL) return;

    if(tree->current->left == NULL && tree->current->right == NULL)
    {
        tree->current->parent->
    }*/
}

void eraseTreeMap(TreeMap * tree, void* key)
{
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) 
{
  TreeNode* aux = tree->root;

  while(aux != NULL)
  {

    if(tree->lower_than(key, aux->pair->key) == 1)
    {
      aux = aux->left;
      if(aux != NULL) tree->current = aux;
    }
    else if(tree->lower_than(aux->pair->key, key) == 1)
    {
      aux = aux->right;
      if(aux != NULL) tree->current = aux;
    }
    else
    {
      tree->current = aux;
      return aux->pair;
    }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) 
{
  Pair * auxPair;

  auxPair = searchTreeMap(tree,key);

  if(auxPair != NULL) return auxPair;

  while(tree->lower_than(key, tree->current->pair->key) != 1)
  {
    if(tree->current->parent !=  NULL)
    {
      tree->current = tree->current->parent;
    }

    if(tree->current == tree->root)
    {
      return NULL;
    }
  }
  
  return tree->current->pair;
}

Pair * firstTreeMap(TreeMap * tree) 
{
  TreeNode * auxNode;
  Pair * auxPair;
  
  auxNode = minimum(tree->root);

  auxPair = auxNode->pair;
  
  return auxPair;
}

Pair * nextTreeMap(TreeMap * tree) 
{
  TreeNode * auxNode;
  Pair * auxPair;

  auxNode = tree->current;

  if(tree->current->right != NULL)
  {
    tree->current = tree->current->right;
    
    /*while(tree->current->left != NULL)
    {
      if(tree->current->left == NULL) break;

      tree->current = tree->current->left;
    }*/
    
    return tree->current->pair;
  }
  
  while(auxNode != NULL)
  {
    if(tree->current->parent != NULL)
    {
      tree->current = tree->current->parent;
    }

    if(auxNode != tree->current && tree->current->right != NULL && auxNode != tree->current->right)
    {
      tree->current = tree->current->right;
    }

    while(auxNode != tree->current && tree->current->left != NULL && auxNode != tree->current->left)
    {
      tree->current = tree->current->left;
      if(tree->current->left == NULL)
      {
        auxPair = tree->current->pair;

        return auxPair;
      }
    }
  }
  return NULL;
}