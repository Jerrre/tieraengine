#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "mesh.h"

//texName [Ux Uy Uz Uoff] [Vx Vy Vz Voff] rot Uscale Vscale
struct TexInfo{
    std::string name;
    glm::vec3 u_axis;
    glm::vec3 v_axis;
    glm::vec2 uv_offset;
    float rotation;
    glm::vec2 uv_scale;
    int textureIndex;
    int height;
    int width;
};
struct BrushFace{
    std::vector<glm::vec3> plane;
    TexInfo texInfo;
    std::vector<glm::vec3> polygon;
};
struct MeshInfo{
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> texCoords;
    std::vector<glm::vec3> normals;
};

//int get_material_index(std::vector<std::string> &texNames, std::vector<Material> &mapMaterials, std::string textureName);

void parse_map(const char* filePath);

//Model load_custom_model_from_mesh(std::vector<Mesh> meshArr, std::vector<Material> matArr, std::vector<BrushFace> brushFaces);

//Texture2D create_texture(std::string texName);

void triangulate(BrushFace brushFace, std::vector<float> &triVertices, std::vector<float> &triTexCoords);

glm::vec2 calc_UV_coord(glm::vec3 vertex, TexInfo texture);

std::vector<glm::vec3> sort_vertices(BrushFace brushFace);

bool vertex_inside_brush(std::vector<BrushFace> brushFaces, glm::vec3 vertex);

glm::vec3 calc_plane_normal(std::vector<glm::vec3> plane);

glm::vec3 get_plane_intersection(
    std::vector<glm::vec3> plane1, 
    std::vector<glm::vec3> plane2, 
    std::vector<glm::vec3> plane3,
    int* valid);

//Mesh gen_mesh_custom(MeshInfo meshInfo);