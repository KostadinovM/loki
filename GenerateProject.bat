mkdir build
cd build
del CMakeCache.txt
cd ..
cmake . -Bbuild -DCMAKE_GENERATOR_PLATFORM=x64
PAUSE