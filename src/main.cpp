#include <iostream>
#include <fstream>
#include <string>

#define HEADER_EXT ".hr"
#define DATA_EXT ".rc"

int main(int argc, char *argv[]) {

    // Parse command line args
    if (argc < 2) {
        std::cout << "ERROR: Must specify source file" << std::endl;
        return 1;
    }
    const char *sourceFileName = nullptr;
    const char *varName = nullptr;
    for (int i = 1; i < argc; i++) {
        if (argv[i] == "--n" || argv[i] == "--name") {
            i++;
            if (i < argc) {
                varName = argv[i];
            } else {
                std::cout << "ERROR: unpaired parameter " << argv[i-1] << std::endl;
                return 1;
            }
        } else if (sourceFileName == nullptr) {
            sourceFileName = argv[i];
        } else {
            std::cout << "WARNING: superfluous source file " << argv[i] << " will be ignored" << std::endl;
        }
    }
    if (sourceFileName == nullptr) {
        std::cout << "ERROR: Must specify source file" << std::endl;
        return 1;
    }

    std::string compiled;

    std::string name(argv[1]);
    {
        std::string::iterator nameEnd = name.end();
        std::string::iterator nameBegin = name.begin();
        std::string::iterator it = name.end()-1;
        std::string::iterator end = name.begin()-1;
        for (; it != end && *it != '/' && *it != '\\'; it--) {
            if (*it == '.') {
                it = name.erase(it, name.end());
                end = name.begin()-1;
                break;
            }
        }
        for (; it != end; it--) {
            if (*it == '/' || *it == '\\') {
                name.erase(name.begin(), it+1);
                break;
            }
        }
    }

    compiled += "#include \"";
    compiled += name;
    compiled += HEADER_EXT"\"\n";

    std::ifstream file(argv[1], std::ios::binary);
    file.seekg(0, file.end);
    const int len = (int)file.tellg();
    std::string lenS = std::to_string(len);
    file.seekg(0, file.beg);
    compiled.reserve(compiled.capacity() + len * 2 + 30);

    compiled += "tl_image ";
    compiled += varName == nullptr ? "image_" + name : varName;
    compiled += "= tl_image(";
    compiled += lenS;
    compiled += ',';

    compiled += "new unsigned char[";
    compiled += lenS;
    compiled += "]{";
    for (int i = 0; i < len; i++) {
        compiled += std::to_string(file.get());
        compiled += ", ";
    }
    file.close();
    compiled.erase(compiled.end()-2, compiled.end());

    compiled += "});\n";

    std::string header;

    header += "#ifndef ";
    header += name;
    header += "_IMAGE_LOADED\n#define ";
    header += name;
    header += "_IMAGE_LOADED\n#include \"tl_image.h\"\nextern tl_image ";
    header += varName == nullptr ? "image_" + name : varName;
    header += ";\n#endif\n";

    std::string base(argv[1]);
    for (std::string::iterator it = base.end()-1, end = base.begin()-1; it != end && *it != '/' && *it != '\\'; it--) {
        if (*it == '.') {
            base.erase(it, base.end());
            break;
        }
    }

    std::ofstream out;
    out.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        out.open(base + HEADER_EXT);
        out.write(header.c_str(), header.size());
        out.close();
        out.open(base + DATA_EXT);
        out.write(compiled.c_str(), compiled.size());
        out.close();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR: could not save compiled image files: " << e.what() << std::endl;
        return 1;
    }
}
