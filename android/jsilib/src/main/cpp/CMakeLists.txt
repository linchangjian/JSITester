# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
message( ${CMAKE_CURRENT_SOURCE_DIR} )
# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
link_directories(
        ../../../../../node_modules/react-native/ReactAndroid/src/main/jni/first-party/fb/include
)

include_directories(
        ../../../../../node_modules/react-native/React
        ../../../../../node_modules/react-native/React/Base
        ../../../../../node_modules/react-native/ReactCommon/jsi

        ../../../../../node_modules/react-native/third-party/folly-2018.10.22.00
        ../../../../../node_modules/react-native/third-party/double-conversion-1.1.6
        ../../../../../node_modules/react-native/third-party/boost_1_63_0
        ../../../../../node_modules/react-native/third-party/glog-0.3.5/src
)
add_library( # Sets the name of the library.
             jsi-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
            ../../../../../node_modules/react-native/ReactCommon/jsi/jsi/jsi.cpp
             JSIinstaller.cpp
             JSIinstaller.h)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.

              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       jsi-lib

                       # Links the target library to the log library
                       # included in the NDK.
                        android
                       ${log-lib} )

target_include_directories(jsi-lib PUBLIC
        ../../../../../node_modules/react-native/ReactAndroid/src/main/jni/first-party/fb/include
        )