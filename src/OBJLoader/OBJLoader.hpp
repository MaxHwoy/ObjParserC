#pragma once



namespace ObjParserC
{
	class ObjLoader
	{
	private:
		MeshCollection _collection;
		std::wstring _name;
		std::wstring _filename;

		void LoadMTLLib(const std::wstring& filename, std::unordered_map<std::wstring, MTLMaterial>* map);
		void LoadMTLLib(LineReader* lr, std::unordered_map<std::wstring, MTLMaterial>* map);

	public:
		ObjLoader();
		ObjLoader(const ObjLoader& loader);
		ObjLoader& operator =(const ObjLoader& loader);

		MeshCollection* Collection();
		void Load(LineReader* objLR, LineReader* mtlLR = nullptr);
		void Load(const std::wstring& objFile, const std::wstring& mtlFile = WStringEmpty);
	};
}
