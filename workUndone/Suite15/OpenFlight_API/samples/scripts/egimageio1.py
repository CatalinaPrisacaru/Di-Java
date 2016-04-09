##
##
##  Sample file: egimageio1.py
##
##  Objective: Show how to access and manipulate an image.
##
##  Program functions: Reads an image from the command line.
##     Swaps the channels of the image.
##     Writes the swapped image.
##   
##  API functions used:
##     mgInit(), mgExit(),
##     mgReadImage(), mgWriteImage(),
##     mgReadImageAttributes(), mgWriteImageAttributes(),
##
##
##

import sys

# import OpenFlight API module 
from mgapilib import *

def SwapChannels (pixels, newpixels, type, width, height):

	size = width * height

	if type == MIMG_INT: # intensity - 1 channel - no need to swap 
		for i in range (0, size * (type - 1)):
			newpixels[i] = pixels[i]
		return MG_TRUE, newpixels

	elif type == MIMG_INTA:     # intensity alpha - 2 channels 
		iptr1 = 0
		iptr2 = size
		optr1 = 0
		optr2 = size
		i = size
		for i in range (size, 0, -1):
			newpixels[optr1] = pixels[iptr2]
			newpixels[optr2] = pixels[iptr1]
			iptr1 = iptr1 + 1
			iptr2 = iptr2 + 1
			optr1 = optr1 + 1
			optr2 = optr2 + 1
		return MG_TRUE, newpixels

	elif type == MIMG_RGB:     # RGB - 3 channels - only need to swap channels 1 & 3 
		iptr1 = 0
		iptr2 = size
		iptr3 = 2*size
		optr1 = 0
		optr2 = size
		optr3 = 2*size
		for i in range (size, 0, -1):
			newpixels[optr1] = pixels[iptr3]
			newpixels[optr2] = pixels[iptr2]
			newpixels[optr3] = pixels[iptr1]
			iptr1 = iptr1 + 1
			iptr2 = iptr2 + 1
			iptr3 = iptr3 + 1
			optr1 = optr1 + 1
			optr2 = optr2 + 1
			optr3 = optr3 + 1
		return MG_TRUE, newpixels
 
	elif type == MIMG_RGBA:     # RGBA - 4 channels 
		# Note the different way the channels are stored 
		iptr1 = 0
		optr1 = 0
		for i in range (size, 0, -1):
			newpixels[optr1] = pixels[iptr1+3]
			newpixels[optr1+1] = pixels[iptr1+2]
			newpixels[optr1+2] = pixels[iptr1+1]
			newpixels[optr1+3] = pixels[iptr1]
			iptr1 = iptr1 + 4
			optr1 = optr1 + 4
		return MG_TRUE, newpixels
  
	else:
		return MG_FALSE, newpixels
		
	return MG_FALSE, newpixels

def main ():

	# check for correct number of arguments 
	if len(sys.argv) < 3:
		print "\nUsage: ", sys.argv[0], " <input_texture_filename> <output_texture_filename>\n"
		return

   # initialize the OpenFlight API
   # always call mgInit BEFORE any other OpenFlight API calls 
   #
	mgInit (None, None)

	# Read the input image, pixels is allocated 
	status, pixels, type, width, height = mgReadImage (sys.argv[1])

	if status:
		print "Error reading image: ",sys.argv[1], "status:", status, "\n"
		return

	# Read the input image attributes 
	imgAttrRec = mgReadImageAttributes (sys.argv[1])

	if not imgAttrRec:
		print "Error reading image attributes for: ",sys.argv[1], "\n"
		return

	newpixels = mgunsignedchar(width * height * (type - 1))
	if not newpixels:
		print "Error allocating memory for swapped image\n"
		return

	# Swap the channels 
	if not SwapChannels (pixels, newpixels, type, width, height):
		print "Error swapping the channels\n"
		return

	# Write the swapped image 
	status = mgWriteImage (sys.argv[2], newpixels, type, width, height, MG_FALSE)
	if status:
		print "Error writing image: ",sys.argv[2], "\n"
		return

	# Write the swapped image attributes 
	if not mgWriteImageAttributes (sys.argv[2], imgAttrRec):
		print "Error writing image attributes for: ",sys.argv[2], "\n"
		return

	# always call mgExit() AFTER all OpenFlight API calls 
	mgExit ()

main()
