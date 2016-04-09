/*******************************************************************************

  Sample file: EGIMAGEIO1.C

  Objective: Show how to access and manipulate an image.

  Program functions: Reads an image from the command line.
     Swaps the channels of the image.
     Writes the swapped image.
   
  API functions used:
     mgInit(), mgExit(),
     mgReadImage(), mgWriteImage(),
     mgReadImageAttributes(), mgWriteImageAttributes(),
	  mgMalloc(), mgFree()

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

static int SwapChannels (unsigned char* pixels, unsigned char* newpixels,
									int type, int width, int height)
{
   unsigned char *iptr1, *iptr2, *iptr3;
   unsigned char *optr1, *optr2, *optr3;
   int i, size;

   size = width * height;
   switch (type)
   {
   case MIMG_INT:     /* intensity - 1 channel - no need to swap */
      memcpy (newpixels, pixels, size * (type -1));
      return (MG_TRUE);
		break;
   
	case MIMG_INTA:     /* intensity alpha - 2 channels */
      iptr1 = pixels;
      iptr2 = pixels + size;
      optr1 = newpixels;
      optr2 = newpixels + size;
      i = size;
      while (i--)
      {
         *optr1++ = *iptr2++;
         *optr2++ = *iptr1++;
      }
      return (MG_TRUE);
		break;
   
	case MIMG_RGB:     /* RGB - 3 channesl - only need to swap channels 1 & 3 */
      iptr1 = pixels;
      iptr2 = pixels + size;
      iptr3 = pixels + 2*size;
      optr1 = newpixels;
      optr2 = newpixels + size;
      optr3 = newpixels + 2*size;
      i = size;
      while (i--)
      {
         *optr1++ = *iptr3++;
         *optr2++ = *iptr2++;
         *optr3++ = *iptr1++;
      }
      return (MG_TRUE);
		break;
 
	case MIMG_RGBA:     /* RGBA - 4 channels */
		/* Note the different way the channels are stored */
      iptr1 = pixels;
      optr1 = newpixels;
      i = size;
      while (i--)
      {
         *optr1 = *(iptr1+3);
         *(optr1+1) = *(iptr1+2);
         *(optr1+2) = *(iptr1+1);
         *(optr1+3) = *iptr1;
         iptr1 += 4;
         optr1 += 4;
      }
      return (MG_TRUE);
		break;
  
	default:
      return (MG_FALSE);
		break;
   }
	return (MG_FALSE);
}

int main (int argc, char* argv[])
{
   int type, width, height, status;
   unsigned char *pixels, *newpixels;
   mgrec* imgAttrRec;

   /* check for proper arguments */
   if (argc < 3) {
      printf ("\nUsage: %s <input_texture_filename> <output_texture_filename>\n", argv[0]);
      exit (0);
   }

   /* initialize the OpenFlight API
      always call mgInit BEFORE any other OpenFlight API calls 
      */
   mgInit (&argc, argv);

   /* Read the input image, pixels is allocated, remember to mgFree */
   status = mgReadImage (argv[1], &pixels, &type, &width, &height);

   if (status != 0) {
		printf ("Error reading image: %s\n", argv[1]);
      exit (EXIT_FAILURE);
   }

   /* Read the input image attributes */
   imgAttrRec = mgReadImageAttributes (argv[1]);

   if (imgAttrRec == NULL) {
      printf ("Error reading image attributes for: %s\n", argv[1]);
      exit (EXIT_FAILURE);     
   }

   /* Allocate the swapped image */
   newpixels = (unsigned char*) mgMalloc (width * height * (type -1));
   if (!newpixels) {
      printf ("Error allocating memory for swapped image\n");
      exit (EXIT_FAILURE);     
   }

   /* Swap the channels */
   if (!SwapChannels (pixels, newpixels, type, width, height)) {
      printf ("Error swapping the channels\n");
      exit (EXIT_FAILURE);     
   }

   /* Write the swapped image */
   status = mgWriteImage (argv[2], newpixels, type, width, height, MG_FALSE);
   if (status != 0) {
		printf ("Error writing image: %s\n", argv[2]);
      exit (EXIT_FAILURE);
   }

   /* Write the swapped image attributes */
   if (!mgWriteImageAttributes (argv[2], imgAttrRec)) {
      printf ("Error writing image attributes for: %s\n", argv[2]);
      exit (EXIT_FAILURE);     
   }

   mgFree (pixels);
   mgFree (newpixels);

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}
