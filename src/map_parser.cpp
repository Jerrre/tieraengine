#include "map_parser.h"

void parse_map(const char* filePath)
{
    std::string line;
    std::string mapContent;
    std::ifstream mapFile(filePath);

    if (mapFile.is_open()){
        while (getline (mapFile,line)){
            std::cout << line << std::endl;
        }
        mapFile.close();
    }
    else{
        std::cout << "ERROR: Unable to open map file" << std::endl;
    }
}
