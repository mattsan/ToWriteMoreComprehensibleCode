/// @date 2007/07/14
/// @author E.Matsumoto

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "Object.h"
#include "Point.h"

#include <string>

class TextObject : public Object
{
public:
    explicit TextObject(const Point& position);
    TextObject& set(const std::string& text);
    const std::string& get() const;
    void draw();

private:
    std::string text_;
};

#endif//TEXTOBJECT_H
