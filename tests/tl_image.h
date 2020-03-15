#ifndef TEXTURE_IMAGE_H_INCLUDED
#define TEXTURE_IMAGE_H_INCLUDED

/**
 * Orion "KeinR" Musselman
 * Version 1.0
 */

class tl_image {
    int sizeVal;
    int widthVal;
    int heightVal;
    int channelsVal;
    int rawLength;
    unsigned char *raw;
    unsigned char *pixelsVal;
    public:
    tl_image(int length, unsigned char *raw);
    ~tl_image();
    void free();
    void load();
    int size();
    int width();
    int height();
    int channels();
    const unsigned char *pixels();
};

#endif
