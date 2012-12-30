#pragma once

#include	<windows.h>										// Header File For Windows
#include	<stdio.h>										// Header File For Standard Input / Output
#include	<stdarg.h>										// Header File For Variable Argument Routines
#include	<string.h>										// Header File For String Management
#include	<gl\gl.h>										// Header File For The OpenGL32 Library
#include	<gl\glu.h>										// Header File For The GLu32 Library

typedef struct												// Create A Structure
{
	GLubyte	*imageData;										// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
} TextureImage;												// Structure Name


class TgaTextureLoader
{
public:
    static bool TgaTextureLoader::LoadTgaTexture(TextureImage *texture, char *filename);
};

