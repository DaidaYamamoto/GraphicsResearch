#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include <iostream>
#include <random>
#include <string>
#include <filesystem> // std::tr2::sys::path etc.
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "main.h"

struct float3 {
    float x, y, z;
};

struct float2 {
    float u, v;
};

struct vertex_index {
    int v_idx, vt_idx, vn_idx;
    vertex_index() {};
    vertex_index(int idx) : v_idx(idx), vt_idx(idx), vn_idx(idx) {};
    vertex_index(int vidx, int vtidx, int vnidx) : v_idx(vidx), vt_idx(vtidx), vn_idx(vnidx) {};
    int total_idx{ 0 };
    bool overlapping{ false };
};

inline bool isSpace(const char c) {
    return (c == ' ') || (c == '\t');
}

inline bool isNewLine(const char c) {
    return (c == '\r') || (c == '\n') || (c == '\0');
}

// Make index zero-base, and also support relative index. 
inline int fixIndex(int idx, int n)
{
    int i;

    if (idx > 0) {
        i = idx - 1;
    }
    else if (idx == 0) {
        i = 0;
    }
    else { // negative value = relative
        i = n + idx;
    }
    return i;
}

inline float parseFloat(const char*& token)
{
    token += strspn(token, " \t");
    float f = (float)atof(token);
    token += strcspn(token, " \t\r");
    return f;
}

inline void parseFloat2(
    float& x, float& y,
    const char*& token)
{
    x = parseFloat(token);
    y = parseFloat(token);
}

inline void parseFloat3(
    float& x, float& y, float& z,
    const char*& token)
{
    x = parseFloat(token);
    y = parseFloat(token);
    z = parseFloat(token);
}

// Parse triples: i, i/j/k, i//k, i/j
vertex_index parseTriple(
    const char* &token,
    int vsize,
    int vnsize,
    int vtsize)
{
    vertex_index vi(-1);

    vi.v_idx = fixIndex(atoi(token), vsize);
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') {
        return vi;
    }
    token++;

    // i//k
    if (token[0] == '/') {
        token++;
        vi.vn_idx = fixIndex(atoi(token), vnsize);
        token += strcspn(token, "/ \t\r");
        return vi;
    }

    // i/j/k or i/j
    vi.vt_idx = fixIndex(atoi(token), vtsize);
    token += strcspn(token, "/ \t\r");
    if (token[0] != '/') {
        return vi;
    }

    // i/j/k
    token++;  // skip '/'
    vi.vn_idx = fixIndex(atoi(token), vnsize);
    token += strcspn(token, "/ \t\r");
    return vi;
}

void CleanupObj(const char* directory, const char* filename)
{
    // first pass : compute bounding box / load all vertices / texcoords / normals
    // second pass : split object based on material
    int dumpTarget = 0; // which object
    int dumpTexcoord = 1;
    char filepath[512];
    int num_vert[3] = { 0, 0, 0 };

    std::vector<float3> v;
    std::vector<float3> vn;
    std::vector<float2> vt;

    std::vector< std::vector<vertex_index> > faceGroup;
    std::unordered_map<std::string, vertex_index> allVertices;

    std::stringstream err;

    sprintf_s(filepath, "%s%s", directory, filename);
    std::ifstream ifs(filepath);
    if (!ifs) {
        std::cout << "Cannot open file [" << filepath << "]" << std::endl;
        exit(0);
    }

    int maxchars = 8192;  // Alloc enough size.
    std::vector<char> buf(maxchars);  // Alloc enough size.
    while (ifs.peek() != -1) {
        ifs.getline(&buf[0], maxchars);

        std::string linebuf(&buf[0]);

        // Trim newline '\r\n' or '\r'
        if (linebuf.size() > 0) {
            if (linebuf[linebuf.size() - 1] == '\n') linebuf.erase(linebuf.size() - 1);
        }
        if (linebuf.size() > 0) {
            if (linebuf[linebuf.size() - 1] == '\n') linebuf.erase(linebuf.size() - 1);
        }

        // Skip if empty line.
        if (linebuf.empty()) {
            continue;
        }

        // Skip leading space.
        const char* token = linebuf.c_str();
        token += strspn(token, " \t");

        assert(token);
        if (token[0] == '\0') continue; // empty line

        if (token[0] == '#') continue;  // comment line

        // vertex
        if (token[0] == 'v' && isSpace((token[1]))) {
            token += 2;
            float3 xyz;
            parseFloat3(xyz.x, xyz.y, xyz.z, token);
            v.push_back(xyz);
            continue;
        }

        // normal
        if (token[0] == 'v' && token[1] == 'n' && isSpace((token[2]))) {
            token += 3;
            float3 xyz;
            parseFloat3(xyz.x, xyz.y, xyz.z, token);
            vn.push_back(xyz);
            continue;
        }

        // texcoord
        if (token[0] == 'v' && token[1] == 't' && isSpace((token[2]))) {
            token += 3;
            float2 uv;
            parseFloat2(uv.u, uv.v, token);
            vt.push_back(uv);
            continue;
        }

        // face
        if (token[0] == 'f' && isSpace((token[1]))) {
            char namebuf[4096];
            token += 2;
            token += strspn(token, " \t");

            std::vector<vertex_index> face;
            while (!isNewLine(token[0])) {
                vertex_index vi = parseTriple(token, v.size(), vn.size(), vt.size());
                face.push_back(vi);
                int n = strspn(token, " \t\r");
                token += n;

                char vertexName[128];
                sprintf(vertexName, "%.5d_%.5d_%.5d", vi.v_idx, vi.vt_idx, vi.vn_idx);

                if (allVertices[vertexName].overlapping == false)
                {
                    allVertices[vertexName].v_idx = vi.v_idx;
                    allVertices[vertexName].vt_idx = vi.vt_idx;
                    allVertices[vertexName].vn_idx = vi.vn_idx;
                    allVertices[vertexName].overlapping = true;
                }
            }

            faceGroup.push_back(face);
            continue;
        }

        // use mtl
        if ((0 == strncmp(token, "usemtl", 6)) && isSpace((token[6]))) {
            char namebuf[4096];
            continue;
        }

        // load mtl
        if ((0 == strncmp(token, "mtllib", 6)) && isSpace((token[6]))) {
            continue;
        }

        // group name
        if (token[0] == 'g' && isSpace((token[1]))) {
            continue;
        }

        // object name
        if (token[0] == 'o' && isSpace((token[1]))) {
            continue;
        }

        // Ignore unknown command.
    }

    // dump all summary
    {
        char searchPath[256];
        sprintf_s(searchPath, sizeof(searchPath), "./%s/clean_%s", directory, filename);
        FILE* fp = fopen(searchPath, "w");

        // numbering
        int vertexIndex = 1;
        for (auto it = allVertices.begin(); it != allVertices.end(); ++it)
        {
            it->second.total_idx = vertexIndex;
            vertexIndex++;
        }

        // dump positions
        for (auto it = allVertices.begin(); it != allVertices.end(); ++it)
        {
            int tmp = it->second.v_idx;
            fprintf(fp, "v %f %f %f\n", v[tmp].x, v[tmp].y, v[tmp].z);
        }

        // dump textures
        for (auto it = allVertices.begin(); it != allVertices.end(); ++it)
        {
            int tmp = it->second.vt_idx;
            fprintf(fp, "vt %f %f\n", vt[tmp].u, vt[tmp].v);
        }

        // dump normals
        for (auto it = allVertices.begin(); it != allVertices.end(); ++it)
        {
            int tmp = it->second.vn_idx;
            fprintf(fp, "vn %f %f %f\n", vn[tmp].x, vn[tmp].y, vn[tmp].z);
        }

        // dump faces
        char vertexName[128];
        for (size_t i = 0; i < faceGroup.size(); i++)
        {
            fprintf(fp, "f ");
            for (size_t j = 0; j < faceGroup[i].size(); j++)
            {
                sprintf(vertexName, "%.5d_%.5d_%.5d", faceGroup[i][j].v_idx, faceGroup[i][j].vt_idx, faceGroup[i][j].vn_idx);
                int tmp = allVertices[vertexName].total_idx;
                fprintf(fp, "%d/%d/%d ", tmp, tmp, tmp);
            }
            fprintf(fp, "\n");
        }

        fclose(fp);
    }

    faceGroup.clear();
}
