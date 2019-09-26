#include "grid.h"
#include "grid_given.cpp"

// PA1 functions


/**
 * Destroys the current Grid. This function should ensure that
 * memory does not leak on destruction of a grid.
 */
Grid::~Grid(){ /*your code here*/
    clear();
}

/**
 * Rotate row r (row 0 is the first) by count positions.
 * If row r is ABCDE (left to right) in grid g then row r
 * in grid g should be DEABC after the call g.rotateR(r, 2).
 * Rotate headOfCol_ if necessary.
 */
void Grid::rotateR(int r, int count) { /* your code here */
    r = r % numRows();
    if (r < 0 || r >= headOfRow_.size()) return;
    count = count % headOfCol_.size();

    Node * mid = headOfRow_[r];
    Node * above = mid->up;
    Node * below = mid->down;
    
    for(int i = 0; i < headOfCol_.size(); i++) {
        mid = above->down;
        for (int j = 0; j < count; j++) {
            mid = mid->left;
        }
        above->down = mid;
        mid->up = above;
        below->up = mid;
        mid->down = below;

        above = above->right;
        below = below->right;

        if (r == 0) {
            headOfCol_[i] = mid;
        }
    }

    headOfRow_[r] = mid->right;
}

/**
 * Rotate column c (column 0 is the first) by count positions.
 * If column c is ABCDE (top to bottom) in grid g then column c
 * in grid g should be DEABC after the call g.rotateC(c, 2). 
 * Rotate headOfRow_ if necessary.
 */
void Grid::rotateC(int c, int count) { /* your code here */
    c = c % numCols();
    if (c < 0 || c >= headOfCol_.size()) return;
    count = count % headOfRow_.size();

    Node * mid = headOfCol_[c];
    Node * front = mid->right;
    Node * back = mid->left;
    
    for(int i = 0; i < headOfRow_.size(); i++) {
        mid = front->left;
        for (int j = 0; j < count; j++) {
            mid = mid->up;
        }
        front->left = mid;
        mid->right = front;
        back->right = mid;
        mid->left = back;
        front = front->down;
        back = back->down;

        if (c == 0) {
            headOfRow_[i] = mid;
        }
    }

    headOfCol_[c] = mid->down;
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Grid class. Clears headOfRow_ and headOfCol_ vectors.
 * Sets bwidth_, bheight_ to zero.
 * After clear() the grid represents an empty grid.
 */
void Grid::clear() { /*your code here*/
    for (int i = 0; i < headOfRow_.size(); i++) {
        Node * head = headOfRow_[i];
        if (head == NULL) continue;
        Node * n = head->right;

        while (n != head) {
            n = n->right;
            delete n->left;
        }
        delete n;
        headOfRow_[i] = NULL;
    }

    bwidth_ = 0;
    bheight_ = 0;
}


/**
 * Makes the current Grid a copy of the "other" Grid.
 * The dimensions should be the same.  The Nodes should
 * contain the same blocks, but the Nodes should be newly
 * allocated. This function is used in both the copy
 * constructor and the assignment operator for Grids.
 */
void Grid::copy(Grid const& other) { /*your code here*/
    // temporary 2D storing pointers to all new copies of nodes
    vector< vector < Node * >> N;

    int nRows = other.numRows();
    int nCols = other.numCols();

    for (int i = 0; i < nRows; i++) {
        vector< Node * > temp;
        Node * curr = other.headOfRow_[i];
        for (int j = 0; j < nCols; j++) {
            Node * p = new Node(curr->block);
            temp.push_back(p);
            curr = curr->right;
        }
        N.push_back(temp);
    }

    for( int j=0; j<nRows; j++ ) {
        for( int i=0; i<nCols; i++ ) {
        Node *p = N[j][i];
        // The following uses the C++ conditional operator
        // (also known as the C ternary operator):
        //
        // (condition) ? (if_true) : (if_false)
        //
        // which has the value if_true if the condition is true
        // and has the value if_false otherwise.
        p->up    = N[(j==0) ? nRows-1 : j-1] [i]; 
        p->down  = N[(j==nRows-1) ? 0 : j+1][i];
        p->left  = N[j] [(i==0) ? nCols-1 : i-1];
        p->right = N[j] [(i==nCols-1) ? 0 : i+1];
        }
    }

    for (int i = 0; i < other.numRows(); i++) {
        headOfRow_.push_back(N[i][0]);
    }
    for (int j = 0; j < other.numCols(); j++) {
        headOfCol_.push_back(N[0][j]);
    }

    bheight_ = other.bheight_;
    bwidth_ = other.bwidth_;
}
