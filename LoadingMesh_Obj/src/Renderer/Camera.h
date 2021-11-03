#pragma once

namespace dx9
{
	class Camera
	{
	public:

	// Constructors and Destructor:

		Camera();

		virtual ~Camera();

	// Functions:

		//

	// Accessors:

		//

	// Modifiers:

		void SetDevice(IDirect3DDevice9* device);

		void SetFovY(float fovY);

		void SetAspectRatio(float aspectRatio);

		void SetPosition(D3DXVECTOR3 position, D3DXVECTOR3 target, D3DXVECTOR3 up);

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
	};
}
