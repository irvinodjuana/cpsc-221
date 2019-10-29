#include "fadeColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade)
{
    /* your code here */
    fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p)
{
    /* your code here */
    HSLAPixel ret;
    ret.h = p.c.color.h;
    ret.s = p.c.color.s;
    int distX = p.x - p.c.x;
    int distY = p.y - p.c.y;
    double distSq = sqrt(distX * distX + distY * distY);
    ret.l = (p.c.color.l) * pow(fadeFactor, distSq);
    
    return ret;
}
