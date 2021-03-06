#ifndef HEADER_GRMATH
#define HEADER_GRMATH
#include <math.h>
#include "graphicsraptor.h"

typedef float grFloat;
#define DEGTORAD 0.01745329251

typedef struct grVec4
{
	union
	{
		struct { grFloat x, y, z, w; };
		struct { grFloat r, g, b, a; };
		grFloat v[4];
	};
} grVec4;

typedef struct grVec2
{
	union
	{
		struct { grFloat x, y; };
		grFloat v[2];
	};
} grVec2;

typedef struct grMat4
{
	union
	{
		grVec4 m[4];
		grFloat n[4][4];
	};
} grMat4;

extern inline grVec2 grV2(const grFloat x, const grFloat y);
extern inline grVec2 grVec2Add(const grVec2 a, const grVec2 b);
extern inline grVec2 grVec2Sub(const grVec2 a, const grVec2 b);
extern inline grVec2 grVec2Mult(const grVec2 a, const grVec2 b);
extern inline grVec2 grVec2Div(const grVec2 a, const grVec2 b);
extern inline grVec2 grVec2Scale(const grVec2 a, const grFloat b);
extern inline grVec2 grVec2Normalize(const grVec2 a);
extern inline grFloat grVec2Length(const grVec2 a);
extern inline grFloat grVec2LengthSqr(const grVec2 a);
extern inline grVec4 grV4(const grFloat x, const grFloat y, const grFloat z, const grFloat w);
extern inline grVec4 grVec4Add(const grVec4 a, const grVec4 b);
extern inline grVec4 grVec4Sub(const grVec4 a, const grVec4 b);
extern inline grVec4 grVec4Mult(const grVec4 a, const grVec4 b);
extern inline grVec4 grVec4Div(const grVec4 a, const grVec4 b);
extern inline grVec4 grVec4Scale(const grVec4 a, const grFloat b);
extern inline grVec4 grVec4Normalize(const grVec4 a);
extern inline grFloat grVec4Length(const grVec4 a);
extern inline grFloat grVec4LengthSqr(const grVec4 a);
extern inline grVec4 grVec4Translate(const grVec4 a, const grMat4 b);
extern inline grMat4 grM4(const grVec4 m, const grVec4 m2, const grVec4 m3, const grVec4 m4);
extern inline grMat4 grOrtho(grFloat right,grFloat left,grFloat top,grFloat bottom);
extern inline grMat4 grPerspective(grFloat fovy, grFloat aspect, grFloat front, grFloat back);
const GLfloat* grMat4Ptr(const grMat4* m);
const GLfloat* grVec4Ptr(const grVec4* m);
extern inline grMat4 grLookAt(const grVec4 eye, const grVec4 center, const grVec4 up);
extern inline grVec4 grVec4Cross(const grVec4 a, const grVec4 b);
extern inline grFloat grVec4Dot(const grVec4 a, const grVec4 b);
extern inline grMat4 grMat4Ones();
extern inline grMat4 grMat4Zeroes();
extern inline grMat4 grMat4Identity();
extern inline grMat4 grMat4Multiply(const grMat4 a, const grMat4 b);
extern inline grMat4 grMat4Translate(const grMat4 m, const grVec4 v);
extern inline grMat4 grMat4Scale(grMat4 m, const grVec4 v);
extern inline grMat4 grMat4Rotate(grMat4 m, grVec4 axis, const grFloat rotation);
extern inline grFloat grDegreesToRadian(const grFloat a);
extern inline grFloat grRadiansToDegrees(const grFloat a);
#endif