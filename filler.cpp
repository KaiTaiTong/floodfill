/**
 * Author: Alan Tong
 * Date: June 5, 2019
 */
/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */
#include "filler.h"

animation filler::fillDotDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                             int dotGrid,int dotSize, double tolerance, int frameFreq)
{
    dotColorPicker a(fillColor, dotGrid, dotSize);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);

}

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                HSLAPixel borderColor, double tolerance, int frameFreq)
{
    // according to piazza post, center point is where we start
    // in this case, it is (x,y)

//    HSLAPixel* center = img.getPixel(x,y);
    HSLAPixel centerPixel = *img.getPixel(x,y);;
    borderColorPicker a(borderColor,img, tolerance, centerPixel);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);

}

animation filler::fillRainDFS(PNG& img, int x, int y,
                              long double freq, double tolerance, int frameFreq)
{

    /* example, implemented for you! */
    rainbowColorPicker a(freq);
    return fill<Stack>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillDotBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                             int dotGrid,int dotSize, double tolerance, int frameFreq)
{
    dotColorPicker a(fillColor, dotGrid, dotSize);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                HSLAPixel borderColor, double tolerance, int frameFreq)
{
    // according to piazza post, center point is where we start
    // in this case, it is (x,y)

//    HSLAPixel* center = img.getPixel(x,y);
    HSLAPixel centerPixel = *img.getPixel(x,y);;
    borderColorPicker a(borderColor,img, tolerance, centerPixel);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);

}

animation filler::fillRainBFS(PNG& img, int x, int y,
                              long double freq, double tolerance, int frameFreq)
{
    /* example, completed for you! */
    rainbowColorPicker a(freq);
    return fill<Queue>(img, x, y, a, tolerance, frameFreq);
}


template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure(OS), marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure.
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are
     *              within (or equal to) tolerance distance from the center,
     *              to the ordering structure.
     *        2.    use the colorPicker to set the new color of the point.
     *        3.    mark the point as processed.
     *        4.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
    *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        For this assignment, each pixel p has 4 neighbors, consisting of
     *        the 4 pixels who share an edge p. (We leave it to
     *        you to describe those 4 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours!
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** UP(-y), LEFT(-x), DOWN(+y), RIGHT(+x)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and
     *        it will be the one we test against.
     */

    /*
     * <Queue> : breadth-first-search
     * <Stack> : depth-first-search
     */

    //     declare and initialize variables
    int width = img.width();
    int height = img.height();

    OrderingStructure<vector<int>> container;   // each holds a vector of size 2 (x,y)
    bool pixelCheckMat [width][height];    // checkboard for visited pixel

    // I have to manually initize this bool matrix, even
    // tho when I used repl, compiler automatically
    // does this for me. (spent hours debugging and finally
    // found this problem)

    for (int row = 0; row < width; ++row) {
        for (int col = 0; col < height; ++col) {
            pixelCheckMat [row][col] = false;
        }
    }


    int counter = 0; // counting # of processed pixels for frame updating
    animation anime; // animation to return
    vector<int> currentPts;
    int temp_x;
    int temp_y;

    HSLAPixel centerPixel = *img.getPixel(x,y);

    /* Psudo Code:
     *
     * push{(x,y)}
     * mark as processed
     * pop{(x,y)}
     * push{(x,y) 4 neighbors: color <= tol from center}
     * colorPick(points in struct)
     * mark as processed
     *
     * if (f==freq) save current frame
     *
     *
     *
     */

    // initialize the first case at (x,y)
    currentPts.push_back(x);
    currentPts.push_back(y);

    container.add(currentPts);
    pixelCheckMat[x][y] = true;

    *img.getPixel(x,y) = fillColor(x,y); // first time have color dist = 0
    counter++;
    if (counter % frameFreq == 0){
        anime.addFrame(img);
    }

    while(!container.isEmpty()){

        vector<int> temp = container.remove();

        temp_x = temp[0];
        temp_y = temp[1];

        // Follow this Order:        ** UP(-y), LEFT(-x), DOWN(+y), RIGHT(+x)**

        // test UP
        if ((temp_y-1) >= 0 && pixelCheckMat[temp_x][temp_y-1] != true){

            HSLAPixel tempPixel = *img.getPixel(temp_x, temp_y-1);

            if (centerPixel.dist(tempPixel) <= tolerance){

                vector<int> temp2add;
                temp2add.push_back(temp_x);
                temp2add.push_back(temp_y-1);

                container.add(temp2add);            // push to ordering structure
                *img.getPixel(temp_x, temp_y-1) = fillColor(temp_x, temp_y-1);// fill color

                counter++;
                if (counter % frameFreq == 0){
                    anime.addFrame(img);

                }
            }

             pixelCheckMat[temp_x][temp_y-1] = true;// mark as visited
        }

        // test LEFT
        if ((temp_x-1) >= 0 && pixelCheckMat[temp_x-1][temp_y] != true){

            HSLAPixel tempPixel = *img.getPixel(temp_x-1, temp_y);


            if (centerPixel.dist(tempPixel) <= tolerance){

                vector<int> temp2add;
                temp2add.push_back(temp_x-1);
                temp2add.push_back(temp_y);

                container.add(temp2add);            // push to ordering structure
                *img.getPixel(temp_x-1, temp_y) = fillColor(temp_x-1, temp_y);        // fill color

                counter++;
                if (counter % frameFreq == 0){
                    anime.addFrame(img);
                }
            }
            pixelCheckMat[temp_x-1][temp_y] = true;// mark as visited

        }

        // test DOWN
        if ((temp_y+1) <= (height-1) && pixelCheckMat[temp_x][temp_y+1] != true){


            HSLAPixel tempPixel = *img.getPixel(temp_x, temp_y+1);

            if (centerPixel.dist(tempPixel) <= tolerance){

                vector<int> temp2add;
                temp2add.push_back(temp_x);
                temp2add.push_back(temp_y+1);

                container.add(temp2add);            // push to ordering structure
                *img.getPixel(temp_x, temp_y+1) = fillColor(temp_x, temp_y+1);         // fill color

                counter++;
                if (counter % frameFreq == 0){
                    anime.addFrame(img);
                }
            }
            pixelCheckMat[temp_x][temp_y+1] = true;// mark as visited
        }

        // test RIGHT
        if ((temp_x+1) <= (width-1) && pixelCheckMat[temp_x+1][temp_y] != true){


            HSLAPixel tempPixel = *img.getPixel(temp_x+1, temp_y);

            if (centerPixel.dist(tempPixel) <= tolerance){


                vector<int> temp2add;
                temp2add.push_back(temp_x+1);
                temp2add.push_back(temp_y);

                container.add(temp2add);            // push to ordering structure
                *img.getPixel(temp_x+1, temp_y) = fillColor(temp_x+1, temp_y);        // fill color

                counter++;
                if (counter % frameFreq == 0){
                    anime.addFrame(img);
                }
            }

            pixelCheckMat[temp_x+1][temp_y] = true;// mark as visited
        }

    }

    anime.addFrame(img);
    return anime;

}
