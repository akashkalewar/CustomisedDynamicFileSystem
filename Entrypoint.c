#include"Header.h"

extern UFDT UFDTArr[MAXINODE];
extern SUPERBLOCK SUPERBLOCKobj;
extern PINODE head;

int main ()
{
  char *ptr = NULL;
  int ret = 0, fd = 0, count = 0;
  char command[4][80], str[80], arr[1024];
  InitialiseSuperBlock ();
  CreateDILB ();
  while (1)
    {
      fflush (stdin);
      fflush (stdout);
      strcpy (str, "");
      printf ("\nCDFS : > ");
      fgets (str, 80, stdin);
      count =
	sscanf (str, "%s %s %s %s", command[0], command[1], command[2],
		command[3]);
      if (count == 1)
	{
	  if (strcmp (command[0], "ls") == 0)
	    {
	      ls_file ();
	    }
	  else if (strcmp (command[0], "closeall") == 0)
	    {
	      closeAllFile ();
	      printf ("Files closed successfully");
	    }
	  else if (strcmp (command[0], "clear") == 0)
	    {
	      system ("cls");
	      continue;
	    }
	  else if (strcmp (command[0], "help") == 0)
	    {
	      DisplayHelp ();
	      continue;
	    }
	  else if (strcmp (command[0], "exit") == 0)
	    {
	      Exitxx ();
	      printf ("Terminating the Customized Dynamic File System\n");
	      break;
	    }
	  else
	    {
	      printf ("\nError : Command not found!!!\n");
	      continue;
	    }
	}
      else if (count == 2)
	{
	  if (strcmp (command[0], "stat") == 0)
	    {
	      ret = stat_file (command[1]);
	      if (ret == -1)
		printf ("ERROR : Incorrect parameters\n");
	      if (ret == -2)
		printf ("ERROR : There is no such file\n");
	      continue;
	    }
	  else if (strcmp (command[0], "fstat") == 0)
	    {
	      ret = fstat_file (atoi (command[1]));
	      if (ret == -1)
		printf ("ERROR : Incorrect parameters\n");
	      if (ret == -2)
		printf ("ERROR : There is no such file\n");
	      continue;
	    }
	  else if (strcmp (command[0], "close") == 0)
	    {
	      ret = CloseFileByName (command[1]);
	      if (ret == -1)
		{
		  printf ("File Not Found");
		}
	      if (ret == 0)
		{
		  printf ("File closed successfully");
		}
	      continue;
	    }
	  else if (strcmp (command[0], "rm") == 0)
	    {
	      ret = removexx (command[1]);
	      if (ret == -1)
		{
		  printf ("File Not Found");
		}
	      else if (ret == 1)
		{
		  printf ("File Deleted Successfully");
		}
	      continue;
	    }
	  else if (strcmp (command[0], "man") == 0)
	    {
	      man (command[1]);
	    }
	  else if (strcmp (command[0], "write") == 0)
	    {
	      fd = GetFDFromName (command[1]);
	      if (fd == -1)
		{
		  printf ("Error: Incorrect Parameter\n");
		  continue;
		}
	      printf ("Enter the data: \n");
	      scanf ("%[^\n]", arr);
	      ret = strlen (arr);
	      if (ret == 0)
		{
		  printf ("Error: Incorrect Parameter");
		  continue;
		}
	      ret = write (fd, arr, ret);
	      if (ret == -1)
		printf ("Error: Permission Denied\n");
	      if (ret == -2)
		printf ("Error: There is no sufficient memory to write\n");
	      if (ret == -3)
		printf ("Error: It is not a regular file\n");
	      continue;
	    }
	  else if (strcmp (command[0], "truncate") == 0)
	    {
	      ret = truncate_file (command[1]);
	      if (ret == -1)
		{
		  printf ("File Not Found");
		}
	      continue;
	    }
	  else
	    {
	      printf ("\nError : Command not found!!!\n");
	      continue;
	    }
	}
      else if (count == 3)
	{
	  if (strcmp (command[0], "create") == 0)
	    {
	      ret = CreateFile (command[1], atoi (command[2]));
	      if (ret >= 0)
		{
		  printf
		    ("File is successfully created with file descriptor : %d\n",
		     ret);
		}
	      if (ret == -1)
		printf ("ERROR : Incorrect parameters\n");
	      if (ret == -2)
		printf ("ERROR : There is no inodes\n");
	      if (ret == -3)
		printf ("ERROR : File already exists\n");
	      if (ret == -4)
		printf ("ERROR : Memory allocation failure\n");
	      continue;
	    }
	  else if (strcmp (command[0], "open") == 0)
	    {
	      ret = open_file (command[1], atoi (command[2]));
	      if (ret == -1)
		{
		  printf ("Invalid Parameters");
		}
	      else if (ret == -2)
		{
		  printf ("File not Present");
		}
	      else if (ret == -3)
		{
		  printf ("Permission Denied");
		}
	      else if (ret == -4)
		{
		  printf ("No Nodes Available");
		}
	      else if (ret >= 0)
		{
		  printf ("File successfully opened with descriptor %d", ret);
		}
	      continue;
	    }
	  else if (strcmp (command[0], "read") == 0)
	    {
	      fd = GetFDFromName (command[1]);
	      if (fd == -1)
		{
		  printf ("Error: Incorrect parameter\n");
		  continue;
		}
	      ret = read (fd, arr, atoi (command[2]));
	      if (ret == -1)
		{
		  printf ("File does not exist");
		}
	      if (ret == -2)
		{
		  printf ("Permission Denied");
		}
	      if (ret == -3)
		{
		  printf ("Reached at EOF");
		}
	      if (ret == -4)
		{
		  printf ("File not a regular file\n");
		}
	      if (ret == 0)
		{
		  printf ("\n%s", arr);
		}
	      continue;
	    }
	  else
	    {
	      printf ("\nError : Command not found!!!\n");
	      continue;
	    }
	}
      else if (count == 4)
	{
	  if (strcmp (command[0], "lseek") == 0)
	    {
	      fd = 0;
	      fd = GetFDFromName (command[1]);
	      if (fd == -1)
		{
		  printf ("Error: Incorrect Parameter\n");
		  continue;
		}
	      ret = LseekFile (fd, atoi (command[2]), atoi (command[3]));
	      if (ret == -1)
		{
		  printf ("Error: Unable to perform lseek\n");
		}
	    }
	  else
	    {
	      printf ("\nERROR : Command not found !!!\n");
	      continue;
	    }
	}
    }
  return 0;
}
