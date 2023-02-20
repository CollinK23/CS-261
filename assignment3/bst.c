/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>

#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  /*
   * FIXME:
   */

  struct bst* newBst = malloc(sizeof(struct bst)); //Allocates memory to new BST
  newBst->root = NULL; //Sets the root equal to NULL
  return newBst;
}

/*
 * This function recursively frees the memory allocated to each node
 *
 * Params:
 *   bst_node - the node to be destroyed
 */
void bstDelete(struct bst_node* node){
  if (node == NULL){
    return;
  }

  if (node->left){
    bstDelete(node->left); //Recursively deletes left node
  }
  if (node->right){
    bstDelete(node->right); //Recursively deletes right node
  }
  free(node);
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  /*
   * FIXME:
   */
  bstDelete(bst->root);
  free(bst);
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst_node - the node that is being counted.  May not be NULL.
 */
int bstSizeRecursion(struct bst_node* node){
  int total = 0;
  if (node->left){
    total += 1; //Adds 1 to total size of tree if left node exists
    total += bstSizeRecursion(node->left); //Recursively checks child nodes
  }
  if (node->right){
    total += 1; //Adds 1 to total size of tree if right node exists
    total += bstSizeRecursion(node->right); //Recursively checks child nodes
  }
  return total;
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  /*
   * FIXME:
   */
  if (bst->root){
    return bstSizeRecursion(bst->root) + 1; //Add one for root node
  }
  return 0;
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  /*
   * FIXME:
   */

  //Sets values of root node
  if (bst->root == NULL) {
    // create a new root node
    bst->root = malloc(sizeof(struct bst_node));
    bst->root->key = key;
    bst->root->value = value;
    bst->root->left = NULL;
    bst->root->right = NULL;
    return;
  }

  struct bst_node* curr = bst->root;

  //Sets values of new nodes
  struct bst_node* newNode = malloc(sizeof(struct bst_node));
  newNode->key = key;
  newNode->value = value;
  newNode->left = NULL;
  newNode->right = NULL;

  while (curr) {
    //Goes to the left if the new key is less than the current key
    if (key < curr->key) {
      if (curr->left) {
        //Iterates to next left node if left child node already exists
        curr = curr->left;
      } else {
        //Sets left child node if current one doesnt exist
        curr->left = newNode;
        break;
      }
    } else {
      //Goes to the right if the new key is greater than the current key
      if (curr->right) {
        //Iterates to next right node if right child node already exists
        curr = curr->right;
      } else {
        //Sets right child node if current one doesnt exist
        curr->right = newNode;
        break;
      }
    }
  }

}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  /*
   * FIXME:
   */
  struct bst_node* node = bst->root;
  struct bst_node* parent = NULL;

  // Find the node with the specified key
  while (node != NULL && node->key != key) {
    parent = node;
    if (key < node->key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  
  //Removes leaf nodes
  if (node->left == NULL && node->right == NULL) {
    if (parent == NULL) {
      bst->root = NULL; //Removes root node
    } else if (parent->left == node) {
      parent->left = NULL; //Removes current node from parent node pointer
    } else {
      parent->right = NULL; //Removes current node from parent node pointer
    }
    free(node); //Frees memory allocated to node
  }
  //Removes nodes with only one child node
  else if (node->left == NULL || node->right == NULL) {
    //Child node that the parent will point to based on which child node isn't null
    struct bst_node* child = (node->left != NULL) ? node->left : node->right;
    if (parent == NULL) {
      bst->root = child; //Removes root node
    } else if (parent->left == node) {
      parent->left = child; //Updates the parent left pointer to new child node
    } else {
      parent->right = child; //Upates the parent right pointer to new child node
    }
    free(node); //Frees memory allocated to node
  }
  //Removes nodes with two child nodes;
  else {
    struct bst_node* successor = node->right; //In order successor of node being removed
    parent = node;
    //While loop to find the next in order successor
    while (successor->left != NULL) {
      parent = successor;
      successor = successor->left; //Traverses left until it finds the in order successor
    }
    //Changes original node to successor node
    node->key = successor->key;
    node->value = successor->value;
    if (parent->left == successor) {
      parent->left = successor->right;
    } else {
      parent->right = successor->right;
    }
    free(successor);
  }
}

/*
 * This function recursively searches for the tree node with the specified key
 *
 * Params:
 *   bst_node - the BST node that is being compared to the specified key
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_recursive(struct bst_node* node, int key){
  if(node != NULL){
    if (node->key == key){
      //Returns node value when the key has been found
      return node->value;
    }else if(node->key > key){
      //Searches left if the current node key is larger than the one being searched for
      bst_recursive(node->left, key);
    }else if(node->key < key){
      //Searches right if the current node key is less than the one being searched for
      bst_recursive(node->right, key);
    }
  }
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  /*
   * FIXME:
   */

  struct bst_node* curr = bst->root; //Sets the current node as the root of the tree
  return bst_recursive(curr, key);
}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * Helper function to find height of the Binary Search Tree
 *
 * Params:
 *   bst_node - the current node being traversed in the BST
 *
 * Return:
 *   Should return the height of bst.
 */
int bstHeightRecursive(struct bst_node* node){
  //Return -1 if the node doesn't exist
  if (node == NULL){
    return -1;
  }

  //Recursively calls the function to traverse through all nodes
  int heightLeft = bstHeightRecursive(node->left);
  int heightRight = bstHeightRecursive(node->right);
  
  //Returns the side with the larger height
  if (heightRight > heightLeft){
    return heightRight + 1; //Add one to track total height
  }else {
    return heightLeft + 1; //Add one to track total height
  }
}

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
 int bst_height(struct bst* bst) {
  /*
   * FIXME:
   */
  return bstHeightRecursive(bst->root);
 }

/*
 * Helper function to find valid path sums
 *
 * Params:
 *   bst_node - the current node in the BST path
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bstSumRecursive(struct bst_node* node, int sum){
  int hasSum1 = 0; //Indicates if the left node is a valid path
  int hasSum2 = 0; //Indicates if the right node is a valid path
  sum -= node->key; //Updates sum after traversing to next node

  if (sum == 0 && node->left == NULL && node->right == NULL){
    return 1; //Valid path if sum equals 0 and no child nodes
  }else if (sum != 0 && node->left == NULL && node->right == NULL){
    return 0; //Invalid path if sum not equal to 0 and no child nodes
  }

  //Recursively calls function until left node equals NULL
  if (node->left){
    hasSum1 = bstSumRecursive(node->left, sum);
  }
  
  //Recursively calls function until right node equals NULL
  if (node->right){
    hasSum2 = bstSumRecursive(node->right, sum);
  }

  return (hasSum1 < hasSum2 ? hasSum2 : hasSum1); //Will return 1 if the path is valid
}

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
  /*
   * FIXME:
   */
  return bstSumRecursive(bst->root, sum);
}

/*
 * Helper function to find sum of nodes within a specific range
 *
 * Params:
 *   bst_node - the BST node being added to the total sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bstRangeRecursive(struct bst_node* node, int lower, int upper){
  int sum = 0; //Sets value being added to the total sum

  //Checks if root node is in range
  if (lower <= node->key && node->key <= upper){
    sum = node->key;
  }

  //Checks if child node is within the range
  if (node->left && node->key >= lower){
    sum += bstRangeRecursive(node->left, lower, upper); //Recursively adds valid nodes to the total sum
  }
  if (node->right && node->key <= upper){
    sum += bstRangeRecursive(node->right, lower, upper); //Recursively adds valid nodes to the total sum
  }
  return sum; //Returns the total sum
}

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
  /*
   * FIXME:
   */
  return bstRangeRecursive(bst->root, lower, upper);
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/*
 * This function recursively pushes BST nodes to the stack
 *
 * Params:
 *   iter - The BST iterator that the nodes are being pushed to
 *   node - The node that is being pushed into the stack
 * 
 */
void* iteratorRecursive(struct bst_iterator* iter, struct bst_node* node){
  //Checks if right node exists first
  if (node->right){
    iteratorRecursive(iter, node->right); //Recursive call to function
    stack_push(iter->stack, node); //Pushes the current node to the stack
    if (node->left){
      iteratorRecursive(iter, node->left); //Pushes values from left child after pushing right child values
    }
  }else if (node->left){
    //Pushes values from left child node if the right child node doesnt exist
    iteratorRecursive(iter, node->left);
  }else {
    //Pushes node to stack if no child nodes exist
    stack_push(iter->stack, node);
  }
}

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  /*
   * FIXME:
   */
  struct bst_iterator* newIterator = malloc(sizeof(struct bst_iterator)); //Allocates memory to new iterator struct
  newIterator->stack = stack_create(); //Creates a new stack
  iteratorRecursive(newIterator, bst->root);
  return newIterator;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  /*
   * FIXME:
   */
  stack_free(iter->stack); //Frees nodes from stack
  free(iter); //Frees iterator
  return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  /*
   * FIXME:
   */
  //Checks if stack is empty
  if (stack_isempty(iter->stack) == 1){
    return 0;
  }
  return 1;
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  /*
   * FIXME:
   */
  struct bst_node* curr = stack_pop(iter->stack); //Stores node being popped from stack
  if (value) {
    *value = curr->value;
  }
  
  return curr->key;
}
