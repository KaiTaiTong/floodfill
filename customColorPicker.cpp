/**
 * Author: Alan Tong
 * Date: June 5, 2019
 */
#include "customColorPicker.h"
#include <math.h>

customColorPicker::customColorPicker(PNG& img2write, PNG& img2ref){
    im2write = img2write;

    // implement dummy de-resolution approach to the ref Image
    PNG blank;
    blank.resize(im2write.width(), im2write.height());

    for (int row = 0; row < im2write.width(); ++row) {
        for (int col = 0; col < im2write.height(); ++col) {

            // normalize new row and col values based on
            // input targe image size

            int normalized_row = (img2ref.width()/im2write.width())*row;
            int normalized_col = (img2ref.height()/im2write.height())*col;

            *blank.getPixel(row, col) = *img2ref.getPixel(normalized_row, normalized_col);
        }
    }

    im2ref = blank;
}



HSLAPixel customColorPicker::operator()(int x, int y)
{

    /* directly replace the pixel in the im2write by im2ref
     * since, we have already de-resoluted the ref image
     * to have the same size as the target image
     */

    return *im2ref.getPixel(x, y);

}
