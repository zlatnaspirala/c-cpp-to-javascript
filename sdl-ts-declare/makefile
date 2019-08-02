EXPORTS_FILE=makefile_exports.txt
VARIABLE=`cat $(EXPORTS_FILE)`
LDFLAGS=-O1 --llvm-opts 2

test:
	mkdir -p build
	emcc \
	testSDL.cpp \
	-o build/testSDL \
	$(SDLFLAGS) \
	-framework OpenGL.framework \
	-std=c++14 \
	-g

app:
	mkdir -p build
	emcc \
	main.cpp shaders.cpp \
	--bind \
	-s FULL_ES2=1 \
	-lGL \
	-s EXPORTED_FUNCTIONS='["_initGL", "_drawTriangle"]' \
	-std=c++11 \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "setValue"]' \
	$(LDFLAGS) \
	-o build/glcore.js \
	-g