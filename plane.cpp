// GLM
#include <glm/glm.hpp>

// Project
#include "plane.h"

namespace static_meshes_3D {

    glm::vec3 Plane::vertices[6] =
    {
        glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(-0.5f, 0.0f, 0.5f),
    };

    // complex texturing technique: texture tiling for more details on the ground
	// using 5.0f as max texture coordinate to repeat the image 5 times
    glm::vec2 Plane::textureCoordinates[6] =
    {
        glm::vec2(0.0f, 5.0f), glm::vec2(5.0f, 5.0f), glm::vec2(5.0f, 0.0f),
        glm::vec2(5.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 5.0f)
    };

    Plane::Plane(glm::vec4 color)
        : StaticMesh3D(true, true, true),
        _color(color)
    {
        initializeData();
    }


    glm::vec4 Plane::getColor() const
    {
        return _color;
    }

    void Plane::render() const
    {
        if (!_isInitialized) {
            return;
        }

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void Plane::renderPoints() const
    {
        if (!_isInitialized) {
            return;
        }

        glBindVertexArray(_vao);
        glDrawArrays(GL_POINTS, 0, 6);
    }

    /*void Cube::renderFaces(int facesBitmask) const
    {
        if (!_isInitialized) {
            return;
        }

        glBindVertexArray(_vao);

        if (facesBitmask & CUBE_FRONT_FACE) {
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        if (facesBitmask & CUBE_BACK_FACE) {
            glDrawArrays(GL_TRIANGLES, 6, 6);
        }
        if (facesBitmask & CUBE_LEFT_FACE) {
            glDrawArrays(GL_TRIANGLES, 12, 6);
        }
        if (facesBitmask & CUBE_RIGHT_FACE) {
            glDrawArrays(GL_TRIANGLES, 18, 6);
        }
        if (facesBitmask & CUBE_TOP_FACE) {
            glDrawArrays(GL_TRIANGLES, 24, 6);
        }
        if (facesBitmask & CUBE_BOTTOM_FACE) {
            glDrawArrays(GL_TRIANGLES, 30, 6);
        }
    }*/

    void Plane::initializeData()
    {
        if (_isInitialized) {
            return;
        }

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        const auto numVertices = 6;
        const auto vertexByteSize = getVertexByteSize();
        _vbo.createVBO(vertexByteSize * numVertices);
        _vbo.bindVBO();

        if (hasPositions())
        {
            _vbo.addRawData(vertices, sizeof(glm::vec3) * numVertices);
        }

        if (hasTextureCoordinates())
        {
            _vbo.addRawData(textureCoordinates, sizeof(glm::vec2) * numVertices);
        }


        // Add color for every vertex of cylinder bottom cover
        _vbo.addData(_color, numVertices);


        _vbo.uploadDataToGPU(GL_STATIC_DRAW);
        setVertexAttributesPointers(numVertices);
        _isInitialized = true;
    }

} // namespace static_meshes_3D