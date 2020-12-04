#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <stdarg.h>
#include <filesystem>
#include <unordered_map>



const uint32_t NaNAsUInt32 = 0xFFC00000;
const uint32_t PosIAsUInt32 = 0x7F800000;
const uint32_t NegIAsUInt32 = 0xFF800000;
const uint32_t EpsAsUInt32 = 0x00000001;
const float NaN = *(float*)&NaNAsUInt32;
const float PositiveInfinity = *(float*)&PosIAsUInt32;
const float NegativeInfinity = *(float*)&NegIAsUInt32;
const float Epsilon = *(float*)&EpsAsUInt32;
constexpr auto StringEmpty = "";
constexpr auto WStringEmpty = L"";

template <typename T> using Method = T*;

#include <Array/Array.hpp>
#include <Shared/Shared.hpp>
#include <Utils/StringExtensions/StringExtensions.hpp>
#include <Utils/Formatter/Formatter.hpp>
#include <LineReader/LineReader.hpp>
#include <MTLTexture/MTLTexture.hpp>
#include <MTLMaterial/MTLMaterial.hpp>
#include <OBJMesh/OBJMesh.hpp>
#include <MeshCollection/MeshCollection.hpp>
#include <MTLLoader/MTLLoader.hpp>
#include <OBJLoader/OBJLoader.hpp>

