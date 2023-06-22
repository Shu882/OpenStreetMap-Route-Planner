1. refresh brew: done
    brew update
    brew upgrade
2. install cmake:done
    brew install cmake
   cmake --version
3. gcc:done
   gcc --version
   g++ --version
4. Cairo:done
5. graphicsmagick: done
   brew install graphicsmagick
6. libpng: done
   brew install libpng
7. Macports: done
8. update libc++: done, followed https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md
Set up IO2D lib:
1. clone repo git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
2. enter dir and mkdir build
3. comment out the last two build options for tests and samples in the CMakeLists.txt
4. from the build directory run cmake: cmake --config Release "-DCMAKE_BUILD_TYPE=Release" .. (Release should be default, but just in case)
5. compile with make -j $number of your processor threads
6. install the library with sudo make install