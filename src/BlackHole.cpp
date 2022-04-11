//
//  BlackHole.cpp
//  Blackhole
//
//  Created by JunfengZhou on 2021/12/9.
//

#include "BlackHole.hpp"

BlackHole::BlackHole(unsigned int w, unsigned int h){
    m_Pos = glm::vec3(0.0f, 0.0f, 2.0f);
    
    m_FrameBuffer.Create(w, h);
}

void BlackHole::Update(glm::mat4 projection, unsigned int screenWidth, unsigned int screenHeight){
    m_FrameBuffer.Update();
    m_FrameBuffer.Bind();
    
    
    m_FrameBuffer.m_fboShader->SetUniform3f("camPos", Camera::Instance().GetEyeXPosition(), Camera::Instance().GetEyeYPosition(), Camera::Instance().GetEyeZPosition());
    m_FrameBuffer.m_fboShader->SetUniform3f("pos", m_Pos.x, m_Pos.y, m_Pos.z);
    m_FrameBuffer.m_fboShader->SetUniform1f("eventHorizonRadius", 0.3f);
    m_FrameBuffer.m_fboShader->SetUniform2f("resolution", (float)screenWidth, (float)screenHeight);
    m_FrameBuffer.m_fboShader->SetUniformMatrix4fv("projection", &projection[0][0]);
    m_FrameBuffer.m_fboShader->SetUniformMatrix4fv("view", &Camera::Instance().GetWorldToViewmatrix()[0][0]);
    m_FrameBuffer.m_fboShader->SetUniform1f("time", SDL_GetTicks()/1000.0f);
    
    m_Pos.x = sin(SDL_GetTicks()/5000.0f);
    m_Pos.y = cos(SDL_GetTicks()/5000.0f);
}

void BlackHole::Render(){
    m_FrameBuffer.Unbind();
    glDisable(GL_DEPTH_TEST);
    m_FrameBuffer.m_fboShader->Bind();
    m_FrameBuffer.DrawFBO();
    m_FrameBuffer.m_fboShader->Unbind();
}
