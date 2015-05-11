#ifndef SCANIMAGE_H
#define SCANIMAGE_H

#include "jpeglib.h"
#include "jerror.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

class ScanImage
{
	//Source file
	char *filename;

	//Quality of JPEG
	int quality = 50;

	//JPEG object
	struct jpeg_decompress_struct cinfo;
	
	//Error manager
	struct my_error_mgr jerr;
	
	FILE *infile;
	JSAMPARRAY buffer;
	int row_stride;

	//Creates a ScanImage from a filename
	ScanImage(char *name)
	{
		filename = name;

		if ((infile = fopen(filename, "rb")) == NULL) {
			fprintf(stderr, "Unable to open %s\n", filename);
			return;
		}


	}
};
#endif