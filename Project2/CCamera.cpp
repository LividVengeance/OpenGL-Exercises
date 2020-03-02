#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace glm;

class CCamera
{
public:
	CCamera();
	~CCamera();

	mat4 Translation(vec3 objPosition);
	mat4 Rotation(vec3 rotationAxis, float angle);
	mat4 Scale(vec3 objScale);

private:

};

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
}

mat4 CCamera::Translation(vec3 objPosition)
{
	/// Creates Translation Matrax of Objects Postion
	mat4 translationMatrix = translate(mat4(), objPosition);
	return(translationMatrix);
}

mat4 CCamera::Rotation(vec3 rotationAxis, float angle)
{
	/// Creates Rotation Matrix Given Angle and Rotation Axis
	mat4 rotation = rotate(mat4(), radians(angle), rotationAxis);
	return(rotation);
}

mat4 CCamera::Scale(vec3 objScale)
{
	/// Create Scale Matrix of Object
	mat4 scaleMatrix = scale(mat4(), objScale * 1000.0f);
	return(scaleMatrix);
}