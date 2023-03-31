#include <string>

class Drawable{
  public:
    virtual void draw() = 0;
    virtual void getLog() = 0;
    virtual void setLog(const unsigned int&, const std::string&) = 0;
};


