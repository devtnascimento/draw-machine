#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace algorithms {
    class Transformation {
    public:
        virtual void rotate() = 0;
        virtual void move() = 0;
        virtual void MCRotate();

    private:

    };

} // algorithms