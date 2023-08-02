//
// Created by Justin Galin on 10/29/22.
//

#include "Image.h"

void Image::ReadImage(string file_name)
{
    ifstream file(file_name, ios::binary);
    //file.open(file_name, ios::binary);
    if (file.is_open())
    {
        char idLength;
        file.read(&idLength, sizeof(idLength));
        char colorMapType;
        file.read(&colorMapType, sizeof(colorMapType));
        char dataTypeCode;
        file.read(&dataTypeCode, sizeof(dataTypeCode));
        short colorMapOrigin;
        file.read((char*)&colorMapOrigin, sizeof(colorMapOrigin));
        short colorMapLength;
        file.read((char*)&colorMapLength, sizeof(colorMapLength));
        char colorMapDepth;
        file.read(&colorMapDepth, sizeof(colorMapDepth));
        short xOrigin;
        file.read((char*)&xOrigin, sizeof(xOrigin));
        short yOrigin;
        file.read((char*)&yOrigin, sizeof(yOrigin));
        short width;
        file.read((char*)&width, sizeof(width));
        short height;
        file.read((char*)&height, sizeof(height));
        char bitsPerPixel;
        file.read(&bitsPerPixel, sizeof(bitsPerPixel));
        char imageDescriptor;
        file.read(&imageDescriptor, sizeof(imageDescriptor));

        header = Header(idLength, colorMapType, dataTypeCode,colorMapOrigin,  colorMapLength, colorMapDepth,xOrigin,yOrigin,width,height, bitsPerPixel,imageDescriptor);

        //Loop for constructing a Pixel and adding it into the pixel array
        for (int i = 0; i < GetImageSize(); i++)
        {
            unsigned char blue;
            file.read((char*)&blue, sizeof(blue));

            unsigned char green;
            file.read((char*)&green, sizeof(green));

            unsigned char red;
            file.read((char*)&red, sizeof(red));

            Pixel pixel = Pixel(red, green, blue);
            pixel_vec.push_back((pixel));
        }
    }
    file.close();
}

void Image::WriteImage(string file_name){
    ofstream file(file_name, ios::binary);

    if (file.is_open()){
        file.write(&header.idLength, sizeof(header.idLength));
        file.write(&header.colorMapType, sizeof(header.colorMapType));
        file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
        file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
        file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
        file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
        file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
        file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
        file.write((char*)&header.width, sizeof(header.width));
        file.write((char*)&header.height, sizeof(header.height));
        file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
        file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

        for (int i = 0; i < GetImageSize(); i++) {
            file.write((char *) &pixel_vec[i].blue, sizeof(pixel_vec[i].blue));
            file.write((char *) &pixel_vec[i].green, sizeof(pixel_vec[i].green));
            file.write((char *) &pixel_vec[i].red, sizeof(pixel_vec[i].red));
        }
    }
    file.close();

}

int Image::GetImageSize(){
    return header.height*header.width;
}

void Image::Header::printHeader(){
    cout << int(idLength) << endl;
    cout << int(colorMapType) << endl;
    cout << int(dataTypeCode) << endl;
    cout << colorMapOrigin << endl;
    cout << colorMapLength << endl;
    cout << int(colorMapDepth) << endl;
    cout << xOrigin << endl;
    cout << yOrigin << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Bits per pixel: " << int(bitsPerPixel) << endl;
    cout << int(imageDescriptor) << endl;
}

//rhs is top layer
Image Image::Multiply(Image& rhs){
    Image newImage;
    newImage.header = header;
    for (int i = 0; i < this->GetImageSize(); i++)
    {
        Pixel pixel((unsigned char)(pixel_vec[i].red*rhs.pixel_vec[i].red/255.0f + 0.5f),(unsigned char)(pixel_vec[i].green*rhs.pixel_vec[i].green/255.0f + 0.5f),(unsigned char)((pixel_vec[i].blue*rhs.pixel_vec[i].blue)/255.0f + 0.5f));
        newImage.pixel_vec.push_back(pixel);
    }
    return newImage;
}

unsigned char Image::Clamp(int val){
    unsigned char final;
    if (val < 0)
    {
        final = 0;
    } else if (val > 255){
        final = 255;
    } else {
        final = (unsigned char)val;
    }
    return final;
}

//rhs is top
Image Image::Subtract(Image& rhs){
    Image newImage;
    newImage.header = header;
    for (int i = 0; i < GetImageSize(); i++)
    {
        Pixel pixel;
        pixel.red =Clamp((int)(pixel_vec[i].red-rhs.pixel_vec[i].red));
        pixel.green = Clamp((int)(pixel_vec[i].green-rhs.pixel_vec[i].green));
        pixel.blue = Clamp((int)(pixel_vec[i].blue-rhs.pixel_vec[i].blue));

        newImage.pixel_vec.push_back(pixel);
    }

    Clamp(5);
    return newImage;
}

Image Image::Screen(Image& rhs){
    Image newImage;
    newImage.header = header;
    for (int i = 0; i < this->GetImageSize(); i++)
    {
        Pixel pixel;
        float red = 1.0f-(1.0f-pixel_vec[i].red/255.0f)*(1.0f-rhs.pixel_vec[i].red/255.0f);
        pixel.red =(unsigned char)(red*255.0f + 0.5f);
        float green = 1.0f-(1.0f-pixel_vec[i].green/255.0f)*(1.0f-rhs.pixel_vec[i].green/255.0f);
        pixel.green =(unsigned char)(green*255.0f + 0.5f);
        float blue = 1.0f-(1.0f-pixel_vec[i].blue/255.0)*(1.0f-rhs.pixel_vec[i].blue/255.0f);
        pixel.blue =(unsigned char)(blue*255.0f + 0.5f);


        newImage.pixel_vec.push_back(pixel);
    }
    return newImage;
}

//FIGURE OUT THE B CONDITION
Image Image::Overlay(Image& rhs){
    Image newImage;
    newImage.header = header;

    for (int i = 0; i < this->GetImageSize(); i++)
    {
        Pixel pixel;

        if (rhs.pixel_vec[i].blue < 128)
        {
            pixel.blue = (unsigned char) (2.0f * pixel_vec[i].blue * rhs.pixel_vec[i].blue / 255.0f + 0.5f);
        } else {
            float blue = 1.0f - 2.0f*(1.0f - pixel_vec[i].blue / 255.0) * (1.0f - rhs.pixel_vec[i].blue / 255.0f);
            pixel.blue = (unsigned char) (blue * 255.0f + 0.5f);
        }
        if (rhs.pixel_vec[i].green < 128)
        {
            pixel.green = (unsigned char) (pixel_vec[i].green * rhs.pixel_vec[i].green * 2.0f / 255.0f + 0.5f);
        } else {
            float green = 1.0f - 2.0f*(1.0f - pixel_vec[i].green / 255.0) * (1.0f - rhs.pixel_vec[i].green / 255.0f);
            pixel.green = (unsigned char) (green * 255.0f + 0.5f);
        }
        if (rhs.pixel_vec[i].red < 128)
        {
            pixel.red = (unsigned char) (pixel_vec[i].red * rhs.pixel_vec[i].red * 2.0f / 255.0f + 0.5f);
        } else {
            float red = 1.0f - 2.0f*(1.0f - pixel_vec[i].red / 255.0) * (1.0f - rhs.pixel_vec[i].red / 255.0f);
            pixel.red = (unsigned char) (red * 255.0f + 0.5f);
        }
        newImage.pixel_vec.push_back(pixel);

    }
    return newImage;
}

Image Image::Green(){
    Image newImage;
    newImage.header = header;
    for (int i = 0; i < GetImageSize(); i++)
    {
        Pixel pixel;
        pixel.red = pixel_vec[i].red;
        pixel.blue = pixel_vec[i].blue;
        pixel.green = Clamp((int)(pixel_vec[i].green+200));

        newImage.pixel_vec.push_back(pixel);
    }
    return newImage;
}

Image Image::MultiplyNumbers(){
    Image newImage;
    newImage.header = header;
    for (int i = 0; i < this->GetImageSize(); i++)
    {
        Pixel pixel;

        pixel.red = Clamp((int)(4.0f*pixel_vec[i].red + 0.5f));
        pixel.blue = (unsigned char)0*pixel_vec[i].blue;
        pixel.green = pixel_vec[i].green;

        newImage.pixel_vec.push_back(pixel);
    }
    return newImage;
}

Image Image::SeperateRed(){
    Image newImage;
    newImage.header = header;
    for (int i = 0; i < this->GetImageSize(); i++)
    {
        Pixel pixel;
        pixel.red = pixel_vec[i].red;
        pixel.blue = pixel_vec[i].red;
        pixel.green = pixel_vec[i].red;

        newImage.pixel_vec.push_back(pixel);
    }
    return newImage;
}

Image Image::SeperateGreen(){
    Image newImage;
    newImage.header = header;
    for (int i = 0; i < this->GetImageSize(); i++)
    {
        Pixel pixel;
        pixel.red = pixel_vec[i].green;
        pixel.blue = pixel_vec[i].green;
        pixel.green = pixel_vec[i].green;

        newImage.pixel_vec.push_back(pixel);
    }
    return newImage;
}

Image Image::SeperateBlue(){
    Image newImage;
    newImage.header = header;
    for (int i = 0; i < this->GetImageSize(); i++)
    {
        Pixel pixel;
        pixel.red = pixel_vec[i].blue;
        pixel.blue = pixel_vec[i].blue;
        pixel.green = pixel_vec[i].blue;

        newImage.pixel_vec.push_back(pixel);
    }
    return newImage;
}

void Image::LoadRGB(Image& redI, Image& greenI,Image& blueI){
    header = redI.header;
    for (unsigned int i = 0; i < redI.GetImageSize(); i++)
    {
        Pixel pixel;
        pixel.red = redI.pixel_vec[i].red;
        pixel.blue = blueI.pixel_vec[i].blue;
        pixel.green = greenI.pixel_vec[i].green;

        pixel_vec.push_back(pixel);
    }
}

void Image::Flip180(){
    for (int i = 0; i < (GetImageSize()/2); i++)
    {
        Pixel temp = pixel_vec[i];
        pixel_vec[i] = pixel_vec[GetImageSize()-1-i];
        pixel_vec[GetImageSize()-1-i] = temp;
    }
}

void Image::Test(string example, string number){
    Image imExample;
    imExample.ReadImage(example);
    bool passed = true;
    if (header.idLength != imExample.header.idLength)
    {
        passed = false;
    }
    if (header.colorMapType != imExample.header.colorMapType)
    {
        passed = false;
    }
    if (header.dataTypeCode != imExample.header.dataTypeCode)
    {
        passed = false;
    }
    if (header.colorMapOrigin != imExample.header.colorMapOrigin)
    {
        passed = false;
    }
    if (header.colorMapLength != imExample.header.colorMapLength)
    {
        passed = false;
    }
    if (header.colorMapDepth != imExample.header.colorMapDepth)
    {
        passed = false;
    }
    if (header.xOrigin != imExample.header.xOrigin)
    {
        passed = false;
    }
    if (header.idLength != imExample.header.idLength){
        passed = false;
    }
    if (header.yOrigin != imExample.header.yOrigin){
        passed = false;
    }
    if (header.width != imExample.header.width){
        passed = false;
    }
    if (header.height != imExample.header.height)
    {
        passed = false;
    }
    if (header.bitsPerPixel != imExample.header.bitsPerPixel)
    {
        passed = false;
    }
    if (header.imageDescriptor != imExample.header.imageDescriptor)
    {
        passed = false;
    }

    if (passed == true)
    {
        int bcounter, rcounter, gcounter = 0;
        for (int i = 0; i < this->GetImageSize(); i++)
        {
            if (pixel_vec[i].red != imExample.pixel_vec[i].red)
            {
                passed = false;
                rcounter++;
                if (rcounter == 1){
                    cout << "bad red " << i << " ";
                }
            }
            if (pixel_vec[i].green != imExample.pixel_vec[i].green)
            {
                passed = false;
                gcounter++;
                if (gcounter == 1){
                    cout << "bad green " << i << " ";
                }
            }
            if (pixel_vec[i].blue != imExample.pixel_vec[i].blue)
            {
                passed = false;
                bcounter++;
                if (bcounter < 5){
                    cout << "bad blue " << i << " " << (int)pixel_vec[i].blue << " ";
                }
            }
        }

    }
    if (passed == true)
    {
        cout << "Test" << number <<  " Passed" << endl;
    } else {
        cout << "Test" << number << " Failed" << endl;
    }
}
