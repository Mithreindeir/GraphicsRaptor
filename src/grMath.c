#include "../include/grMath.h"

inline grVec4 grV4(const grFloat x, const grFloat y, const grFloat z, const grFloat w)
{
	grVec4 v = { x, y, z, w };
	return v;
}

inline grVec4 grVec4Add(const grVec4 a, const grVec4 b)
{
	return grV4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

inline grVec4 grVec4Sub(const grVec4 a, const grVec4 b)
{
	return grV4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

inline grVec4 grVec4Mult(const grVec4 a, const grVec4 b)
{
	return grV4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

inline grVec4 grVec4Div(const grVec4 a, const grVec4 b)
{
	return grV4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

inline grVec4 grVec4Scale(const grVec4 a, const grFloat b)
{
	return grV4(a.x * b, a.y * b, a.z * b, a.w * b);
}

inline grVec4 grVec4Normalize(const grVec4 a)
{
	grFloat l = grVec4Length(a);
	return grV4(a.x/l, a.y/l, a.z/l, a.w/l);
}

inline grFloat grVec4Length(const grVec4 a)
{
	return sqrt(a.x + a.y + a.z + a.w);
}

inline grFloat grVec4LengthSqr(const grVec4 a)
{
	return (a.x + a.y + a.z + a.w);
}

inline grVec4 grVec4Translate(const grVec4 a, const grMat4 b)
{
	grVec4 v;
	v.x = a.x * b.m[0].x + a.y * b.m[0].y + a.z * b.m[0].z + a.w * b.m[0].w;
	v.y = a.x * b.m[1].x + a.y * b.m[1].y + a.z * b.m[1].z + a.w * b.m[1].w;
	v.z = a.x * b.m[2].x + a.y * b.m[2].y + a.z * b.m[2].z + a.w * b.m[2].w;
	v.w = a.x * b.m[3].x + a.y * b.m[3].y + a.z * b.m[3].z + a.w * b.m[3].w;
	return v;
}

inline grMat4 grM4(const grVec4 m, const grVec4 m2, const grVec4 m3, const grVec4 m4)
{
	grMat4 mt;
	mt.m[0] = m;
	mt.m[1] = m2;
	mt.m[2] = m3;
	mt.m[3] = m4;
	return mt;
}

inline grMat4 grOrtho(grFloat right, grFloat left, grFloat top, grFloat bottom, grFloat front, grFloat back)
{
	grMat4 m;
	m.m[0] = grV4(1.0 / (left - right), 0, 0, 0);
	m.m[1] = grV4(0, 1.0 / (bottom - top), 0, 0);
	m.m[2] = grV4(0, 0, -2.0 / (back - front), -(back + front) / (back - front));
	m.m[3] = grV4(0, 0, 0, 1.0);
	return m;
}

inline grMat4 grPerspective(grFloat fovy, grFloat aspect, grFloat front, grFloat back)
{
	grMat4 m;
	m.m[0] = grV4(atan(aspect/2.0), 0, 0, 0);
	m.m[1] = grV4(0, atan(fovy/2.0), 0, 0);
	m.m[2] = grV4(0, 0, -(back + front)/(back-front), -2.0*(front*back)/(back-front));
	m.m[3] = grV4(0, 0, -1.0, 0);
	return m;
}

GLfloat * grMat4Ptr(grMat4 m)
{
	return m.m[0].v;
}