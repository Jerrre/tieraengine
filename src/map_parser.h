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

#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))

const float EPSILON = 0.000001;

struct ImageStruct {
    unsigned char* data;
    int width, height, nrChannels;
};

struct MeshStruct {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    ImageStruct img;
    std::string name;
};

//texName [Ux Uy Uz Uoff] [Vx Vy Vz Voff] rot Uscale Vscale
struct TexInfo {
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
struct BrushFace {
    std::vector<glm::vec3> plane;
    TexInfo texInfo;
    std::vector<glm::vec3> polygon;
};

void parse_map(const char* filePath, glm::vec3* playerOrig);

void write_bin_file(std::vector<MeshStruct> meshStructs);

int get_texture_index(std::vector<std::string>& texNames, std::vector<MeshStruct>& sortedMeshes, std::string textureName);

void triangulate(BrushFace brushFace, MeshStruct& brushMesh);

glm::vec2 calc_UV_coord(glm::vec3 vertex, TexInfo texture);

std::vector<glm::vec3> sort_vertices(BrushFace brushFace);

bool vertex_inside_brush(std::vector<BrushFace> brushFaces, glm::vec3 vertex);

glm::vec3 calc_plane_normal(std::vector<glm::vec3> plane);

glm::vec3 get_plane_intersection(
    std::vector<glm::vec3> plane1,
    std::vector<glm::vec3> plane2,
    std::vector<glm::vec3> plane3,
    int* valid);

float mat_3x3_det(glm::mat3x3 nM);

double calcDotProd(glm::vec3 a, glm::vec3 b);