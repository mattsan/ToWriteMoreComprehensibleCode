/// @date 2007/07/14
/// @author E.Matsumoto

#include "TextObject.h"
#include "RGBColor.h"

#include <GLUT/glut.h>

static const GLdouble Scale = 0.1;
static const RGBColor TextColor(1, 0, 0);

TextObject::TextObject(const Point& position) : Object(position)
{
}

TextObject& TextObject::set(const std::string& text)
{
    text_ = text;
    return *this;
}

const std::string& TextObject::get() const
{
    return text_;
}

void TextObject::draw()
{
    glColor3dv(TextColor.get());
    glPushMatrix();
    glTranslatef(getPosition().x, getPosition().y, 0);
    glScalef(Scale, -Scale, 0);

    std::for_each(text_.begin(), text_.end(), std::bind1st(std::ptr_fun(glutStrokeCharacter), GLUT_STROKE_ROMAN));

    glPopMatrix();
}
