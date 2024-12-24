#pragma once
#include <Windows.h>
#include <errhandlingapi.h>
#include <strsafe.h>

#include <iostream>
#include <conio.h>

namespace cbd {
	class Clipboard
	{
	private:

	public:
		Clipboard();

		bool set_image(const char* imagePath);
	};
}


