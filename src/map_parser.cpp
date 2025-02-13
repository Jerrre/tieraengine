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
                            std::string texPart = line;
                            std::string coordPart = "";
                            std::vector<glm::vec3> planeCoords; // 3 points (xyz) defining a plane
                            
                            while (texPart.find(" ) ") != std::string::npos){
                                unsigned int ind = texPart.find(" ) ") ;
                                coordPart = texPart.substr(0, ind);
                                coordPart.erase(0,2);
                                
                                std::vector<std::string> tempPlaneCoord;
                                while (coordPart.find(" ") != std::string::npos){
                                    unsigned int ind2 = coordPart.find(" ");
                                    std::string value = coordPart.substr(0, ind2);
                                    coordPart.erase(0, ind2+1);
                                    tempPlaneCoord.push_back(value);
                                }
                                tempPlaneCoord.push_back(coordPart);
                                planeCoords.push_back(glm::vec3(std::stof(tempPlaneCoord[0]), std::stof(tempPlaneCoord[1]), std::stof(tempPlaneCoord[2])));

                                texPart.erase(0, ind+3);
                                
                            }
                            std::cout << glm::to_string(planeCoords[0]) << " ";
                            std::cout << glm::to_string(planeCoords[1]) << " ";
                            std::cout << glm::to_string(planeCoords[2]) << std::endl;

                            // process tempTail here
                            //std::cout << tempTail << std::endl;
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
