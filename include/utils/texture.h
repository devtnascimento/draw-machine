#pragma once

#include <utils/model.h>

namespace utils {
    class Texture {
    public:
        unsigned int id{};

        Texture(const char* name, const int format, const bool flip = false);
        
    private:
        const bool flip;
        const int format{};
        std::string path = PATH + "/static/textures";
        const char* name{};
        std::string filename{};
        int width{}, height{}, channels{};
        unsigned char* data{};
        DIR* dir{};

        void load();
        void getFilename();
        static std::string remove_extension(const std::string& filename);
        void generate();
    };  
}
