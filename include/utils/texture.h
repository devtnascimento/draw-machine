#ifndef DRAW_MACHINE_TEXTURE_H
#define DRAW_MACHINE_TEXTURE_H

#include <glad/glad.h>
#include <dirent.h>
#include <algorithm>
#include <iostream>
#include <external/stb_image.h>

namespace utils {
    class Texture {
    public:
        unsigned int id{};

        Texture(const char* name, const int format, const bool flip = false);
        
    private:
        const bool flip;
        const int format{};
        std::string path = "../static/textures";
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


#endif



