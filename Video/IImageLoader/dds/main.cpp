/* main.cpp -- Example interface to DdsLib

 Copyright (C) 2007 by Egon A. Rath

 This software is provided 'as-is', without any express or implied
 warranty.  In no event will the author be held liable for any damages
 arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:

 1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgement in the product documentation would be
	appreciated but is not required.
 2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.
 3. This notice may not be removed or altered from any source distribution.
 
*/
 
#include <irrlicht.h>
#include "DdsImage.h"
#include <iostream>

using namespace irr;
using namespace io;
using namespace video;
using namespace std;

int main( int argc, char **argv )
{
	if( argc != 3 )
	{
		cout << "DdsTool" << endl;
		cout << "usage: " << argv[0] << " input output" << endl;
	}
	else
	{
		IrrlichtDevice *dev = createDevice( EDT_NULL, core::dimension2d<u32>(), 32, false, false, false, 0 );
		irrutils::CImageLoaderDDS *img = new irrutils::CImageLoaderDDS( dev->getVideoDriver() );
		dev->getVideoDriver()->addExternalImageLoader(img);
		img->drop();

		IImage *image = dev->getVideoDriver()->createImageFromFile(argv[1]);

		if( image != 0 )
		{
			IImageWriter *writer = dev->getVideoDriver()->getImageWriter( 0 );
			writer->writeImage( createWriteFile( argv[2], false ), image, 0 );
			image->drop();
		}
	}
}

