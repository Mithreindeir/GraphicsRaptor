#ifndef HEADER_GRCAMERA
#define HEADER_GRCAMERA

#include "graphicsraptor.h"
#include "grMath.h"

typedef struct grCamera
{
	grVec4 front;
	grVec4 up;
	grVec2 pos;
} grCamera;

grCamera* grCameraAlloc();
grCamera* grCameraInit(grCamera* camera);
grMat4 grCameraGetViewMatrix(grCamera* cam);


#endif