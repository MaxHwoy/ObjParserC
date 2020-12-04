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

	MTLTexture::MTLTexture()
	{
		this->BlendU = nbool();
		this->BlendV = nbool();
		this->Bm = nfloat();
		this->Boost = nfloat();
		this->CC = nbool();
		this->Clamp = nbool();
		this->Filename = WStringEmpty;
		this->Imfchan = ImfchanType::Invalid;
		this->MMBase = nfloat();
		this->MMGain = nfloat();
		this->O = nvec();
		this->S = nvec();
		this->T = nvec();
		this->TexRes = nint();
	}

	MTLTexture::MTLTexture(const MTLTexture& texture)
	{
		this->BlendU = texture.BlendU;
		this->BlendV = texture.BlendV;
		this->Bm = texture.Bm;
		this->Boost = texture.Boost;
		this->CC = texture.CC;
		this->Clamp = texture.Clamp;
		this->Filename = texture.Filename;
		this->Imfchan = texture.Imfchan;
		this->MMBase = texture.MMBase;
		this->MMGain = texture.MMGain;
		this->O = texture.O;
		this->S = texture.S;
		this->T = texture.T;
		this->TexRes = texture.TexRes;
	}

	MTLTexture::MTLTexture(MTLTexture* texture)
	{
		if (this == texture) return;

		this->BlendU = texture->BlendU;
		this->BlendV = texture->BlendV;
		this->Bm = texture->Bm;
		this->Boost = texture->Boost;
		this->CC = texture->CC;
		this->Clamp = texture->Clamp;
		this->Filename = texture->Filename;
		this->Imfchan = texture->Imfchan;
		this->MMBase = texture->MMBase;
		this->MMGain = texture->MMGain;
		this->O = texture->O;
		this->S = texture->S;
		this->T = texture->T;
		this->TexRes = texture->TexRes;
	}

	MTLTexture& MTLTexture::operator =(const MTLTexture& texture)
	{
		if (this != &texture)
		{

			this->BlendU = texture.BlendU;
			this->BlendV = texture.BlendV;
			this->Bm = texture.Bm;
			this->Boost = texture.Boost;
			this->CC = texture.CC;
			this->Clamp = texture.Clamp;
			this->Filename = texture.Filename;
			this->Imfchan = texture.Imfchan;
			this->MMBase = texture.MMBase;
			this->MMGain = texture.MMGain;
			this->O = texture.O;
			this->S = texture.S;
			this->T = texture.T;
			this->TexRes = texture.TexRes;

		}

		return *this;
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
