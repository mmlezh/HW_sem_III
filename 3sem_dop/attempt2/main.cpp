#include "avlt.hpp"

int main() {
  TreeNode *root = nullptr;
  root = add_node(root, "33", 0);
  root = add_node(root, "13", 0);
  root = add_node(root, "53", 0);
  root = add_node(root, "9", 0);
  root = add_node(root, "21", 0);
  root = add_node(root, "61", 0);
  root = add_node(root, "8", 0);
  root = add_node(root, "11", 0);
  //printTree(root, "", true);
  print_tree(root, 0);
  root = del_node_key(root, "13");
  printf("\n===========================After deleting===========================\n");
  print_tree(root, 0);
  //printTree(root, "", true);
  free_tree(root);
  return 0;
}