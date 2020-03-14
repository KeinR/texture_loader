#ifndef TEXTURE_IMAGE_H_INCLUDED
#define TEXTURE_IMAGE_H_INCLUDED

#include "../extern/stb_image.h"

class tl_image {
    int size;
    int width;
    int height;
    int channels;
    const unsigned char *pixels;
    public:
    tl_image(int length, unsigned char *raw): pixels(stbi_load_from_memory(raw, length, &width, &height, &channels, 0)) {
        delete[] raw;
        if (pixels == NULL) {
            std::cout << "ERROR: Failed to load image from memory: " << stbi_failure_reason() << std::endl;
        }
    }
    void free() {
        if (size) {
            stbi_image_free(pixels);
            size = 0;
        }
    }
    int size() {
        return size;
    }
    int width() {
        return width;
    }
    int height() {
        return height;
    }
    int channels() {
        return channels;
    }
    const unsigned char *pixels() {
        return pixels;
    }
};

#endif
