#ifndef TEXTURE_IMAGE_H_INCLUDED
#define TEXTURE_IMAGE_H_INCLUDED

class tl_image {
    int sizeVal;
    int widthVal;
    int heightVal;
    int channelsVal;
    unsigned char *pixelsVal;
    public:
    tl_image(int length, unsigned char *raw);
    void free();
    int size();
    int width();
    int height();
    int channels();
    const unsigned char *pixels();
};

#endif
