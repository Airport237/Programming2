//
// Created by Justin Galin on 10/29/22.
//

#ifndef PROJECT2_IMAGEPROCESSING_IMAGE_H
#define PROJECT2_IMAGEPROCESSING_IMAGE_H
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Image {
    string file_name;
public:
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
        //Header Constructor
        Header(){};
        Header(char idLength_, char colorMapType_, char dataTypeCode_, short colorMapOrigin_, short colorMapLength_, char colorMapDepth_, short xOrigin_, short yOrigin_, short width_, short height_, char bitsPerPixel_, char imageDescriptor_)
        {
            idLength = idLength_;
            colorMapType = colorMapType_;
            dataTypeCode = dataTypeCode_;
            colorMapOrigin = colorMapOrigin_;
            colorMapLength = colorMapLength_;
            colorMapDepth = colorMapDepth_;
            xOrigin = xOrigin_;
            yOrigin = yOrigin_;
            width = width_;
            height = height_;
            bitsPerPixel = bitsPerPixel_;
            imageDescriptor = imageDescriptor_;
        };
        void printHeader();
    };
    Header header;

    struct Pixel {
        unsigned char red;
        unsigned char green;
        unsigned char blue;

        //Pixel Constructor
        Pixel(unsigned char red_,unsigned char green_,unsigned char blue_){
            red = red_;
            blue = blue_;
            green = green_;
        }
        Pixel(){}

    };
    void ReadImage(string file_name);
    void WriteImage(string file_name);
    int GetImageSize();
    Image Multiply(Image& rhs);
    Image Subtract(Image& rhs);
    unsigned char Clamp(int val);
    Image Screen(Image& rhs);
    Image Overlay(Image& rhs);
    Image Green();
    Image MultiplyNumbers();
    Image SeperateRed();
    Image SeperateGreen();
    Image SeperateBlue();
    void LoadRGB(Image& red, Image& green, Image& blue);
    void Flip180();
    void Test(string example, string number);

    vector<Pixel> pixel_vec;
};

#endif //PROJECT2_IMAGEPROCESSING_IMAGE_H
