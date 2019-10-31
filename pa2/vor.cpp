/**
 * @file vor.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//included within  "vor.h" for template instantiation


/* vorDotDFS given as an example for PA2 */
animation filler::vorDotDFS(PNG& img, double density,
                                int dotGrid,int dotSize, int frameFreq)
{
    dotColorPicker a(dotGrid,dotSize);
    return vor<Stack>(img, density, a, frameFreq);
}

animation filler::vorSolidDFS(PNG& img, double density, int frameFreq)
{
    /**
     * @todo Your code here! 
     */

    solidColorPicker a;
    return vor<Stack>(img, density, a, frameFreq);
}

animation filler::vorFadeDFS(PNG& img, double density, double fadeFactor, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    fadeColorPicker a(fadeFactor);
    return vor<Stack>(img, density, a, frameFreq);
}


/* vorDotBFS given as an example for PA2 */
animation filler::vorDotBFS(PNG& img, double density,
                                int dotGrid,int dotSize, int frameFreq)
{
    dotColorPicker a(dotGrid, dotSize);
    return vor<Queue>(img, density, a, frameFreq);
}

animation filler::vorSolidBFS(PNG& img, double density, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    solidColorPicker a;
    return vor<Queue>(img, density, a, frameFreq);
}

animation filler::vorFadeBFS(PNG& img, double density, double fadeFactor, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    fadeColorPicker a(fadeFactor);
    return vor<Queue>(img, density, a, frameFreq);
}

// helper for vor
template <template <class T> class OrderingStructure>
bool filler::vector_is_empty(vector<OrderingStructure<point>> o_s){
    for(int i=0; i<o_s.size(); i++){
        if(!o_s[i].isEmpty()){
            return false;
        }
    }
    return true;
}

// helper for get_valid_neighbors
bool filler::is_valid_and_mark(int x, int y, PNG& img, center c, int k, vector<vector<bool>>& tracker){

    // point is not inside img
    if(x<0 || x>img.width()){
        return false;
    }
    if(y<0 || y>img.height()){
        return false;
    }

    // this position has already been marked
    if(tracker[x][y] == true){
        return false;
    }

    // neighbor is not k distance from center
    int dist_squared = (x-c.x)*(x-c.x) + (y-c.y)*(y-c.y);
    if(dist_squared > k*k){
        return false;
    }

    // thus the point is valid, mark it in tracker_x and tracker_y
    tracker[x][y] = true;

    return true;
}

// helper for vor
vector<point> filler::get_valid_neighbors(PNG& img, point p, center c, int k, vector<vector<bool>>& tracker){
    
    vector<point> ret;

    // top
    if(filler::is_valid_and_mark(p.x, p.y-1, img, c, k, tracker)){
        point top(p.x, p.y-1, c, k);
        ret.push_back(top);
    }

    // topleft
    if(filler::is_valid_and_mark(p.x-1, p.y-1, img, c, k, tracker)){
        point topleft(p.x-1, p.y-1, c, k);
        ret.push_back(topleft);
    }

    // left
    if(filler::is_valid_and_mark(p.x-1, p.y, img, c, k, tracker)){
        point left(p.x-1, p.y, c, k);
        ret.push_back(left);
    }

    // botleft
    if(filler::is_valid_and_mark(p.x-1, p.y+1, img, c, k, tracker)){
        point botleft(p.x-1, p.y+1, c, k);
        ret.push_back(botleft);
    }

    // bot
    if(filler::is_valid_and_mark(p.x, p.y+1, img, c, k, tracker)){
        point bot(p.x, p.y+1, c, k);
        ret.push_back(bot);
    }

    // botright
    if(filler::is_valid_and_mark(p.x+1, p.y+1, img, c, k, tracker)){
        point botright(p.x+1, p.y+1, c, k);
        ret.push_back(botright);
    }

    // right
    if(filler::is_valid_and_mark(p.x+1, p.y, img, c, k, tracker)){
        point right(p.x+1, p.y, c, k);
        ret.push_back(right);
    }

    // topright
    if(filler::is_valid_and_mark(p.x+1, p.y-1, img, c, k, tracker)){
        point topright(p.x+1, p.y-1, c, k);
        ret.push_back(topright);
    }

    return ret;
}


template <template <class T> class OrderingStructure>
animation filler::vor(PNG& img, double density, colorPicker& fillColor,
                       int frameFreq)
{

    /**
     * @todo You need to implement this function!
     *
     * This is a general description of a space filling algorithm, where 
     * the space is partitioned into a set of regions each color of which
     * is determined by the color of a point 
     * chosen from an original image. We call those original points
     * "centers." (See pictures in the specification.)
     *
     * The algorithm requires ordering structures used to orchestrate
     * the sequence of points filled. This structure type info is passed to the 
     * fill algorithm via its template parameter. For a breadth-first fill,
     * we use Queues, and for a depth-first fill, we use Stacks. Function
     * vorDotDFS provides an example call to function vor.
     * 
     * The algorithm includes the following steps:
     * 1) you will first select a random set
     * of coordinates (and their colors) to use as centers from which to
     * begin the fill. (this function is in file vor_given.cpp -- for 
     * testing purposes, you'll use regularly spaced points, rather than 
     * random.)
     * 2) Initialize a structure to use to maintain a collection of 
     * ordering structures
     *
     * 3) Initialize the fill: For each center c, in round-robin order, 
     *     do the following:
     *     a)  add the center to the its ordering structure. (every center 
     *         its own!
     *     b)  mark the location of that center as processed (the way you 
     *         do this is up to you!)
     *     c)  we have a choice to actually set the color of the pixel in 
     *         the fill when we add or when we remove. In our test cases, 
     *         we assume that you will change a color when a point is 
     *         added to a structure. (this is mostly relevant for checking 
     *         the animations.)
     *
     * 5) Complete the fill: Until all ordering structures (OS) are empty, 
     *    do the following for each OS, in a round robin order, indexing
     *    the iterations by k (an integer distance from the center):
     *    
     *      For each point less than or equal to distance k from its center:
     *      a)Remove the  point p from the ordering structure, and then...
     *
     *        i.    add p's unprocessed neighbors to the ordering structure if 
     *              they are within the appropriate distance from the center. We 
     *              describe this more carefully below. We call these the "valid"
     *              neighbors.
     *        ii.    use the colorPicker to set the new color of the valid neighbors.
     *        iii.   mark the valid neighbors as processed.
     *        iv.    as each neighbor is processed, if it is an appropriate 
     *              frame, send the current PNG to the
     *              animation (as described below).
    *
     *      b) When implementing your breadth-first and depth-first fills, 
     *            you will need to explore neighboring pixels in some order.
     *
     *        For this assignment, each pixel p has *up to* 8 neighbors, consisting of 
     *        the 8 pixels who share an edge with p. (We leave it to
     *        you to describe those 8 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** UP(-y), UPLEFT(-x,-y), LEFT(-x), LEFTDOWN(-x,+y), DOWN(+y), 
     *        DOWNRIGHT(+x,+y), RIGHT(+x), RIGHTUP(+x,-y)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        TWO IMPORTANT NOTES: 
     *        1) *UP* here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction. 
     *        2) not all of the 8 neighbors will be processed at every iteration of the
     *        while loop. You must assure that all vertices distance k or less
     *        from the center are processed (colored and put on the queue) before
     *        ANY whose distance is *greater than* k. k is a non-negative integer. 
     *        Finally, distance is the standard Euclidean distance  (computed 
     *        using the Pythagorean theorem). It is this requirement that assures
     *        that the fill grows outward from the center in the shape of a circle,
     *        rather than a diamond or a square. 
     *
     *      c) For every g pixels filled, **starting at the gth pixel**, you
     *        must add a frame to the animation, where g = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *      d) Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */



     /* Your code here. As a point of reference, we used three different helper
      * functions to complete this code. You may add as many as you wish, since
      * we will be grading vor.h. File "vor_given.cpp also includes the function
      * used to generate the original set of centers. 
      */
    
    // getting the centers.
    vector<center> centers = randSample(img, density);

    // 2D array to keep track of which x,y coordinates have been processed.
    vector<vector<bool>> tracker;
    
    for(int i=0; i < img.width() ; i++){
        vector<bool> y_vector;
        tracker.push_back(y_vector);
        for(int j=0; j<img.height() ; j++){
            y_vector.push_back(false);
        }
    }

    // Each center will have its own ordering structure
    vector<OrderingStructure<point>> patches ;
    for(int i=0; i<centers.size(); i++){
        OrderingStructure<point> temp;
        temp.add(point(centers[i]));
    
        tracker[centers[i].x][centers[i].y] = true;
        patches.push_back(temp);
    }

    // animation
    animation ani;
    // start filling the PNG make.
    PNG make(img.width(),img.height());
    // int k is the distance from the center.
    int k;
    // int g is the amount of pixels added since last frame
    int g = 0;

    while(!vector_is_empty(patches)){

        for(int i=0; i<patches.size(); i++){
            OrderingStructure<point> os = patches[i];
            
            if(os.isEmpty()) continue;

            k = os.peek().level;

            while(!os.isEmpty() && os.peek().level==k){

                point p = os.remove();

                // the order the valide neighbors are returned will be starting from top and in ccw
                vector<point> neighbors = get_valid_neighbors(img, p, centers[i], k+1, tracker);
                
                for(int i = 0; i < neighbors.size(); i++){
                    point neigh = neighbors[i];
                    
                    //paint the color and then insert the valid neighbor into the os
                    *make.getPixel(neigh.x, neigh.y) = fillColor(neigh);
                    os.add(neigh);
                    g++;
                    
                    // once g reaches frame frequency, add the png to gif and reset g
                    if(g==frameFreq){
                        g=0;
                        ani.addFrame(make);
                    }
                }
            }
        }
    }
    // as we leave the function send the last PNG as the last frame
    ani.addFrame(make);

}