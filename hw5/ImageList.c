/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

static IENTRY *NewImageEntry(void)
{ 
	IENTRY *e;
	e = malloc(sizeof(IENTRY));
	if (! e)
	{ 
		perror("Out of memory! Aborting...");
		exit(10);
	}
	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;
	e->RGBImage = NULL;
	e->YUVImage = NULL;
	return e;
}

static void DeleteImageEntry(IENTRY *e)
{ 
	assert(e);
	e->List = NULL;
	e->Next = NULL;
	e->Prev = NULL;

	if(e->RGBImage)
	{
		DeleteImage(e->RGBImage);
		e->RGBImage = NULL;
	}
	if(e->YUVImage)
	{
		DeleteYUVImage(e->YUVImage);
		e->YUVImage = NULL;
	}
	free(e);
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *list;
	list = malloc(sizeof(ILIST));
	if (! list)
	{
		perror("Out of memory! Aborting...");
		exit(10);
	}
	list->Length = 0;
	list->First = NULL;
	list->Last = NULL;
	return list;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	assert(list);
	assert(list->Length);
	assert(list->First);
	
	IENTRY *currentEntry, *nextEntry;

	assert(list);
	currentEntry = list->First;
	while(currentEntry)
	{
		nextEntry = currentEntry->Next;
		DeleteImageEntry(currentEntry);
		currentEntry = nextEntry;
	}
	free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	assert(list);
	assert(RGBimage);

	IENTRY *entry = NewImageEntry();
	
	entry->RGBImage = RGBimage; 
	entry->List = list;

	if (list->Last)
	{
		entry->Prev = list->Last;
		list->Last->Next = entry;
		list->Last = entry;
	}
	else
	{
		entry->Prev = NULL;
		list->First = entry;
		list->Last = entry;
	}
	list->Length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
	assert(list);
        assert(YUVimage);

        IENTRY *entry = NewImageEntry();

        entry->YUVImage = YUVimage;
        entry->List = list;
        entry->Next = NULL;

        if (list->Last)
        {
                entry->Prev = list->Last;
                list->Last->Next = entry;
                list->Last = entry;
        }
        else
        {
                entry->Prev = NULL;
                list->First = entry;
                list->Last = entry;
        }
        list->Length++;
}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
	assert(list);
	/* to be implemented */
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	assert(list);	
	/* to be implemented */
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	assert(list);
	/* to be implemented */
}

/* EOF */
