#include "util.h"
#include "interfaces.h"
#include "SDK/definitions.h"

std::vector<Color>* rainbow = nullptr;

void SetupRainbow ()
{
	rainbow = new std::vector<Color>();
	
	for (int r=0; r<100; r++)
		rainbow->push_back(Color(r*255/100, 255, 0));
	for (int g=100; g>0; g--)
		rainbow->push_back(Color(255, g*255/100, 0));
	for (int b=0; b<100; b++)
		rainbow->push_back(Color(255, 0, b*255/100));
	for (int r=100; r>0; r--)
		rainbow->push_back(Color(r*255/100, 0, 255));
	for (int g=0; g<100; g++)
		rainbow->push_back(Color(0, g*255/100, 255));
	for (int b=100; b>0; b--)
		rainbow->push_back(Color(0, 255, b*255/100));
		
	rainbow->push_back(Color(0, 255, 0));
	
	pstring str;
	str << "size: ";
	str + rainbow->size();
	PRINT (str.c_str());
}