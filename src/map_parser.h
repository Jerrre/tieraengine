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

class Mesh;
class Texture;

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

std::vector<Mesh> parse_map(const char* filePath);

//Model load_custom_model_from_mesh(std::vector<Mesh> meshArr, std::vector<Material> matArr, std::vector<BrushFace> brushFaces);

int get_texture_index(std::vector<std::string> &texNames, std::vector<Texture> &mapTextures, std::string textureName);

void triangulate(BrushFace brushFace, Mesh &brushMesh);

glm::vec2 calc_UV_coord(glm::vec3 vertex, TexInfo texture);

std::vector<glm::vec3> sort_vertices(BrushFace brushFace);

bool vertex_inside_brush(std::vector<BrushFace> brushFaces, glm::vec3 vertex);

glm::vec3 calc_plane_normal(std::vector<glm::vec3> plane);

glm::vec3 get_plane_intersection(
    std::vector<glm::vec3> plane1, 
    std::vector<glm::vec3> plane2, 
    std::vector<glm::vec3> plane3,
    int* valid);