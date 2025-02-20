#include "map_parser.h"

/*int get_material_index(std::vector<std::string> &texNames, std::vector<Material> &mapMaterials, std::string textureName){
    
    for (int texInd =0; texInd < texNames.size(); texInd++){
        if (textureName == texNames[texInd]){
            return texInd;
        }
    }
    
    Material newMat = rl.LoadMaterialDefault();
    rl.SetMaterialTexture(&newMat, .ALBEDO, CreateTexture(textureName));
    
    mapMaterials.push_back(newMat);
    texNames.push_back(textureName);

    return texNames.size()-1;
}*/

std::vector<Mesh> parse_map(const char* filePath)
{
    std::string line;
    std::string mapContent;
    std::ifstream mapFile(filePath);

    bool entityStart = false;
    bool brushStart = false;
    bool worldspawn_entity = true;
    std::string prevLine = "";

    std::vector<BrushFace> brushFaces;
    std::vector<Mesh> mapMeshes;

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
                            glm::vec3 vertex;
                            int valid = 0;

                            // iterate each face of one brush and calculate the intersections to determine the final brush vertices
                            for (int pln1 = 0; pln1 < brushFaces.size(); pln1++){
                                std::vector<glm::vec3> convexPolygon;
                                for (int pln2 = 1; pln2 < brushFaces.size(); pln2++){
                                    glm::vec3 n1 = calc_plane_normal(brushFaces[0].plane);
                                    glm::vec3 n2 = calc_plane_normal(brushFaces[pln2].plane);
                                    if (glm::cross(n1,n2) != glm::vec3(0,0,0)){
                                        for (int pln3 = 2; pln3 < brushFaces.size(); pln3++){
                                            vertex = get_plane_intersection(brushFaces[0].plane, brushFaces[pln2].plane, brushFaces[pln3].plane, &valid);
                                            if (valid){
                                                //std::cout << glm::to_string(vertex) << std::endl;
                                                if (vertex_inside_brush(brushFaces, vertex)){
                                                    bool dup = false;
                                                    for (int vert = 0; vert < convexPolygon.size(); vert++){
                                                        if (convexPolygon[vert] == vertex){
                                                            dup = true;
                                                        }
                                                    }
                                                    if (!dup){
                                                        convexPolygon.push_back(vertex);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                brushFaces[0].polygon = convexPolygon;
                                brushFaces.push_back(brushFaces[0]);
                                brushFaces.erase(brushFaces.begin());
                            }
                        
                            // iterate calculated vertices and sort their order and winding, format the data for custom mesh generator
                            for (int face = 0; face < brushFaces.size(); face++){
                                Mesh brushMesh;
                                brushFaces[face].polygon = sort_vertices(brushFaces[face]);

                                triangulate(brushFaces[face], brushMesh);
                                brushMesh.create_mesh();

                                mapMeshes.push_back(brushMesh);
                            }
                            //newModel: rl.Model
                            //newModel = LoadCustomModelFromMesh(mapMeshes, mapMaterials, brushFaces)
                            //append(&mapModels, newModel)

                            /*for (int ind = 0; ind < brushFaces.size(); ind++){
                                for (int ind2 = 0; ind2 < brushFaces[ind].polygon.size(); ind2++){
                                    std::cout << glm::to_string(brushFaces[ind].polygon[ind2]); 
                                }
                                std::cout << std::endl;
                            }*/

                            brushFaces.clear();
                        }
                        if (line != "}" && line != "{"){
                            std::string texPart = line;
                            std::string coordPart = "";
                            std::vector<glm::vec3> planeCoords; // 3 points (xyz) defining a plane
                            
                            BrushFace brushFace;

                            while (texPart.find(" ) ") != std::string::npos){
                                unsigned int ind = texPart.find(" ) ") ;
                                coordPart = texPart.substr(0, ind);
                                coordPart.erase(0,2); // trim spaces
                                
                                std::vector<std::string> tempPlaneCoord;
                                while (coordPart.find(" ") != std::string::npos){
                                    unsigned int ind2 = coordPart.find(" ");
                                    std::string value = coordPart.substr(0, ind2);
                                    coordPart.erase(0, ind2+1); // trim space too
                                    tempPlaneCoord.push_back(value);
                                }
                                tempPlaneCoord.push_back(coordPart);
                                brushFace.plane.push_back(glm::vec3(std::stof(tempPlaneCoord[0]), std::stof(tempPlaneCoord[2]), -std::stof(tempPlaneCoord[1])));

                                texPart.erase(0, ind+3); // trim spaces
                                
                            }
                            // process tempTail here
                            //std::cout << texPart << std::endl;

                            brushFaces.push_back(brushFace);
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
    return mapMeshes;
}

/*Model load_custom_model_from_mesh(std::vector<Mesh> meshArr, std::vector<Material> matArr, std::vector<BrushFace> brushFaces){

    int meshCount = meshArr.size();
    int matCount = matArr.size();

    model.transform = rl.Matrix(1);

    model.meshCount = i32(meshCount)
    model.meshes = make([^]rl.Mesh, meshCount*size_of(rl.Mesh))
    model.meshes = raw_data(meshArr)

    model.materialCount = i32(matCount)
    model.materials = make([^]rl.Material, 2*size_of(rl.Material))
    model.materials = raw_data(matArr)

    model.meshMaterial = make([^]i32, meshCount*size_of(i32))

    for mod:=0; mod<meshCount; mod+=1{
        rl.SetModelMeshMaterial(&model, i32(mod), brushFaces[mod].texInfo.textureIndex)
    }

    return model;
}*/

/*Texture2D create_texture(std::string texName){
    std::vector<std::string> imgPathArr = {"resources//textures/", texName, ".png"};
    std::string imgPath = imgPathArr[0] + imgPathArr[1] + imgPathArr[2];
    
    texImg: rl.Image = rl.LoadImage(strings.clone_to_cstring(imgPath))
    texture = rl.LoadTextureFromImage(texImg)
    
    rl.UnloadImage(texImg)
    return texture
}*/

void triangulate(BrushFace brushFace, Mesh &brushMesh){
    int triCount = brushFace.polygon.size() - 2;
    glm::vec3 triPoly[3];

    triPoly[0] = brushFace.polygon[0];

    glm::vec3 planeNormal = calc_plane_normal(brushFace.plane);
    glm::vec3 triNormal;

    for (int tri = 0; tri < triCount; tri++){
        triPoly[1] = brushFace.polygon[tri+1];
        triPoly[2] = brushFace.polygon[tri+2];

        for (int vert = 0; vert < 3; vert++){
            brushMesh.vertices.push_back(triPoly[vert]);
            glm::vec2 uv_coord = calc_UV_coord(triPoly[vert], brushFace.texInfo) ;
            brushMesh.texCoords.push_back(uv_coord);
        }
    }
}

glm::vec2 calc_UV_coord(glm::vec3 vertex, TexInfo texture){
    glm::vec2 uv_coord; 
    uv_coord.x = glm::dot(vertex, texture.u_axis / texture.uv_scale.x) + texture.uv_offset.x;
    uv_coord.y = glm::dot(vertex, texture.v_axis / texture.uv_scale.y) + texture.uv_offset.y;
    uv_coord.x /= float(texture.width);
    uv_coord.y /= float(texture.height);
    return uv_coord;
}

std::vector<glm::vec3> sort_vertices(BrushFace brushFace){
    int vertCount = brushFace.polygon.size();
    std::vector<glm::vec3> sorted;

    glm::vec3 n = calc_plane_normal(brushFace.plane);
    glm::vec3 u = glm::normalize(brushFace.plane[1] - brushFace.plane[0]);
    glm::vec3 v = glm::normalize(glm::cross(u, n));

    std::vector<glm::vec2> mapped;
    glm::vec2 sum = {0,0};
    for (int pntIndex = 0; pntIndex < vertCount; pntIndex++){
        glm::vec2 uv;
        uv.x = glm::dot(brushFace.polygon[pntIndex], u);
        uv.y = glm::dot(brushFace.polygon[pntIndex], v);
        mapped.push_back(uv);
        sum += uv;
    }
    glm::vec2 center = {sum.x/float(vertCount),sum.y/float(vertCount)};
    
    std::vector<glm::vec3> poly = brushFace.polygon;

    std::vector<float> angles;
    float signTest;
    glm::vec2 refVec = glm::normalize(mapped[0]-center);
    glm::vec2 signTestVec = {refVec[1], -refVec[0]};
    for (int ind = 0; ind < vertCount; ind++){
        double dotProd = glm::dot(signTestVec, glm::normalize(mapped[ind]-center));
        signTest = std::min(std::max(dotProd, -1.0), 1.0);
        double acosDot = glm::dot(refVec, glm::normalize(mapped[ind]-center));
        float angle = glm::acos(std::min(std::max(acosDot, -1.0), 1.0));
        if (signTest < 0){
            angle = 2*glm::pi<float>()-angle;
        }
        angles.push_back(angle);
    }

    std::vector<float> sortedAngles;
    sortedAngles.push_back(angles[0]);
    sorted.push_back(poly[0]);

    poly.erase(poly.begin());
    angles.erase(angles.begin());

    for (int loop = 0; loop < vertCount - 2; loop++){
        int ite = 0;
        float smallest = 100;
        for (int an = 0; an < angles.size(); an++){
            if (angles[an] < smallest){
                smallest = angles[an];
                ite = an;
            }
        }
        sorted.push_back(poly[ite]);
        sortedAngles.push_back(angles[ite]);
        
        angles.erase(angles.begin() + ite);
        poly.erase(poly.begin() + ite);
    }

    sortedAngles.push_back(angles[0]);
    sorted.push_back(poly[0]);

    return sorted;
}

bool vertex_inside_brush(std::vector<BrushFace> brushFaces, glm::vec3 vertex){
    bool inside = true;
    for (int face = 0; face < brushFaces.size(); face++){
        glm::vec3 testVec = vertex - brushFaces[face].plane[0];
        float dotProd = glm::dot(testVec, calc_plane_normal(brushFaces[face].plane));
        //std::cout << dotProd << std::endl;
        if (dotProd > 0){
            inside = false;
        }
    }
    return inside;
}

glm::vec3 calc_plane_normal(std::vector<glm::vec3> plane){
    glm::vec3 n = glm::normalize(glm::cross((plane[2] - plane[0]), (plane[1] - plane[0]))); 
    return n;
}

glm::vec3 get_plane_intersection(std::vector<glm::vec3> plane1, std::vector<glm::vec3> plane2, std::vector<glm::vec3> plane3, int* valid){
    glm::vec3 n1 = calc_plane_normal(plane1);
    glm::vec3 n2 = calc_plane_normal(plane2);
    glm::vec3 n3 = calc_plane_normal(plane3);

    glm::vec3 dist;
    dist.x = glm::dot(n1, plane1[0]);
    dist.y = glm::dot(n2, plane2[0]);
    dist.z = glm::dot(n3, plane3[0]);

    glm::mat3x3 normalMat = {
        n1[0], n1[1], n1[2],
        n2[0], n2[1], n2[2],
        n3[0], n3[1], n3[2]
    };

    float det = glm::determinant(normalMat);

    if (det == 0){
        *valid = 0;
    }
    else{
        *valid = 1;
    }

    glm::mat3x3 normalMatInv = glm::inverse(normalMat);
    
    glm::vec3 vertex = dist*normalMatInv;

    /*
    vertex.x = glm::round(vertex.x);
    vertex.y = glm::round(vertex.y);
    vertex.z = glm::round(vertex.z);
    */

    return vertex;
}