#include "AVLTree.hpp"

int main() {
 
  TreeNode *root = nullptr;
 
  root = add_node(root, "asdfas", 5);
  root = add_node(root, "khbshe", 6);
  root = add_node(root, "5xcv", 5);
  root = add_node(root, "jnwve9", 234);
  root = add_node(root, "2wvetb1", 52);
  root = add_node(root, "61wbbbbwct", 3);
  root = add_node(root, "8aacsdwadf", 6234);
  root = add_node(root, "1kjhgbnvje1", 123);
 
  print_tree(root, 0);
  
  search(root, "jnwve9");
 
  root = del_node_key(root, "5xcv");
 
  printf("\nУдаляем 5xcv:\n");

  print_tree(root, 0);

  free_tree(root);
  
  return 0;
}