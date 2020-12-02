#include <pch.hpp>
#include <MTLTexture/MTLTexture.hpp>



namespace ObjParserC
{
	std::unordered_map<std::wstring, ImfchanType> MTLTexture::_imfchans =
	{
		{ L"R", ImfchanType::R },
		{ L"G", ImfchanType::G },
		{ L"B", ImfchanType::B },
		{ L"M", ImfchanType::M },
		{ L"L", ImfchanType::L },
		{ L"Z", ImfchanType::Z },
	};

	std::wstring MTLTexture::ToString()
	{
		return this->Filename.length() == 0 ? L"No Texture" : this->Filename;
	}

	void MTLTexture::Parse(LineReader* lr)
	{
		const auto on = L"on";

		while (!lr->IsOutOfBounds())
		{

			auto value = lr->ReadString();
			auto arg = ObjParserC::Utils::StringExtensions::ToLower(value);

			if (arg == L"-blendu")
			{

				this->BlendU = nbool(lr->ReadString() == on);
				continue;

			}
			if (arg == L"-blendv")
			{

				this->BlendV = nbool(lr->ReadString() == on);
				continue;

			}
			if (arg == L"-bm")
			{

				this->Bm = nfloat(lr->ReadSingle());
				continue;

			}
			if (arg == L"-boost")
			{

				this->Boost = nfloat(lr->ReadSingle());
				continue;

			}
			if (arg == L"-cc")
			{

				this->CC = nbool(lr->ReadString() == on);
				continue;

			}
			if (arg == L"-clamp")
			{

				this->Clamp = nbool(lr->ReadString() == on);
				continue;

			}
			if (arg == L"-imfchan")
			{

				const auto itr = MTLTexture::_imfchans.find(lr->ReadString());
				if (itr != MTLTexture::_imfchans.end()) this->Imfchan = itr->second;

			}
			if (arg == L"-mm")
			{

				this->MMBase = nfloat(lr->ReadSingle());
				this->MMGain = nfloat(lr->ReadSingle());
				continue;

			}
			if (arg == L"-o")
			{

				this->O = nvec(lr->ReadVector3());
				continue;

			}
			if (arg == L"-s")
			{

				this->S = nvec(lr->ReadVector3());
				continue;

			}
			if (arg == L"-t")
			{

				this->T = nvec(lr->ReadVector3());
				continue;

			}
			if (arg == L"-texres")
			{

				this->TexRes = nint(lr->ReadInt32());
				continue;

			}

			this->Filename = value;

		}
	}
}
