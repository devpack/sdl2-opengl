#ifndef __RENDER_H_
#define __RENDER_H_

#include "init_playfield.h"

/*---------------------------------------------------------------------------*/

class Render
{   
       
public:
        Render();
        virtual ~Render();

public: 
        void Scene();
        void DrawCube();   
};

#endif