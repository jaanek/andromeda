/*
    Orion OS, The educational operatingsystem
    Copyright (C) 2011  Bart Kuivenhoven

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __FS_FS_H
#define __FS_FS_H

#include <fs/file.h>

#define _FS_PROT_DIR   0x200
#define _FS_PROT_OWN_R 0x100
#define _FS_PROT_OWN_W 0x080
#define _FS_PROT_OWN_X 0x040
#define _FS_PROT_GRP_R 0x020
#define _FS_PROT_GRP_W 0x010
#define _FS_PROT_GRP_X 0x008
#define _FS_PROT_ALL_R 0x004
#define _FS_PROT_ALL_W 0x002
#define _FS_PROT_ALL_X 0x001

#define _FS_META_DIR  0x000
#define _FS_META_BLK  0x001
#define _FS_META_BIN  0x002
#define _FS_META_SYM  0x003
#define _FS_META_MNT  0x004
#define _FS_META_ROOT 0x004

#define _FS_USER_ROOT  0
#define _FS_GROUP_ROOT 0

#define _FS_MAX_DRIVES 0x20

#define _FS_ROOT_RIGHTS (_FS_PROT_DIR|_FS_PROT_OWN_R|_FS_PROT_OWN_W|_FS_PROT_OWN_X|_FS_PROT_GRP_R|_FS_PROT_GRP_X|_FS_PROT_ALL_R|_FS_PROT_ALL_X)

#define _VFS_STD_BLCK 0x200
#define _VFS_STD_SIZE (0x100000/_VFS_STD_BLCK)

struct _FS_INODE
{
  char* name;                // File name
  unsigned short protection; // protection bits d-rwx-rwx-rwx
  unsigned int userid;       // Owner data
  unsigned int groupid;      // Owner data
  unsigned int meta;         // Any flags required for administration
  unsigned int inode;        // Address of inode on disk
  unsigned int offset;       // Offset from inode start to access the first bit of data
  unsigned int length;       // Length of the file in units of 1 byte
  struct _FS_INODE* poiter;  // For symlinks
  struct _FS_INODE* parent;  // Should point to the parent directory
  struct _FS_ROOTNODE* root; // Pointer to the super block
};

struct _FS_ROOTNODE
{
  unsigned int* bmp;         // Bitmap of free blocks
  unsigned int size;         // The size of the filesystem in blocks
  unsigned int device;       // The device ID
  unsigned int free;         // The ammount of free blocks
  struct _FS_INODE* root;    // A pointer to the root inode
  unsigned int mounts;       // The amount of mounts performed on this system
};

#define _FS_MNT_ERR  0x000
#define _FS_MNT_EXT  0x001
#define _FS_MNT_EXT2 0x002
#define _FS_MNT_EXT3 0x003
#define _FS_MNT_EXT4 0x004
#define _FS_MNT_FT12 0x005
#define _FS_MNT_FT16 0x006
#define _FS_MNT_FT32 0x007
#define _FS_MNT_NTFS 0x008
#define _FS_MNT_REIS 0x009

typedef struct _FS_INODE inode_t;

extern struct _FS_INODE* _fs_root;

void fsInit(inode_t* root);
struct _FS_INODE* vfsInit(size_t size, unsigned int protection);

#endif