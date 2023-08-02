
#include "Image.h"
#include <cstdlib>



int main() {

    //Part 1 Done Yay
    Image layer1;
    Image pattern1;
    layer1.ReadImage("input/layer1.tga");
    pattern1.ReadImage("input/pattern1.tga");
    Image part1 = pattern1.Multiply(layer1);
    part1.WriteImage("output/part1.tga");


    //Part 2 YAY
    Image layer2;
    Image car;
    layer2.ReadImage("input/layer2.tga");
    car.ReadImage("input/car.tga");
    Image part2 = car.Subtract(layer2);
    part2.WriteImage("output/part2.tga");

    //PART 3
    Image pattern2;
    pattern2.ReadImage("input/pattern2.tga");
    Image temp = layer1.Multiply(pattern2);
    Image text;
    text.ReadImage("input/text.tga");
    Image part3 = text.Screen(temp);
    part3.WriteImage("output/part3.tga");

    //Part4
    Image circles;
    circles.ReadImage("input/circles.tga");
    Image temp1 = circles.Multiply(layer2);
    Image part4 = temp1.Subtract(pattern2);
    part4.WriteImage("output/part4.tga");

    //Part5
    Image part5;
    part5 = layer1.Overlay(pattern1);
    part5.WriteImage("output/part5.tga");

    //Part 6
    car.ReadImage("input/car.tga");
    Image part6 = car.Green();
    part6.WriteImage("output/part6.tga");

    //Part 7 BAD
    Image part7 = car.MultiplyNumbers();
    part7.WriteImage("output/part7.tga");

    //Part 8 DONE
    Image part8_r = car.SeperateRed();
    Image part8_g = car.SeperateGreen();
    Image part8_b = car.SeperateBlue();
    part8_r.WriteImage("output/part8_r.tga");
    part8_g.WriteImage("poutput/art8_g.tga");
    part8_b.WriteImage("output/part8_b.tga");


    //Part 9 SOMETHING IS WRONG
    Image layer_blue, layer_green, layer_red, part9;
    layer_blue.ReadImage("input/layer_blue.tga");
    layer_green.ReadImage("input/layer_green.tga");
    layer_red.ReadImage("input/layer_red.tga");
    layer_blue.WriteImage("output/TEST.tga");
    part9.LoadRGB(layer_red,layer_green,layer_blue);
    part9.WriteImage("output/part9.tga");


    //Part 10 DONE
    Image text2;
    text2.ReadImage("input/text2.tga");
    text2.Flip180();
    text2.WriteImage("output/part10.tga");

    part1.Test("examples/EXAMPLE_part1.tga","1");
    part2.Test("examples/EXAMPLE_part2.tga","2");
    part3.Test("examples/EXAMPLE_part3.tga","3");
    part4.Test("examples/EXAMPLE_part4.tga","4");
    part5.Test("examples/EXAMPLE_part5.tga","5");
    part6.Test("examples/EXAMPLE_part6.tga","6");
    part7.Test("examples/EXAMPLE_part7.tga", "7");
    part8_r.Test("examples/EXAMPLE_part8_r.tga","8r");
    part8_b.Test("examples/EXAMPLE_part8_b.tga","8b");
    part8_g.Test("examples/EXAMPLE_part8_g.tga","8g");
    part9.Test("examples/EXAMPLE_part9.tga", "9");
    text2.Test("examples/EXAMPLE_part10.tga", "10");

    return 0;
}
