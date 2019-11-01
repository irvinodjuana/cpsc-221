/**
 * @file customColorPicker.h
 * Definition of a custom color picker.
 *
 */
#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include "colorPicker.h"
#include "point.h"
#include "center.h"
#include <cmath>

/**
 * customColorPicker: a functor that determines the color that should be used
 * given a point p, and simply returning the color of the center.
 *
 */
class customColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new customColorPicker.
     *
     */
    customColorPicker(double fade);

    /**
     * Picks the color for point p
    *
     * @param p
     * @return The color of p's center
     */
    virtual HSLAPixel operator()(point p);

  private:
    double fadeFactor;

};

#endif
