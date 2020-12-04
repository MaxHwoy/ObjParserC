#pragma once



namespace ObjParserC
{
	class OBJMesh
	{
	public:
		struct Triangle
		{
			int32_t Index1;
			int32_t Index2;
			int32_t Index3;

			Triangle(int32_t i1, int32_t i2, int32_t i3);
			Triangle(const Triangle& triangle);
			Triangle& operator =(const Triangle& triangle);
		};

		struct MeshVertex
		{
			int32_t VertexIndex;
			int32_t UVIndex;
			int32_t NormalIndex;
			int32_t SmoothingGroup;

			MeshVertex();
			MeshVertex(const MeshVertex& vert);
			MeshVertex& operator =(const MeshVertex& vert);
			MeshVertex(int32_t smoothing, int32_t vertex, int32_t uv = 0, int32_t normal = 0);
			bool operator ==(const MeshVertex& vert) const;

			struct Hasher
			{
				std::size_t operator()(const MeshVertex& vert) const
				{
					std::size_t v = std::hash<int32_t>{}(vert.VertexIndex);
					std::size_t u = std::hash<int32_t>{}(vert.UVIndex);
					std::size_t n = std::hash<int32_t>{}(vert.NormalIndex);
					std::size_t s = std::hash<int32_t>{}(vert.SmoothingGroup);

					std::size_t result = ObjParserC::Utils::Formatter::CombineHashes(v, u);
					result = ObjParserC::Utils::Formatter::CombineHashes(result, n);
					return ObjParserC::Utils::Formatter::CombineHashes(result, s);
				}
			};
		};

		class SubMesh
		{
		private:
			MTLMaterial* _material;
			std::vector<Triangle> _triangles;
			bool _has_missing_normals;

		public:
			SubMesh();
			SubMesh(MTLMaterial* material);
			SubMesh(const SubMesh& subMesh);
			SubMesh& operator =(const SubMesh& subMesh);
			void EnableMissingNormals();
			MTLMaterial* Material();
			std::vector<Triangle>* Triangles();
			bool HasMissingNormals();
		};

	private:
		std::wstring _name;
		std::vector<Vector3> _vertices;
		std::vector<Vector3> _normals;
		std::vector<Vector2> _uvs;
		std::vector<int32_t> _smoothings;
		std::unordered_map<std::wstring, SubMesh> _nameToSubMesh;
		std::unordered_map<MeshVertex, int32_t, MeshVertex::Hasher> _meshVertexToIndex;

	public:
		OBJMesh();
		OBJMesh(const std::wstring& name);
		OBJMesh(const OBJMesh& objMesh);
		OBJMesh& operator =(const OBJMesh& objMesh);

		std::wstring& Name();
		std::vector<Vector3>* Vertices();
		std::vector<Vector3>* Normals();
		std::vector<Vector2>* UVs();
		std::vector<int32_t>* SmoothingGroups();
		std::unordered_map<std::wstring, SubMesh>* SubMeshes();
		void ReadFace(LineReader* lr, int32_t smoothing, MTLMaterial* material,
			std::vector<Vector3>* vertices, std::vector<Vector3>* normals, std::vector<Vector2>* uvs);
	};
}
