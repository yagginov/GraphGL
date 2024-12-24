#ifndef CLIPBOARD_H
#define CLIPBOARD_H

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

#endif 		// CLIPBOARD_H