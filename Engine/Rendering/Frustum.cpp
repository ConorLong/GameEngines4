
#include "Frustum.h"
Frustum::Frustum()
{
}
Frustum::~Frustum()
{
}
void Frustum::CalculateFrustum()
{
	//gluPerspective();
	float p[16];
	float m[16];
	float clip[16];
	
	glGetFloatv(GL_PROJECTION_MATRIX, &p[0]);
	glGetFloatv(GL_MODELVIEW_MATRIX, &m[0]);


	clip[0] = m[0] * p[0] + m[1] * p[4] + m[2] * p[8] + m[3] * p[12];
	clip[1] = m[0] * p[1] + m[1] * p[5] + m[2] * p[9] + m[3] * p[13];
	clip[2] = m[0] * p[2] + m[1] * p[6] + m[2] * p[10] + m[3] * p[14];
	clip[3] = m[0] * p[3] + m[1] * p[7] + m[2] * p[11] + m[3] * p[15];

	clip[4] = m[4] * p[0] + m[5] * p[4] + m[6] * p[8] + m[7] * p[12];
	clip[5] = m[4] * p[1] + m[5] * p[5] + m[6] * p[9] + m[7] * p[13];
	clip[6] = m[4] * p[2] + m[5] * p[6] + m[6] * p[10] + m[7] * p[14];
	clip[7] = m[4] * p[3] + m[5] * p[7] + m[6] * p[11] + m[7] * p[15];

	clip[8] = m[8] * p[0] + m[9] * p[4] + m[10] * p[8] + m[11] * p[12];
	clip[9] = m[8] * p[1] + m[9] * p[5] + m[10] * p[9] + m[11] * p[13];
	clip[10] = m[8] * p[2] + m[9] * p[6] + m[10] * p[10] + m[11] * p[14];
	clip[11] = m[8] * p[3] + m[9] * p[7] + m[10] * p[11] + m[11] * p[15];

	clip[12] = m[12] * p[0] + m[13] * p[4] + m[14] * p[8] + m[15] * p[12];
	clip[13] = m[12] * p[1] + m[13] * p[5] + m[14] * p[9] + m[15] * p[13];
	clip[14] = m[12] * p[2] + m[13] * p[6] + m[14] * p[10] + m[15] * p[14];
	clip[15] = m[12] * p[3] + m[13] * p[7] + m[14] * p[11] + m[15] * p[15];

	frustum[RIGHT][A] = clip[ 3] - clip[0];
	frustum[RIGHT][B] = clip[ 7] - clip[4];
	frustum[RIGHT][C] = clip[11] - clip[8];
	frustum[RIGHT][D] = clip[15] - clip[12];

	NormalizePlane(frustum, RIGHT);

	frustum[LEFT][A] = clip[ 3] + clip[1];
	frustum[LEFT][B] = clip[ 7] + clip[5];
	frustum[LEFT][C] = clip[11] + clip[9];
	frustum[LEFT][D] = clip[15] + clip[13];

	NormalizePlane(frustum, LEFT);

	frustum[BOTTOM][A] = clip[ 3] + clip[1];
	frustum[BOTTOM][B] = clip[ 7] + clip[5];
	frustum[BOTTOM][C] = clip[11] + clip[9];
	frustum[BOTTOM][D] = clip[15] + clip[13];

	NormalizePlane(frustum, BOTTOM);

	frustum[TOP][A] = clip[ 3] - clip[1];
	frustum[TOP][B] = clip[ 7] - clip[5];
	frustum[TOP][C] = clip[11] - clip[9];
	frustum[TOP][D] = clip[15] - clip[13];

	NormalizePlane(frustum, TOP);

	frustum[FAR][A] = clip[ 3] - clip[2];
	frustum[FAR][B] = clip[ 7] - clip[6];
	frustum[FAR][C] = clip[11] - clip[10];
	frustum[FAR][D] = clip[15] - clip[14];

	NormalizePlane(frustum, FAR);

	frustum[NEAR][A] = clip[ 3] + clip[2];
	frustum[NEAR][B] = clip[ 7] + clip[6];
	frustum[NEAR][C] = clip[11] + clip[10];
	frustum[NEAR][D] = clip[15] + clip[14];

	NormalizePlane(frustum, NEAR);
}

void Frustum::NormalizePlane(float frus[6][4], int side)
{
	float mag = (float)sqrt(frus[side][A] * frus[side][A] + frus[side][B] * frus[side][B] + frus[side][C] * frus[side][C]);

	frus[side][A] /= mag;
	frus[side][B] /= mag;
	frus[side][C] /= mag;

}

bool Frustum::CheckBox(BoundingBox &box)
{
	for (int i = 0; i < 6; i++) {
		if (frustum[i][A] * box.maxVert.x + frustum[i][B] * box.maxVert.y + frustum[i][C] * box.maxVert.z + frustum[i][D] <= 0) {
			return false;
		}
		 if ((frustum[i][A] * box.minVert.x + frustum[i][B] * box.minVert.y + frustum[i][C] * box.minVert.z + frustum[i][D] <= 0)) {
			return false;
		}
	}
	return true;
}
