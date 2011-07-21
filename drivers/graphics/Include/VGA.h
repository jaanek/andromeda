/*
    Orion OS, The educational operatingsystem
    Copyright (C) 2011  Steven van der Schoot

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


#ifndef __VGA_H
#define __VGA_H

struct imageBuffer_s
{
  char *buffer;
  unsigned int width;
  unsigned int height;
};

struct pixel_s
{
  unsigned int x;
  unsigned int y;
};

typedef struct imageBuffer_s imageBuffer;
typedef struct pixel_s pixel;

imageBuffer screenbuf; // sreen buffer, containing all pixels that should be written to the screen.

boolean vgaInit();
int setVideoMode(int mode);

#endif