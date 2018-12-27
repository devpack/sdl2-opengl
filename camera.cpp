#include "camera.h"

/*---------------------------------------------------------------------------*/

Camera::Camera( GLfloat screen_width, GLfloat screen_height,
                GLfloat xcamera, GLfloat ycamera_height, GLfloat zcamera_distance,
                GLfloat znear, GLfloat zfar,
                GLfloat angle_view,
                GLfloat mouse_sensitivity, GLfloat key_forward_sensitivity, GLfloat key_lateral_sensitivity, GLfloat key_height_sensitivity) 
        
                : yrotcamera(0.0), xrotcamera(0.0), zrotcamera(0.0)      

{
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    this->xcamera = xcamera;
    this->ycamera = ycamera_height;
    this->zcamera = zcamera_distance;
    
    this->znear = znear;
    this->zfar = zfar;
    this->angle_view = angle_view;

    this->mouse_sensitivity = mouse_sensitivity;
    this->key_forward_sensitivity = key_forward_sensitivity;
    this->key_lateral_sensitivity = key_lateral_sensitivity;
    this->key_height_sensitivity = key_height_sensitivity;

    Init3dView();
}
 
/*---------------------------------------------------------------------------*/

void Camera::Init3dView()
{
    glViewport(0, 0, this->screen_width, this->screen_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(angle_view, (GLdouble)this->screen_width/this->screen_height, znear, zfar);

    glMatrixMode (GL_MODELVIEW); 
    glLoadIdentity(); 
}

/*---------------------------------------------------------------------------*/

void Camera::ProcessMouse(float xoffset, float yoffset)
{
    Yrotcamera( (GLfloat)(xoffset * this->mouse_sensitivity) );
    Xrotcamera( (GLfloat)(yoffset * this->mouse_sensitivity) );  

    //ycamera += 10*mouse_z; 
}

/*---------------------------------------------------------------------------*/

void Camera::ProcessKeyboard(bool forward, bool backward, bool left, bool right, bool up, bool down)
{
    if(forward)
        Walk( this->key_forward_sensitivity );
    else if(backward)
        Walk( -this->key_forward_sensitivity );

    if(left)
        Yrotcamera( this->key_lateral_sensitivity ); 
    else if(right)
        Yrotcamera( -this->key_lateral_sensitivity ); 

    if(up)
        ycamera += this->key_height_sensitivity; 
    else if(down)
        ycamera -= this->key_height_sensitivity; 
}

/*---------------------------------------------------------------------------*/

void Camera::Walk(GLfloat speed)
{
    GLfloat yangle = (-yrotcamera - 90.0) * Deg2Rad;
    GLfloat xangle = (-xrotcamera - 90.0) * Deg2Rad;

    ycamera += -cos(xangle) * speed; 
    xcamera += cos(yangle) * -sin(xangle) * speed;
    zcamera += sin(yangle) * -sin(xangle) * speed; 
}

/*---------------------------------------------------------------------------*/
    
void Camera::Yrotcamera(GLfloat speed) 
{ 
    yrotcamera += speed; 
}

void Camera::Xrotcamera(GLfloat speed) 
{ 
    xrotcamera += speed; 
}

void Camera::Zrotcamera(GLfloat speed) 
{ 
    zrotcamera += speed; 
}
 
/*---------------------------------------------------------------------------*/
           
void Camera::CameraTransformations()
{
    glLoadIdentity();         
    glRotatef(-xrotcamera, 1.0, 0.0, 0.0);
    glRotatef(-zrotcamera, 0.0, 0.0, 1.0);
    glRotatef(-yrotcamera, 0.0, 1.0, 0.0);
    glTranslatef(-xcamera, -ycamera, -zcamera); 
}  

/*---------------------------------------------------------------------------*/

void Camera::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble znear, GLdouble zfar )
{
    GLdouble fW, fH;

    fH = tan( fovY / 180 * PI ) * znear / 2;
    fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, znear, zfar );
}