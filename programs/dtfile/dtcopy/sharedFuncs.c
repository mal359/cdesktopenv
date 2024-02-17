/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these libraries and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* $TOG: sharedFuncs.c /main/9 1998/04/06 13:15:57 mgreess $ */
/************************************<+>*************************************
 ****************************************************************************
 *
 *   FILE:           sharedFuncs.c
 *
 *
 *   DESCRIPTION:    Common functions for both dtfile and dtfile_copy
 *
 *   FUNCTIONS: CreateDefaultImage
 *		ImageInitialize
 *		auto_rename
 *		build_path
 *		generate_NewPath
 *		split_path
 *
 *   (c) Copyright 1993, 1994, 1995 Hewlett-Packard Company
 *   (c) Copyright 1993, 1994, 1995 International Business Machines Corp.
 *   (c) Copyright 1993, 1994, 1995 Sun Microsystems, Inc.
 *   (c) Copyright 1993, 1994, 1995 Novell, Inc.
 *
 ****************************************************************************
 ************************************<+>*************************************/

#if defined(SVR4)
#  include <sys/fs/ufs_fs.h>
#  define ROOTINO UFSROOTINO
#endif	/* SVR4 */

#if defined(__linux__) || defined(CSRG_BASED)
#  include <sys/param.h>
#  define ROOTINO 2
#endif


#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <pwd.h>
#include <fcntl.h>
#if !defined(CSRG_BASED) && !defined(__linux__)
#include <ustat.h>
#endif
#if defined(__linux__)
#include <sys/vfs.h>
#include <linux/magic.h>
#endif
#include <dirent.h>


#include <Xm/Xm.h>

#include <Xm/Form.h>
#include <Xm/PushB.h>

#include <Dt/Connect.h>
#include <Dt/DtNlUtils.h>
#include <Dt/SharedProcs.h>

#include "sharedFuncs.h"
#include "dtcopy.h"



/************************************************************************
 *  Bitmap Data for Default Symbol
 **********************************<->***********************************/
#include <X11/bitmaps/xm_error>
#include <X11/bitmaps/xm_information>
#include <X11/bitmaps/xm_question>
#include <X11/bitmaps/xm_warning>
#include <X11/bitmaps/xm_working>

Widget G_toplevel;
int    G_dialog_closed = FALSE;

/*----------------------------------------------------------
 *
 *  split_path
 *
 *  Given a path, return a pointer to the directory (folder)
 *  and file (object). On error, both will be set to empty
 *  strings.
 *
 *  The calling routine is responsible for allocating space
 *  for object and folder.
 *
 *  This function simply searches for the last slash (/) in
 *  the path and returns the characters preceding the slash
 *  as folder and the characters after the last slash as
 *  object. Thus, object could be a directory/folder or a
 *  file.
 *
 *  There is a complimentary function, build_path, to put
 *  object and folder back together to form a path.
 *
 *-----------------------------------------------------------*/

void
split_path(const String path, String folder, String object)

{

   String lastSlash;

   if ( (lastSlash = strrchr(path,'/')) != NULL)
   {
      strcpy(object,lastSlash+1);
      if(lastSlash == path)  /* Must be root Folder */
        strcpy(folder,"/");
      else
      {
        *lastSlash = '\0';
        strcpy(folder,path);
        *lastSlash = '/';
      }
   }
   else
   {
      folder[0] = object[0] = '\0';
   }
}  /* end split_path */

char *
get_path(char *path)
{
    char *rpath, tmppath[MAX_PATH];
    char * _DtCopyPathFromInput();
    if (!getcwd(tmppath,MAX_PATH))
        return NULL;
    rpath = _DtCopyPathFromInput(path,tmppath);
    return rpath;
}

/*-----------------------------------------------------------------
 *
 *  build_path
 *
 *  Given a directory (folder) and file (object), build a string
 *  with the complete path and return it.
 *
 *  The calling routine is responsible for freeing storage used
 *  for the returned string.
 *
 *  There is a complimentary function, split_path, to take
 *  path apart to form folder and object
 *
 *-----------------------------------------------------------------*/

String
build_path(const String folder, const String object)

{
   char    s[MAX_PATH];
   String  path;

   strncpy(s, folder, MAX_PATH);
   strncat(s, "/",    MAX_PATH-strlen(s));
   strncat(s, object, MAX_PATH-strlen(s));
   path = (String) malloc(strlen(s)+1);
   strcpy(path,s);

   return path;

}  /* end build_path */



/*--------------------------------------------------------------
 *
 *  auto_rename
 *
 *  Given a path, generate a new file name and rename the file.
 *
 *  The rc from the system call is returned and errno is set.
 *
 *--------------------------------------------------------------*/

int
auto_rename(const String path)

{
   char newPath[MAX_PATH];

   generate_NewPath(newPath,path);
   errno = 0;
   return (rename(path,newPath));

}  /* end auto_rename */


/*-----------------------------------------------------------------------
 *
 *  generate_NewPath
 *
 *  Given a path (and a complete path is required), append a
 *  sequence number to generate a new file name. The new file
 *  will not exist. The sequence number consists of a one-character
 *  delimiter and an integer. The function will start with
 *  1, if the file with 1 exists it will continue to 2, etc.
 *  newPath and oldPath can point to the same area. The sequence number
 *  is appended to the end of the name unless it contains a
 *  dot, in which case the sequence number precedes the dot. For example,
 *  /cde/dtfile/dtcopy/overwrtdialog.c becomes
 *  /cde/dtfile/dtcopy/overwrtdialog~1.c. However, if the dot
 *  is the first character in the file name, the sequence number is
 *  appended, (e.g. .profile --> .profile~1).
 *
 *-----------------------------------------------------------------------*/

void
generate_NewPath(String newPath, String oldPath)

{

   const char   delim = '_';

   struct stat  buf;
   String       lastDot, lastSlash;
   char         firstPart[MAX_PATH], lastPart[MAX_PATH];
   int          i = 0;
   int          len;


   lastDot   = strrchr(oldPath,'.');
   lastSlash = strrchr(oldPath,'/');
   if (lastSlash == NULL)
      lastSlash = oldPath - 1;   /* allows for no path and first char is dot */
   len = lastDot - oldPath;
   if ( lastDot != NULL &&            /* no dot */
        lastDot > lastSlash+1 &&      /* dot is in filename, not directory name */
        len != strlen(oldPath)-1 )    /* dot is not last character of filename */
   {
      /* sequence number will be inserted before filename suffix */
      memcpy(firstPart,oldPath,len);
      firstPart[len] = '\0';
      strcpy(lastPart,lastDot);
   }
   else
   {
      /* sequence number will be appended to filename */
      strcpy(firstPart,oldPath);
      lastPart[0] = '\0';
   }


   do
   {
      i++;
      sprintf(newPath,"%s%c%d%s",firstPart,delim,i,lastPart);
   } while (lstat(newPath,&buf) == 0);

   return;


}  /* end generate_NewPath */


/****************************************************************
 * Create a default images for symbol... used in ClassInitialize.
 ****************/

XImage *
CreateDefaultImage(
	Display *display,
        char *bits,
        unsigned int width,
        unsigned int height )
{
    XImage *image ;

    image = XCreateImage(display,
			 DefaultVisual(display, DefaultScreen(display)),
			 1, XYBitmap, 0, bits, width, height, 8,
			 (width+7) >> 3);
    image->byte_order = LSBFirst;
    image->bitmap_unit = 8;
    image->bitmap_bit_order = LSBFirst;

    return( image) ;
}  /* end CreateDefaultImage */



void
ImageInitialize( Display *display )
{
    XImage *image;

    /* create and install the default images for the symbol */

    image = CreateDefaultImage (display, (char *)xm_error_bits, xm_error_width,
		    xm_error_height);
    XmInstallImage (image, "default_xm_error");

    image = CreateDefaultImage (display, (char *)xm_information_bits,
		    xm_information_width, xm_information_height);
    XmInstallImage (image, "default_xm_information");

    image = CreateDefaultImage (display, (char *)xm_question_bits,
		    xm_question_width, xm_question_height);
    XmInstallImage (image, "default_xm_question");

    image = CreateDefaultImage (display, (char *)xm_warning_bits,
		    xm_warning_width, xm_warning_height);
    XmInstallImage (image, "default_xm_warning");

    image = CreateDefaultImage (display, (char *)xm_working_bits,
		    xm_working_width, xm_working_height);
    XmInstallImage (image, "default_xm_working");

    return ;
}  /*  end ImageInitialize */

static int
CopyCheckDeletePermissionRecur(
  char *destinationPath)
{
  struct stat statbuf;
  DIR *dirp;
  struct dirent * dp;
  Boolean first_file;
  char *fnamep;

  DPRINTF(("CheckDeletePermissionRecur(\"%s\")\n", destinationPath));

  if (lstat(destinationPath, &statbuf) < 0)
    return -1;  /* probably does not exist */

  if (! S_ISDIR(statbuf.st_mode))
  {
    if(access(destinationPath,04) < 0)
       return -1;
    return 0;   /* no need to check anything more */
  }

  dirp = opendir (destinationPath);
  if (dirp == NULL)
    return -1;  /* could not read directory */


  first_file = True;

  while (dp = readdir (dirp))
  {
    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
    {
      if (first_file)
      {
        /* check for write permission in this directory */
        if (access(destinationPath, 04|02|01) < 0)
        {
            closedir(dirp);
            return -1;
        }

        /* append a '/' to the end of directory name */
        fnamep = destinationPath + strlen(destinationPath);
        *fnamep++ = '/';

        first_file = False;
      }

      /* append file name to end of directory name */
      strcpy(fnamep, dp->d_name);

      /* recursively check permission on this file */
      if (CopyCheckDeletePermissionRecur(destinationPath))
        {
            closedir(dirp);
            return -1;
        }
    }
  }

  closedir(dirp);
  return 0;
}

static int
CopyCheckDeletePermission(
  char *parentdir,
  char *destinationPath)
{
#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__linux__)
  struct statfs statbuf;
#elif defined(__NetBSD__)
  struct statvfs statbuf;
#else
  struct stat statbuf;
#endif
  char fname[PATH_MAX];

#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__linux__)
  if (statfs(parentdir,&statbuf) < 0)  /* does not exist */
#elif defined(__NetBSD__)
  if (statvfs(parentdir,&statbuf) < 0)  /* does not exist */
#else
  if (lstat(parentdir,&statbuf) < 0)  /* does not exist */
#endif
    return -1;

  /* check if we are root */
  if (getuid() == 0)
  {
    /* if NFS, need to check if server trusts root */
#if defined(CSRG_BASED)
    if (!strcmp(statbuf.f_fstypename, "nfs"))  /* Root user and nfs */
#elif defined(__linux__)
    if (statbuf.f_type == NFS_SUPER_MAGIC)
#else
    /* nothing - always check if root */
#endif
    {
       char *tmpfile;
       int rv;
       tmpfile = tempnam(parentdir,"dtfile");
       if (tmpfile)
       {
           /* Create a temporary file */
           if ( (rv = creat(tmpfile,O_RDONLY)) < 0)
           {
               free(tmpfile);
               return -1;
           }
           close(rv);
           /* Delete the created file */
           if (remove(tmpfile) < 0)
           {
               free(tmpfile);
               return -1;
           }

           free(tmpfile);
       }
       else
           return -1;
    }

    /* root user can delete anything */
    return 0;
  }

  /* check for read/write and execute permission on parent dir */
  if (access(parentdir, R_OK | W_OK | X_OK) < 0)
      return -1;

  /* copy destinationPath to tmp buffer */
  strcpy(fname, destinationPath);

  return CopyCheckDeletePermissionRecur(fname);
}

void
CloseTopLevel(
     Widget w,
     void *client_data,
     void *call_data)
{
  XtDestroyWidget((Widget)G_toplevel);
  exit(-1);
}

void
CheckDeleteAccess(
     XtAppContext app_context,
     int delay,
     Boolean checkPerms,
     Boolean move,
     char *source_name)
{
  if(checkPerms && move)
  {
     char title[200],*msg,*tmpmsg;
     char *tmpstring = strdup(source_name),*tmpptr;
     XEvent event;
     int perm_status = 0;

     delay = 10000;
     tmpptr = strrchr(tmpstring,'/');
     if(!tmpstring || !tmpptr)                               /* Error */
       perm_status = 1;
     else
     {
       if(tmpptr == tmpstring)
          tmpptr = "/";
       else
       {
         *tmpptr = '\0';
         tmpptr = tmpstring;
       }
       perm_status = CopyCheckDeletePermission(tmpptr,source_name);
       free(tmpstring);
       tmpstring = NULL;
     }
     if(!perm_status)  /* Everything is fine just return */
     {
         return;
     }

     free(tmpstring);

     strcpy(title,GETMESSAGE(4,7,"Object Trash - Error"));
     tmpmsg =  GETMESSAGE(4,8,"You do not have permission to put the object \n\n%s\n\ninto trash.\n\nUse the Change Permissions choice from the object's\npopup menu or from the Selected menu to turn on your\nRead permission on the object.\n\nNote: If this object is a folder, you must also have\nRead permission for each of the objects inside the\nfolder before you can put the folder in the trash.");

     msg = XtMalloc(strlen(tmpmsg)+strlen(source_name)+2);
     sprintf(msg,tmpmsg,source_name);
     _DtMessageDialog (G_toplevel, title, msg, 0, FALSE, NULL,
         CloseTopLevel, NULL, NULL, False, ERROR_DIALOG);
/*
     XtAppAddTimeOut(app_context, delay, TimeoutHandler, NULL);
*/

    /* wait for user to close the dialog before exiting */
     XtFree(msg);
     while (!G_dialog_closed)
     {
         XtAppNextEvent(app_context, &event);
         XtDispatchEvent(&event);
     }
  }
}

void
TimeoutHandler(XtPointer client_data, XtIntervalId *id)
{
  exit(0);
}

/*
 * This is a generic function for resolving a cannonical path from user input.
 */

char *
_DtCopyPathFromInput(char *input_string, char *current_dir)
{
    char *path = NULL;
    char *tmp_path = NULL;
    int dir_len;
    char *_DtCopyChangeTildeToHome();

    /* find relative path */

    tmp_path = path = XtNewString(input_string);


    /* Strip any spaces from name -- input is overwritten */
    path = (char *) _DtStripSpaces(path);

    /* Resolve, if there're any, environement variables */
    {
        FILE *pfp;
        char command[MAX_PATH];

        sprintf(command,"echo %s",path);
        if((pfp=popen(command,"r")) == NULL)
        {

        }
        else
        {
            if (fscanf(pfp,"%s",command) >= 1)
            {
                XtFree(path);
                path = XtNewString(command);
            }
            else
                path = NULL;

            pclose(pfp);
        }
    }

    if (!path)
        return NULL;

    /* Resolve '~' -- new memory is allocated, old memory is freed */
    if (*path == '~')
        path = _DtCopyChangeTildeToHome(path);

    /* If current dir provided, check for relative path */
    if (path && current_dir)
    {
        if (*path != '/')
        {
            /* file is relative path i.e.      xyz/abc */
            if (strcmp(current_dir, "/") == 0)
            {
                tmp_path = (char *)XtMalloc(strlen(current_dir) + strlen(path) + 1);
                sprintf(tmp_path, "%s%s", current_dir, path);
            }
            else
            {
                tmp_path = (char *)XtMalloc(strlen(current_dir) + strlen(path) + 2);
                sprintf(tmp_path, "%s/%s", current_dir, path);
            }

            XtFree(path);
            path = tmp_path;
            tmp_path = NULL;
        }
    }
    else if (!path)
    {
        XtFree(tmp_path);
        return NULL;
    }

    /* Resolve '.' or '..' -- input is overwritten, output may be NULL! */
    /* Save pointer to path to free if output is NULL.                  */
    tmp_path = path;
    path = (char *) XeEliminateDots(path);

    /* Strip off trailing '/' */
    dir_len = strlen(path);
    if (dir_len > 1 && *(path + dir_len - 1) == '/')
        *(path + dir_len - 1) = '\0';
    return path;
}
char *
#ifdef _NO_PROTO
_DtCopyChangeTildeToHome (input_string)
    char *input_string;
#else
    _DtCopyChangeTildeToHome (
    char *input_string)
#endif
{
    char *path;
    char *full_path;
    struct passwd * pwInfo;
    char * homedir = (char *) XtNewString(getenv("HOME"));

    if ((input_string[1] != '/'))
    {
        char *path;

        /* ~user or ~user/path format */

        /* is there a path? */
        path = (char *) DtStrchr(input_string, '/');

        /* find user */
        if (path)
            *path = '/';
        if ((pwInfo = getpwnam(input_string + 1)) == NULL)
        {
            /* user doesn't exist */
            if (path)
                *path = '/';
            return NULL;
        }

        if (path)
        {
            /* ~user/path format */

            *path = '/';

            if (strcmp(pwInfo->pw_dir, "/") == 0)
            {
                /* We don't want to end up with double '/' in the path */
                full_path = (char *) XtMalloc(strlen(path) + 1);
                strcpy(full_path, path);
            }
            else
            {
                full_path = (char *) XtMalloc(strlen(pwInfo->pw_dir) +
                                              strlen(path) + 1);
                sprintf(full_path, "%s%s", pwInfo->pw_dir, path);
            }
        }
        else
        {
            /* ~user format */

            full_path = XtMalloc(strlen(pwInfo->pw_dir) + 1);
            strcpy(full_path, pwInfo->pw_dir);
        }
    }
    else if (input_string[1])
    {
        /* ~/path format */

        /* NOTE: users_home_dir has trailing '/' */
        full_path = (char *) XtMalloc(strlen(homedir) + strlen(input_string+2) + 1);
        sprintf(full_path, "%s%s", homedir, (input_string + 2));
    }
    else
    {

        /* ~ format */

        full_path = XtMalloc(strlen(homedir) + 1);
        strcpy(full_path, homedir);
    }

    XtFree(homedir);
    XtFree(input_string);
    return(full_path);
}

int
Check(char *spth, char *dpth, int mode)
{
    struct stat sbuf, dbuf;
    char filename [MAX_PATH];
    char * msg;
    char * tmpStr;
    char title[300];

    sbuf.st_ino = 0;
    if (lstat (spth, &sbuf) < 0)
    {
        tmpStr = (GETMESSAGE(4,9, "Cannot open %s"));
        msg = XtMalloc(strlen(tmpStr)+strlen(filename)+1);
        sprintf(msg,tmpStr,filename);
        _DtMessageDialog (G_toplevel, title, msg, 0, FALSE, NULL,
                          CloseTopLevel, NULL, NULL, False, ERROR_DIALOG);
        XtFree(msg);
        return 0;
    }
    (void) strcpy (filename, dpth);
    if(mode)
        strcpy(title,GETMESSAGE(4,5,"Object Move - Error"));
    else
        strcpy(title,GETMESSAGE(4,6,"Object Copy - Error"));

    dbuf.st_ino = 0;
    while (dbuf.st_ino != ROOTINO)
    {
        /* Destination may not be available, in which case we need to
           create it, so just return as successful and the remaining
           code takes care of everything */

        if (lstat (filename, &dbuf) < 0)
            return 0;

        if (dbuf.st_ino == sbuf.st_ino)
        {
            if(mode)
                tmpStr = GETMESSAGE(3,19,"Cannot move folder into itself. %s");
            else
                tmpStr = GETMESSAGE(3,20,"Cannot copy folder into itself. %s");
            msg = XtMalloc(strlen(tmpStr)+strlen(dpth)+1);
            sprintf(msg,tmpStr,dpth);
            _DtMessageDialog (G_toplevel, title, msg, 0, FALSE, NULL,
                              CloseTopLevel, NULL, NULL, False, ERROR_DIALOG);

            XtFree(msg);
            return(1);
        }

        (void) strcat (filename, "/..");
    }

    return(0);
}
