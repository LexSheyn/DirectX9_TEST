#pragma once

#include "GraphicDevice.h"

namespace dx9
{
	class Camera
	{
	public:

	// Constructors and Destructor:

		Camera();

		virtual ~Camera();

	// Functions:

		void Update(const float& dt);

		void Rotate_X(float offsetAngle_X);

		void Rotate_Y(float offsetAngle_Y);

		void Rotate_Z(float offsetAngle_Z);

	// Accessors:

		//

	// Modifiers:

		void SetDevice(IDirect3DDevice9* device);

		void SetMatrices(D3DXMATRIX* sceneMatrix, D3DXMATRIX* rotationMatrix_X, D3DXMATRIX* rotationMatrix_Y, D3DXMATRIX* rotationMatrix_Z);

		void SetFovY(float fovY);

		void SetAspectRatio(float aspectRatio);

		void SetPosition(D3DXVECTOR3 position, D3DXVECTOR3 target, D3DXVECTOR3 up);

		void SetRotation_X(float angle_X);

		void SetRotation_Y(float angle_Y);		
		
		void SetRotation_Z(float angle_Z);

	private:

	// Variables:

		D3DXMATRIX  m_View;
		D3DXMATRIX  m_ProjectionMatrix;

		D3DXVECTOR3 m_Position;
		D3DXVECTOR3 m_Target;
		D3DXVECTOR3 m_Up;		

		// Field of view Y
		float m_FovY;
		float m_AspectRatio;

		IDirect3DDevice9* m_DevicePtr;

		// Rotation
		D3DXMATRIX* m_SceneMatrixPtr;
		D3DXMATRIX* m_RotationMatrixPtr_X;
		D3DXMATRIX* m_RotationMatrixPtr_Y;
		D3DXMATRIX* m_RotationMatrixPtr_Z;
		float m_RotationAngle_X;
		float m_RotationAngle_Y;
		float m_RotationAngle_Z;
	};
}
