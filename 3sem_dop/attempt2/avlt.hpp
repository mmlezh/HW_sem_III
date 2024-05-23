#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

template <class T>
class TreeNode{
  public:
  string key;
  T value;
  int height;

  TreeNode *parent;
  TreeNode *left;
  TreeNode *right;

  TreeNode(string k, T v);
};

int get_height(TreeNode *N);

TreeNode *new_node(string key, T value);
TreeNode *rotate_right(TreeNode *N);
TreeNode *rotate_left(TreeNode *N);

int get_balance(TreeNode *N);

TreeNode *add_node(TreeNode *N, string key, T value);
TreeNode *min_node(TreeNode *N);
TreeNode *del_node_key(TreeNode *root, string key);

void print_tree(TreeNode *root, int space);

void free_tree(TreeNode *root);
