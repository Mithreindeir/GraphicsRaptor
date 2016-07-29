#ifndef HEADER_GRCAMERA
#define HEADER_GRCAMERA

#include "graphicsraptor.h"
#include "grMath.h"

typedef struct grCameraShake
{
	grFloat amount;
	grFloat growth;
	grFloat time;
	grFloat frequency;
	grFloat amplitude;
	grFloat duration;
} grCameraShake;

typedef struct grCameraZoom
{
	grVec2 view;
	grVec2 pos;
	grVec2 actualView;
	grFloat zoom;
	grFloat zoomTarget;
	grFloat speed;
} grCameraZoom;

typedef struct grCamera
{
	grVec4 front;
	grVec4 up;
	grVec2 pos;
	grVec2 target;
	grVec2 speed;
	grCameraShake shake;
	grCameraZoom zoom;
} grCamera;

grCamera* grCameraAlloc();
grCamera* grCameraInit(grCamera* camera, grVec2 size);
grMat4 grCameraGetViewMatrix(grCamera* cam);
grMat4 grCameraGetProjectionMatrix(grCamera* cam);
void grCameraPan(grCamera* cam, grVec2 move);
void grCameraZoomLevel(grCamera* cam, grFloat z);
void grCameraZoomMultiply(grCamera* cam, grFloat z);
void grCameraZoomAdd(grCamera* cam, grFloat add);
void grCameraShakeStart(grCamera* cam, grFloat growth, grFloat amplitude, grFloat frequency);
void grCameraShakeUpdate(grCamera* cam, grFloat dt);
void grCameraUpdate(grCamera* cam, grFloat dt);
void grCameraSetZoom(grCamera* cam, grFloat zoom, grFloat speed);
grVec2 grCameraGetPos(grCamera* cam);
grVec2 grCameraGetMouse(grCamera* cam, grVec2 mouse);

#endif