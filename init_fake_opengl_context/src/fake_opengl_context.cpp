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

// This code was written following this guide:
// http://renderingpipeline.com/2012/05/windowless-opengl/

#include <init_fake_opengl_context/fake_opengl_context.h>

#include <GL/glx.h>

#include <ros/ros.h>

void InitFakeOpenGLContext(const std::string display_name) {
    ROS_INFO("init_fake_opengl_context: Initializing fake OpenGL context...");
    const char * const DISPLAY = (display_name == "") ? NULL : display_name.c_str();
    Display* display = XOpenDisplay(DISPLAY);
    if (!display) {
        ROS_ERROR("init_fake_opengl_context: Could not create display!");
        exit(1);
    }

    typedef GLXContext(*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
    static glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;

    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB((const GLubyte *) "glXCreateContextAttribsARB");
    if (!glXCreateContextAttribsARB) {
        ROS_ERROR("!glXCreateContextAttribsARB");
        exit(1);
    }

    const int visualAttribs[] = {
        GLX_X_RENDERABLE, True,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_STENCIL_SIZE, 8,
        None
    };
    int numberOfFramebufferConfigurations = 0;
    GLXFBConfig* fbConfigs = glXChooseFBConfig(display, DefaultScreen(display),
            visualAttribs, &numberOfFramebufferConfigurations);

    if (!fbConfigs || numberOfFramebufferConfigurations == 0) {
        ROS_ERROR("No fbConfigs!");
        exit(1);
    }

    ROS_INFO("init_fake_opengl_context: Number of framebuffer configurations: %d", int(numberOfFramebufferConfigurations));

    int context_attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
        GLX_CONTEXT_MINOR_VERSION_ARB, 0,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        None
    };

    const int FB_CONFIG = 0;

    GLXContext openGLContext = glXCreateContextAttribsARB(display, fbConfigs[FB_CONFIG], 0, True, context_attribs);

//    int pbufferAttribs[] = {
//        GLX_PBUFFER_WIDTH, 32,
//        GLX_PBUFFER_HEIGHT, 32,
//        None
//    };

//    GLXPbuffer pbuffer = glXCreatePbuffer(display, fbConfigs[FB_CONFIG], pbufferAttribs);
    GLXPbuffer pbuffer = None; // use GLX_ARB_create_context

    XFree(fbConfigs);
    XSync(display, False);

    if (!glXMakeContextCurrent(display, pbuffer, pbuffer, openGLContext)) {
        ROS_ERROR("init_fake_opengl_context: Something went wrong!");
        exit(1);
    }

    glewInit();

    if (!GLEW_ARB_framebuffer_object) {
        ROS_ERROR("init_fake_opengl_context: GLEW: Framebuffer object not supported!");
        exit(1);
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);

    ROS_INFO("init_fake_opengl_context: Fake context initialized ok.");
}
