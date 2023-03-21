/* basename.c
 *
 * $Id: basename.c,v 1.2 2007/03/08 23:15:58 keithmarshall Exp $
 *
 * Provides an implementation of the "basename" function, conforming
 * to SUSv3, with extensions to accommodate Win32 drive designators,
 * and suitable for use on native Microsoft(R) Win32 platforms.
 *
 * Written by Keith Marshall <keithmarshall@users.sourceforge.net>
 *
 * This is free software.  You may redistribute and/or modify it as you
 * see fit, without restriction of copyright.
 *
 * This software is provided "as is", in the hope that it may be useful,
 * but WITHOUT WARRANTY OF ANY KIND, not even any implied warranty of
 * MERCHANTABILITY, nor of FITNESS FOR ANY PARTICULAR PURPOSE.  At no
 * time will the author accept any form of liability for any damages,
 * however caused, resulting from the use of this software.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <locale.h>

#ifndef __cdecl
#define __cdecl
#endif

char *__cdecl basename(char *path)
{
	static char *retfail = NULL;
	size_t len;

	if (path && *path)
	{
		/* allocate sufficient local storage space,
		 * in which to create a  character reference copy of path
		 */
		char refcopy[1 + strlen(path)];
		/* create the character reference copy of path,
		 * and step over the drive designator, if present ...
		 */
		char *refpath = strcpy(refcopy, path);

		if ((len = strlen(refpath)) > 1 && refpath[1] == ':')
		{
			/* FIXME: maybe should confirm *refpath is a valid drive designator */
			refpath += 2;
		}
		/* ensure that our character reference path is NUL terminated */
		refcopy[len] = '\0';
		/* check again, just to ensure we still have a non-empty path name ... */
		if (*refpath)
		{
			/* and, when we do, process it  ...
			 * scanning from left to right, to the char after the final dir separator.  */
			char *refname;

			for (refname = refpath; *refpath; ++refpath)
			{
				if (*refpath == '/' || *refpath == '\\')
				{
					/* we found a dir separator ...
					 * step over it, and any others which immediately follow it.  */
					while (*refpath == '/' || *refpath == '\\')
						++refpath;
					/* if we didn't reach the end of the path string ... */
					if (*refpath)
						/* then we have a new candidate for the base name.  */
						refname = refpath;
					/* otherwise ...
					 * strip off any trailing dir separators which we found.  */
					else
						while (refpath > refname && (*--refpath == '/' || *refpath == '\\'))
							*refpath = '\0';
				}
			}

			/* refname now points at the resolved base name ...  */
			if (*refname)
			{
				/* if it's not empty,
				 * then we skip over the dirname,
				 * to return the resolved basename.  */
				if ((len = strlen(strcpy(path, refcopy))) != 0)
					path[len] = '\0';
				*refname = '\0';
				if ((len = strlen(refcopy)) != 0)
					path += len;
			}
			else
			{
				/* the basename is empty, so return the default value of "/", and
				 * returning it in our own buffer.  */
				retfail = "/";
			}
			/*  return the result */
			return path;
		}
		/* or we had an empty residual path name, after the drive designator,
		 * in which case we simply fall through ...  */
	}
	/* and, if we get to here ...
	 * the path name is either NULL, or it decomposes to an empty string;
	 * in either case, we return the default value of "." in our own buffer,
	 * reloading it with the correct value, just in case the caller trashed it
	 * after a previous call.
	 */
	retfail = ".";

	/* eturn the result.  */
	return retfail;
}
