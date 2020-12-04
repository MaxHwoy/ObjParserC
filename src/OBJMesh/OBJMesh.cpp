#include <pch.hpp>
#include <OBJMesh/OBJMesh.hpp>



namespace ObjParserC
{
	OBJMesh::Triangle::Triangle(int32_t i1, int32_t i2, int32_t i3)
	{
		this->Index1 = i1;
		this->Index2 = i2;
		this->Index3 = i3;
	}

	OBJMesh::Triangle::Triangle(const Triangle& triangle)
	{
		this->Index1 = triangle.Index1;
		this->Index2 = triangle.Index2;
		this->Index3 = triangle.Index3;
	}

	OBJMesh::Triangle& OBJMesh::Triangle::operator =(const Triangle& triangle)
	{
		if (this != &triangle)
		{

			this->Index1 = triangle.Index1;
			this->Index2 = triangle.Index2;
			this->Index3 = triangle.Index3;

		}

		return *this;
	}

	OBJMesh::MeshVertex::MeshVertex()
	{
		this->VertexIndex = 0;
		this->NormalIndex = 0;
		this->UVIndex = 0;
		this->SmoothingGroup = -1;
	}

	OBJMesh::MeshVertex::MeshVertex(const MeshVertex& vert)
	{
		this->VertexIndex = vert.VertexIndex;
		this->NormalIndex = vert.NormalIndex;
		this->UVIndex = vert.UVIndex;
		this->SmoothingGroup = vert.SmoothingGroup;
	}

	OBJMesh::MeshVertex& OBJMesh::MeshVertex::operator =(const MeshVertex& vert)
	{
		if (this != &vert)
		{

			this->VertexIndex = vert.VertexIndex;
			this->NormalIndex = vert.NormalIndex;
			this->UVIndex = vert.UVIndex;
			this->SmoothingGroup = vert.SmoothingGroup;

		}

		return *this;
	}

	OBJMesh::MeshVertex::MeshVertex(int32_t smoothing, int32_t vertex, int32_t uv, int32_t normal)
	{
		this->SmoothingGroup = smoothing;
		this->VertexIndex = vertex;
		this->UVIndex = uv;
		this->NormalIndex = normal;
	}

	bool OBJMesh::MeshVertex::operator ==(const MeshVertex& vert) const
	{
		return this->VertexIndex == vert.VertexIndex && this->UVIndex == vert.UVIndex &&
			this->NormalIndex == vert.NormalIndex && this->SmoothingGroup == vert.SmoothingGroup;
	}

	OBJMesh::SubMesh::SubMesh()
	{
		this->_has_missing_normals = false;
	}

	OBJMesh::SubMesh::SubMesh(MTLMaterial* material)
	{
		this->_material = material;
		this->_has_missing_normals = false;
	}

	OBJMesh::SubMesh::SubMesh(const SubMesh& subMesh)
	{
		this->_has_missing_normals = subMesh._has_missing_normals;
		this->_material = subMesh._material;
		this->_triangles = subMesh._triangles;
	}

	OBJMesh::SubMesh& OBJMesh::SubMesh::operator =(const SubMesh& subMesh)
	{
		if (this != &subMesh)
		{

			this->_has_missing_normals = subMesh._has_missing_normals;
			this->_material = subMesh._material;
			this->_triangles = subMesh._triangles;

		}

		return *this;
	}

	void OBJMesh::SubMesh::EnableMissingNormals()
	{
		this->_has_missing_normals = true;
	}

	MTLMaterial* OBJMesh::SubMesh::Material()
	{
		return this->_material;
	}

	std::vector<OBJMesh::Triangle>* OBJMesh::SubMesh::Triangles()
	{
		return &this->_triangles;
	}

	bool OBJMesh::SubMesh::HasMissingNormals()
	{
		return this->_has_missing_normals;
	}

	OBJMesh::OBJMesh()
	{
		this->_name = WStringEmpty;
	}

	OBJMesh::OBJMesh(const std::wstring& name)
	{
		this->_name = name;
	}

	OBJMesh::OBJMesh(const OBJMesh& objMesh)
	{
		this->_name = objMesh._name;
		this->_meshVertexToIndex = objMesh._meshVertexToIndex;
		this->_nameToSubMesh = objMesh._nameToSubMesh;
		this->_vertices = objMesh._vertices;
		this->_normals = objMesh._normals;
		this->_uvs = objMesh._uvs;
		this->_smoothings = objMesh._smoothings;
	}

	OBJMesh& OBJMesh::operator =(const OBJMesh& objMesh)
	{
		if (this != &objMesh)
		{

			this->_name = objMesh._name;
			this->_meshVertexToIndex = objMesh._meshVertexToIndex;
			this->_nameToSubMesh = objMesh._nameToSubMesh;
			this->_vertices = objMesh._vertices;
			this->_normals = objMesh._normals;
			this->_uvs = objMesh._uvs;
			this->_smoothings = objMesh._smoothings;

		}

		return *this;
	}

	std::wstring& OBJMesh::Name()
	{
		return this->_name;
	}

	std::vector<Vector3>* OBJMesh::Vertices()
	{
		return &this->_vertices;
	}

	std::vector<Vector3>* OBJMesh::Normals()
	{
		return &this->_normals;
	}

	std::vector<Vector2>* OBJMesh::UVs()
	{
		return &this->_uvs;
	}

	std::vector<int32_t>* OBJMesh::SmoothingGroups()
	{
		return &this->_smoothings;
	}

	std::unordered_map<std::wstring, OBJMesh::SubMesh>* OBJMesh::SubMeshes()
	{
		return &this->_nameToSubMesh;
	}

	void OBJMesh::ReadFace(LineReader* lr, int32_t smoothing, MTLMaterial* material,
		std::vector<Vector3>* vertices, std::vector<Vector3>* normals, std::vector<Vector2>* uvs)
	{
		int32_t count = lr->Splits().Length() - 1;
		if (count < 3) return;
		auto faceIndeces = int32s(count);

		SubMesh* subMesh = nullptr;
		auto matName = material->Name();
		auto itr = this->_nameToSubMesh.find(matName);

		if (itr == this->_nameToSubMesh.end())
		{

			this->_nameToSubMesh[matName] = SubMesh(material);
			subMesh = &(this->_nameToSubMesh[matName]);

		}
		else
		{

			subMesh = &(this->_nameToSubMesh[matName]);

		}

		for (int32_t i = 0; i < count; ++i)
		{

			wchars separator = wchars(2);
			separator[0] = '/';
			separator[1] = '\0';
			auto combo = ObjParserC::Utils::StringExtensions::Split(lr->ReadString(), &separator);
			auto meshVertex = MeshVertex();

			switch (combo.Length())
			{

			case 3:
				meshVertex.NormalIndex = ObjParserC::Utils::Formatter::ParseInt32(combo[2]);
				[[fallthrough]];

			case 2:
				meshVertex.UVIndex = ObjParserC::Utils::Formatter::ParseInt32(combo[1]);
				[[fallthrough]];

			case 1:
				meshVertex.VertexIndex = ObjParserC::Utils::Formatter::ParseInt32(combo[0]);
				meshVertex.SmoothingGroup = smoothing;
				break;

			default:
				break;

			}

			int32_t index = 0;
			auto vertItr = this->_meshVertexToIndex.find(meshVertex);

			if (vertItr == this->_meshVertexToIndex.end())
			{

				index = (int32_t)this->_meshVertexToIndex.size();
				this->_meshVertexToIndex.insert(std::pair<MeshVertex, int32_t>(meshVertex, index));

				auto vertexIndex = meshVertex.VertexIndex;
				auto normalIndex = meshVertex.NormalIndex;
				auto uvIndex = meshVertex.UVIndex;

				if (vertexIndex <= 0 || vertexIndex > (int32_t)vertices->size()) this->_vertices.push_back(Vector3());
				else this->_vertices.push_back(vertices->at(vertexIndex - 1));

				if (uvIndex <= 0 || uvIndex > (int32_t)uvs->size()) this->_uvs.push_back(Vector2());
				else this->_uvs.push_back(uvs->at(uvIndex - 1));

				if (0 < normalIndex && normalIndex <= (int32_t)normals->size()) this->_normals.push_back(normals->at(normalIndex - 1));
				else { this->_normals.push_back(Vector3()); subMesh->EnableMissingNormals(); }

				this->_smoothings.push_back(smoothing);

			}
			else
			{

				index = vertItr->second;

			}

			faceIndeces[i] = index;

		}

		auto list = subMesh->Triangles();

		switch (count)
		{

		case 3:
			list->push_back(Triangle(faceIndeces[0], faceIndeces[1], faceIndeces[2]));
			break;

		case 4:
			list->push_back(Triangle(faceIndeces[0], faceIndeces[1], faceIndeces[2]));
			list->push_back(Triangle(faceIndeces[2], faceIndeces[3], faceIndeces[0]));
			break;

		default: // 5 and more
			for (int i = count - 2; i > 0; --i)
			{

				list->push_back(Triangle(faceIndeces[0], faceIndeces[i], faceIndeces[i + 1]));

			}
			break;

		}
	}
}
