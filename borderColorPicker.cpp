/**
 * Author: Alan Tong
 * Date: June 5, 2019
 */
#include "borderColorPicker.h"
#include <cmath>

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
    color = fillColor;
    im = img;
    tol = tolerance;
    ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{
    HSLAPixel * cur = im.getPixel(x,y);

    int border_x = im.width();
    int border_y = im.height();

    // check if the point (x,y) is near the border of the image
    if (x-3 < 0 || border_x-1-x-3 < 0 || y-3 < 0 || border_y-1-y-3 <0){
        return color;
    }

    // check if the point (x,y) is near the border of fill
    for (int row = -3; row <= 3; ++row) {
        for (int col = -3; col <= 3; ++col) {

            int current_x = x+row;
            int current_y = y+col;

            // test if within a circle distance of 3
            double eucDist = pow((current_x-x),2) + pow((current_y-y),2);

            if (eucDist <= 9){
                // test color distance
                HSLAPixel tempColor = *im.getPixel(current_x, current_y);
                double colorDist = ctr.dist(tempColor);
                if (colorDist > tol){
                    return color;
                }
            }
        }
    }

    return *cur;
}
