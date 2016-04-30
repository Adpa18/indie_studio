/* DdsImage.cpp -- Irrlicht Image Loader
   This code was adapted by Christian Stehno based on the original loader from Egon A. Rath

   Original Copyright
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

#ifndef DDSIMAGE_H
#define DDSIMAGE_H

#include <IImageLoader.h>
#include <IVideoDriver.h>

namespace irrutils
{
	class CImageLoaderDDS : public irr::video::IImageLoader
	{
		public:
		CImageLoaderDDS( irr::video::IVideoDriver *driver = 0 );

		virtual bool isALoadableFileExtension(const irr::io::path& filename) const;

		virtual bool isALoadableFileFormat(irr::io::IReadFile* file) const;

		virtual irr::video::IImage * loadImage(irr::io::IReadFile* file) const;

		private:
		irr::video::IVideoDriver *m_Driver;

		bool decodeDdsHeader(const irr::u8* rawBytes) const;
		bool decodePixels( irr::video::IImage *destination, const irr::u8* rawBytes ) const;
	};

}

#endif // DDSIMAGE_H

