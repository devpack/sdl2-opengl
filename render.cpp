#include "render.h"  

/*---------------------------------------------------------------------------*/

Render::Render()
{

}

Render::~Render()
{

}

/*---------------------------------------------------------------------------*/

void Render::Scene() {

    this -> DrawCube();
}

/*---------------------------------------------------------------------------*/

void Render::DrawCube()
{
    glColor4f(0.2, 0.2, 0.25, 1.0);

    float XWORLD = 1.0f;
    float YWORLD = 1.0f;
    float ZWORLD = 1.0f;

    // Front
    glBegin(GL_LINE_LOOP);
    glVertex3f(-XWORLD,  YWORLD, ZWORLD);
    glVertex3f( XWORLD,  YWORLD, ZWORLD);
    glVertex3f( XWORLD, -YWORLD, ZWORLD);
    glVertex3f(-XWORLD, -YWORLD, ZWORLD);  
    glEnd();
    
    // Back
    glBegin(GL_LINE_LOOP);
    glVertex3f(-XWORLD,  YWORLD, -ZWORLD);
    glVertex3f( XWORLD,  YWORLD, -ZWORLD);
    glVertex3f( XWORLD, -YWORLD, -ZWORLD);
    glVertex3f(-XWORLD, -YWORLD, -ZWORLD);  
    glEnd(); 
    
    // Side
    glBegin(GL_LINES);
    
    glVertex3f(-XWORLD,  YWORLD, ZWORLD);
    glVertex3f(-XWORLD,  YWORLD, -ZWORLD);
    glVertex3f(XWORLD, YWORLD, ZWORLD);
    glVertex3f(XWORLD, YWORLD, -ZWORLD); 
    
    glVertex3f(XWORLD, -YWORLD, ZWORLD);
    glVertex3f(XWORLD, -YWORLD, -ZWORLD);
    
    glVertex3f(-XWORLD, -YWORLD, ZWORLD);
    glVertex3f(-XWORLD, -YWORLD, -ZWORLD); 
    
    glEnd();  
}
