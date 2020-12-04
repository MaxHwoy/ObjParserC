#include <pch.hpp>
#include <iostream>
#include <chrono>



void main()
{
	auto file = L"C:\\Users\\Max\\source\\repos\\ObjParserC\\build\\bin\\debug\\350Z.obj";

	auto start = std::chrono::high_resolution_clock::now();

	auto loader = ObjParserC::ObjLoader();
	loader.Load(file);


	auto end = std::chrono::high_resolution_clock::now();

	//std::wprintf(L"Name: %ls\n", loader.Collection()->Name.c_str());
	//std::wprintf(L"Meshes: %d\n", loader.Collection()->Meshes().size());
	//std::wprintf(L"Materials: %d\n", loader.Collection()->Materials().size());
	std::wprintf(L"Time elapsed: %f ms\n", (end - start).count() / 1000000.0f);

	int32_t aaa = 0;
	std::cin >> aaa;
}
