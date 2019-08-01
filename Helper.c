#include"Header.h"

UFDT UFDTArr[MAXINODE];
SUPERBLOCK SUPERBLOCKobj;
PINODE head;

///////////////////////////////////////////////////////////////////////////////
//
//  Name :          CreateDILB
//  INPUT :         NONE
//  OUTPUT :        NONE
//  Description :   This fucntion is used to create Disk Inode List Block
//
////////////////////////////////////////////////////////////////////////////////

void
CreateDILB ()
{
  int i = 1;
  PINODE temp = head;
  while (i <= MAXINODE)
    {
      PINODE newn = NULL;
      newn = (PINODE) malloc (sizeof (INODE));
      newn->InodeNumber = i;
      newn->LinkCount = 0;
      newn->ReferenceCount = 0;
      newn->FileType = 0;
      newn->FileSize = 0;
      newn->ActualFileSize = 1024;
      newn->Buffer = NULL;
      newn->next = NULL;
      if (temp == NULL)
	{
	  head = newn;
	  temp = head;
	}
      else
	{
	  while (NULL != temp->next)
	    {
	      temp = temp->next;
	    }
	  temp->next = newn;
	}
      i++;
    }
  printf ("CreateDILB is Successfull\n");
}

///////////////////////////////////////////////////////////////////////////////
//
//  Name :          InitialiseSuperBlock
//  INPUT :         NONE
//  OUTPUT :        NONE
//  Description :   This fucntion is used to initialise super block and UFDT
//
///////////////////////////////////////////////////////////////////////////////

void
InitialiseSuperBlock ()
{

  int i = 0;
  while (i < 50)
    {
      UFDTArr[i].ptrfiletable = NULL;
      i++;
    }


  SUPERBLOCKobj.TotalInodes = MAXINODE;


  SUPERBLOCKobj.FreeInodes = MAXINODE;


  printf ("Superblock is Successfull\n");


}

///////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :              Get_Inode
//  INPUT:              CHARACTER POINTER
//  OUTPUT :            STRUCTURE POINTER
//  Description :       This function is used to check if file with same name is already in
//                      file system or not
//
///////////////////////////////////////////////////////////////////////////////////////////



PINODE
Get_Inode (char *name)
{


  PINODE temp = head;


  int i = 0;


  if (name == NULL)


    return NULL;


  while (temp != NULL)


    {


      if (strcmp (name, temp->FileName) == 0)


	break;


      temp = temp->next;


    }


  return temp;


}


////////////////////////////////////////////////////////////////////////////////
//
//  Name :          CreateFile
//  Input :         CHARACTER POINTER, INTEGER
//  Output :        INTEGER
//  Description :   This function is used to create file
//
////////////////////////////////////////////////////////////////////////////////


int
CreateFile (char *name, int permission)
{


  if (name == NULL || permission < 0 || permission > 3)


    {


      return -1;


    }



  PINODE temp = head;


  int i = 1, j = 0;


  if (SUPERBLOCKobj.FreeInodes == 0)


    {


      return -2;


    }


  if (Get_Inode (name) != NULL)


    {


      return -3;


    }


  for (j = 0; j < 50; j++)


    {


      if (UFDTArr[j].ptrfiletable == NULL)


	{


	  break;


	}


    }


  while (temp != NULL)


    {


      if (temp->FileType == 0)


	{


	  break;


	}


      temp = temp->next;


    }



  UFDTArr[j].ptrfiletable = (PFILETABLE) malloc (sizeof (FILETABLE));


  if (UFDTArr[j].ptrfiletable == NULL)


    {


      return -4;


    }


  UFDTArr[j].ptrfiletable->ptrinode = temp;


  UFDTArr[j].ptrfiletable->readoffset = 0;


  UFDTArr[j].ptrfiletable->writeoffset = 0;


  UFDTArr[j].ptrfiletable->count = 1;


  UFDTArr[j].ptrfiletable->mode = permission;



  std::copy (name, name + 20, UFDTArr[j].ptrfiletable->ptrinode->FileName);


  UFDTArr[j].ptrfiletable->ptrinode->FileType = REGULAR;


  UFDTArr[j].ptrfiletable->ptrinode->InodeNumber = i;


  UFDTArr[j].ptrfiletable->ptrinode->ActualFileSize = 0;


  UFDTArr[j].ptrfiletable->ptrinode->FileSize = MAXFILESIZE;


  UFDTArr[j].ptrfiletable->ptrinode->LinkCount = 1;


  UFDTArr[j].ptrfiletable->ptrinode->ReferenceCount = 1;


  UFDTArr[j].ptrfiletable->ptrinode->Permission = permission;


  UFDTArr[j].ptrfiletable->ptrinode->Buffer =
    (char *) malloc (sizeof (MAXFILESIZE));



  (SUPERBLOCKobj.FreeInodes)--;

  return j;


}

///////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :              man
//  INPUT:              NONE
//  OUTPUT :            NONE
//  Description :       This function is used to display manual of commands used
//
///////////////////////////////////////////////////////////////////////////////////////////


void
man (char *name)
{


  if (name == NULL)


    {


      return;


    }


  if (strcmp (name, "create") == 0)


    {


      printf ("Description : Used to create new regular file\n");


      printf ("Usage : create File_name Permission\n");


    }


  else if (strcmp (name, "read") == 0)


    {


      printf ("Description : Used to read data from regular file\n");


      printf ("Usage : read File_name No_Of_Bytes_To_Read\n");


    }


  else if (strcmp (name, "write") == 0)


    {


      printf ("Description : Used to write into regular file\n");


      printf
	("Usage : write File_name\n After this enter the data that we want to write\n");


    }


  else if (strcmp (name, "ls") == 0)


    {


      printf ("Description : Used to list all information of files\n");


      printf ("Usage : ls\n");


    }


  else if (strcmp (name, "stat") == 0)


    {


      printf ("Description : Used to display information of file\n");


      printf ("Usage : stat File_name\n");


    }


  else if (strcmp (name, "fstat") == 0)


    {


      printf ("Description : Used to display information of file\n");


      printf ("Usage : stat File_Descriptor\n");


    }


  else if (strcmp (name, "truncate") == 0)


    {


      printf ("Description : Used to remove data from file\n");


      printf ("Usage : truncate File_name\n");


    }


  else if (strcmp (name, "open") == 0)


    {


      printf ("Description : Used to open existing file\n");


      printf ("Usage : open File_name mode\n");


    }


  else if (strcmp (name, "close") == 0)


    {


      printf ("Description : Used to close opened file\n");


      printf ("Usage : close File_name\n");


    }


  else if (strcmp (name, "closeall") == 0)


    {


      printf ("Description : Used to close all opened file\n");


      printf ("Usage : closeall\n");


    }


  else if (strcmp (name, "lseek") == 0)


    {


      printf ("Description : Used to change file offset\n");


      printf ("Usage : lseek File_Name ChangeInOffset StartPoint\n");


    }


  else if (strcmp (name, "rm") == 0)


    {


      printf ("Description : Used to delete the file\n");


      printf ("Usage : rm File_Name\n");


    }


  else


    {


      printf ("ERROR : No manual entry available.\n");


    }


}


///////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :              DisplayHelp
//  INPUT:              NONE
//  OUTPUT :            NONE
//  Description :       This function is used to display system calls used in project
//
//////////////////////////////////////////////////////////////////////////////////////////

void
DisplayHelp ()
{


  printf ("ls : To List out all files\n");


  printf ("clear : To clear console\n");


  printf ("open : To open the file\n");


  printf ("close : To close the file\n");


  printf ("closeall : To close all opened files\n");


  printf ("read : To Read the contents from file\n");


  printf ("write :To Write contents into file\n");


  printf ("exit : To Terminate file system\n");


  printf ("stat : To Display information of file using name\n");


  printf ("fstat :To Display information of file using file descriptor\n");


  printf ("truncate : To Remove all data from file\n");


  printf ("rm : To Delete the file\n");


}


/////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          ls_file
//  Input :         NONE
//  Output :        NONE
//  Description :   This function is used display files from DILB
//
/////////////////////////////////////////////////////////////////////////////////////////


void
ls_file ()
{


  PINODE temp = head;


  while (temp != NULL)


    {


      if (temp->FileType != 0)


	{


	  printf ("%s", temp->FileName);


	  printf ("\n");


	}


      temp = temp->next;


    }


}


/////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          fstat_file
//  Input :         INTEGER
//  Output :        INTEGER
//  Description :   This function is used display statastical information about file
//                  from file descriptor
//
/////////////////////////////////////////////////////////////////////////////////////////



int
fstat_file (int fd)
{


  if (fd > MAXINODE || fd < 0)


    {


      return -1;


    }



  int i = 0;


  PINODE temp = head;


  if (UFDTArr[fd].ptrfiletable == NULL)


    return -2;



  temp = UFDTArr[fd].ptrfiletable->ptrinode;



  printf ("\n-------Statistical Information about File--------\n");


  printf ("File name: %s\n", temp->FileName);


  printf ("Inode Number: %d\n", temp->InodeNumber);


  printf ("File Size: %d\n", temp->FileSize);


  printf ("Actual File Size: %d\n", temp->ActualFileSize);


  printf ("Link Count: %d\n", temp->LinkCount);


  printf ("Reference Count: %d\n", temp->ReferenceCount);



  if (temp->Permission == 1)


    printf ("File Permission: Read Only\n");


  else if (temp->Permission == 2)


    printf ("File Permission: Write\n");


  else if (temp->Permission == 3)


    printf ("File Permission: Read & Write\n");



}

/////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          stat_file
//  Input :         CHARACTER POINTER
//  Output :        INTEGER
//  Description :   This function is used display statastical information about file
//
/////////////////////////////////////////////////////////////////////////////////////////


int
stat_file (char *name)
{


  if (name == NULL)


    {


      return -1;


    }


  PINODE temp = head;


  if (temp == NULL)


    {


      return -2;


    }


  while (temp != NULL)


    {


      if (strcmp (temp->FileName, name) == 0)


	{


	  printf
	    ("FileName: %s\nInodeNumber: %d\nFileSize: %d\nActualFileSize: %d\nFileType: %d\nLinkCount: %d\nReferenceCount: %d\nPermission: %d",
	     temp->FileName, temp->InodeNumber, temp->FileSize,
	     temp->ActualFileSize, temp->FileType, temp->LinkCount,
	     temp->ReferenceCount, temp->Permission);


	}


      temp = temp->next;


    }



}

///////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :              GetFDFromName
//  INPUT:              CHARACTER POINTER
//  OUTPUT :            INTEGER
//  Description :       This function is used to get file descriptor from file name
//
///////////////////////////////////////////////////////////////////////////////////////////


int
GetFDFromName (char *name)
{


  int i = 0;


  while (i < MAXINODE)


    {


      if (UFDTArr[i].ptrfiletable != NULL)


	if (strcmp ((UFDTArr[i].ptrfiletable->ptrinode->FileName), name) == 0)


	  break;


      i++;


    }


  if (i == MAXINODE)

    return -1;


  else

    return i;


}


/////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          removexx
//  Input :         CHARACTER POINTER
//  Output :        INTEGER
//  Description :   This function is used to delete/remove file from file from 
//                  file descriptor
//
/////////////////////////////////////////////////////////////////////////////////////////



int
removexx (char *name)
{


  int fd = 0;


  fd = GetFDFromName (name);


  if (fd == -1)


    {


      return -1;


    }


  free (UFDTArr[fd].ptrfiletable->ptrinode->Buffer);


  UFDTArr[fd].ptrfiletable->ptrinode->Buffer = NULL;


  (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount)--;



  if (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount == 0)


    {


      UFDTArr[fd].ptrfiletable->ptrinode->ReferenceCount = 0;


      UFDTArr[fd].ptrfiletable->ptrinode->FileType = 0;


      strncpy (UFDTArr[fd].ptrfiletable->ptrinode->FileName, "\0",
	       sizeof (UFDTArr[fd].ptrfiletable->ptrinode->FileName));


      free (UFDTArr[fd].ptrfiletable);


      UFDTArr[fd].ptrfiletable = NULL;


    }


  (SUPERBLOCKobj.FreeInodes)++;


  return 1;


}

/////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          write
//  Input :         INTEGER, CHARACTER POINTER, INTEGER
//  Output :        INTEGER
//  Description :   This function is used to write data into the file
//
/////////////////////////////////////////////////////////////////////////////////////////


int
write (int fd, char *name, int isize)
{


  if (((UFDTArr[fd].ptrfiletable->mode) != WRITE)
      && ((UFDTArr[fd].ptrfiletable->mode) != READWRITE))


    return -1;


  if (((UFDTArr[fd].ptrfiletable->ptrinode->Permission) != WRITE)
      && ((UFDTArr[fd].ptrfiletable->ptrinode->Permission) != READWRITE))


    return -1;


  if ((UFDTArr[fd].ptrfiletable->writeoffset) == MAXFILESIZE)


    return -2;


  if ((UFDTArr[fd].ptrfiletable->ptrinode->FileType) != REGULAR)


    return -3;


  strncpy ((UFDTArr[fd].ptrfiletable->ptrinode->Buffer) +
	   (UFDTArr[fd].ptrfiletable->writeoffset), name, isize);


  (UFDTArr[fd].ptrfiletable->writeoffset) =
    (UFDTArr[fd].ptrfiletable->writeoffset) + isize;


  (UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize) =
    (UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize) + isize;


  return isize;


}

/////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          Exitxx
//  Input :         NONE
//  Output :        NONE
//  Description :   This function is used to deallocate resources before terminating
//
/////////////////////////////////////////////////////////////////////////////////////////


void
Exitxx ()
{


  int i = 0;


  while (i < MAXINODE)


    {


      if (UFDTArr[i].ptrfiletable != NULL)


	{


	  free (UFDTArr[i].ptrfiletable);


	  UFDTArr[i].ptrfiletable = NULL;


	}


      i++;


    }


  PINODE temp1 = head;


  i = 1;


  while (i <= MAXINODE)


    {


      if (temp1->Buffer != NULL)


	{


	  free (temp1->Buffer);


	}


      temp1 = temp1->next;


      i++;


    }


  PINODE temp = head;


  while (head != NULL)


    {


      head = head->next;


      free (temp);


      temp = head;


    }


}

/////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          read
//  Input :         INTEGER, CHARACTER POINTER, INTEGER
//  Output :        INTEGER
//  Description :   This function is used to read data from file
//
/////////////////////////////////////////////////////////////////////////////////////////



int
read (int fd, char *name, int bytes)
{


  if (UFDTArr[fd].ptrfiletable == NULL)


    return -1;


  if (UFDTArr[fd].ptrfiletable->mode != READ
      && UFDTArr[fd].ptrfiletable->mode != READWRITE)


    return -2;


  if (UFDTArr[fd].ptrfiletable->ptrinode->Permission != READ
      && UFDTArr[fd].ptrfiletable->ptrinode->Permission != READWRITE)


    return -2;


  if (UFDTArr[fd].ptrfiletable->readoffset ==
      UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize)


    return -3;


  if (UFDTArr[fd].ptrfiletable->ptrinode->FileType != REGULAR)


    return -4;



  int len = 0;


  len = strlen (UFDTArr[fd].ptrfiletable->ptrinode->Buffer);


  if (bytes >= UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize)


    {


      memset (name + 0, '\0', MAXFILESIZE * sizeof (char));


      strncpy (name,
	       UFDTArr[fd].ptrfiletable->ptrinode->Buffer +
	       UFDTArr[fd].ptrfiletable->readoffset,
	       UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize);


      UFDTArr[fd].ptrfiletable->readoffset = 0;


      return 0;


    }


  else if (bytes < UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize)


    {


      len = strlen (UFDTArr[fd].ptrfiletable->ptrinode->Buffer) - (bytes);


      memset (name + 0, '\0', MAXFILESIZE * sizeof (char));


      strncpy (name,
	       UFDTArr[fd].ptrfiletable->ptrinode->Buffer +
	       UFDTArr[fd].ptrfiletable->readoffset, bytes);


      UFDTArr[fd].ptrfiletable->readoffset =
	UFDTArr[fd].ptrfiletable->readoffset + bytes;



      return 0;


    }



}

//////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          truncate_file
//  Input :         CHARACTER POINTER
//  Output :        INTEGER
//  Description :   This function is used to trim size of file by bytes given by user
//  
/////////////////////////////////////////////////////////////////////////////////////////



int
truncate_file (char *name)
{


  int fd = 0;


  fd = GetFDFromName (name);


  if (fd == -1)


    {


      return -1;


    }


  memset (UFDTArr[fd].ptrfiletable->ptrinode->Buffer, 0, 2048);


  UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize = 0;


  UFDTArr[fd].ptrfiletable->writeoffset = 0;


  UFDTArr[fd].ptrfiletable->readoffset = 0;


  printf ("File Truncated Successfully");


}




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          open_file
//  Input :         CHARACTER POINTER, INTEGER
//  Output :        INTEGER
//  Description :   This function is used to open file from file descriptor
//
/////////////////////////////////////////////////////////////////////////////////////////


int
open_file (char *name, int mode)
{


  if (name == NULL || mode == 0)


    {


      return -1;


    }


  PINODE temp = NULL;


  if ((temp = Get_Inode (name)) == NULL)


    {


      return -2;


    }


  if (temp->Permission < mode)


    {


      return -3;


    }


  int i = 0;


  while (i < MAXINODE)


    {


      if (UFDTArr[i].ptrfiletable == NULL)


	{


	  break;


	}


      i++;


    }


  if (UFDTArr[i].ptrfiletable != NULL)


    {


      return -4;


    }


  UFDTArr[i].ptrfiletable = (PFILETABLE) malloc (sizeof (FILETABLE));


  UFDTArr[i].ptrfiletable->count = 1;


  UFDTArr[i].ptrfiletable->mode = mode;



  if (mode == READ + WRITE)


    {


      UFDTArr[i].ptrfiletable->readoffset = 0;


      UFDTArr[i].ptrfiletable->writeoffset = 0;


    }


  else if (mode == READ)


    {


      UFDTArr[i].ptrfiletable->readoffset = 0;


    }


  else if (mode == WRITE)


    {


      UFDTArr[i].ptrfiletable->writeoffset = 0;


    }


  UFDTArr[i].ptrfiletable->ptrinode = temp;


  (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)++;



  return i;


}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          closeAllFile
//  Input :         NONE
//  Output :        INTEGER
//  Description :   This function is used to close all the files from file descriptor
//
/////////////////////////////////////////////////////////////////////////////////////////

void
closeAllFile ()
{


  int i = 0;


  while (i < MAXINODE)


    {


      if (UFDTArr[i].ptrfiletable != NULL)


	{


	  UFDTArr[i].ptrfiletable->readoffset = 0;


	  UFDTArr[i].ptrfiletable->writeoffset = 0;


	  (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;


	}


      i++;


    }


}


//////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          CloseFileByName
//  Input :         CHARACTER POINTER
//  Output :        INTEGER
//  Description :   This function is used to close file from file descriptor
//
/////////////////////////////////////////////////////////////////////////////////////////


int
CloseFileByName (char *name)
{


  int fd = 0;


  fd = GetFDFromName (name);


  if (fd == -1)


    {


      return -1;


    }


  UFDTArr[fd].ptrfiletable->readoffset = 0;


  UFDTArr[fd].ptrfiletable->writeoffset = 0;


  (UFDTArr[fd].ptrfiletable->ptrinode->ReferenceCount)--;


  return 0;


}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//  Name :          LseekFile
//  Input :         INTEGER, INTEGER, INTEGER
//  Output :        INTEGER
//  Description :   This function is used reset offset of a file by offset provided by user
//  
/////////////////////////////////////////////////////////////////////////////////////////////



int
LseekFile (int fd, int size, int from)
{


  if ((fd < 0) || (from > 2))


    return -1;


  if (UFDTArr[fd].ptrfiletable == NULL)


    return -1;


  if ((UFDTArr[fd].ptrfiletable->mode == READ)
      || (UFDTArr[fd].ptrfiletable->mode == READWRITE))


    {


      if (from == CURRENT)


	{


	  if (((UFDTArr[fd].ptrfiletable->readoffset) + size) >
	      UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize)


	    return -1;


	  if (((UFDTArr[fd].ptrfiletable->readoffset) + size) < 0)


	    return -1;


	  (UFDTArr[fd].ptrfiletable->readoffset) =
	    (UFDTArr[fd].ptrfiletable->readoffset) + size;


	}


      else if (from == START)


	{


	  if (size > (UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize))


	    return -1;


	  if (size < 0)


	    return -1;


	  (UFDTArr[fd].ptrfiletable->readoffset) = size;



	}


      else if (from == END)


	{


	  if ((UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize) + size >
	      MAXFILESIZE)


	    return -1;


	  if (((UFDTArr[fd].ptrfiletable->readoffset) + size) < 0)


	    return -1;


	  (UFDTArr[fd].ptrfiletable->readoffset) =
	    (UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize) + size;


	}


    }


  else if (UFDTArr[fd].ptrfiletable->mode == WRITE)


    {


      if (from == CURRENT)


	{


	  if (((UFDTArr[fd].ptrfiletable->writeoffset) + size) > MAXFILESIZE)


	    return -1;


	  if (((UFDTArr[fd].ptrfiletable->writeoffset) + size) < 0)


	    return -1;


	  if (((UFDTArr[fd].ptrfiletable->writeoffset) + size) >
	      (UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize))


	    (UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize) =
	      (UFDTArr[fd].ptrfiletable->writeoffset) + size;


	  (UFDTArr[fd].ptrfiletable->writeoffset) =
	    (UFDTArr[fd].ptrfiletable->writeoffset) + size;


	}


      else if (from == START)


	{


	  if (size > MAXFILESIZE)


	    return -1;


	  if (size < 0)


	    return -1;


	  if (size > (UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize))


	    (UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize) = size;


	  (UFDTArr[fd].ptrfiletable->writeoffset) = size;


	}


      else if (from == END)


	{


	  if ((UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize) + size >
	      MAXFILESIZE)


	    return -1;


	  if (((UFDTArr[fd].ptrfiletable->writeoffset) + size) < 0)


	    return -1;


	  (UFDTArr[fd].ptrfiletable->writeoffset) =
	    (UFDTArr[fd].ptrfiletable->ptrinode->ActualFileSize) + size;


	}


    }


}
