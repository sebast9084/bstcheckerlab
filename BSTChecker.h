#ifndef BSTCHECKER_H
#define BSTCHECKER_H
// TODO: Include any needed header files
#include "BSTNode.h"
#include <queue>
#include <unordered_set>
using namespace std;
class BSTChecker {
public:
   // TODO: Add any desired utility functions
   // CheckBSTValidity() determines if the tree is a valid BST. If so, nullptr
   // is returned. If not, the first (in preorder traversal) node in violation
   // of BST requirements is returned. Such a node will be one of the following:
   // - A node in the left subtree of an ancestor with a lesser or equal key
   // - A node in the right subtree of an ancestor with a greater or equal key
   // - A node that is encountered more than once during traversal
   // Keep track of any duplicates, keys, maximums, minimums
   static BSTNode* CheckBSTValidity(BSTNode* rootNode) {
	if(rootNode == nullptr){
		return nullptr;
	}
	queue<BSTNode*> nodeQueue; //Make the node queue
	queue<int> minQueue;
	queue<int> maxQueue;
	unordered_set<BSTNode*> encountered;
	nodeQueue.push(rootNode);
	maxQueue.push(0);
	minQueue.push(0);
	while(!nodeQueue.empty()){
		BSTNode* node = nodeQueue.front();
		nodeQueue.pop();
		int smallerKey = minQueue.front();
		nodeQueue.pop();
		int largerKey = maxQueue.front();
		nodeQueue.pop();
		if (encountered.count(node)){ //Checks for duplicates
			return node;
		}
		encountered.insert(node);
		if (node->key <= smallerKey || node->key >= largerKey) { //Checks if keys are within range
            		return node;  
        	}
 		if (node->left != nullptr) {
        	    nodeQueue.push(node->left); //Push left node to the queue
		    minQueue.push(smallerKey); //Makes sure minimum limit is same
		    maxQueue.push(node->key); //Left child must be less than parent, parent key becomes maximum for left subtree
        	}
		if (node->right != nullptr) {
        	    nodeQueue.push(node->right); //Push right node to the queue
		    minQueue.push(node->key); //Right child must be greater than parent, key of parent becomes new minimum for right subtree
		    maxQueue.push(largerKey); //Makes sure maximum limit is same
        	}
	}
       	return rootNode;
    }
};
#endif

