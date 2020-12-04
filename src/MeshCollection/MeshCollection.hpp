#pragma once



namespace ObjParserC
{
	class MeshCollection
	{
	private:
		std::unordered_map<std::wstring, OBJMesh> _meshes;
		std::unordered_map<std::wstring, MTLMaterial> _materials;

	public:
		std::wstring Name;
		std::wstring Filename;

		MeshCollection();
		MeshCollection(const MeshCollection& collection);
		MeshCollection& operator =(const MeshCollection& collection);
		std::unordered_map<std::wstring, OBJMesh>& Meshes();
		std::unordered_map<std::wstring, MTLMaterial>& Materials();
	};
}
