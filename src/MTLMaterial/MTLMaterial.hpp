#pragma once



namespace ObjParserC
{
	/// <summary>
	/// Stores data of an MTL material. All comments are taken from http://paulbourke.net/dataformats/mtl/,
	/// for more information please visit their website.
	/// </summary>
	struct MTLMaterial
	{
	private:
		std::wstring _name;

	public:
	    /// <summary>
	    /// Name of the material.
	    /// </summary>
		std::wstring& Name();
	
	    /// <summary>
	    /// Ambient reflectivity of this material. This is a nullable value, if it does not 
	    /// exist in the material, it is <see langword="null"/>.
	    /// </summary>
	    ncolor Ka;
	
	    /// <summary>
	    /// Diffuse reflectivity of this material. This is a nullable value, if it does not 
	    /// exist in the material, it is <see langword="null"/>.
	    /// </summary>
	    ncolor Kd;
	
	    /// <summary>
	    /// Specular reflectivity of this material. This is a nullable value, if it does not 
	    /// exist in the material, it is <see langword="null"/>.
	    /// </summary>
	    ncolor Ks;
	
	    /// <summary>
	    /// Transmission filter setup. Any light passing through the object is filtered 
	    /// by the transmission filter, which only allows the specifiec colors to pass 
	    /// through. This is a nullable value, if it does not exist in the material, it is
	    /// <see langword="null"/>.
	    /// </summary>
	    ncolor Tf;
	
	    /// <summary>
	    /// Specifies the dissolve for this material. This is a nullable value, if it does not 
	    /// exist in the material, it is <see langword="null"/>.
	    /// </summary>
	    nfloat D;
	
	    /// <summary>
	    /// Specifies that a dissolve is dependent on the surface orientation relative to the viewer.
	    /// This is a nullable value, if it does not exist in the material, it is <see langword="null"/>.
	    /// </summary>
	    nbool Halo;
	
	    /// <summary>
	    /// Specifies the specular exponent for the current material. This defines the focus 
	    /// of the specular highlight. This is a nullable value, if it does not exist in the 
	    /// material, it is <see langword="null"/>.
	    /// </summary>
	    nfloat Ns;
	
	    /// <summary>
	    /// Specifies the optical density for the surface.  This is also known as index of 
	    /// refraction. Default This is a nullable value, if it does not exist in the 
	    /// material, it is <see langword="null"/>.
	    /// </summary>
	    nfloat Ni;
	
	    /// <summary>
	    /// Specifies the sharpness of the reflections from the local reflection map. 
	    /// This is a nullable value, if it does not exist in the material, it is 
	    /// <see langword="null"/>.
	    /// </summary>
	    nfloat Sharpness;
	
	    /// <summary>
	    /// Specifies the illumination model to use in the material. Illumination models are 
	    /// mathematical equations that represent various material lighting and shading effects.
	    /// This is a nullable value, if it does not exist in the material, it is 
	    /// <see langword="null"/>.
	    /// </summary>
	    IlluminanceType Illuminance = IlluminanceType::Invalid;
	
	    /// <summary>
	    /// Turns on anti-aliasing of textures in this material without anti-aliasing all 
	    /// textures in the scene. This is a nullable value, if it does not exist in the 
	    /// material, it is <see langword="null"/>.
	    /// </summary>
	    nbool MapAat;
	
	    /// <summary>
	    /// Specifies that a color texture file or a color procedural texture file is 
	    /// applied to the ambient reflectivity of the material. During rendering, the 
	    /// MapKa value is multiplied by the Ka value. If material has no MapKa set,
	    /// this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* MapKa;
	
	    /// <summary>
	    /// Specifies that a color texture file or color procedural texture file is 
	    /// linked to the diffuse reflectivity of the material. During rendering, 
	    /// the MapKd value is multiplied by the Kd value. If material has no MapKd
	    /// set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* MapKd;
	
	    /// <summary>
	    /// Specifies that a color texture file or color procedural texture file is 
	    /// linked to the specular reflectivity of the material. During rendering, 
	    /// the MapKs value is multiplied by the Ks value. If material has no MapKs
	    /// set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* MapKs;
	
	    /// <summary>
	    /// Specifies that a scalar texture file or scalar procedural texture file is linked 
	    /// to the specular exponent of the material. During rendering, the MapNs value is 
	    /// multiplied by the Ns value. If material has no MapNs set, this returns 
	    /// <see langword="null"/>.
	    /// </summary>
		MTLTexture* MapNs;
	
	    /// <summary>
	    /// Specifies that a scalar texture file or scalar procedural texture file is 
	    /// linked to the dissolve of the material. During rendering, the MapD value is 
	    /// multiplied by the D value. If material has no MapD set, this returns 
	    /// <see langword="null"/>.
	    /// </summary>
		MTLTexture* MapD;
	
	    /// <summary>
	    /// Specifies that a scalar texture file or a scalar procedural texture file 
	    /// is used to selectively replace the material color with the texture color.
	    /// If material has no Decal set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* Decal;
	
	    /// <summary>
	    /// Specifies that a scalar texture is used to deform the surface of an object, 
	    /// creating surface roughness. If material has no Disp set, this returns 
	    /// <see langword="null"/>.
	    /// </summary>
		MTLTexture* Disp;
	
	    /// <summary>
	    /// Specifies that a bump texture file or a bump procedural texture file is linked 
	    /// to the material. If material has no Bump set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* MapBump;
	
	    /// <summary>
	    /// Specifies an infinitely large sphere that casts reflections onto the material from all
	    /// sides. If material has no "refl -type sphere" set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* ReflSphere;
	
	    /// <summary>
	    /// Specifies an infinitely large sphere that casts reflections onto the material from top
	    /// side. If material has no "refl -type cube_top" set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* ReflCubeTop;
	
	    /// <summary>
	    /// Specifies an infinitely large sphere that casts reflections onto the material from bottom
	    /// side. If material has no "refl -type cube_bottom" set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* ReflCubeBottom;
	
	    /// <summary>
	    /// Specifies an infinitely large sphere that casts reflections onto the material from front
	    /// side. If material has no "refl -type cube_front" set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* ReflCubeFront;
	
	    /// <summary>
	    /// Specifies an infinitely large sphere that casts reflections onto the material from back
	    /// side. If material has no "refl -type cube_back" set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* ReflCubeBack;
	
	    /// <summary>
	    /// Specifies an infinitely large sphere that casts reflections onto the material from left
	    /// side. If material has no "refl -type cube_left" set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* ReflCubeLeft;
	
	    /// <summary>
	    /// Specifies an infinitely large sphere that casts reflections onto the material from right
	    /// side. If material has no "refl -type cube_right" set, this returns <see langword="null"/>.
	    /// </summary>
		MTLTexture* ReflCubeRight;
	
		/// <summary>
		/// Initializes new material instance.
		/// </summary>
		MTLMaterial();

	    /// <summary>
	    /// Initializes new material instance.
	    /// </summary>
	    /// <param name="name">Name of the material.</param>
		MTLMaterial(const std::wstring& name);
	
		/// <summary>
		/// Copies data in the passed instances to the current instance.
		/// </summary>
		/// <param name="material">Instance to copy.</param>
		MTLMaterial(const MTLMaterial& material);

		/// <summary>
		/// Assigns and copies all data from the instance passed to the current instance.
		/// </summary>
		/// <param name="material">Instance to copy.</param>
		/// <returns>Reference to this instance.</returns>
		MTLMaterial& operator =(const MTLMaterial& material);

		/// <summary>
		/// Gets name of this material.
		/// </summary>
		/// <returns>Name of this material as a wide string.</returns>
		std::wstring ToString();

		/// <summary>
		/// Destroys current instance.
		/// </summary>
		~MTLMaterial();
	};
}
