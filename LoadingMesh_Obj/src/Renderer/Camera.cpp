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
	}
	
	Camera::~Camera()
	{
	}


// Functions:

	//

// Accessors:

	//

// Modifiers:

	void Camera::SetDevice(IDirect3DDevice9* device)
	{
		m_DevicePtr = device;
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
}