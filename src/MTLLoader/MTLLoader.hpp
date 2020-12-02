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
		std::vector<MTLMaterial>& Materials();
		void Load(LineReader* lr);
		void Load(const std::wstring& file);
	};
}
