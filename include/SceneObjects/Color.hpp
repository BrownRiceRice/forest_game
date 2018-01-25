#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
   public:
    Color(float r, float g, float b) : red(r), green(g), blue(b) {}
    float getRed() const { return red; }
    float getBlue() const { return blue; }
    float getGreen() const { return green; }
    Color shiftUp(float val) const
    {
        return Color(std::min(red + val, 1.0f), std::min(green + val, 1.0f),
                     std::min(blue + val, 1.0f));
    }

    Color shiftDown(float val) const
    {
        return Color(std::max(red - val, 0.0f), std::max(green - val, 0.0f),
                     std::max(blue - val, 0.0f));
    }

   private:
    const float red, green, blue;
};

#endif
