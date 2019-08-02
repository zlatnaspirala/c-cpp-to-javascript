
 #    Nikola Lukic emcc learning project     #
 ##   Basic examples porting with success   ##
 ###  Author of this project: Nikola Lukic ###
 ###  email: zlatnaspirala@gmail.com       ###
-----------------------------------------------

### Structure of project example is: ###

<pre>

  root/
  |------build (Auto generated files)
  |------source (any c or cpp source file)
  |------default.html (Minimal html template)

</pre>

#### C GL Shader: ####

```
  ./emcc sdl2-c-shader/sdl2glshader.c -s USE_SDL=2 -s LEGACY_GL_EMULATION=1  -s GL_UNSAFE_OPTS=0  -o build/sdl2.html
```

#### Mouse events: ####
```
  emcc mouse-events/test_html5_mouse.c -O2 -g1 --closure 1 -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -DAUTOMATE_SUCCESS=1  -o build/tmouse.html
```

#### Draw object, declare in typescript, opengles2 ####
```
  emcc tests/webgl_draw_triangle.c  -lGL -s OFFSCREEN_FRAMEBUFFER=1 -DEXPLICIT_SWAP=1 -DDRAW_FROM_CLIENT_MEMORY=1 -s FULL_ES2=1  -o build/gles2test.html
```

#### Not succesed for now ####

```
  emcc tests/sdl_image.c -o emcc -s ASSERTIONS=2 tests/sdl_image.c -o TEST.html -s -lSDL -s -lGL -USE_LIBPNG --memory-init-file 1 --preload-file tests --use-preload-pluginsTEST.html -s WASM=O2 -s -lSDL -s -lGL -USE_LIBPNG=1  --preload-file tests --use-preload-plugins

  ! memallo error

```

   You can help at :

    https://stackoverflow.com/questions/57290635/rewrite-python-script-runner-browser-and-make-inline-emcc-command-for-bui/57291122?noredirect=1#comment101078100_57291122


### LICENCE: ###

```
 Copyright 2014 The Emscripten Authors.  All rights reserved.
 Emscripten is available under two separate licenses, the MIT license and the
 University of Illinois/NCSA Open Source License.  Both these licenses can be
 found in the LICENSE file.
```
