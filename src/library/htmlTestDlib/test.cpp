//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//                           License Agreement
//             For Example Library Build System using Emscripten
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//  * Attribution, you must give the original author credit.
//  * Redistribution of source code must retain the above license notice,
//    this list of conditions and the following disclaimer.
//  * This file is provided 'as is' with no expressed or implied warranty, the author is not
//    responsible for any damage it may cause.

// THIS FILE WAS CREATED BY NATHAN POTTER. IT IS PROVIDED AS IS AND IS NOT TO BE USED FOR COMMERCIAL PURPOSES.
// LAST UPDATED: 2024-11-08

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_io.h>
#include <iostream>
#include <emscripten/emscripten.h>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN EMSCRIPTEN_KEEPALIVE int detect_faces() {
    EM_ASM({
        console.log("Starting Detect function!");
    });
    // Initialize the face detector
    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();

    // Load the image from the provided path
    dlib::array2d<dlib::rgb_pixel> img;
    dlib::load_image(img, "/monalisa.jpg"); // emcc virtual file system path

    EM_ASM({
        console.log("Image Loaded!");
    });

    // Detect faces in the image
    std::vector<dlib::rectangle> faces = detector(img);

    EM_ASM_({
        console.log("Detected Faces: " + $0);
    }, faces.size());

    // std::cout << "Faces detected: " << faces.size() << std::endl;

    // Return the number of faces detected
    return faces.size();
}

int main() {
    EM_ASM({
        console.log("Starting main function!");
    });

    return 0;
}

// BUILD COMMANDS

// see library/buildRules for instructions on how to build the library for this file.
// see library/htmlTestDlib/DLIBEMC/install for the emcmake cmake build of dlib. it includes
// the libdlib.a file and all the necessary headers.

// BUILD EXAMPLE FILE

// INCLUDES
// -I"emsdk/upstream/emscripten/cache/sysroot/include"
// -I/Desktop/DLIBEMC/install/include

// ensure we preload files. emscripten will generate a .data file that it will then look for. pay
// attention to the browser console for which path it expects the file to be at. move the .data file.

// in order to use ccall effectively, we need to export the function. we can do this by using the extern "C"
// keyword in C++ or by using the EMSCRIPTEN_KEEPALIVE macro.

// ccall command
// emcc test.cpp -o build/cargo/ccall/face.js -I"/Desktop/DLIBEMC/install/include" -I"/emsdk/upstream/emscripten/cache/sysroot/include" -L"/Desktop/DLIBEMC/static_build/dlib" -ldlib -s EXPORT_ALL=1 -s EXPORTED_RUNTIME_METHODS=["ccall"] -s WASM=1 -s STACK_OVERFLOW_CHECK=2 -s ENVIRONMENT=web -s DISABLE_EXCEPTION_CATCHING=0 -s ASSERTIONS=1 --preload-file "/Documents/Work/Refactor Games/Eye Tracking/pyTrack/webapp/cpp/build/htmlTestDlib/build/monalisa.jpg@/monalisa.jpg"