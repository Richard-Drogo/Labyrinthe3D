#include "rgbcolor.h"

RGBColor::RGBColor(GLclampf red, GLclampf green, GLclampf blue)
{
    this->red_ = red;
    this->green_ = green;
    this->blue_ = blue;
}

const RGBColor RGBColor::red_color_ = RGBColor(255, 0, 0);
const RGBColor RGBColor::green_color_ = RGBColor(0, 255, 0);
const RGBColor RGBColor::blue_color_ = RGBColor(0,0,255);
const RGBColor RGBColor::yellow_color_ = RGBColor(255, 255, 0);
const RGBColor RGBColor::pink_color_ = RGBColor(255, 0, 255);
const RGBColor RGBColor::cyan_color_ = RGBColor(0, 255, 255);
const RGBColor RGBColor::black_color_ = RGBColor(0, 0, 0);
const RGBColor RGBColor::white_color_ = RGBColor(255, 255, 255);
const RGBColor RGBColor::silver_color_ = RGBColor(192, 192, 192);
