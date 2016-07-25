#ifndef HEADER_GRMATH
#define HEADER_GRMATH
#include <math.h>
#include "graphicsraptor.h"

typedef float grFloat;

typedef struct grVec4
{
	union
	{
		struct { grFloat x, y, z, w; };
		struct { grFloat r, g, b, a; };
		grFloat v[4];
	};
} grVec4;

typedef struct grMat4
{
	grVec4 m[4];
} grMat4;

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
extern inline grMat4 grOrtho(grFloat right,grFloat left,grFloat top,grFloat bottom, grFloat front, grFloat back);
extern inline grMat4 grPerspective(grFloat fovy, grFloat aspect, grFloat front, grFloat back);
GLfloat* grMat4Ptr(grMat4 m);

#endif