#include <iostream>
#include <sstream>
#include <vector>
#include "DicomFormat.h"

bool DicomFormat::load(const std::string& filename) {
    // Implementation for loading DICOM
     OFCondition status = fileFormat.loadFile(filename.c_str());
    if (status.good()) {
        // Process the file or extract information as needed
        std::cout << "Loaded Successfuly " << std::endl;
        return true;
    } else {
        std::cerr << "Error loading DICOM file: " << status.text() << std::endl;
        return false;
    }
}

bool DicomFormat::save(const std::string& filename) {
     // Example: Changing a patient's name
    OFString newPatientName = "Doe^John";
    OFCondition result = fileFormat.getDataset()->putAndInsertString(DCM_PatientName, newPatientName);
    
    if (result.bad()) {
        return false;
    }
    // Implementation for saving DICOM
     OFCondition status = fileFormat.saveFile(filename.c_str(), EXS_LittleEndianExplicit);
    if (status.good()) {
        return true;    
    } else {
        std::cerr << "Error saving DICOM file: " << status.text() << std::endl;
        return false;
    }   
    
}

std::string DicomFormat::getMetadata() const {
    std::string patientName;
    std::string patientID;
    std::string studyDate;
    std::string modality;
    int rows;
    int columns;
    float pixelSpacingX;
    float pixelSpacingY;
    std::ostringstream metadata;
    DcmDataset* dataset = fileFormat.getDataset();

    if (dataset) {
        dataset->findAndGetOFString(DCM_PatientName,patientName);
        dataset->findAndGetOFString(DCM_PatientID,patientID);
        dataset->findAndGetOFString(DCM_StudyDate,studyDate);
        dataset->findAndGetOFString(DCM_Modality,modality);
        dataset->findAndGetInt(DCM_Rows,rows);
        dataset->findAndGetInt(DCM_Columns,columns);
        dataset->findAndGetFloatString(DCM_PixelSpacing,pixelSpacingX, 0);
        dataset->findAndGetFloatString(DCM_PixelSpacing,pixelSpacingY, 1);
        
        std::cout << "Patient Name" << patientName << std::endl;
        std::cout << "Patient ID" << patientID << std::endl;
        std::cout << "Study Date" << studyDate << std::endl;
        std::cout << "Modality" << modality << std::endl;
        std::cout << "Number of rows in the image" << rows << std::endl;
        std::cout << "Number of columns in the image" << columns << std::endl;
        return true
    }
    std::cerr << "Error loading DICOM file: " << status.text() << std::endl;
    return false
}

std::vector<int> DicomFormat::getPixelValues() const {
    DcmDataset* dataset = fileFormat.getDataset();
    // Retrieve image dimensions
    unsigned long rows, cols;
    dataset->findAndGetUint32(DCM_Rows, rows);
    dataset->findAndGetUint32(DCM_Columns, cols);

    // Access pixel data asuming it is 16-bit image
    const Uint16* pixelData;
    dataset->findAndGetUint16Array(DCM_PixelData, pixelData);

        if (pixelData) {
         // Iterate over each pixel to calculate its X, Y coordinates
         for (unsigned long row = 0; row < rows; ++row) {
             for (unsigned long col = 0; col < cols; ++col) {
                 // Calculate the index of the current pixel
                 unsigned long index = row * cols + col;
                std::cout << "PIXEL Index:"<<index << std::endl;
                 // Retrieve the pixel value (assuming 16-bit grayscale)
                 Uint16 pixelValue = pixelData[index];
                 // Output or process the X, Y position and pixel value
                 std::cout << "Pixel at (" << col << ", " << row << ") has value: " << pixelValue << std::endl;
             }
         }
        } else {
            std::cerr << "Error: No pixel data found in the file." << std::endl;
        }
        std::cerr << "Error: Cannot read DICOM file (" << status.text() << ")" << std::endl;
        return false;
}