#pragma once



namespace ObjParserC
{
	class MTLLoader
	{
	private:
		std::vector<MTLMaterial> _materials;
		ColorF ReadColorF(LineReader* lr);
		void ParseMTLReflection(MTLMaterial* material, LineReader* lr);

	public:
		MTLLoader();
		MTLLoader(const MTLLoader& loader);
		MTLLoader& operator =(const MTLLoader& loader);

		std::vector<MTLMaterial>* Materials();
		void Load(LineReader* lr);
		void Load(const std::wstring& file);
	};
}
