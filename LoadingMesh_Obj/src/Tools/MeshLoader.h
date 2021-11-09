#pragma once

namespace dx9
{
	class MeshLoader
	{
	public:

	// Constructors and Destructor:

		MeshLoader();

		~MeshLoader();

	// Functions:

		bool LoadObj(const std::string& filePath);

	private:

	// Variables:

		std::vector<D3DXVECTOR3> m_Vertices;
	//	std::vector<>
		std::vector<D3DXVECTOR3> m_Normals;
	};
}
