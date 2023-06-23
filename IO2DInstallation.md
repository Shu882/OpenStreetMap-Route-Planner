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

fatal error: 'X11/Xlib.h' file not found:

1. this didn't help: https://knowledge.udacity.com/questions/548098
2. doesn't help: https://stackoverflow.com/questions/14321038/x11-xlib-h-no-such-file-or-directory-on-mac-os-x-mountain-lion
3. this one uses: export CPPFLAGS=-I/opt/X11/include. not working. https://stackoverflow.com/questions/11465258/xlib-h-not-found-when-building-graphviz-on-mac-os-x-10-8-mountain-lion
4. then tried, nothing: export CPPFLAGS=-I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers
5. eventually this worked for me: from https://stackoverflow.com/questions/11465258/xlib-h-not-found-when-building-graphviz-on-mac-os-x-10-8-mountain-lion
if(APPLE)
   include_directories(AFTER "/opt/X11/include")
endif()

Another error: libc++abi: terminating due to uncaught exception of type std::__1::system_error: Input/output error
1. 
