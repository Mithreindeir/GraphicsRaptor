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

	camera->zoom.zoom = 1;
	camera->zoom.zoomTarget = 1;
	camera->zoom.actualView = size;
	camera->zoom.view = camera->zoom.actualView;
	camera->zoom.speed = 0.01;
	camera->shake.growth = 0;
	camera->shake.amplitude = 0;
	camera->shake.frequency = 0;
	camera->shake.time = 0;
	camera->shake.amount = 0;

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


void grCameraShakeStart(grCamera* cam, grFloat growth, grFloat amplitude, grFloat frequency)
{
	cam->shake.growth = growth;
	cam->shake.amplitude = amplitude;
	cam->shake.frequency = frequency;
	cam->shake.amount = 1 + cam->shake.growth;
}

void grCameraShakeUpdate(grCamera * cam, grFloat dt)
{
	
	cam->shake.amount = fmax(1.0, powf(cam->shake.amount, 0.9));
	cam->shake.time += dt;
}

void grCameraUpdate(grCamera * cam, grFloat dt)
{
	cam->pos = grVec2Add(cam->pos, grVec2Mult(grVec2Sub(cam->target, cam->pos), cam->speed));
	cam->zoom.zoom += (cam->zoom.zoomTarget - cam->zoom.zoom)*cam->zoom.speed;
	grVec2 ov = cam->zoom.view;
	cam->zoom.view = grVec2Scale(cam->zoom.actualView, 1.0 / cam->zoom.zoom);
	cam->pos = grVec2Sub(cam->pos, grVec2Sub(cam->zoom.view, ov));
	cam->target = grVec2Sub(cam->target, grVec2Sub(cam->zoom.view, ov));

	grFloat la = cam->shake.amount != 0.0 ? log(cam->shake.amount) : cam->shake.amount;
	grFloat shakeFactor = cam->shake.amplitude * la;
	grVec2 wave = grV2(sin(cam->shake.time * cam->shake.frequency), cos(cam->shake.time * cam->shake.frequency));
	cam->pos = grVec2Add(cam->pos, grVec2Scale(wave, shakeFactor));
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
