//
//  BlackHole.hpp
//  Blackhole
//
//  Created by JunfengZhou on 2021/12/9.
//

#ifndef BlackHole_hpp
#define BlackHole_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <string>
#include <vector>
#include <iostream>

#include "Shader.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "Framebuffer.hpp"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class BlackHole{
public:
    BlackHole(unsigned int w, unsigned int h);
    void Update(glm::mat4 projection, unsigned int screenWidth, unsigned int screenHeight);
    void Render();
    Transform GetTransform();
    void Bind();

private:
    glm::vec3 m_Pos;
    Framebuffer m_FrameBuffer;
};

#endif /* BlackHole_hpp */
