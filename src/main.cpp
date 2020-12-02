#include <pch.hpp>
#include <iostream>



void main()
{
	auto file = L"C:\\Users\\Max\\source\\repos\\ObjParserC\\build\\bin\\debug\\350Z.mtl";

	auto linereader = ObjParserC::LineReader(file);

	while (linereader.ReadNext())
	{

		int32_t bbb = 0;

	}

	int32_t aaa = 0;
}
