#include "map_parser.h"

void parse_map(const char* filePath)
{
    std::string line;
    std::string mapContent;
    std::ifstream mapFile(filePath);

    bool entityStart = false;
    bool brushStart = false;
    bool worldspawn_entity = true;
    std::string prevLine = "";

    if (mapFile.is_open()){
        while (getline (mapFile,line)){
            if (entityStart){
                if (worldspawn_entity){
                    if (line.find("mapversion") != std::string::npos){
                        if (line.find("220") == std::string::npos){
                            std::cout << "ERROR: Map version 220 not used" << std::endl;
                        }
                    }
                    if (line == "}" && prevLine == "}"){
                        worldspawn_entity = false;
                    }

                    if (brushStart){
                        if (line == "}"){
                            brushStart = false;
                        }
                        if (line != "}" && line != "{"){
                            std::cout << line << std::endl;
                        }
                    }
                    if (line.find("brush") != std::string::npos){
                        brushStart = true;
                    }
                    prevLine = line;
                }
                else{
                    // TODO parse other entities
                }
            }
            if (line.find("entity") != std::string::npos){
                entityStart = true;
            }
        }
        mapFile.close();
    }
    else{
        std::cout << "ERROR: Unable to open map file" << std::endl;
    }
}
