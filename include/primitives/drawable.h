#ifndef DRAW_MACHINE_DRAWABLE_H
#define DRAW_MACHINE_DRAWABLE_H

#include <string>

namespace primitive {
    class Drawable {
    public:
        virtual void build() = 0;
        virtual void draw() = 0;
        virtual void getLog() = 0;
        virtual void setLog(const unsigned int&, const std::string&) = 0;
    };
}

#endif //DRAW_MACHINE_DRAWABLE_H
