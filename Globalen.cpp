
#include <iostream>
#include "Scene.h"
#include "Camera.h"
#include "Tetrahedron.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    Scene S;
    Camera C;

    
    C.render(S);
    C.createImage();

    

}
