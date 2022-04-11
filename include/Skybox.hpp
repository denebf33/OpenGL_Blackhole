//
//  Skybox.hpp
//  Blackhole
//
//  Created by JunfengZhou on 2021/12/6.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <string>
#include <vector>
#include <iostream>

#include "Shader.hpp"
#include "Camera.hpp"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Skybox{
public:
    Skybox();
    ~Skybox();
    void LoadCubeTexture(std::vector<std::string> paths);
    void Update(glm::mat4 projection);
    void Render();
    
private:
    GLuint textureID;
    Shader m_shader;
    unsigned int skyboxVAO, skyboxVBO;
};

#endif /* Skybox_hpp */
