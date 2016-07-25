#ifndef HEADER_GRMATH
#define HEADER_GRMATH
#include <math.h>
#include "graphicsraptor.h"

typedef struct grVec4
{
	union
	{
		struct { double x, y, z, w; };
		struct { double r, g, b, a; };
	};
} grVec4;

typedef struct grMat4
{
	grVec4 m[4];
} grMat4;

extern inline grVec4 grV4(const double x, const double y, const double z, const double w);
extern inline grVec4 grVec4Add(const grVec4 a, const grVec4 b);
extern inline grVec4 grVec4Sub(const grVec4 a, const grVec4 b);
extern inline grVec4 grVec4Mult(const grVec4 a, const grVec4 b);
extern inline grVec4 grVec4Div(const grVec4 a, const grVec4 b);
extern inline grVec4 grVec4Scale(const grVec4 a, const double b);
extern inline grVec4 grVec4Normalize(const grVec4 a);
extern inline double grVec4Length(const grVec4 a);
extern inline double grVec4LengthSqr(const grVec4 a);
extern inline grVec4 grVec4Translate(const grVec4 a, const grMat4 b);
extern inline grMat4 grM4(const grVec4 m, const grVec4 m2, const grVec4 m3, const grVec4 m4);
extern inline grMat4 grOrtho(double right,double left,double top,double bottom, double front, double back);
extern inline grMat4 grPerspective(double fovy, double aspect, double front, double back);

#endif