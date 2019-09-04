++++++++++++++++++++++++++++++++++++++++++++++++

## Nikola Lukic emcc learning project ##

### Basic examples porting with success ###
### Author of this project: Nikola Lukic ###
### email: zlatnaspirala@gmail.com ###

++++++++++++++++++++++++++++++++++++++++++++++++

Objective : Learn from base example samples in context of all game-dev interest functionality.
Structure of project example:

<pre>

  root/
  |------build (Auto generated files)
  |------ (any c or cpp source file)
  |------default.html (Minimal html template)
  
</pre>


- C GL Shader:
```
  emcc sdl2-c-shader/sdl2glshader.c -s USE_SDL=2 -s LEGACY_GL_EMULATION=1  -s GL_UNSAFE_OPTS=0  -o sdl2-c-shader/build/sdl2.html
```

- Mouse events:
```
  emcc mouse-events/test_html5_mouse.c -O2 -g1 --closure 1 -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -DAUTOMATE_SUCCESS=1  -o mouse-events/build/tmouse.html
Draw object, declare in typescript, opengles2
```

```
  emcc sdl-ts-declare/webgl_draw_triangle.c  -lGL -s OFFSCREEN_FRAMEBUFFER=1 -DEXPLICIT_SWAP=1 -DDRAW_FROM_CLIENT_MEMORY=1 -s FULL_ES2=1  -o sdl-ts-declare/build/gles2test.html
```

- Keyboard (c)
```
  emcc keyboard-c/test_keyboard_codes.c -O2 -g1 --closure 1 -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -DAUTOMATE_SUCCESS=1  -o keyboard-c/build/keyboard-mouse.html
```

- Write file (cpp)
```
  emcc write-file/write_file.cpp -s ENVIRONMENT=web --closure 1 -o write-file/build/test.html
```
  
- Draw trianlge object, (c, opengles2)
```
  emcc webgl-triangle/webgl_draw_triangle.c  -lGL -s OFFSCREEN_FRAMEBUFFER=1 -DEXPLICIT_SWAP=1 -DDRAW_FROM_CLIENT_MEMORY=1 -s FULL_ES2=1  -o webgl-triangle/build/test.html
```

- Test mem-cpu
```
  emcc cpu-mem/benchmark_memcpy.cpp -DBUILD_FOR_SHELL -I tests/tick.h -s WASM=0 -s TOTAL_MEMORY=512MB --memory-init-file 1  -o cpu-mem/nik.html
```

- Test bullet
```
    Building.emcc(path_from_root('tests', 'bullet_hello_world.cpp'), ['-s', 'USE_BULLET=1'], output_filename='a.out.js')
    self.assertContained('BULLET RUNNING', run_process(JS_ENGINES[0] + ['a.out.js'], stdout=PIPE, stderr=PIPE).stdout)

    emcc bullet-test/bullet_hello_world.cpp -s USE_BULLET=1 -o a.out.js

    emcc bullet-test/bullet_hello_world.cpp -s USE_BULLET=1 -o bullet-test/build/a.html
```

- not work 1

```
  emcc test5/test_glfw_dropfile.c -s USE_GLFW=3 -lglfw -lGL
Not succesed for now

  emcc tests/sdl_image.c -o emcc -s ASSERTIONS=2 tests/sdl_image.c -o TEST.html -s -lSDL -s -lGL -USE_LIBPNG --memory-init-file 1 --preload-file tests --use-preload-pluginsTEST.html -s WASM=O2 -s -lSDL -s -lGL -USE_LIBPNG=1  --preload-file tests --use-preload-plugins

  ! memallo error

You can help at :

https://stackoverflow.com/questions/57290635/rewrite-python-script-runner-browser-and-make-inline-emcc-command-for-bui/57291122?noredirect=1#comment101078100_57291122
```


### LICENCE: ###

 Copyright 2014 The Emscripten Authors.  All rights reserved.
 Emscripten is available under two separate licenses, the MIT license and the
 University of Illinois/NCSA Open Source License.  Both these licenses can be
 found in the LICENSE file.
