#include <iostream>
#include <cstdlib>

// A utility function to find min of two integers
int min(int x, int y) { return (x < y)? x: y; }

/* A binary tree node has data, pointer to left child and a pointer to
right child */ 
struct node
{
	int data;
	node *left, *right;
};

// The function returns size of the minimum vertex cover
int vCover(node *root)
{
	// The size of minimum vertex cover is zero if tree is empty or there
	// is only one node
	if (root == nullptr)
		return 0;
	if (root->left == nullptr && root->right == nullptr)
		return 0;

	// Calculate size of vertex cover when root is part of it
	int size_incl = 1 + vCover(root->left) + vCover(root->right);

	// Calculate size of vertex cover when root is not part of it
	int size_excl = 0;
	if (root->left)
	size_excl += 1 + vCover(root->left->left) + vCover(root->left->right);
	if (root->right)
	size_excl += 1 + vCover(root->right->left) + vCover(root->right->right);

	// Return the minimum of two sizes
	return min(size_incl, size_excl);
}

// A utility function to create a node
node* newNode( int data )
{
	node* temp = new node;
	temp->data = data;
	temp->left = temp->right = nullptr;
	return temp;
}

// Driver program to test above functions
int main()
{
	// Let us construct the tree given in the above diagram
	node *root		 = newNode(20);
	root->left			 = newNode(8);
	root->left->left		 = newNode(4);
	root->left->right		 = newNode(12);
	root->left->right->left = newNode(10);
	root->left->right->right = newNode(14);
	root->right			 = newNode(22);
	root->right->right	 = newNode(25);

	std::cout << "Size of the smallest vertex cover is " << vCover(root) << std::endl;

	return 0;
}
