/**
 * Author: Alan Tong
 * Date: June 5, 2019
 */

#include "dotColorPicker.h"
#include <cmath>

dotColorPicker::dotColorPicker(HSLAPixel fillColor, int dotGrid,int dotSize)
{
    color = fillColor;
    spacing = dotGrid;
    size = dotSize;
}

HSLAPixel dotColorPicker::operator()(int x, int y)
{

    /* Notice that we have no access to the image, but indeed
     * we don't need to know any info about image.
     * Basically, we just need to find the closest Grid
     * Point from (x,y). Even if this Grid Point does not
     * exit in the input image (due to boundary), that is
     * still ok, as we treat it as a virtual boundary.
     */

    // find nearest Grid Point from (x,y) by searching
    // (x,y) 4 quadrats with length spacing
    bool flag = true;
    vector<vector<int>> gpMat;
    gpMat = getGridPoint(x-spacing, y-spacing, spacing*2);

    for (int numCoords = 0; numCoords < gpMat[0].size(); ++numCoords) {
        int distance = pow((gpMat[0][numCoords]-x),2)+pow((gpMat[1][numCoords]-y),2);

        std::cout << "distance:" << distance << std::endl;
        std::cout << "Size:" << pow(size,2) << std::endl;
        std::cout << "x:" << x << std::endl;
        std::cout << "y:" << y << std::endl;
        std::cout << "x_GP:" << gpMat[0][numCoords] << std::endl;
        std::cout << "y_GP:" << gpMat[1][numCoords] << std::endl;


        if (distance > pow(size,2)){
            flag = true;
        }else {
            // distance < dotSize, deal-breaker!
            flag = false;
            break;
        }
    }

    // if the distance from point (x,y) to GP is < dotSize,
    // return fillColor, otherwise return white.

    if (!flag){
        return color;
    }else {
        // return white
        HSLAPixel ret;
        ret.h = 0.; ret.s = 0.; ret.l = 1.;
        return ret;
    }


}

// helper functions
vector<vector<int>> dotColorPicker::getGridPoint(int lowerLx, int lowerLy, int sidelen){

    /* Starting from the coordinates (lowerLx,lowerLy) as
     * lower left corner of a square box with length sidelen,
     * search in this square for all Grid Points (GPs),
     * then return a matrix containing all coordinates of
     * GPs with form:
     *
     *              | x1 x2 x3 x4|
     *              | y1 y2 y3 y4|
     *
     * Grid Points:
     *      any (x,y) that have (x % dotGrid)==(y % dotGrid)==0
     *      dotGrid = sidelen/2
     */
    vector<int> rowList;
    vector<int> colList;

    for (int row = lowerLx; row <= lowerLx+sidelen; ++row) {
        if (row % (sidelen/2) == 0){
            rowList.push_back(row);
        }
    }

    for (int col = lowerLy; col <= lowerLy+sidelen; ++col) {
        if (col % (sidelen/2) == 0){
            colList.push_back(col);
        }
    }

    // put all combinations into matrix
    // colList size determines how many repetition we have
    // for each rowList element

    vector<vector<int>> coordListMat(2, vector<int>(colList.size()*rowList.size()));

    int counter = 0;
    for (int rowindex = 0; rowindex < rowList.size(); ++rowindex) {
        for (int colindex = 0; colindex < colList.size(); ++colindex) {
            coordListMat[0][counter] = rowList[rowindex];
            coordListMat[1][counter] = colList[colindex];
            counter++;
        }
    }

    return coordListMat;
}





