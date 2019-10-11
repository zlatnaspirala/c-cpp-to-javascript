
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 #    Nikola Lukic emcc learning project     #
 ####   Basic examples porting with success   ####
 #####  Author of this project: Nikola Lukic #####
 #####  email: zlatnaspirala@gmail.com       #####
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


 - Objective : Learn from base example samples in context of all game-dev interest functionality.

##### Structure of project example: #####

<pre>

  root/
  |------build (Auto generated files)
  |------<example_name> (any c or cpp source file)
  |------default.html (Minimal html template)

</pre>

##### C GL Shader: #####

```
  emcc sdl2-c-shader/sdl2glshader.c -s USE_SDL=2 -s LEGACY_GL_EMULATION=1  -s GL_UNSAFE_OPTS=0  -o sdl2-c-shader/build/sdl2.html
```

##### Mouse events: #####
```
  emcc mouse-events/test_html5_mouse.c -O2 -g1 --closure 1 -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -DAUTOMATE_SUCCESS=1  -o mouse-events/build/tmouse.html
```

##### Draw object, declare in typescript, opengles2 #####
```
  emcc sdl-ts-declare/webgl_draw_triangle.c  -lGL -s OFFSCREEN_FRAMEBUFFER=1 -DEXPLICIT_SWAP=1 -DDRAW_FROM_CLIENT_MEMORY=1 -s FULL_ES2=1  -o sdl-ts-declare/build/gles2test.html
```

##### Keyboard (c) #####
```
  emcc keyboard-c/test_keyboard_codes.c -O2 -g1 --closure 1 -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -DAUTOMATE_SUCCESS=1  -o keyboard-c/build/keyboard-mouse.html
```

##### Write file (cpp) #####
```
  emcc write-file/write_file.cpp -s ENVIRONMENT=web --closure 1 -o write-file/build/test.html
```

##### Draw trianlge object, (c, opengles2) #####
```
  emcc webgl-triangle/webgl_draw_triangle.c  -lGL -s OFFSCREEN_FRAMEBUFFER=1 -DEXPLICIT_SWAP=1 -DDRAW_FROM_CLIENT_MEMORY=1 -s FULL_ES2=1  -o webgl-triangle/build/test.html
```


##### geometry cube SDL #####

```
 // self.btest('cubegeom_pre3.c', reference='cubegeom_pre2.png', args=['-s', 'LEGACY_GL_EMULATION=1', '-lGL', '-lSDL'])

 emcc cubegeom_pre3.c -s LEGACY_GL_EMULATION=1 -lGL -lSDL -o build/test.html preload-file res

```

##### Test mem-cpu #####
```
  emcc cpu-mem/benchmark_memcpy.cpp -DBUILD_FOR_SHELL -I tests/tick.h -s WASM=0 -s TOTAL_MEMORY=512MB --memory-init-file 1  -o cpu-mem/nik.html
```

##### Test bullet ! #####
```
    Building.emcc(path_from_root('tests', 'bullet_hello_world.cpp'), ['-s', 'USE_BULLET=1'], output_filename='a.out.js')
    self.assertContained('BULLET RUNNING', run_process(JS_ENGINES[0] + ['a.out.js'], stdout=PIPE, stderr=PIPE).stdout)

    emcc bullet-test/bullet_hello_world.cpp -s USE_BULLET=1 -o a.out.js

    emcc bullet-test/bullet_hello_world.cpp -s USE_BULLET=1 -o bullet-test/build/a.html
```

##### gl-matrix-identity-c #####

```
  emcc gl_matrix_identity.c -s LEGACY_GL_EMULATION=1 -lGL -s USE_SDL=2 -o build/test.html -s GL_UNSAFE_OPTS=0
```

##### opengles in c #####
```
emcc hello_world_gles_deriv.c -DHAVE_BUILTIN_SINCOS -lGL -lglut -o build/something.html
```

##### no work 1 - glfw_dropfile.c #####
```
  emcc test5/test_glfw_dropfile.c -s USE_GLFW=3 -lglfw -lGL
```

##### Not succesed for now #####

```
emcc sdl_image.c -o TEST.html -s -lSDL -s -lGL -USE_LIBPNG --memory-init-file 1 --preload-file tests --use-preload-plugins TEST.html -s WASM=O2 -s -lSDL -s -lGL -USE_LIBPNG=1  --preload-file tests --use-preload-plugins

  ! memallo error

```

   You can help at :

    https://stackoverflow.com/questions/57290635/rewrite-python-script-runner-browser-and-make-inline-emcc-command-for-bui/57291122?noredirect=1#comment101078100_57291122


#### GLFW ####

```
1)  Test
     emcc glfw_events.c -s USE_GLFW=3 -DUSE_GLFW=3 -lglfw -lGL  -o build/events.html
2)
  emcc clientside_vertex_arrays_es3.c -s USE_WEBGL2=1 -s FULL_ES2=1 -s FULL_ES3=1 -s USE_GLFW=3 -lglfw -lGLESv2  -o build/nik2.html --preload-file res

```

### Games Session ###

#### Simple ball game ####
 
 Work only on keyevent.
 
 ```
   emcc test.c -s -lGL -o build/nikolatest.html -std=c11 -s LEGACY_GL_EMULATION=1  -s GL_UNSAFE_OPTS=0
 ```

#### xo-console-log game ####

 Interest for AI and 
```
  emcc xo.cpp -o build/xo.html
```

#### Test game ####

```
  emcc projS.cpp -s USE_SDL=2 -lSDL --preload-file data -s USE_SDL_IMAGE=2 -s --no-heap-copy --use-preload-plugins -o nikolatest.html -s GL_UNSAFE_OPTS=0
```

#### SDL tutorials ####

 Image example :
```
    emcc image.cpp -o -s ASSERTIONS=2 -o build/TEST.html -s -lSDL -s -lGL -USE_LIBPNG --memory-init-file 1 --preload-file res --use-preload-plugins -s WASM=O2 -s -lSDL -s -lGL -USE_LIBPNG=1
```

opengl
```
  emcc image.cpp -o -s ASSERTIONS=2 -o build/TEST.html -s -lSDL -s -lGL -USE_LIBPNG --memory-init-file 1 --preload-file res --use-preload-plugins -s WASM=O2 -s -lSDL -s -lGL -USE_LIBPNG=1

    self.btest('glfw.c', '1', args=['-s', 'LEGACY_GL_EMULATION=1', '-lglfw', '-lGL'])
    self.btest('glfw.c', '1', args=['-s', 'LEGACY_GL_EMULATION=1', '-s', 'USE_GLFW=2', '-lglfw', '-lGL'])

    emcc opengl.cpp -o1 -s LEGACY_GL_EMULATION=1 --preload-file data -s USE_GLFW=2 -lglfw -lGL
```

### Help ###

#### Args ####

```
  -std= XXX

  note: use 'c89', 'c90', or 'iso9899:1990' for 'ISO C 1990' standard
  note: use 'iso9899:199409' for 'ISO C 1990 with amendment 1' standard
  note: use 'gnu89' or 'gnu90' for 'ISO C 1990 with GNU extensions' standard
  note: use 'c99' or 'iso9899:1999' for 'ISO C 1999' standard
  note: use 'gnu99' for 'ISO C 1999 with GNU extensions' standard
  note: use 'c11' or 'iso9899:2011' for 'ISO C 2011' standard
  note: use 'gnu11' for 'ISO C 2011 with GNU extensions' standard
  note: use 'c17', 'iso9899:2017', 'c18', or 'iso9899:2018' for 'ISO C 2017' standard
  note: use 'gnu17' or 'gnu18' for 'ISO C 2017 with GNU extensions' standard
  note: use 'c2x' for 'Working Draft for ISO C2x' standard
  note: use 'gnu2x' for 'Working Draft for ISO C2x with GNU extensions' standard

```

### LICENCE: ###

```
 Copyright 2014 The Emscripten Authors.  All rights reserved.
 Emscripten is available under two separate licenses, the MIT license and the
 University of Illinois/NCSA Open Source License.  Both these licenses can be
 found in the LICENSE file.
```
