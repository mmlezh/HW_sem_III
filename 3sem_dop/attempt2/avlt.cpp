#include "avlt.hpp"

template <class T>
TreeNode::TreeNode(string k, T v)
{
	key = k;
	value = v;
	height = 1;
	right = nullptr;
	left = nullptr;
}

template <class T>
int get_height(TreeNode<T> *N)
{
	if(N == NULL)
	{
		return 0;
	}
	return N->height;
}

template <class T>
TreeNode *new_node(string key, T value)
{
  TreeNode<T> *node = new <T>TreeNode(key, value);

  return node;
}

template <class T>
TreeNode *rotate_right(TreeNode<T> *N)
{
	TreeNode<T> *M = N->left;
	TreeNode<T> *K = M->right;
	M->right = N;
	N->left = K;
	N->height = ((get_height(N->left) > get_height(N->right)) ? get_height(N->left) : get_height(N->right)) +1;
	M->height = ((get_height(M->left) > get_height(M->right)) ? get_height(M->left) : get_height(M->right)) +1;
	return M;
}

template <class T>
TreeNode *rotate_left(TreeNode<T> *N)
{
	TreeNode<T> *M = N->right;
	TreeNode<T> *K = M->left;
	M->left = N;
	N->right = K;
	N->height = ((get_height(N->left) > get_height(N->right)) ? get_height(N->left) : get_height(N->right)) +1;
	M->height = ((get_height(M->left) > get_height(M->right)) ? get_height(M->left) : get_height(M->right)) +1;
	return M;
}

template <class T>
int get_balance(TreeNode<T> *N)
{
	if(N == nullptr)
	{
		return 0;	
	}
	return get_height(N->left) - get_height(N->right);
}

template <class T>
TreeNode *add_node(TreeNode<T> *N, string key, T value)
{
	if(N == nullptr)
	{
		return (new_node(key, value));
	}
	if(key.compare(N->key) < 0)//(key < N->key)//<-тут
	{
		N->left = add_node(N->left, key, value);
	}else if(key.compare(N->key) > 0)//(key > N->key) <-тут
		{
			N->right = add_node(N->right, key, value);
		}
		else
		{
			return N;
		}

	N->height = 1 + ((get_height(N->left) > get_height(N->right)) ? get_height(N->left) : get_height(N->right));
	int balance = get_balance(N);
	if(balance > 1)
	{
		if(key.compare(N->left->key) < 0)//(key < N->left->key)
    	{
			return rotate_right(N);
    	}else if(key.compare(N->left->key) > 0)//(key > N->left->key)
			{
				N->left = rotate_left(N->left);
				return rotate_right(N);
			}
	}
	if(balance < -1)
	{
		if(key.compare(N->right->key) > 0)//(key > N->right->key)
		{
			return rotate_left(N);
		}else if(key.compare(N->right->key) < 0)//(key < N->right->key)
			{
				N->right = rotate_right(N->right);
				return rotate_left(N);
			}
	}
	return N;
}

template <class T>
TreeNode *min_node(TreeNode<T> *N)
{
	TreeNode<T> *cur = N;
	while (cur->left != nullptr)
		cur = cur->left;
	return cur;
}

template <class T>
TreeNode *del_node_key(TreeNode<T> *root, string key)
{
  if(root == NULL)
  {
    return root;
  }
  if(key.compare(root->key) < 0)//(key < root->key)
  {
    root->left = del_node_key(root->left, key);
  }else if(key.compare(root->key) > 0)//(key > root->key)
    {
      root->right = del_node_key(root->right, key);
    }else{
      if((root->left == NULL) || (root->right == NULL))
      {
        TreeNode<T> *temp = root->left ? root->left : root->right;
        if(temp == NULL)
        {
          temp = root;
          root = NULL;
        } else
        *root = *temp;
        delete temp; //free(temp);
      }else{
        TreeNode<T> *temp = min_node(root->right);
        root->key = temp->key;
        root->right = del_node_key(root->right, temp->key);
      }
    }

  if(root == NULL)
  {
    return root;
  }

  root->height = 1 + ((get_height(root->left) > get_height(root->right)) ? get_height(root->left) : get_height(root->right));
  int balance = get_balance(root);
  if(balance > 1)
  {
    if(get_balance(root->left) >= 0)
    {
      return rotate_right(root);
    }else{
      root->left = rotate_left(root->left);
      return rotate_right(root);
    }
  }
  if(balance < -1){
    if(get_balance(root->right) <= 0)
    {
      return rotate_left(root);
    }else{
      root->right = rotate_right(root->right);
      return rotate_left(root);
    }
  }
  return root;
}

template <class T>
void print_tree(TreeNode<T> *root, int space)
{
  if(root == NULL)
  {
    return;
  }

  space += 10;

  print_tree(root->right, space);

  cout << endl;
  for(int i = 10; i < space; i++)
  {
    cout << " ";
  }

  cout << "(" << root->key << "->" << root->value << ")\n";
  //printf("(%d->%d)\n",root->key, root->value);

  print_tree(root->left, space);
}

template <class T>
void free_tree(TreeNode *root)
{ 
	if(root->left)
	{
		free_tree(root->left); 
	}
	if(root->right)
	{
		free_tree(root->right); 
	}  
	delete root; 
}