//-------------------------------------------------------------------------------
// $Revision: 1.2 $
// $Date: 2005/07/28 01:23:04 $
//-------------------------------------------------------------------------------
// Sample Plugin: SUN raster image Import Plugin
//
// Overview:
//	   This plugin registers a image importer tool that reads in 
//		images in the SUN raster image format
// 
// API Functionality:
//		Texture Attributes Access
//-------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <mgapiall.h>

/****************************************************
*	Sun Raster Format defines
****************************************************/

#define RMT_EQUAL_RGB	1
#define RMT_NONE			0
#define RMT_RAW			2
#define RT_OLD				0
#define RT_STANDARD		1
#define RT_ENCODED		2
#define RT_FORMAT_RGB	3

#define PSEUDOCLASS		2
#define DIRECTCLASS		1

#define MaxRGB				255

#define MAXOPENIMGS		20

/****************************************************
*	Byte Swapping Macros	
****************************************************/

#define swap_word(a) ( ((a) << 24) | \
		      (((a) << 8) & 0x00ff0000) | \
		      (((a) >> 8) & 0x0000ff00) | \
	((unsigned long)(a) >>24) )

#define swap_half(a) ( ((a & 0xff) << 8) | ((unsigned short)(a) >> 8) )

/****************************************************
*	Sun Raster Data Types	
****************************************************/

typedef struct colorpacket {
  unsigned char
    red,
    green,
    blue,
    flags;

  unsigned short
    index;
} colorpacket;

typedef struct SUNHeader {
	unsigned long
				magic,
				width,
				height,
				depth,
				length,
				type,
				maptype,
				maplength;
} SUNHeader;


typedef struct rgbdata {
  unsigned char red, green, blue;
} rgbdata, *rgbdatapt;

typedef struct rgbadata {
  unsigned char red, green, blue, alpha;
} rgbadata, *rgbadatapt;


/****************************************************
*	Local Variables								
****************************************************/

static int NumOpen = 0;
static FILE *OpenFiles [ MAXOPENIMGS ];

/****************************************************
*	Plugin Name definition	
****************************************************/

mgDeclarePlugin(
	MVENDOR_MULTIGEN,									// vendor
	"SunRaster Image Importer",					// name
	"54385790-3687-11d1-b0ef-00a02495eed5"		// uuid
	);


/****************************************************
*	Byte swapping routines
****************************************************/

static void swapInt ( unsigned long *val )
{
	*val = swap_word ( *val );
}

static void swapshort (short *val )
{
	*val = swap_half ( *val );
}

/****************************************************
*	Runlength encoding decompression 		
****************************************************/

static unsigned int SUNDecodeImage ( unsigned char *compressed_pixels, 
							unsigned char *pixels, unsigned int number_columns, 
							unsigned int number_rows )
{
	register int count;
	register unsigned char *p,*q;
	unsigned char byte;

	p=compressed_pixels;
	q=pixels;
	while ( (unsigned int)(q-pixels) <= ( number_columns*number_rows ) )
	{
    byte=(*p++);
    if (byte != 128)
      *q++=byte;
    else
      {
        /*
          Runlength-encoded packet: <count><byte>
        */
        count=(*p++);
        if (count > 0)
          byte=(*p++);
        while (count >= 0)
        {
          *q++=byte;
          count--;
        }
     }
  }
  return ( MG_TRUE );
}
	
/****************************************************
*	Flip image routine							
*													
*	Sun raster images have their origin in the
*	upper left corner of the image.  MultiGen		
*   images have the origin in the lower left		
*	corner.  So the image must be flipped about	
*	the X (horizontal) axis.					
****************************************************/

static int Flipit ( unsigned char *image, int w, int h, int pad, int bands )
{
	unsigned char *row;
	int rowwidth = w * bands + pad;
	register int i;

	row = ( unsigned char * ) mgMalloc ( rowwidth );
	if ( row == MG_NULL )
		return ( MIMG_MALLOC_ERR );

	for ( i = 0; i < h / 2 + 1; i++ )
	{
		if ( ( h - i ) == i )
			break;
		memcpy ( row , ( image + ( h - i - 1 ) * rowwidth ), rowwidth );
		memcpy ( ( image + ( h - i - 1 ) * rowwidth ),
					( image + i * rowwidth ), rowwidth );
		memcpy ( ( image + i * rowwidth ), row, rowwidth );
	}
	mgFree ( row );

	return ( MIMG_NO_ERROR );
}

/****************************************************
*	Read Sun Raster Header and tell MultiGen
*	about the size and type of the image.
****************************************************/

static int readSunHeader ( FILE *fp, SUNHeader *sun_header )
{
	fseek ( fp, 0, 0 );

	fread ( &sun_header->magic, sizeof ( long ) , 1, fp );

	/*	Verify SUN identifier. */

	swapInt ( &sun_header->magic );
	if ( sun_header->magic != 0x59a66a95 )
	{
		  return ( MIMG_BAD_FILE_TYPE );
	}

	fread ( &sun_header->width, sizeof ( long ) , 1, fp );
	fread ( &sun_header->height, sizeof ( long ) , 1, fp );
	fread ( &sun_header->depth, sizeof ( long ) , 1, fp );
	fread ( &sun_header->length, sizeof ( long ) , 1, fp );
	fread ( &sun_header->type, sizeof ( long ) , 1, fp );
	fread ( &sun_header->maptype, sizeof ( long ) , 1, fp );
	fread ( &sun_header->maplength, sizeof ( long ) , 1, fp );

	swapInt ( &sun_header->width );
	swapInt ( &sun_header->height );
	swapInt ( &sun_header->depth );
	swapInt ( &sun_header->length );
	swapInt ( &sun_header->type );
	swapInt ( &sun_header->maptype );
	swapInt ( &sun_header->maplength );

	return ( MIMG_NO_ERROR );
}

/****************************************************
*													*
*	Texture Open Callback							*
*													*
****************************************************/

static mgstatus sunImgOpen ( mgplugintool pluginTool,
						void *callbackData,
						const char *filename,
						const char *filemode,
						int *imageid )
{
	unsigned long magic;

	if ( NumOpen >= MAXOPENIMGS )
		return ( MIMG_OPEN_ERR );

	if ( filemode[0] != 'r' )
		return ( MIMG_OPEN_ERR );

	OpenFiles [ NumOpen ] = fopen ( filename, filemode );
	if ( !OpenFiles [ NumOpen ] )
		return ( MIMG_OPEN_ERR );

	fread ( &magic, sizeof ( long ), 1, OpenFiles [ NumOpen ] );

	/*	Verify SUN identifier. */

	swapInt ( &magic );
	if ( magic != 0x59a66a95 )
	{
		fclose ( OpenFiles [ NumOpen ] );
		return ( MIMG_BAD_FILE_TYPE );
	}

	*imageid = NumOpen++;

	return ( MIMG_NO_ERROR );
}


/****************************************************
*	Texture Close Callback				
****************************************************/

static mgstatus sunImgClose ( mgplugintool pluginTool,
						 void *callbackData,
						int imageid )
{
	int i;

	if ( ( imageid > -1 ) && ( imageid < MAXOPENIMGS ) &&
			OpenFiles [ imageid ] )
	{
		fclose ( OpenFiles [ imageid ] );
		for ( i = imageid; i < NumOpen - 1; i++ )
		{
			OpenFiles [ i ] = OpenFiles [ i + 1 ];
		}
		NumOpen--;

		return ( MIMG_NO_ERROR );
	}
	return ( MIMG_BAD_DATA );
}


/****************************************************
*	Get Texture Info Callback
****************************************************/

static mgstatus sunImgGetInfo ( mgplugintool pluginTool,
						void *callbackData,
						int imageid,
						mgimageinfo textureInfo )
{
	SUNHeader sun_header;
	char msgstr [ 50 ];
	int status;

	if ( ( imageid > -1 ) && ( imageid < MAXOPENIMGS ) &&
			OpenFiles [ imageid ] )
	{
		/*Read SUN raster header. */

		status = readSunHeader ( OpenFiles [ imageid ], &sun_header );
		if ( status != MIMG_NO_ERROR )
			return ( status );

		sprintf ( msgstr, "Setting width = %d\n", sun_header.width );
		sprintf ( msgstr, "Setting height = %d\n", sun_header.height );

		if ( !mgSetTextureWidth ( textureInfo, sun_header.width ) )
			return ( MIMG_BAD_DATA );
		if ( !mgSetTextureHeight ( textureInfo, sun_header.height ) )
			return ( MIMG_BAD_DATA );
		if ( sun_header.depth == 1 )
		{
			if ( !mgSetTextureType ( textureInfo, MIMG_INT ) )
				return ( MIMG_BAD_DATA );
		}
		else if ( sun_header.depth > 1 && sun_header.depth <= 24 )
		{
			if ( !mgSetTextureType ( textureInfo, MIMG_RGB ) )
				return ( MIMG_BAD_DATA );
		}
		else if ( sun_header.depth == 32 )
		{
			if ( !mgSetTextureType ( textureInfo, MIMG_RGBA ) )
				return ( MIMG_BAD_DATA );
		}
		if ( !mgSetTextureSampleSize ( textureInfo, 8 ) )
			return ( MIMG_BAD_DATA );
		if ( !mgSetTextureTiledFlag ( textureInfo, MG_FALSE ) )
			return ( MIMG_BAD_DATA );

		return ( MIMG_NO_ERROR );
	}
	return ( MIMG_BAD_DATA );
}

/****************************************************
*	Get Texture Texels Callback	
****************************************************/
static int compute_length( int w, int h, int d )
{
	w *= (d/8);
	w += (w%2);
	return h*w;
}

static mgstatus sunImgGetTexels ( mgplugintool pluginTool,
							void *callbackData,
							int imageid,
							int resolution,
							unsigned char *texels )
{
	int bit, i, x, y;
	rgbadatapt q;
	unsigned char *p;
	SUNHeader sun_header;
	unsigned char *sun_data, *sun_pixels;
	unsigned char *gi;
	unsigned int status;
	int colors = 0, iclass;
	int matte, packets;
	colorpacket *colormap = NULL;
	int height, width, type;
	int pad, rowwidth;

	/* check for bogus input from MultiGen */

	if ( ( imageid > -1 ) && ( imageid < MAXOPENIMGS ) &&
			OpenFiles [ imageid ] && texels )
	{
		/* Reread SUN raster header */

		status = readSunHeader ( OpenFiles [ imageid ], &sun_header );
		if ( status != MIMG_NO_ERROR )
			return ( status );

		switch ( sun_header.maptype )
		{
			case RMT_NONE:
			{
				if (sun_header.depth < 24)
				{
					/*
						Create linear color ramp.
					*/
					colors = 1 << sun_header.depth;
            
					colormap = ( colorpacket *) mgMalloc ( colors*sizeof( colorpacket ) );
            
					if ( colormap == MG_NULL )
					{
						return ( MIMG_MALLOC_ERR );
					}
					for (i=0;i<colors;i++)
					{
						colormap[i].red = ( MaxRGB*i )/( colors-1 );
						colormap[i].green = ( MaxRGB*i )/( colors-1 );
						colormap[i].blue = ( MaxRGB*i )/( colors-1 );
					}
				}
				break;
			}
			case RMT_EQUAL_RGB:
			{
				unsigned char *sun_colormap;

				/*
					Read SUN raster colormap.
				*/
				colors=sun_header.maplength/3;
				colormap=( colorpacket * ) mgMalloc ( colors*sizeof( colorpacket ) );
				if ( colormap == MG_NULL )
				{
					return ( MIMG_MALLOC_ERR );
				}
				sun_colormap=(unsigned char *) mgMalloc ( colors*sizeof( unsigned char ) );
				if ( sun_colormap == MG_NULL )
				{
					mgFree ( (char *) colormap );
					return ( MIMG_MALLOC_ERR );
				}
				status = fread ( (char *) sun_colormap, colors, 1, OpenFiles [ imageid ] );
				for (i=0; i < colors; i++)
					colormap[i].red=sun_colormap[i];
				status = fread ( (char *) sun_colormap, colors, 1, OpenFiles [ imageid ] );
				for (i=0; i < colors; i++)
					colormap[i].green=sun_colormap[i];
				status = fread ( (char *) sun_colormap, colors, 1, OpenFiles [ imageid ] );
				for (i=0; i < colors; i++)
					colormap[i].blue=sun_colormap[i];
				mgFree ( (char *) sun_colormap );
				break;
			}
			case RMT_RAW:
			{
				unsigned char *sun_colormap;

				/*
					Read SUN raster colormap.
				*/
				sun_colormap=(unsigned char *) mgMalloc (sun_header.maplength*sizeof(unsigned char));
				if ( sun_colormap == MG_NULL )
				{
					return ( MIMG_MALLOC_ERR );
				}
				fread ( (char *) sun_colormap, 1, (unsigned int) sun_header.maplength, OpenFiles [ imageid ] );
				mgFree ( (char *) sun_colormap );
				break;
			}
			default:
			{
				return ( MIMG_BAD_DATA );
			}
		}

		if ( sun_header.type == RT_OLD ) // Compute the length as it will be set to 0
			sun_header.length = compute_length (sun_header.width, sun_header.height, sun_header.depth);

		sun_data=(unsigned char *) mgMalloc ( sun_header.length*sizeof( unsigned char ) );
		if ( sun_data == MG_NULL )
		{
			return ( MIMG_MALLOC_ERR );
		}
		status = fread ( (char *) sun_data, 1, (unsigned int) sun_header.length, OpenFiles [ imageid ] );
		if ((status == MG_FALSE ) && (sun_header.type != RT_ENCODED ) )
		{
			mgFree ( ( char *) sun_data );
			return ( MIMG_READ_ERR );
		}
      
		sun_pixels = sun_data;
		if ( sun_header.type == RT_ENCODED )
		{
			unsigned int width, height;

			/*
				Read run-length encoded raster pixels.
			*/
			width=sun_header.width*(((sun_header.depth-1) >> 3)+1);
			height=sun_header.height;
			sun_pixels=(unsigned char *) mgMalloc ( width*height*sizeof(unsigned char) );
			if ( sun_pixels == MG_NULL )
			{
				return ( MIMG_MALLOC_ERR );
			}
			(void) SUNDecodeImage ( sun_data, sun_pixels, width, height );
			mgFree ( (char *) sun_data );
		}
		/* Initialize image structure. */
    
		matte = ( sun_header.depth == 32 );
		if ( sun_header.depth == 1 )
		{
			type = MIMG_INT;
		}
		else if ( sun_header.depth > 1 && sun_header.depth <= 24 )
		{
			type = MIMG_RGB;
		}
		else if ( sun_header.depth == 32 )
		{
			type = MIMG_RGBA;
		}
		
		iclass = (sun_header.depth < 24 ? PSEUDOCLASS : DIRECTCLASS );
		width = sun_header.width;
		height = sun_header.height;
		packets=sun_header.width*sun_header.height;

      
		/*
			Convert SUN raster image to MultiGen Image.
			Texels packed as:
				MIMG_RGBA:  RGBARGBARGBA...
				MIMG_RGB:	RGBRGBRGB...
				MIMG_INTA:	IAIAIAIA...
				MIMG_INT:	IIIIIIII...
		*/

		p = sun_pixels;
		q = ( rgbadatapt ) &texels [0];
    
		rowwidth = width * ( type - 1 );
		pad = rowwidth & 3;  /* rowwidth % 4 */
		if ( pad )
		{
			pad = 4 - pad;
		}
		gi = texels;
		if ( sun_header.depth == 1 )
		{
			for (y=0; y < height; y++)
			{
				/*
					Convert bitmap scanline to MIMG_INT.
				*/
				for (x=0; x < ( ( width ) >> 3); x++)
				{
					for (bit=7; bit >= 0; bit--)
					{
						*gi++ = ((*p) & (0x01 << bit) ? 0x00 : 0x01) * 255;
					}
					p++;
				}
				if ( ( (width ) % 8) != 0 )
				{
					for (bit=7; bit >= (8-((width) % 8)); bit--)
					{
						*gi++ = ((*p) & (0x01 << bit) ? 0x00 : 0x01) * 255;
					}
					p++;
				}
				if ( ( ( ( sun_header.width/8)+(sun_header.width % 8 ? 1 : 0 ) ) % 2 ) != 0 )
					p++;
			}
			gi += pad;
		}
		else
		{
			if ( iclass == PSEUDOCLASS )
			{
				int index;
				for (y=0; y < height; y++)
				{	

					/* Convert Color indexed scanline to MIMG_RGB. */
			
					for ( x=0; x < width; x++ )
					{
						index = (*p++);
						if ( colors != 0 )
						{
							*gi++ = colormap[ index ].red;
							*gi++ = colormap[ index ].green;
							*gi++ = colormap[ index ].blue;
						}
						else
							gi += 3;
					}
					if ( ( ( width ) % 2) != 0 )
						p++;
					gi += pad;
				}
			}
			else
			{
				if ( type == MIMG_RGB )
				{
					for (y=0; y < height; y++)
					{

						/* Convert DirectColor scanline to MIMG_RGB. */
			
						for ( x=0; x < width; x++ )
						{
							unsigned char r, g, b;
							if ( sun_header.type == RT_STANDARD )
							{
								b = (*p++);
								g = (*p++);
								r = (*p++);
							}
							else
							{
								r = (*p++);
								g = (*p++);
								b = (*p++);
							}
							if ( colors != 0 )
							{
								*gi++ = colormap[ r ].red;
								*gi++ = colormap[ g ].green;
								*gi++ = colormap[ b ].blue;
							}
							else
							{
								*gi++ = r;
								*gi++ = g;
								*gi++ = b;
							}
						}
						if ( ( ( width ) % 2) != 0 )
							p++;
						gi += pad;
					}
				}
				else		/* RGBA */
				{
					for (y=0; y < height; y++)
					{

						/* Convert DirectColor scanline MIMG_RGBA. */
			
						for ( x=0; x < width; x++ )
						{
							q->alpha = ( unsigned char ) ( matte ? (*p++) : 0 );
							if ( sun_header.type == RT_STANDARD )
							{
								q->blue=(*p++);
								q->green=(*p++);
								q->red=(*p++);
							}
							else
							{
								q->red=(*p++);
								q->green=(*p++);
								q->blue=(*p++);
							}
							if ( colors != 0 )
							{
								q->red = colormap[ q->red ].red;
								q->green = colormap[ q->green ].green;
								q->blue = colormap[ q->blue ].blue;
							}
							q++;
						}
						if ( ( ( ( width ) % 2) != 0 ) && ( matte == MG_FALSE ) )
							p++;
						gi += pad;
					}
				}
			}
		}

		/*  Flip the image */

		if ( Flipit ( texels, width, height, pad, ( type - 1 ) ) )
		{
			return ( MIMG_MALLOC_ERR );
		}

		if ( sun_pixels )   
			mgFree ( ( char * ) sun_pixels );

		if ( colormap )
			mgFree ( ( char * ) colormap );

		return ( MIMG_NO_ERROR );
	}
	return ( MIMG_BAD_DATA );
}

/****************************************************
*	Plugin Init Function	
****************************************************/

MGPIDECLARE(mgbool) mgpInit ( mgplugin plugin, int* argc, char* argv [] )
{
	mgplugintool importer;
	/* Register the texture import callbacks */

	importer = mgRegisterImageImporter ( plugin,
		"SunRaster Image Importer",			/* Tool Name */
		MGP_IMAGEWHOLE,							/* Capability Flags */
		sunImgOpen,									/* Texture Open Callback */
		sunImgClose,								/* Texture Close Callback */
		sunImgGetInfo,								/* Texture Get Info Callback */
		sunImgGetTexels,							/* Texture Get Texels Callback */
		MG_NULL,										/* Callback Data */
		MTA_VERSION, "1.0",						/* Texture Importer Version # */
		MTA_FILTER, "*.ras;*.sun",				/* File Open Filter String */
		MTA_FILETYPE, "Sun Raster",			/* File Open Filter Type String */
		MG_NULL );

	return (importer?MG_TRUE:MG_FALSE);
}
		
/****************************************************
*	Plugin Exit Function	
****************************************************/

MGPIDECLARE(void) mgpExit ( mgplugin plugin )
{
	mgUnregisterAllTools ( plugin );
}

