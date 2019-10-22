/*
 * Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Ported to GLES2.
 * Kristian Høgsberg <krh@bitplanet.net>
 * May 3, 2010
 *
 * Improve GLES2 port:
 *   * Refactor gear drawing.
 *   * Use correct normals for surfaces.
 *   * Improve shader.
 *   * Use perspective projection transformation.
 *   * Add FPS count.
 *   * Add comments.
 * Alexandros Frantzis <alexandros.frantzis@linaro.org>
 * Jul 13, 2010
 */

#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES

#define _GNU_SOURCE

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <Glut/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#ifndef HAVE_BUILTIN_SINCOS
#include "sincos.h"
#endif

#define STRIPS_PER_TOOTH 7
#define VERTICES_PER_TOOTH 34
#define GEAR_VERTEX_STRIDE 6

// no need
#include <math.h>
#define PI 3.14159265


#include "shaders.c"

/** The gears */
static struct gear *gear1, *gear2, *gear3;

#include "gear.c"

static struct nidza_gear *nidza_gear1, *nidza_gear2, *nidza_gear3;

#include "gear-custom.c"

#include "draw.c"

int main(int argc, char *argv[])
{
   /* Initialize the window */
   glutInit(&argc, argv);
   glutInitWindowSize(600, 600);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

   glutCreateWindow("es2gears");

   /* Set up glut callback functions  */
      glutIdleFunc(gears_idle);
   // glutReshapeFunc(gears_reshape);
   // glutDisplayFunc(gears_draw);
   // glutDisplayFunc(_DRAW);
   // glutSpecialFunc(gears_special);

   // test
   /* Set up glut callback functions */

   // glutIdleFunc(nidza_gears_idle);
   glutReshapeFunc(nidza_gears_reshape);
   //glutDisplayFunc(nidza_gears_draw);
   glutDisplayFunc(_DRAW);

   glutSpecialFunc(nidza_gears_special);

   /* Initialize the gears */
   gears_init();
   nidza_gears_init();

   printf("Program loaded!");

   glutMainLoop();

   return 0;
}
