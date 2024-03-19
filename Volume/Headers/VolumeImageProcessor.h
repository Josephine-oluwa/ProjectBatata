#ifndef VOLUMEIMAGEPROCESSOR_H
#define VOLUMEIMAGEPROCESSOR_H

#pragma once
#include <string>
#include <memory>
#include "VolumeImageLoader.h"

//Declaration of our image creation function
std::unique_ptr<VolumeImageLoader> VolumecreateImageFormat(const std::string& format);
//createImageFormat takes a string of the format to be used
std::unique_ptr<VolumeImageLoader> VolumeLoadImage(const std::string& filename, std::unique_ptr<VolumeImageLoader> createdImage);

#endif