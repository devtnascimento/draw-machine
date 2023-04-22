#include <utils/texture.h>
#include <iostream>
#include <filesystem>

using namespace std;

utils::Texture::Texture(const char* name, const int format, const bool flip) : name(name), format(format), flip(flip){

    filesystem::path current_path = filesystem::current_path();

    cout << "Current path 2 = " << current_path << endl;

    this->getFilename();
    this->load();
    this->generate();
}

void utils::Texture::load() {
    cout << "filename: " << this->filename << endl;
    stbi_set_flip_vertically_on_load(this->flip);
    this->data = stbi_load(this->filename.c_str(), &this->width, &this->height, &this->channels, 0);
}

void utils::Texture::getFilename(){
    this->dir = opendir(this->path.c_str());
    struct dirent* entry;

    if (dir == nullptr) {
        cerr << "Failed to open directory: " << this->path << endl;
        throw runtime_error("");
    }

    while ((entry = readdir(this->dir)) != nullptr) {
        string complete_current = entry->d_name;
        string current = utils::Texture::remove_extension(complete_current);
        transform(current.begin(), current.end(), current.begin(), ::tolower);

        if (current != "." && current != ".." && current == this->name) {
            cout << "filename: " << current << endl;
            this->filename = this->path + "/" + complete_current;
            break;
        }
    }
}

string utils::Texture::remove_extension(const string& filename) {
    size_t last_dot = filename.find_last_of('.');
    if (last_dot == string::npos) {
        return filename;
    } else {
        return filename.substr(0, last_dot);
    }
}

void utils::Texture::generate() {
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (this->data) {
        glTexImage2D(GL_TEXTURE_2D,
                        0,
                        GL_RGB,
                        this->width,
                        this->height,
                        0,
                        this->format,
                        GL_UNSIGNED_BYTE,
                        this->data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        throw runtime_error("[TEXTURE] Failed to load texture!");
    }
    stbi_image_free(this->data);
}
