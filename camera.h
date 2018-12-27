#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "init_playfield.h"

const GLdouble PI             = 3.1415926535897932384626433832795;
const GLdouble Deg2Rad        = 0.0174532925199432957692369076848861;

/*---------------------------------------------------------------------------*/

class Camera
{
public:
        GLfloat screen_width, screen_height;

        GLfloat xcamera, ycamera, zcamera;
        GLfloat znear, zfar;
        GLfloat angle_view;
        GLfloat speedwalk, speedrot;

        GLfloat yrotcamera, xrotcamera, zrotcamera;

        GLfloat mouse_sensitivity;
        GLfloat key_forward_sensitivity;
        GLfloat key_lateral_sensitivity;
        GLfloat key_height_sensitivity;
;

public:
        Camera( GLfloat screen_width, GLfloat screen_height, 
                GLfloat xcamera, GLfloat ycamera_height, GLfloat zcamera_distance,
                GLfloat znear, GLfloat zfar,
                GLfloat angle_view,
                GLfloat mouse_sensitivity, GLfloat key_forward_sensitivity, GLfloat key_lateral_sensitivity, GLfloat key_height_sensitivity);

        ~Camera() {}

public:

        void Init3dView();

        void Walk(GLfloat speed);
        void Yrotcamera(GLfloat speed);
        void Xrotcamera(GLfloat speed);
        void Zrotcamera(GLfloat speed);

        void CameraTransformations();

        void ProcessKeyboard(bool forward, bool backward, bool left, bool right, bool up, bool down);
        void ProcessMouse(float xoffset, float yoffset);

        void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble znear, GLdouble zfar);
};

#endif