#include <pch.hpp>
#include <MeshCollection/MeshCollection.hpp>



namespace ObjParserC
{
	MeshCollection::MeshCollection()
	{
		this->Name = WStringEmpty;
		this->Filename = WStringEmpty;
	}

	MeshCollection::MeshCollection(const MeshCollection& collection)
	{
		this->Name = collection.Name;
		this->Filename = collection.Filename;
		this->_meshes = collection._meshes;
		this->_materials = collection._materials;
	}

	MeshCollection& MeshCollection::operator =(const MeshCollection& collection)
	{
		if (this != &collection)
		{

			this->Name = collection.Name;
			this->Filename = collection.Filename;
			this->_meshes = collection._meshes;
			this->_materials = collection._materials;

		}

		return *this;
	}

	std::unordered_map<std::wstring, OBJMesh>& MeshCollection::Meshes()
	{
		return this->_meshes;
	}

	std::unordered_map<std::wstring, MTLMaterial>& MeshCollection::Materials()
	{
		return this->_materials;
	}
}
