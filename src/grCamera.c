#include "../include/grCamera.h"

grCamera * grCameraAlloc()
{
	return malloc(sizeof(grCamera));
}

grCamera * grCameraInit(grCamera * camera)
{
	camera->front = grV4(0, 0, -1, 0);
	camera->up = grV4(0, 1, 0, 0);
	camera->pos = grV2(0, 0);
	return camera;
}

grMat4 grCameraGetViewMatrix(grCamera* cam)
{
	grVec4 p = grV4(cam->pos.x, cam->pos.y, 0, 0);
	return grLookAt(p, grVec4Add(p, cam->front), cam->up);
}
