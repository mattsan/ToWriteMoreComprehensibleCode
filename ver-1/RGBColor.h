/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include <GLUT/glut.h>

class RGBColor
{
public:
    RGBColor() { set(0, 0, 0); }
    RGBColor(GLdouble r, GLdouble g, GLdouble b) { set(r, g, b); }

    void set(GLdouble r, GLdouble g, GLdouble b) { rgb[0] = r; rgb[1] = g; rgb[2] = b; }
    const GLdouble* get() const { return rgb; }

    void     setRed(GLdouble   value) { rgb[0] = value; }
    void     setGreen(GLdouble value) { rgb[1] = value; }
    void     setBlue(GLdouble  value) { rgb[2] = value; }
    GLdouble getRed() const           { return rgb[0];  }
    GLdouble getGreen() const         { return rgb[1];  }
    GLdouble getBlue() const          { return rgb[2];  }

private:
    GLdouble rgb[3];
};

#endif//RGBCOLOR_H
