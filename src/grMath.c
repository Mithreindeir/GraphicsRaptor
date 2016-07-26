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

inline grMat4 grOrtho(grFloat right, grFloat left, grFloat top, grFloat bottom)
{
	grMat4 m;
	m.m[0] = grV4(2.0 / (left - right), 0, 0, -1);
	m.m[1] = grV4(0, 2.0 / (bottom - top), 0, 1);
	m.m[2] = grV4(0, 0, -1, 0.0);
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
	return m.n;
}

GLfloat * grVec4Ptr(grVec4 m)
{
	return m.v;
}

inline grMat4 grMat4Ones()
{
	grMat4 m;
	m.m[0] = grV4(1.0, 1.0, 1.0, 1.0);
	m.m[1] = grV4(1.0, 1.0, 1.0, 1.0);
	m.m[2] = grV4(1.0, 1.0, 1.0, 1.0);
	m.m[3] = grV4(1.0, 1.0, 1.0, 1.0);
	return m;
}

inline grMat4 grMat4Zeroes()
{
	grMat4 m;
	m.m[0] = grV4(0.0, 0.0, 0.0, 0.0);
	m.m[1] = grV4(0.0, 0.0, 0.0, 0.0);
	m.m[2] = grV4(0.0, 0.0, 0.0, 0.0);
	m.m[3] = grV4(0.0, 0.0, 0.0, 0.0);
	return m;
}

inline grMat4 grMat4Identity()
{
	grMat4 m;
	m.m[0] = grV4(1.0, 0.0, 0.0, 0.0);
	m.m[1] = grV4(0.0, 1.0, 0.0, 0.0);
	m.m[2] = grV4(0.0, 0.0, 1.0, 0.0);
	m.m[3] = grV4(0.0, 0.0, 0.0, 1.0);
	return m;
}

inline grMat4 grMat4Translate(grMat4 mat, const grVec4 v)
{
	mat.m[0].w += v.x;
	mat.m[1].w += v.y;
	mat.m[2].w += v.z;

	return mat;
}

inline grMat4 grMat4Scale(grMat4 m, const grVec4 v)
{
	m.m[0].x *= v.x;
	m.m[1].y *= v.y;
	m.m[2].z *= v.z;
	return m;
}

inline grMat4 grMat4Rotate(grMat4 m, grVec4 a, const grFloat rotation)
{
	a = grVec4Normalize(a);

	grFloat c = cos(rotation);
	grFloat s = sin(rotation);
	grVec4 temp = grVec4Scale(a, (1.0 - c));
	grVec4 m0;
	m0.x = c + temp.x * a.x;
	m0.y = 0 + temp.x * a.y + s * a.z;
	m0.z = 0 + temp.x * a.z - s * a.y;
	grVec4 m1;
	m1.x = 0 + temp.y * a.x - s * a.z;
	m1.y = c + temp.y * a.y;
	m1.z = 0 + temp.y * a.z + s * a.x;
	grVec4 m2;
	m2.x = 0 + temp.z * a.x + s * a.y;
	m2.y = 0 + temp.z * a.y - s * a.x;
	m2.z = c + temp.z * a.z;

	grMat4 r = grMat4Zeroes();
	r.m[0] = grVec4Add(grVec4Add(grVec4Scale(m.m[0], m0.x), grVec4Scale(m.m[1], m0.y)), grVec4Scale(m.m[2], m0.z));
	r.m[1] = grVec4Add(grVec4Add(grVec4Scale(m.m[0], m1.x), grVec4Scale(m.m[1], m1.y)), grVec4Scale(m.m[2], m1.z));
	r.m[2] = grVec4Add(grVec4Add(grVec4Scale(m.m[0], m2.x), grVec4Scale(m.m[1], m2.y)), grVec4Scale(m.m[2], m2.z));

	return r;
}

inline grFloat grDegreesToRadian(const grFloat a)
{
	return a * DEGTORAD;
}

inline grFloat grRadiansToDegrees(const grFloat a)
{
	return a / DEGTORAD;
}

inline grVec2 grV2(const grFloat x, const grFloat y)
{
	grVec2 v = { x, y };
	return v;
}

inline grVec2 grVec2Add(const grVec2 a, const grVec2 b)
{
	return grV2(a.x + b.x, a.y + b.y);
}

inline grVec2 grVec2Sub(const grVec2 a, const grVec2 b)
{
	return grV2(a.x - b.x, a.y - b.y);
}

inline grVec2 grVec2Mult(const grVec2 a, const grVec2 b)
{
	return grV2(a.x * b.x, a.y * b.y);
}

inline grVec2 grVec2Div(const grVec2 a, const grVec2 b)
{
	return grV2(a.x / b.x, a.y / b.y);
}

inline grVec2 grVec2Scale(const grVec2 a, const grFloat b)
{
	return grV2(a.x * b, a.y * b );
}

inline grVec2 grVec2Normalize(const grVec2 a)
{
	grFloat len = grVec2Length(a);
	return grVec2Scale(a, 1.0 / len);
}

inline grFloat grVec2Length(const grVec2 a)
{
	return sqrt(a.x + a.y);
}

inline grFloat grVec2LengthSqr(const grVec2 a)
{
	return a.x + a.y;
}
