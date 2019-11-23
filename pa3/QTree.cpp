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
  frameColor = frameC;
  construct(imIn);
}


QTree::QTree(PNG & imIn, int leafB, bool bal)
  : leafBound(leafB), balanced(bal), drawFrame(false)
{
  /* YOUR CODE HERE */
  construct(imIn);
}

void QTree::construct(const PNG & imIn) {
  // Assign QTree image, size, root node
  im = imIn;
  pair<int, int> ul(0, 0);
  size = biggestPow2(min(im.height(), im.width()));
  root = new Node(im, ul, size, NULL);
  numLeaf = 1;

  // Create priority queue to split nodes in order 
  // of variance, up to approx. leafBound
  split_queue.push(root);

  while(numLeaf < leafBound) {
    Node* next = split_queue.top();
    split_queue.pop();
    split(next);
  }
}


bool QTree::isLeaf( Node *t ) {
  
  /* YOUR CODE HERE */
  if (t == NULL) return false;
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

  if (t == NULL || !isLeaf(t)) return;

  // check balancing if non-root node
  if (balanced && (t->parent != NULL)) {
      if (t == t->parent->nw) {
        // NW node: check/split parent N and W nbrs
        Node* parNNbr = NNbr(t->parent);
        Node* parWNbr = WNbr(t->parent);
        if (isLeaf(parNNbr)) split(parNNbr);
        if (isLeaf(parWNbr)) split(parWNbr);

      } else if (t == t->parent->ne) {
        // NE node: check/split parent N and E nbrs
        Node* parNNbr = NNbr(t->parent);
        Node* parENbr = ENbr(t->parent);
        if (isLeaf(parNNbr)) split(parNNbr);
        if (isLeaf(parENbr)) split(parENbr);

      } else if (t == t->parent->sw) {
        // SW node: check/split parent S and W nbrs
        Node* parSNbr = SNbr(t->parent);
        Node* parWNbr = WNbr(t->parent);
        if (isLeaf(parSNbr)) split(parSNbr);
        if (isLeaf(parWNbr)) split(parWNbr);

      } else if (t == t->parent->se) {
        // SE node: check/split parent S and E nbrs
        Node* parSNbr = SNbr(t->parent);
        Node* parENbr = ENbr(t->parent);
        if (isLeaf(parSNbr)) split (parSNbr);
        if (isLeaf(parENbr)) split (parENbr);
      }
  }
  
  int newSize = t->size / 2;
  std::pair<int, int> tempPair = t->upLeft;

  t->nw = new Node(im, t->upLeft, newSize, t);
  tempPair.first += newSize;
  t->ne = new Node(im, tempPair, newSize, t);
  tempPair.second += newSize;
  t->se = new Node(im, tempPair, newSize, t);
  tempPair.first -= newSize;
  t->sw = new Node(im, tempPair, newSize, t);

  split_queue.push(t->nw);
  split_queue.push(t->ne);
  split_queue.push(t->sw);
  split_queue.push(t->se);

  numLeaf += 3;
}


/* NNbr(t)
 * return the same-sized quad tree node that is north of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::NNbr(Node *t) {

  /* YOUR CODE HERE */
  if (t == NULL || t->parent == NULL) return NULL;

  if (t == t->parent->sw) return t->parent->nw;
  if (t == t->parent->se) return t->parent->ne;
  
  Node* parNNbr = NNbr(t->parent);
  if (parNNbr == NULL) return NULL;
  if (isLeaf(parNNbr)) {
    if (parNNbr->size > (2 * t->size)) return NULL;
    return parNNbr;
  }

  if (t == t->parent->nw) return parNNbr->sw;
  if (t == t->parent->ne) return parNNbr->se;

  return NULL; // will never reach
}

/* SNbr(t)
 * return the same-sized quad tree node that is south of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::SNbr(Node *t) {

  /* YOUR CODE HERE */
  if (t == NULL || t->parent == NULL) return NULL;

  if (t == t->parent->nw) return t->parent->sw;
  if (t == t->parent->ne) return t->parent->se;

  Node* parSNbr = SNbr(t->parent);
  if (parSNbr == NULL) return NULL;
  if (isLeaf(parSNbr)) {
    if (parSNbr->size > (2 * t->size)) return NULL;
    return parSNbr;
  }

  if (t == t->parent->sw) return parSNbr->nw;
  if (t == t->parent->se) return parSNbr->ne;
  
  return NULL; // will never reach
}

/* ENbr(t)
 * return the same-sized quad tree node that is east of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::ENbr(Node *t) {

  /* YOUR CODE HERE */
  if (t == NULL || t->parent == NULL) return NULL;

  if (t == t->parent->nw) return t->parent->ne;
  if (t == t->parent->sw) return t->parent->se;

  Node* parENbr = ENbr(t->parent);
  if (parENbr == NULL) return NULL;
  if (isLeaf(parENbr)) {
    if (parENbr->size > (2 * t->size)) return NULL;
    return parENbr;
  }

  if (t == t->parent->ne) return parENbr->nw;
  if (t == t->parent->se) return parENbr->sw;
  
  return NULL; // will never reach
}

/* WNbr(t)
 * return the same-sized quad tree node that is west of Node t.
 * return NULL if this node is not in the QTree.
 */
QTree::Node * QTree::WNbr(Node *t) {

  /* YOUR CODE HERE */
  if (t == NULL || t->parent == NULL) return NULL;

  if (t == t->parent->ne) return t->parent->nw;
  if (t == t->parent->se) return t->parent->sw;

  Node* parWNbr = WNbr(t->parent);
  if (parWNbr == NULL) return NULL;
  if (isLeaf(parWNbr)) {
    if (parWNbr-> size > (2 * t->size)) return NULL;
    return parWNbr;
  }

  if (t == t->parent->nw) return parWNbr->ne;
  if (t == t->parent->sw) return parWNbr->se;
  
  return NULL; // will never reach
}

bool QTree::write(string const & fileName){

  /* YOUR CODE HERE */
  PNG pic(size, size);
  DFS_render(pic, root);

  // include the following line to write the image to file.
  return(pic.writeToFile(fileName));
}

void QTree::DFS_render(PNG & pic, Node * n) {
  if (isLeaf(n)) {
    // Render leaf node into pic
    pair<int, int> ul = n->upLeft;
    for (int i = 0; i < n->size; i++) {
      for (int j = 0; j < n->size; j++) {
        RGBAPixel* pixel = pic.getPixel(ul.first + i, ul.second + j);
        // draw pixel, check for frame
        if (drawFrame && (i == 0 || i == n->size - 1 || j == 0 || j == n->size-1)) {
          *pixel = frameColor;
        } else {
          *pixel = n->avg;
        }
      }
    }
  } else {
    // recursively search for leaf nodes
    DFS_render(pic, n->nw);
    DFS_render(pic, n->ne);
    DFS_render(pic, n->sw);
    DFS_render(pic, n->se);
  }
}

void QTree::clear() {

  /* YOUR CODE HERE */
  DFS_delete(root);
}

void QTree::DFS_delete(Node * n) {
  if (n != NULL) {
    DFS_delete(n->nw);
    DFS_delete(n->ne);
    DFS_delete(n->sw);
    DFS_delete(n->se);
    delete n;
  }
}


void QTree::copy(const QTree & orig) {

  /* YOUR CODE HERE */
  leafBound = orig.leafBound;
  drawFrame = orig.drawFrame;
  balanced = orig.balanced;
  frameColor = orig.frameColor;
  split_queue = priority_queue<Node*, vector<Node*>, Comparator>();
  construct(orig.im);
}
