//Imageprocessor.h
#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#pragma once
#include <string>
#include <memory>
#include "ImageLoader.h"

//Declaration of our image creation function
std::unique_ptr<ImageLoader> createImageFormat(const std::string& format);
//createImageFormat takes a string of the format to be used
std::unique_ptr<ImageLoader> LoadImage(const std::string& filename, std::unique_ptr<ImageLoader> createdImage);

#endif //Imageprocessor.h