#pragma once

#pragma warning (disable : 26495)



namespace ObjParserC
{
	template <typename T> struct Nullable
	{
	private:
		T _value;
		bool _exists;

	public:
		T Value()
		{
			return this->_value;
		}
		bool Exists()
		{
			return this->_exists;
		}
		Nullable()
		{
			this->_exists = false;
		}
		Nullable(T value)
		{
			this->_value = value;
			this->_exists = true;
		}
		Nullable(const Nullable& nullable)
		{
			this->_value = nullable._value;
			this->_exists = nullable._exists;
		}
	};

	struct ColorF
	{
		float R;
		float G;
		float B;
		float A;

		ColorF()
		{
			this->A = this->R = this->G = this->B = 0.0f;
		}
		ColorF(const ColorF& color)
		{
			this->R = color.R;
			this->G = color.G;
			this->B = color.B;
			this->A = color.A;
		}
		ColorF(float r, float g, float b, float a)
		{
			this->R = r;
			this->G = g;
			this->B = b;
			this->A = a;
		}
	};

	/// <summary>
	/// Illumination type specifiers for <see cref="MTLMaterial"/>.
	/// </summary>
	enum class IlluminanceType : int32_t
	{
		/// <summary>
		/// Indicates that illumination mode is not specified in the material.
		/// </summary>
		Invalid = -1,

		/// <summary>
		/// This is a constant color illumination model.  The color is the specified Kd 
		/// for the material.
		/// </summary>
		AmbientOff = 0,

		/// <summary>
		/// This is a diffuse illumination model using Lambertian shading. The color includes 
		/// an ambient constant term and a diffuse shading term for each light source.
		/// </summary>
		AmbientOn = 1,

		/// <summary>
		/// This is a diffuse and specular illumination model using Lambertian shading and 
		/// Blinn's interpretation of Phong's specular illumination model (BLIN77). The color 
		/// includes an ambient constant term, and a diffuse and specular shading term for 
		/// each light source.
		/// </summary>
		HighlightOn = 2,

		/// <summary>
		/// This is a diffuse and specular illumination model with reflection using Lambertian 
		/// shading, Blinn's interpretation of Phong's specular illumination model (BLIN77), and 
		/// a reflection term similar to that in Whitted's illumination model (WHIT80). The color 
		/// includes an ambient constant term and a diffuse and specular shading term for each 
		/// light source.
		/// </summary>
		ReflectionOnRayTraceOn = 3,

		/// <summary>
		/// The diffuse and specular illumination model used to simulate glass is the same 
		/// as illumination model 3.  When using a very low dissolve (approximately 0.1), 
		/// specular highlights from lights or reflections become imperceptible.
		/// </summary>
		TransparencyGlassOnRayTraceOn = 4,

		/// <summary>
		/// This is a diffuse and specular shading models similar to illumination model 3, 
		/// except that reflection due to Fresnel effects is introduced into the equation.
		/// Fresnel reflection results from light striking a diffuse surface at a grazing 
		/// or glancing angle.  When light reflects at a grazing angle, the Ks value 
		/// approaches 1.0 for all color samples.
		/// </summary>
		FresnelOnRayTraceOn = 5,

		/// <summary>
		/// This is a diffuse and specular illumination model similar to that used by Whitted 
		/// (WHIT80) that allows rays to refract through a surface. The amount of refraction 
		/// is based on optical density(Ni).  The intensity of light that refracts is equal 
		/// to 1.0 minus the value of Ks, and the resulting light is filtered by 
		/// Tf(transmission filter) as it passes through the object.
		/// </summary>
		RefractionOnFresnelOffRayTraceOn = 6,

		/// <summary>
		/// This illumination model is similar to illumination model 6, except that reflection 
		/// and transmission due to Fresnel effects has been introduced to the equation. At 
		/// grazing angles, more light is reflected and less light is refracted through the object.
		/// </summary>
		RefractionOnFresnelOnRayTraceOn = 7,

		/// <summary>
		/// This illumination model is similar to illumination model 3 without ray tracing.
		/// </summary>
		ReflectionOnRayTraceOff = 8,

		/// <summary>
		/// This illumination model is similar to illumination model 4 without ray tracing.
		/// </summary>
		TransparencyGlassOnRayTraceOff = 9,

		/// <summary>
		/// This illumination model is used to cast shadows onto an invisible surface. This 
		/// is most useful when compositing computer-generated imagery onto live action, 
		/// since it allows shadows from rendered objects to be composited directly on top 
		/// of video-grabbed images.
		/// </summary>
		CastShadowOnInvisibleSurfaces = 10,
	};

	/// <summary>
	/// Channel type for -imfchan command in <see cref="MTLTexture"/>.
	/// </summary>
	enum class ImfchanType : int32_t
	{
		/// <summary>
		/// Indicates that channel type is not specified in the texture.
		/// </summary>
		Invalid = -1,

		/// <summary>
		/// Red channel creates a scalar or bump texture.
		/// </summary>
		R = 0,

		/// <summary>
		/// Green channel creates a scalar or bump texture.
		/// </summary>
		G = 1,

		/// <summary>
		/// Blue channel creates a scalar or bump texture.
		/// </summary>
		B = 2,

		/// <summary>
		/// Matte channel creates a scalar or bump texture.
		/// </summary>
		M = 3,

		/// <summary>
		/// Luminance channel creates a scalar or bump texture.
		/// </summary>
		L = 4,

		/// <summary>
		/// Z-Depth channel creates a scalar or bump texture.
		/// </summary>
		Z = 5,
	};
}

using nbool = ObjParserC::Nullable<bool>;
using nint = ObjParserC::Nullable<int32_t>;
using nuint = ObjParserC::Nullable<uint32_t>;
using nfloat = ObjParserC::Nullable<float>;
using ncolor = ObjParserC::Nullable<ObjParserC::ColorF>;
using nvec = ObjParserC::Nullable<LinearC::Vectors::Vector3>;
