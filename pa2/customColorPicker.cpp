#include "customColorPicker.h"

customColorPicker::customColorPicker(double fade)
{
    fadeFactor = fade;
}

HSLAPixel customColorPicker::operator()(point p)
{
/* your code here */
    HSLAPixel ret = p.c.color;
    // int distX = p.x - p.c.x;
    // int distY = p.y - p.c.y;
    // double distSq = sqrt(distX * distX + distY * distY);
    // ret.h = (360.0 - p.c.color.h) * pow(fadeFactor, distSq);
    // ret.l = (1.0 - p.c.color.l) * pow(fadeFactor, distSq);
    // ret.s = (1.0 - p.c.color.s) * pow(fadeFactor, distSq);
    // ret.a = (1.0 - p.c.color.a) * pow(fadeFactor, distSq);
    ret.h = ((int)ret.h * 5) % 360;
    
    return ret;
}
