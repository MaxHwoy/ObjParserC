#include <pch.hpp>
#include <MTLLoader/MTLLoader.hpp>



namespace ObjParserC
{
	MTLLoader::MTLLoader()
	{
	}

	MTLLoader::MTLLoader(const MTLLoader& loader)
	{
		this->_materials = loader._materials;
	}

	MTLLoader& MTLLoader::operator =(const MTLLoader& loader)
	{
		if (this != &loader)
		{

			this->_materials = loader._materials;

		}

		return *this;
	}

	std::vector<MTLMaterial>* MTLLoader::Materials()
	{
		return &this->_materials;
	}

	ColorF MTLLoader::ReadColorF(LineReader* lr)
	{
		auto r = lr->IsOutOfBounds() ? 0.0f : lr->ReadSingle();
		auto g = lr->IsOutOfBounds() ? r : lr->ReadSingle();
		auto b = lr->IsOutOfBounds() ? r : lr->ReadSingle();
		return ColorF(r, g, b, 1.0f);
	}

	void MTLLoader::ParseMTLReflection(MTLMaterial* material, LineReader* lr)
	{
		auto type = lr->ReadString();
		type = ObjParserC::Utils::StringExtensions::ToLower(type);

		if (type == L"sphere")
		{

			material->ReflSphere = new MTLTexture();
			material->ReflSphere->Parse(lr);
			return;

		}
		if (type == L"cube_top")
		{

			material->ReflCubeTop = new MTLTexture();
			material->ReflCubeTop->Parse(lr);
			return;

		}
		if (type == L"cube_bottom")
		{

			material->ReflCubeBottom = new MTLTexture();
			material->ReflCubeBottom->Parse(lr);
			return;

		}
		if (type == L"cube_front")
		{

			material->ReflCubeFront = new MTLTexture();
			material->ReflCubeFront->Parse(lr);
			return;

		}
		if (type == L"cube_back")
		{

			material->ReflCubeBack = new MTLTexture();
			material->ReflCubeBack->Parse(lr);
			return;

		}
		if (type == L"cube_left")
		{

			material->ReflCubeLeft = new MTLTexture();
			material->ReflCubeLeft->Parse(lr);
			return;

		}
		if (type == L"cube_right")
		{

			material->ReflCubeRight = new MTLTexture();
			material->ReflCubeRight->Parse(lr);
			return;

		}
	}

	void MTLLoader::Load(LineReader* lr)
	{
		// First, find very first material because all other arguments are
		// irrelevant without a material assigned to them
		while (lr->ReadNext())
		{

			if (ObjParserC::Utils::StringExtensions::IsWhiteSpace(lr->Current())) continue;
			if (ObjParserC::Utils::StringExtensions::StartsWith(lr->Current(), L"#")) continue;
			auto arg = ObjParserC::Utils::StringExtensions::ToLower(lr->ReadString());
			if (arg == L"newmtl") break;

		}

		if (lr->EndOfStream()) return;
		
		this->_materials.push_back(MTLMaterial(lr->ReadString()));
		MTLMaterial* currentMTL = &(this->_materials.at(0));

		while (lr->ReadNext())
		{

			if (ObjParserC::Utils::StringExtensions::IsWhiteSpace(lr->Current())) continue;
			if (ObjParserC::Utils::StringExtensions::StartsWith(lr->Current(), L"#")) continue;
			auto arg = ObjParserC::Utils::StringExtensions::ToLower(lr->ReadString());

			if (arg == L"newmtl")
			{

				auto name = lr->ReadString();
				auto count = this->_materials.size();
				this->_materials.push_back(MTLMaterial(name));
				currentMTL = &(this->_materials.at(count));
				continue;

			}
			if (arg == L"kd")
			{

				currentMTL->Kd = ncolor(this->ReadColorF(lr));
				continue;

			}
			if (arg == L"ka")
			{

				currentMTL->Ka = ncolor(this->ReadColorF(lr));
				continue;

			}
			if (arg == L"ks")
			{

				currentMTL->Ks = ncolor(this->ReadColorF(lr));
				continue;

			}
			if (arg == L"tf")
			{

				currentMTL->Tf = ncolor(this->ReadColorF(lr));
				continue;

			}
			if (arg == L"d")
			{

				auto inter = lr->ReadString();
				auto lower = ObjParserC::Utils::StringExtensions::ToLower(inter);

				if (lower != L"-halo")
				{

					currentMTL->D = ObjParserC::Utils::Formatter::ParseSingle(inter);
					continue;

				}

				currentMTL->Halo = nbool(true);
				currentMTL->D = lr->ReadSingle();
				continue;

			}
			if (arg == L"tr")
			{

				currentMTL->D = 1.0f - lr->ReadSingle();
				continue;

			}
			if (arg == L"ns")
			{

				currentMTL->Ns = lr->ReadSingle();
				continue;

			}
			if (arg == L"sharpness")
			{

				currentMTL->Sharpness = lr->ReadSingle();
				continue;

			}
			if (arg == L"ni")
			{

				currentMTL->Ni = lr->ReadSingle();
				continue;

			}
			if (arg == L"illum")
			{

				currentMTL->Illuminance = (IlluminanceType)lr->ReadInt32();
				continue;

			}
			if (arg == L"map_ka")
			{

				currentMTL->MapKa = new MTLTexture();
				currentMTL->MapKa->Parse(lr);
				continue;

			}
			if (arg == L"map_kd")
			{

				currentMTL->MapKd = new MTLTexture();
				currentMTL->MapKd->Parse(lr);
				continue;

			}
			if (arg == L"map_ks")
			{

				currentMTL->MapKs = new MTLTexture();
				currentMTL->MapKs->Parse(lr);
				continue;

			}
			if (arg == L"map_ns")
			{

				currentMTL->MapNs = new MTLTexture();
				currentMTL->MapNs->Parse(lr);
				continue;

			}
			if (arg == L"map_d")
			{

				currentMTL->MapD = new MTLTexture();
				currentMTL->MapD->Parse(lr);
				continue;

			}
			if (arg == L"decal")
			{

				currentMTL->Decal = new MTLTexture();
				currentMTL->Decal->Parse(lr);
				continue;

			}
			if (arg == L"map_aat")
			{

				auto val = ObjParserC::Utils::StringExtensions::ToLower(lr->ReadString());
				currentMTL->MapAat = nbool(val == L"on");
				continue;

			}
			if (arg == L"disp")
			{

				currentMTL->Disp = new MTLTexture();
				currentMTL->Disp->Parse(lr);
				continue;

			}
			if (arg == L"bump" || arg == L"map_bump")
			{

				currentMTL->MapBump = new MTLTexture();
				currentMTL->MapBump->Parse(lr);
				continue;

			}
			if (arg == L"refl")
			{

				this->ParseMTLReflection(currentMTL, lr);
				continue;

			}

		}
	}

	void MTLLoader::Load(const std::wstring& file)
	{
		if (!std::filesystem::exists(file)) return;
		auto lr = LineReader(file);
		this->Load(&lr);
	}
}
