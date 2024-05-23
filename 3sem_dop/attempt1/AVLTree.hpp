#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class TreeNode
{
  public:
  string key;
  int value;
  int height;

  TreeNode *parent;
  TreeNode *left;
  TreeNode *right;

  TreeNode(string k, int v);
};

TreeNode *next_pos(TreeNode *p);

// TreeNode * NextPosition (TreeNode *p)
// {
//   TreeNode *q;
//   if(p == nullptr)
//   {
//     return nullptr;
//   }
//   if(p->left)
//   {
//     return p->left;
//   }
//   if(p->right)
//   {
//     return p->right;
//   }
//   for(q = p->parent; q; p = q, q = q->parent)
//   {
//     if(q->right && q->right != p)
//     {
//       return q->right;
//     }
//   }
//   return nullptr;
// }

int get_height(TreeNode *N);

TreeNode *new_node(string key, int value);
TreeNode *rotate_right(TreeNode *N);
TreeNode *rotate_left(TreeNode *N);

int get_balance(TreeNode *N);

TreeNode *add_node(TreeNode *N, string key, int value);
TreeNode *min_node(TreeNode *N);
TreeNode *del_node_key(TreeNode *root, string key);

void print_tree(TreeNode *root, int space);

void search(TreeNode *root, string key);

void free_tree(TreeNode *root);

void cal_keys(TreeNode *root, int count);