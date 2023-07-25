mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - MinGW Makefiles" ..
cmake --build .
cd ..