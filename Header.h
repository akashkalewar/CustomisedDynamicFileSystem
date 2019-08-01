
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<iostream>

#define MAXINODE 50

#define READ 1
#define WRITE 2
#define READWRITE 3

#define REGULAR 1
#define SPECIAL 2

#define MAXFILESIZE 2048

#define START 0
#define CURRENT 1
#define END 2

typedef struct superblock
{
  int TotalInodes;
  int FreeInodes;
} SUPERBLOCK, *PSUPERBLOCK;

typedef struct inode
{
  char FileName[50];
  int InodeNumber;
  int FileSize;
  int ActualFileSize;
  int FileType;
  char *Buffer;
  int LinkCount;
  int ReferenceCount;
  int Permission;
  struct inode *next;
} INODE, *PINODE, **PPINODE;

typedef struct filetable
{
  int readoffset;
  int writeoffset;
  int count;
  int mode;
  PINODE ptrinode;
} FILETABLE, *PFILETABLE;

typedef struct ufdt
{
  PFILETABLE ptrfiletable;
} UFDT;

extern UFDT UFDTArr[MAXINODE];
extern SUPERBLOCK SUPERBLOCKobj;
extern PINODE head;

void CreateDILB ();
void InitialiseSuperBlock ();
void man (char *);
void DisplayHelp ();
void ls_file ();
void closeAllFile ();
void Exitxx ();

PINODE Get_Inode (char *);

int CreateFile (char *, int);
int fstat_file (int);
int stat_file (char *);
int GetFDFromName (char *);
int removexx (char *);
int write (int, char *, int);
int read (int, char *, int);
int truncate_file (char *);
int open_file (char *, int);
int LseekFile (int, int, int);
int CloseFileByName (char *);
