/*
 * Written in 2018 by Riccardo Monica
 *   RIMLab, Department of Engineering and Architecture, University of Parma, Italy
 *   http://www.rimlab.ce.unipr.it/
 *
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication along
 * with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef FAKE_OPENGL_CONTEXT_H
#define FAKE_OPENGL_CONTEXT_H

#include <string>
#include <GL/glew.h>

// Initializes an OpenGL context without a window (e.g. to use shaders for computation)
// X must be running for this to work
// display_name: the X display to use (usually ":0"). If empty, it is loaded from the $DISPLAY environment variable.
void InitFakeOpenGLContext(const std::string display_name);

#endif // FAKE_OPENGL_CONTEXT_H
