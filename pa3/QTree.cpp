/**
 *
 * Balanced Quad Tree (pa3)
 *
 * This file will be used for grading.
 *
 */

#include "QTree.h"

// Return the biggest power of 2 less than or equal to n
int biggestPow2(int n) {
  if( n < 1 ) return 0;
  int v = 1;
  while( v <= n ) v <<= 1;
  return v >> 1;
}

QTree::Node::Node(PNG & im, pair<int,int> ul, int sz, Node *par)
  :upLeft(ul),size(sz),parent(par),nw(NULL),ne(NULL),sw(NULL),se(NULL)
{
  var = varAndAvg(im,ul,size,avg);
}

QTree::~QTree(){
  clear();
}

QTree::QTree(const QTree & other) {
  copy(other);
}


QTree & QTree::operator=(const QTree & rhs){
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}


QTree::QTree(PNG & imIn, int leafB, RGBAPixel frameC, bool bal)
  : leafBound(leafB), balanced(bal), drawFrame(true), frameColor(frameC)
{

  /* YOUR CODE HERE */

}


QTree::QTree(PNG & imIn, int leafB, bool bal)
  : leafBound(leafB), balanced(bal), drawFrame(false)
{
  /* YOUR CODE HERE */
  im = imIn;
  pair<int, int> ul(0, 0);
  size = biggestPow2(min(im.height(), im.width()));
  root = new Node(im, ul, size, NULL);
  numLeaf = 1;
  // auto greater_var = [](Node* a, Node* b) {return a->var > b->var;};

  priority_queue<Node*, vector<Node*>, Comparator> p_queue;
  p_queue.push(root);

  while(numLeaf <= (leafB - 3)) {
    Node* next = p_queue.top();
    p_queue.pop();
    split(next);
    p_queue.push(next->nw);
    p_queue.push(next->ne);
    p_queue.push(next->sw);
    p_queue.push(next->se);
  }
}


bool QTree::isLeaf( Node *t ) {
  
  /* YOUR CODE HERE */
  return (t->nw == NULL && t->ne == NULL && t->sw == NULL && t->se == NULL);
}
  
void QTree::split( Node *t ) {
  
  /* YOUR CODE HERE */

  // FOR BALANCED QTREES-------------------------------------------------
  // A split might cause one or two nbrs of the parent of t to split
  // to maintain balance.  Note that these two nbrs exist (unless they're
  // not in the image region) because the current set of leaves are
  // balanced.
  // if( t is a NW (or NE or SW or SE) child ) then we need to check that
  // the North and West (or North and East or South and West or
  // South and East) nbrs of t->parent have children. If they don't
  // we need to split them.
  
  // @TODO: finish unbalanced split
  int newSize = t->size / 2;
  std::pair<int, int> tempPair = t->upLeft;

  t->nw = new Node(im, t->upLeft, newSize, t);
  tempPair.first += newSize;
  t->ne = new Node(im, tempPair, newSize, t);
  tempPair.second += newSize;
  t->se = new Node(im, tempPair, newSize, t);
  tempPair.first -= newSize;
  t->sw = new Node(im, tempPair, newSize, t);

  numLeaf += 3;
}


/* NNbr(t)
 * return the same-sized quad tree node that is north of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::NNbr(Node *t) {

  /* YOUR CODE HERE */
  
}

/* SNbr(t)
 * return the same-sized quad tree node that is south of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::SNbr(Node *t) {

  /* YOUR CODE HERE */
  
}

/* ENbr(t)
 * return the same-sized quad tree node that is east of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::ENbr(Node *t) {

  /* YOUR CODE HERE */
  
}

/* WNbr(t)
 * return the same-sized quad tree node that is west of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::WNbr(Node *t) {

  /* YOUR CODE HERE */
  
}

bool QTree::write(string const & fileName){

  /* YOUR CODE HERE */
  // cout << size << endl;
  // cout << root->size << endl;
  PNG pic(size, size);
  DFS(pic, root);

  // include the following line to write the image to file.
  return(pic.writeToFile(fileName));
}

void QTree::DFS(PNG & pic, Node * n) {
  if (isLeaf(n)) {
    // Render leaf node into pic
    pair<int, int> ul = n->upLeft;

    for (int i = 0; i < n->size; i++) {
      for (int j = 0; j < n->size; j++) {
        RGBAPixel* pixel = pic.getPixel(ul.first + i, ul.second + j);
        *pixel = n->avg;
      }
    } 
  } else {
    DFS(pic, n->nw);
    DFS(pic, n->ne);
    DFS(pic, n->sw);
    DFS(pic, n->se);
  }
}

void QTree::clear() {

  /* YOUR CODE HERE */
  
}


void QTree::copy(const QTree & orig) {

  /* YOUR CODE HERE */
  
}