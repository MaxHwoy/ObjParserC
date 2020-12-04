#include <pch.hpp>
#include <OBJLoader/OBJLoader.hpp>



namespace ObjParserC
{
	ObjLoader::ObjLoader()
	{
		this->_name = WStringEmpty;
		this->_filename = WStringEmpty;
	}

	ObjLoader::ObjLoader(const ObjLoader& loader)
	{
		this->_name = loader._name;
		this->_filename = loader._filename;
		this->_collection = loader._collection;
	}

	ObjLoader& ObjLoader::operator =(const ObjLoader& loader)
	{
		if (this != &loader)
		{

			this->_name = loader._name;
			this->_filename = loader._filename;
			this->_collection = loader._collection;

		}

		return *this;
	}

	MeshCollection* ObjLoader::Collection()
	{
		return &this->_collection;
	}

	void ObjLoader::LoadMTLLib(const std::wstring& filename, std::unordered_map<std::wstring, MTLMaterial>* map)
	{
		std::wstring path;

		if (this->_filename == WStringEmpty)
		{
		
			path = filename;
		
		}
		else
		{

			path = std::filesystem::path(this->_filename).parent_path() / filename;

		}

		auto loader = MTLLoader();
		loader.Load(path);
		auto materials = loader.Materials();

		for (uint32_t i = 0; i < materials->size(); ++i)
		{

			auto& mat = materials->at(i);
			map->insert(std::pair<std::wstring, MTLMaterial>(mat.Name(), mat));

		}
	}

	void ObjLoader::LoadMTLLib(LineReader* lr, std::unordered_map<std::wstring, MTLMaterial>* map)
	{
		auto loader = MTLLoader();
		loader.Load(lr);
		auto materials = loader.Materials();

		for (uint32_t i = 0; i < materials->size(); ++i)
		{

			auto& mat = materials->at(i);
			map->insert(std::pair<std::wstring, MTLMaterial>(mat.Name(), mat));

		}
	}

	void ObjLoader::Load(LineReader* objLR, LineReader* mtlLR)
	{
		auto vertices = std::vector<Vector3>();
		auto normals = std::vector<Vector3>();
		auto uvs = std::vector<Vector2>();
		
		auto& meshNameToMesh = this->_collection.Meshes();
		auto& matNameToMat = this->_collection.Materials();

		OBJMesh defaultMesh = OBJMesh(WStringEmpty);
		OBJMesh* currentMesh = nullptr;
		int32_t currentSmoothing = -1;

		MTLMaterial defaultMat = MTLMaterial(WStringEmpty);
		defaultMat.Kd = ncolor(ColorF(0.8f, 0.8f, 0.8f, 1.0f));
		defaultMat.D = nfloat(1.0f);
		defaultMat.Illuminance = IlluminanceType::HighlightOn;

		matNameToMat[WStringEmpty] = defaultMat;
		MTLMaterial* currentMaterial = &(matNameToMat[WStringEmpty]);

		if (mtlLR) this->LoadMTLLib(mtlLR, &matNameToMat);

		while (objLR->ReadNext())
		{

			if (ObjParserC::Utils::StringExtensions::IsWhiteSpace(objLR->Current())) continue;
			if (ObjParserC::Utils::StringExtensions::StartsWith(objLR->Current(), L"#")) continue;

			auto arg = ObjParserC::Utils::StringExtensions::ToLower(objLR->ReadString());
			auto key = std::hash<std::wstring>()(arg);

			switch (key)
			{

			case 0x87CE3DF7: // mtllib
			{
				auto path = objLR->ReadString();
				this->LoadMTLLib(path, &matNameToMat);
				continue;
			}

			case 0x6549FC6B: // v
			{
				vertices.push_back(objLR->ReadVector3());
				continue;
			}

			case 0x837CC00D: // vn
			{
				normals.push_back(objLR->ReadVector3());
				continue;
			}

			case 0x5FBD2EB7: // vt
			{
				uvs.push_back(objLR->ReadVector2());
				continue;
			}

			case 0x0F33AEBA: // o
			case 0xDF1FDB72: // g
			{
				auto name = objLR->ReadString();
				auto itr = meshNameToMesh.find(name);

				if (itr == meshNameToMesh.end())
				{

					meshNameToMesh[name] = OBJMesh(name);
					currentMesh = &(meshNameToMesh[name]);

				}
				else
				{

					currentMesh = &(meshNameToMesh[name]);

				}

				continue;
			}

			case 0xDB19E2A3: // usemtl
			{
				auto name = objLR->ReadString();
				auto itr = matNameToMat.find(name);

				if (itr == matNameToMat.end())
				{

					currentMaterial = &(matNameToMat[WStringEmpty]);

				}
				else
				{

					currentMaterial = &(matNameToMat[name]);

				}

				continue;
			}

			case 0x052255DB: // f
			{
				if (currentMesh == nullptr) currentMesh = &defaultMesh;
				currentMesh->ReadFace(objLR, currentSmoothing, currentMaterial, &vertices, &normals, &uvs);
				continue;
			}

			case 0xD7516BA6: // s
			{
				currentSmoothing = objLR->ReadInt32();
				continue;
			}

			default:
				continue;

			}

		}

		if (defaultMesh.SubMeshes()->size() > 0)
		{

			meshNameToMesh[WStringEmpty] = defaultMesh;

		}
	}

	void ObjLoader::Load(const std::wstring& objFile, const std::wstring& mtlFile)
	{
		if (!std::filesystem::exists(objFile)) return;

		this->_filename = objFile;
		this->_collection.Filename = objFile;
		auto name = std::filesystem::path(objFile).filename();
		
		if (name.has_extension())
		{

			auto at = ObjParserC::Utils::StringExtensions::LastIndexOf(name, '.');
			this->_name = std::wstring(name).substr(0, at);
			this->_collection.Name = this->_name;

		}
		else
		{

			this->_name = std::wstring(name);
			this->_collection.Name = this->_name;

		}

		auto objLR = new LineReader(objFile);

		if (std::filesystem::exists(mtlFile))
		{

			auto mtlLR = new LineReader(mtlFile);
			this->Load(objLR, mtlLR);
			delete mtlLR;

		}
		else
		{

			this->Load(objLR);

		}

		delete objLR;
	}
}
