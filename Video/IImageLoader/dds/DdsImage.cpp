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

#ifndef MAKEFOURCC
#define MAKEFOURCC( ch0, ch1, ch2, ch3 ) \
	(( u32 ) ( unsigned char ) ( ch0 ) | (( u32 ) ( unsigned char ) ( ch1 ) << 8 ) | \
	(( u32 ) ( unsigned char ) ( ch2 ) << 16 ) | (( u32 ) ( unsigned char )( ch3 ) << 24 ))
#endif

#include <irrTypes.h>
#include "DdsImage.h"
#include "s3tc.h"
#include <IReadFile.h>

using namespace irr;
using namespace video;

namespace irrutils
{
	enum DDS_FLAGS
	{
		DDS_CAPS	= 0x00000001,
		DDS_HEIGHT	= 0x00000002,
		DDS_WIDTH	= 0x00000004,
		DDS_PITCH	= 0x00000008,
		DDS_PIXELFORMAT = 0x00001000,
		DDS_MIPMAPCOUNT = 0x00002000,
		DDS_LINEARSIZE	= 0x00008000,
		DDS_DEPTH	= 0x00800000,

		DDS_FOURCC	= 0x00000004,
		DDS_ALPHAPIXELS = 0x00000001
	};

	enum DDS_FOURCC
	{
		DDS_FOURCC_DXT1   = MAKEFOURCC( 'D', 'X', 'T', '1' ),
		DDS_FOURCC_DXT3   = MAKEFOURCC( 'D', 'X', 'T', '3' )
	};

	struct PixelFormat
	{
		u32 Size;
		u32 Flags;
		u32 FourCC;
		u32 RGBBitCount;
		u32 RBitMask;
		u32 GBitMask;
		u32 BBitMask;
		u32 ABitMask;
	};

	struct DdsHeader
	{
		u32 Magic;
		u32 Size;
		u32 Flags;
		u32 Height;
		u32 Width;
		u32 PitchOrLinearSize;
		u32 Depth;
		u32 MipMapCount;
		u32 Reserved1[11];
		PixelFormat PF;
		u32 Caps1;
		u32 Caps2;
		u32 Reserved2[3];
	};

bool CImageLoaderDDS::decodeDdsHeader(const u8* rawBytes) const
{
	const DdsHeader *m_DdsHeader = ( const DdsHeader * ) rawBytes;
	return ( m_DdsHeader->Magic == MAKEFOURCC( 'D', 'D', 'S', ' ' ) );
}

bool CImageLoaderDDS::decodePixels( IImage *destination, const u8* rawBytes ) const
{
	const DdsHeader *m_DdsHeader = ( const DdsHeader * ) rawBytes;
	uint8_t *dest = ( uint8_t * ) destination->lock();
	const u8 *src = rawBytes + 128;

	if( m_DdsHeader->PF.FourCC == DDS_FOURCC_DXT1 )
		ff_decode_dxt1( src, dest, m_DdsHeader->Width, m_DdsHeader->Height, m_DdsHeader->Width * 4 );
	else if( m_DdsHeader->PF.FourCC == DDS_FOURCC_DXT3 )
		ff_decode_dxt3( src, dest, m_DdsHeader->Width, m_DdsHeader->Height, m_DdsHeader->Width * 4 );

	destination->unlock();

	return true;
}

CImageLoaderDDS::CImageLoaderDDS( IVideoDriver *driver ) :
	m_Driver(driver)
{
}

IImage * CImageLoaderDDS::loadImage(irr::io::IReadFile* file) const
{
	// Read file content
	u8* rawBytes = new u8[file->getSize()];
	file->read(rawBytes, file->getSize());

	if( ! decodeDdsHeader(rawBytes) )
		throw( "failed to decode DDS image. Maybe not a DDS file or not DXT1/3 encoded" );
	const DdsHeader *m_DdsHeader = ( const DdsHeader * ) rawBytes;
	IImage *image = m_Driver->createImage( ECF_A8R8G8B8, core::dimension2d<u32>( m_DdsHeader->Width, m_DdsHeader->Height ));
	decodePixels( image, rawBytes );

	delete[] rawBytes;

	return image;
}

bool CImageLoaderDDS::isALoadableFileExtension(const io::path& filename) const
{
	return core::hasFileExtension(filename, "dds") || core::hasFileExtension(filename, "dxt");
}


bool CImageLoaderDDS::isALoadableFileFormat(io::IReadFile* file) const
{
	// Read file content
	u8* rawBytes = new u8[sizeof(DdsHeader)];
	file->read(rawBytes, sizeof(DdsHeader));
	const bool ret = decodeDdsHeader(rawBytes);
	delete[] rawBytes;
	return ret;
}

}

