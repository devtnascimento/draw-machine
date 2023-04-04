#include <string>

namespace D3 {
    class Drawable3D{
    public:
        virtual void build() = 0;
        virtual void draw3D() = 0;
        virtual void getLog() = 0;
        virtual void setLog(const unsigned int&, const std::string&) = 0;
    };

} // D3