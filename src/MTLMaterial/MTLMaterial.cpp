#include <pch.hpp>
#include <MTLMaterial/MTLMaterial.hpp>



namespace ObjParserC
{
	std::wstring MTLMaterial::Name()
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
