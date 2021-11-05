#include "../PrecompiledHeaders/stdafx.h"
#include "Camera.h"

namespace dx9
{
// Constructors and Destructor:

	Camera::Camera()
	{
		m_Position = D3DXVECTOR3( 0.0f, 0.0f, -5.0f );
		m_Target   = D3DXVECTOR3( 0.0f, 0.0f,  1.0f );
		m_Up       = D3DXVECTOR3( 0.0f, 1.0f,  0.0f );

		m_FovY = D3DX_PI / 4.0f;

		// 16/9
		m_AspectRatio = 16.0f / 9.0f;

		m_DevicePtr = nullptr;

		// Rotation
		m_SceneMatrixPtr      = nullptr;
		m_RotationMatrixPtr_X = nullptr;
		m_RotationMatrixPtr_Y = nullptr;
		m_RotationMatrixPtr_Z = nullptr;
		m_RotationAngle_X     = 0.0f;
		m_RotationAngle_Y     = 0.0f;
		m_RotationAngle_Z     = 0.0f;
	}
	
	Camera::~Camera()
	{
	}


// Functions:
	
	void Camera::Update(const float& dt)
	{
		// X Y Z rotations.
	//	D3DXMatrixRotationX(m_RotationMatrixPtr_X, m_RotationAngle_X * dt);
	//	D3DXMatrixRotationY(m_RotationMatrixPtr_Y, m_RotationAngle_Y * dt);
	//	D3DXMatrixRotationZ(m_RotationMatrixPtr_Z, m_RotationAngle_Z * dt);

		// Final SceneMatrix rotation.
	//	*m_SceneMatrixPtr = (*m_RotationMatrixPtr_X) * (*m_RotationMatrixPtr_Y) * (*m_RotationMatrixPtr_Z);
	//	*m_SceneMatrixPtr = (*m_RotationMatrixPtr_X) * (*m_RotationMatrixPtr_Y);
	}
	
	void Camera::Rotate_X(float offsetAngle_X)
	{
		m_RotationAngle_X += offsetAngle_X;

		D3DXMatrixRotationX(m_RotationMatrixPtr_X, m_RotationAngle_X);

		*m_SceneMatrixPtr = (*m_RotationMatrixPtr_X) * (*m_RotationMatrixPtr_Y);
	}

	void Camera::Rotate_Y(float offsetAngle_Y)
	{
		m_RotationAngle_Y += offsetAngle_Y;

		D3DXMatrixRotationY(m_RotationMatrixPtr_Y, m_RotationAngle_Y);

		*m_SceneMatrixPtr = (*m_RotationMatrixPtr_X) * (*m_RotationMatrixPtr_Y);
	}

	void Camera::Rotate_Z(float offsetAngle_Z)
	{
		m_RotationAngle_Z += offsetAngle_Z;
	}


// Accessors:

	//

// Modifiers:

	void Camera::SetDevice(IDirect3DDevice9* device)
	{
		m_DevicePtr = device;
	}

	void Camera::SetMatrices(D3DXMATRIX* sceneMatrix, D3DXMATRIX* rotationMatrix_X, D3DXMATRIX* rotationMatrix_Y, D3DXMATRIX* rotationMatrix_Z)
	{
		m_SceneMatrixPtr      = sceneMatrix;
		m_RotationMatrixPtr_X = rotationMatrix_X;
		m_RotationMatrixPtr_Y = rotationMatrix_Y;
		m_RotationMatrixPtr_Z = rotationMatrix_Z;
	}

	void Camera::SetFovY(float fovY)
	{
		m_FovY = fovY;
	}

	void Camera::SetAspectRatio(float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
	}

	void Camera::SetPosition(D3DXVECTOR3 position, D3DXVECTOR3 target, D3DXVECTOR3 up)
	{
		// View.
		D3DXMatrixLookAtLH(&m_View, &position, &target, &up);
		m_DevicePtr->SetTransform(D3DTS_VIEW, &m_View);

		// Projection matrix.
		D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, m_FovY, m_AspectRatio, 1.0f, 1000.0f);
		m_DevicePtr->SetTransform(D3DTS_PROJECTION, &m_ProjectionMatrix);
		m_DevicePtr->SetRenderState(D3DRS_LIGHTING, false);
		m_DevicePtr->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	}
	
	void Camera::SetRotation_X(float angle_X)
	{
		m_RotationAngle_X = angle_X;
	}
	
	void Camera::SetRotation_Y(float angle_Y)
	{
		m_RotationAngle_Y = angle_Y;
	}
	
	void Camera::SetRotation_Z(float angle_Z)
	{
		m_RotationAngle_Z = angle_Z;
	}
}