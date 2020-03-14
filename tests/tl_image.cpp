#include <iostream>

#include "../extern/stb_image.h"
#include "tl_image.h"

tl_image::tl_image(int length, unsigned char *raw): pixelsVal(stbi_load_from_memory(raw, length, &widthVal, &heightVal, &channelsVal, 0)) {
    delete[] raw;
    if (pixelsVal == NULL) {
        std::cout << "ERROR: Failed to load image from memory: " << stbi_failure_reason() << std::endl;
    }
    sizeVal = widthVal * heightVal * channelsVal;
}

void tl_image::free() {
    if (sizeVal) {
        stbi_image_free(pixelsVal);
        sizeVal = 0;
    }
}

int tl_image::size() {
    return sizeVal;
}

int tl_image::width() {
    return widthVal;
}

int tl_image::height() {
    return heightVal;
}

int tl_image::channels() {
    return channelsVal;
}

const unsigned char *tl_image::pixels() {
    return pixelsVal;
}
