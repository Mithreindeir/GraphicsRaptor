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
	m.m[1] = grV4(0, 2.0 / (top - bottom), 0, 1);
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

const GLfloat * grMat4Ptr(const grMat4* m)
{
	return m->n[0];
}

const GLfloat * grVec4Ptr(const grVec4* m)
{
	return m->v;
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

inline grMat4 grMat4Multiply(const grMat4 a, const grMat4 b)
{
	grMat4 c = grMat4Zeroes();
	for (int i = 0; i<4; ++i)
		for (int j = 0; j<4; ++j)
			for (int k = 0; k<4; ++k)
				c.m[j].v[i] += a.m[k].v[i] * b.m[j].v[k];
	return c;
}

inline grMat4 grMat4Translate(const grMat4 m, const grVec4 v)
{
	grMat4 Result = m;
	Result.m[0].v[3] = m.m[0].v[0] * v.x + m.m[0].v[1] * v.y + m.m[0].v[2] * v.z + m.m[0].v[3];
	Result.m[1].v[3] = m.m[1].v[0] * v.x + m.m[1].v[1] * v.y + m.m[1].v[2] * v.z + m.m[1].v[3];
	Result.m[2].v[3] = m.m[2].v[0] * v.x + m.m[2].v[1] * v.y + m.m[2].v[2] * v.z + m.m[2].v[3];
	Result.m[3].v[3] = m.m[3].v[0] * v.x + m.m[3].v[1] * v.y + m.m[3].v[2] * v.z + m.m[3].v[3];
	return Result;
}

inline grMat4 grMat4Scale(grMat4 m, const grVec4 v)
{
	grMat4 Result;
	Result.m[0].v[0] = m.m[0].v[0] * v.v[0];
	Result.m[1].v[0] = m.m[1].v[0] * v.v[0];
	Result.m[2].v[0] = m.m[2].v[0] * v.v[0];
	Result.m[3].v[0] = m.m[3].v[0] * v.v[0];

	Result.m[0].v[1] = m.m[0].v[1] * v.v[1];
	Result.m[1].v[1] = m.m[1].v[1] * v.v[1];
	Result.m[2].v[1] = m.m[2].v[1] * v.v[1];
	Result.m[3].v[1] = m.m[3].v[1] * v.v[1];

	Result.m[0].v[2] = m.m[0].v[2] * v.v[2];
	Result.m[1].v[2] = m.m[1].v[2] * v.v[2];
	Result.m[2].v[2] = m.m[2].v[2] * v.v[2];
	Result.m[3].v[2] = m.m[3].v[2] * v.v[2];

	Result.m[0].v[3] = m.m[0].v[3];
	Result.m[1].v[3] = m.m[1].v[3];
	Result.m[2].v[3] = m.m[2].v[3];
	Result.m[3].v[3] = m.m[3].v[3];

	return Result;
}

inline grMat4 grMat4Rotate(grMat4 m, grVec4 a, const grFloat rotation)
{
	

	grFloat c = cos(rotation);
	grFloat s = sin(rotation);
	grMat4 Result;

	grVec4 axis = grVec4Normalize(a);

	Result.m[0].v[0] = c + (1 - c)      * axis.x     * axis.x;
	Result.m[1].v[0] = (1 - c) * axis.x * axis.y + s * axis.z;
	Result.m[2].v[0] = (1 - c) * axis.x * axis.z - s * axis.y;
	Result.m[3].v[0] = 0;

	Result.m[0].v[1] = (1 - c) * axis.y * axis.x - s * axis.z;
	Result.m[1].v[1] = c + (1 - c) * axis.y * axis.y;
	Result.m[2].v[1] = (1 - c) * axis.y * axis.z + s * axis.x;
	Result.m[3].v[1] = 0;

	Result.m[0].v[2] = (1 - c) * axis.z * axis.x + s * axis.y;
	Result.m[1].v[2] = (1 - c) * axis.z * axis.y - s * axis.x;
	Result.m[2].v[2] = c + (1 - c) * axis.z * axis.z;
	Result.m[3].v[2] = 0;

	Result.m[0].v[3] = 0;
	Result.m[1].v[3] = 0;
	Result.m[2].v[3] = 0;
	Result.m[3].v[3] = 1;
	return grMat4Multiply(Result, m);
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
