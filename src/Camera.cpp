#include "Camera.hpp"

#include "glm/gtx/transform.hpp"

#include <iostream>

Camera& Camera::Instance(){
    static Camera* instance = new Camera();
    return *instance;
}

void Camera::MouseLook(int mouseX, int mouseY){
    // TODO: Which vector are you modifying?
	// *hint* not the eye...
    if(!mouseMoveEnabled)
    {
        m_oldMousePosition.x = mouseX;
        m_oldMousePosition.y = mouseY;
        mouseMoveEnabled = true;
    }
    
    float deltaX = (mouseX - m_oldMousePosition.x);
    float deltaY = (mouseY - m_oldMousePosition.y);
    m_oldMousePosition.x = mouseX;
    m_oldMousePosition.y = mouseY;
    
    float sensitivity = 0.5f;
    deltaX *= sensitivity;
    deltaY *= sensitivity;
    
    yaw += deltaX;
    pitch -= deltaY;
    
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    m_viewDirection = front;
}

void Camera::MoveForward(float speed){
    // TODO: Which vector are you modifying?
    m_eyePosition.z -= speed;
}

void Camera::MoveBackward(float speed){
    // TODO: Which vector are you modifying?
    m_eyePosition.z += speed;
}

void Camera::MoveLeft(float speed){
    // TODO: Which vector are you modifying?
    m_eyePosition.x -= speed;
}

void Camera::MoveRight(float speed){
    // TODO: Which vector are you modifying?
    m_eyePosition.x += speed;
}

void Camera::MoveUp(float speed){
    // TODO: Which vector are you modifying?
    m_eyePosition.y += speed;
}

void Camera::MoveDown(float speed){
    // TODO: Which vector are you modifying?
    m_eyePosition.x -= speed;
}

float Camera::GetEyeXPosition(){
    return m_eyePosition.x;
}

float Camera::GetEyeYPosition(){
    return m_eyePosition.y;
}

float Camera::GetEyeZPosition(){
    return m_eyePosition.z;
}

float Camera::GetViewXDirection(){
    return m_viewDirection.x;
}

float Camera::GetViewYDirection(){
    return m_viewDirection.y;
}

float Camera::GetViewZDirection(){
    return m_viewDirection.z;
}

Camera::Camera(){
    std::cout << "Created a Single Camera!\n";
	// Position us at the origin.
    m_eyePosition = glm::vec3(0.0f, 0.0f, 10.0f);
	// Looking down along the z-axis initially.
	// Remember, this is negative because we are looking 'into' the scene.
    m_viewDirection = glm::vec3(0.0f,0.0f, -1.0f);
	// For now--our upVector always points up along the y-axis
    m_upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    m_oldMousePosition.x = 0.0f;
    m_oldMousePosition.y = 0.0f;

    mouseMoveEnabled = false;
}

glm::mat4 Camera::GetWorldToViewmatrix() const{
    // Think about the second argument and why that is
    // setup as it is.
    return glm::lookAt( m_eyePosition,
                        m_eyePosition + m_viewDirection,
                        m_upVector);
}
