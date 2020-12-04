#include <pch.hpp>
#include <iostream>
#include <chrono>


void ReadLol();


void main()
{
	ReadLol();

	int32_t aaa = 0;
	std::cin >> aaa;
}


void ReadLol()
{
	auto objFile = L"350Z.obj";
	auto mtlFile = L"350Z.mtl";

	auto start = std::chrono::high_resolution_clock::now();

	auto loader = ObjParserC::ObjLoader();
	loader.Load(objFile);


	auto end = std::chrono::high_resolution_clock::now();

	std::wprintf(L"Name: %ls\n", loader.Collection()->Name.c_str());
	std::wprintf(L"Meshes: %d\n", loader.Collection()->Meshes().size());
	std::wprintf(L"Materials: %d\n", loader.Collection()->Materials().size());
	std::wprintf(L"Time elapsed: %f ms\n", (end - start).count() / 1000000.0f);
}
