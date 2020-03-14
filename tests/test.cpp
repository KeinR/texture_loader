#include <fstream>
#include <iostream>
#include <string>

#include "../extern/stb_image.h"
#include "bash.hr"


int main() {
    image_bash.load();
    std::cout << "EYe image " << image_bash.size() << std::endl;
    unsigned char *s = new unsigned char[1000 * 1900];
    for (int i = 0; i < 1000 * 1900; i++) {
        s[i] = 0xF1;
    }
    std::string a;
    std::cin >> a;
    delete[] s;
    image_bash.free();
    std::cin >> a;
}


