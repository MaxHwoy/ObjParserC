#include <pch.hpp>
#include <MTLMaterial/MTLMaterial.hpp>



namespace ObjParserC
{
	MTLMaterial::MTLMaterial() : MTLMaterial(WStringEmpty)
	{
	}

	MTLMaterial::MTLMaterial(const std::wstring& name)
	{
		this->_name = name;
		this->D = nfloat();
		this->Halo = nbool();
		this->Illuminance = IlluminanceType::Invalid;
		this->Ka = ncolor();
		this->Kd = ncolor();
		this->Ks = ncolor();
		this->MapAat = nbool();
		this->Ni = nfloat();
		this->Ns = nfloat();
		this->Sharpness = nfloat();
		this->Tf = ncolor();
		
		this->MapKa = nullptr;
		this->MapKd = nullptr;
		this->MapKs = nullptr;
		this->MapNs = nullptr;
		this->Decal = nullptr;
		this->MapD = nullptr;
		this->Disp = nullptr;

		this->MapBump = nullptr;
		this->ReflSphere = nullptr;
		this->ReflCubeTop = nullptr;
		this->ReflCubeBottom = nullptr;
		this->ReflCubeFront = nullptr;
		this->ReflCubeBack = nullptr;
		this->ReflCubeLeft = nullptr;
		this->ReflCubeRight = nullptr;
	}

	MTLMaterial::MTLMaterial(const MTLMaterial& material)
	{
		this->_name = material._name;
		this->D = material.D;
		this->Halo = material.Halo;
		this->Illuminance = material.Illuminance;
		this->Ka = material.Ka;
		this->Kd = material.Kd;
		this->Ks = material.Ks;
		this->MapAat = material.MapAat;
		this->Ni = material.Ni;
		this->Ns = material.Ns;
		this->Sharpness = material.Sharpness;
		this->Tf = material.Tf;

		this->MapKa = material.MapKa == nullptr ? nullptr : new MTLTexture(material.MapKa);
		this->MapKd = material.MapKd == nullptr ? nullptr : new MTLTexture(material.MapKd);
		this->MapKs = material.MapKs == nullptr ? nullptr : new MTLTexture(material.MapKs);
		this->MapNs = material.MapNs == nullptr ? nullptr : new MTLTexture(material.MapNs);
		this->Decal = material.Decal == nullptr ? nullptr : new MTLTexture(material.Decal);
		this->MapD = material.MapD == nullptr ? nullptr : new MTLTexture(material.MapD);
		this->Disp = material.Disp == nullptr ? nullptr : new MTLTexture(material.Disp);
		this->MapBump = material.MapBump == nullptr ? nullptr : new MTLTexture(material.MapBump);

		this->ReflSphere = material.ReflSphere == nullptr ? nullptr : new MTLTexture(material.ReflSphere);
		this->ReflCubeTop = material.ReflCubeTop == nullptr ? nullptr : new MTLTexture(material.ReflCubeTop);
		this->ReflCubeBottom = material.ReflCubeBottom == nullptr ? nullptr : new MTLTexture(material.ReflCubeBottom);
		this->ReflCubeFront = material.ReflCubeFront == nullptr ? nullptr : new MTLTexture(material.ReflCubeFront);
		this->ReflCubeBack = material.ReflCubeBack == nullptr ? nullptr : new MTLTexture(material.ReflCubeBack);
		this->ReflCubeLeft = material.ReflCubeLeft == nullptr ? nullptr : new MTLTexture(material.ReflCubeLeft);
		this->ReflCubeRight = material.ReflCubeRight == nullptr ? nullptr : new MTLTexture(material.ReflCubeRight);
	}

	MTLMaterial& MTLMaterial::operator =(const MTLMaterial& material)
	{
		if (this != &material)
		{

			this->_name = material._name;
			this->D = material.D;
			this->Halo = material.Halo;
			this->Illuminance = material.Illuminance;
			this->Ka = material.Ka;
			this->Kd = material.Kd;
			this->Ks = material.Ks;
			this->MapAat = material.MapAat;
			this->Ni = material.Ni;
			this->Ns = material.Ns;
			this->Sharpness = material.Sharpness;
			this->Tf = material.Tf;

			this->MapKa = material.MapKa == nullptr ? nullptr : new MTLTexture(material.MapKa);
			this->MapKd = material.MapKd == nullptr ? nullptr : new MTLTexture(material.MapKd);
			this->MapKs = material.MapKs == nullptr ? nullptr : new MTLTexture(material.MapKs);
			this->MapNs = material.MapNs == nullptr ? nullptr : new MTLTexture(material.MapNs);
			this->Decal = material.Decal == nullptr ? nullptr : new MTLTexture(material.Decal);
			this->MapD = material.MapD == nullptr ? nullptr : new MTLTexture(material.MapD);
			this->Disp = material.Disp == nullptr ? nullptr : new MTLTexture(material.Disp);
			this->MapBump = material.MapBump == nullptr ? nullptr : new MTLTexture(material.MapBump);

			this->ReflSphere = material.ReflSphere == nullptr ? nullptr : new MTLTexture(material.ReflSphere);
			this->ReflCubeTop = material.ReflCubeTop == nullptr ? nullptr : new MTLTexture(material.ReflCubeTop);
			this->ReflCubeBottom = material.ReflCubeBottom == nullptr ? nullptr : new MTLTexture(material.ReflCubeBottom);
			this->ReflCubeFront = material.ReflCubeFront == nullptr ? nullptr : new MTLTexture(material.ReflCubeFront);
			this->ReflCubeBack = material.ReflCubeBack == nullptr ? nullptr : new MTLTexture(material.ReflCubeBack);
			this->ReflCubeLeft = material.ReflCubeLeft == nullptr ? nullptr : new MTLTexture(material.ReflCubeLeft);
			this->ReflCubeRight = material.ReflCubeRight == nullptr ? nullptr : new MTLTexture(material.ReflCubeRight);

		}

		return *this;
	}

	std::wstring& MTLMaterial::Name()
	{
		return this->_name;
	}

	std::wstring MTLMaterial::ToString()
	{
		return this->_name.length() == 0 ? L"No Name" : this->_name;
	}

	MTLMaterial::~MTLMaterial()
	{
		if (this->MapKa) delete this->MapKa;
		if (this->MapKd) delete this->MapKd;
		if (this->MapKs) delete this->MapKs;
		if (this->MapNs) delete this->MapNs;
		if (this->Decal) delete this->Decal;
		if (this->MapD) delete this->MapD;
		if (this->Disp) delete this->Disp;
		if (this->MapBump) delete this->MapBump;

		if (this->ReflSphere) delete this->ReflSphere;
		if (this->ReflCubeTop) delete this->ReflCubeTop;
		if (this->ReflCubeBottom) delete this->ReflCubeBottom;
		if (this->ReflCubeFront) delete this->ReflCubeFront;
		if (this->ReflCubeBack) delete this->ReflCubeBack;
		if (this->ReflCubeLeft) delete this->ReflCubeLeft;
		if (this->ReflCubeRight) delete this->ReflCubeRight;
	}
}
