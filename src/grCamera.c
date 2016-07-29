#include "../include/grCamera.h"
#include <stdio.h>
#include <stdlib.h>

grCamera * grCameraAlloc()
{
	return malloc(sizeof(grCamera));
}

grCamera * grCameraInit(grCamera * camera, grVec2 size)
{
	camera->front = grV4(0, 0, -1, 0);
	camera->up = grV4(0, 1, 0, 0);
	camera->pos = grV2(0, 0);
	camera->target = grV2(0, 0);
	camera->speed = grV2(0.01, 0.01);
	camera->shake.angle = grV2(0, 0);
	camera->shake.decay = grV2(0, 0);
	camera->shake.duration = grV2(0, 0);
	camera->shake.position = grV2(0, 0);
	camera->shake.size = grV2(0, 0);
	camera->shake.speed = grV2(0.1, 0.1);
	camera->zoom.zoom = 1;
	camera->zoom.zoomTarget = 1;
	camera->zoom.actualView = size;
	camera->zoom.view = camera->zoom.actualView;
	camera->zoom.speed = 0.01;
	return camera;
}

grMat4 grCameraGetViewMatrix(grCamera* cam)
{
	grVec4 p = grV4(cam->pos.x, cam->pos.y, 0, 0);
	return grLookAt(p, grVec4Add(p, cam->front), cam->up);
}

grMat4 grCameraGetProjectionMatrix(grCamera * cam)
{
	return grOrtho(0.0, cam->zoom.view.x, 0.0, cam->zoom.view.y);
}

void grCameraPan(grCamera * cam, grVec2 move)
{
	cam->target = grVec2Add(cam->target, move);
}

void grCameraZoomLevel(grCamera * cam, grFloat z)
{
	cam->zoom.zoomTarget = z;
}

void grCameraZoomMultiply(grCamera * cam, grFloat z)
{
	cam->zoom.zoomTarget *= z;
}

void grCameraZoomAdd(grCamera * cam, grFloat add)
{
	cam->zoom.zoomTarget += add;
}

void grCameraShakeStart(grCamera* cam, grVec2 size, grVec2 speed, grVec2 decay, grVec2 duration)
{
	cam->shake.size = size;
	cam->shake.speed = speed;
	cam->shake.angle.x = (rand() % (3415*2))/100.0;
	cam->shake.angle.y = (rand() % (3415 * 2)) / 100.0;
	cam->shake.decay.x = decay.x;
	cam->shake.decay.y = decay.y;
	cam->shake.duration.x = duration.x;
	cam->shake.duration.y = duration.y;
}

void grCameraShakeUpdate(grCamera * cam, grFloat dt)
{
	if (cam->shake.duration.x*dt < dt)
	{
		if (cam->shake.size.x*cam->shake.decay.x < 0)
			cam->shake.size.x = 0;
		cam->pos.x += sin(cam->shake.angle.x * cam->shake.speed.x)*cam->shake.size.x;
	}
	else
		cam->shake.duration.x = 0;
	if (cam->shake.duration.y*dt < dt)
	{
		if (cam->shake.size.y*cam->shake.decay.y < 0)
			cam->shake.size.y = 0;
		cam->pos.y += sin(cam->shake.angle.y * cam->shake.speed.y)*cam->shake.size.y;
	}
	else
		cam->shake.duration.y = 0;
}

void grCameraUpdate(grCamera * cam, grFloat dt)
{
	cam->pos = grVec2Add(cam->pos, grVec2Mult(grVec2Sub(cam->target, cam->pos), cam->speed));
	cam->zoom.zoom += (cam->zoom.zoomTarget - cam->zoom.zoom)*cam->zoom.speed;
	grVec2 ov = cam->zoom.view;
	cam->zoom.view = grVec2Scale(cam->zoom.actualView, 1.0 / cam->zoom.zoom);
	cam->pos = grVec2Sub(cam->pos, grVec2Sub(cam->zoom.view, ov));
	cam->target = grVec2Sub(cam->target, grVec2Sub(cam->zoom.view, ov));

	grCameraShakeUpdate(cam, dt);
}

void grCameraSetZoom(grCamera * cam, grFloat zoom, grFloat speed)
{
	cam->zoom.zoomTarget = zoom;
	cam->zoom.zoom = zoom;
	cam->zoom.speed = speed;
}

grVec2 grCameraGetPos(grCamera * cam)
{
	return cam->pos;
}

grVec2 grCameraGetMouse(grCamera * cam, grVec2 mouse)
{
	return grVec2Add(mouse, cam->pos);
}
