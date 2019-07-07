#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include <stdint.h>
#include <utility>
#include "colorPicker.h"

/**
 * rainbowColorPicker: a functor that determines the color that should be used
 * given an x and a y coordinate using a rainbow pattern.
 *
 */
class customColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new rainbowColorPicker.
     *
     * @param freq_ Frequency at which to cycle colors
     */
    customColorPicker(PNG& img2write, PNG& img2ref);

    /**
     * Picks the color for pixel (x, y).
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(int x, int y);

  private:
    PNG im2write;
    PNG im2ref;

};

#endif
