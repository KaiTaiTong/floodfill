#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"
#include <limits.h>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "filler.h"
#include "dotColorPicker.h"
#include "rainbowColorPicker.h"
#include "borderColorPicker.h"

using namespace std;
using namespace cs221util;

#define FUNCTORTESTHEIGHT 60
#define FUNCTORTESTWIDTH 60
#define FUNCTORTESTFREQ 10
#define FUNCTORTESTX 40
#define FUNCTORTESTY 10
#define FUNCTORTESTRADIUS 45
#define FUNCTORTESTGRIDSPACING 16
#define FUNCTORTESTDOTSIZE 4

// use the following for border tests
#define SOLIDX 80
#define SOLIDY 80
#define SOLIDTOLERANCE 0.01
#define SOLIDTESTIMAGE "originals/Canada.png"
#define SOLIDFRAMEFREQ 100

// use the following for dot tests
#define GRIDX 50
#define GRIDY 70
#define GRIDTOLERANCE 0.2
#define GRIDTESTIMAGE "originals/cat.png"
#define GRIDFRAMEFREQ 50
#define GRIDGRIDSPACING 100
#define DOTSIZE 10

// use for rainbow
#define RAINFREQ 1.0/1000.0
#define RAINTOLERANCE 0.05
#define RAINX 75
#define RAINY 75
#define RAINTESTIMAGE "originals/cloud.png"
#define RAINFRAMEFREQ 500

// use for demo
#define DEMOFREQ 1.0/100.0
#define DEMOTOLERANCE 0.02
#define DEMOX 175
#define DEMOY 175
#define DEMOTESTIMAGE "originals/pikachu.png"
#define DEMOFRAMEFREQ 1000


PNG testColorPicker(colorPicker& picker)
{
    PNG img;
    img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);
    HSLAPixel px;

    for (int x = 1; x < FUNCTORTESTWIDTH; x = x + x) {
        for (int y = 1; y < FUNCTORTESTHEIGHT; y = y + y) {
            px = picker(x, y);
            // these create the output useful for debugging fills
            cout << "\toperator()(" << x << ", " << y << ") = {"
                << (int)px.h << ", "
                << (int)px.s << ", "
                << (int)px.l << "}" << endl;
        }
    }

    for (int x = 0; x < FUNCTORTESTWIDTH; x++){
        for (int y = 0; y < FUNCTORTESTHEIGHT; y++){
            HSLAPixel * p = img.getPixel(x,y);
            * p = picker(x, y);
        }
    }

    return img;
}

//TEST_CASE("colorPicker::basic dot","[weight=1][part=colorPicker]"){
//    HSLAPixel px1;
//    px1.h = 120;
//    px1.s = 1.0; px1.l = 0.25;
//    dotColorPicker dotPicker(px1, FUNCTORTESTGRIDSPACING, FUNCTORTESTDOTSIZE);

//    PNG result = testColorPicker(dotPicker);
//    result.writeToFile("images/dotColorPickerTest.png");
//    PNG expected; expected.readFromFile("soln_images/dotColorPickerTest.png");
//    REQUIRE(result == expected);
//}

//TEST_CASE("colorPicker::basic rainbow","[weight=1][part=colorPicker]"){
//    rainbowColorPicker rainPicker(1.0/1000.0);

//    PNG result = testColorPicker(rainPicker);
//    result.writeToFile("images/rainColorPickerTest.png");
//    PNG expected; expected.readFromFile("soln_images/rainColorPickerTest.png");
//    REQUIRE(result == expected);

//}

//TEST_CASE("colorPicker::basic border","[weight=1][part=colorPicker]"){

//    PNG img;
//    img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);

//    HSLAPixel px1;
//    px1.h = 360.;
//    px1.s = 1.0; px1.l = 0.5;
//    HSLAPixel px2;

//    borderColorPicker borderPicker(px1, img, 0.4, px2);

//    PNG result = testColorPicker(borderPicker);
//    result.writeToFile("images/borderColorPickerTest.png");
//    PNG expected; expected.readFromFile("soln_images/borderColorPickerTest.png");
//    REQUIRE(result == expected);
//}


// ####################### Passed so far #######################


//TEST_CASE("fill::basic border dfs","[weight=1][part=fill]"){
//    PNG img;
//    img.readFromFile(SOLIDTESTIMAGE);
//    HSLAPixel px(200., 1.0, 0.5);

//    animation anim;
//    anim = filler::fillBorderDFS(img, SOLIDX, SOLIDY, px, SOLIDTOLERANCE, SOLIDFRAMEFREQ);
//    PNG result = anim.write("images/dfsborder.gif");
//    result.writeToFile("images/dfsborder.png");
//    PNG expected; expected.readFromFile("soln_images/dfsborder.png");
//    REQUIRE(result==expected);
//}

//TEST_CASE("fill::basic border bfs","[weight=1][part=fill]"){
//    PNG img;
//    img.readFromFile(SOLIDTESTIMAGE);
//    HSLAPixel px(200., 1.0, 0.5);

//    animation anim;
//    anim = filler::fillBorderBFS(img, SOLIDX, SOLIDY, px, SOLIDTOLERANCE, SOLIDFRAMEFREQ);
//    PNG result = anim.write("images/bfsborder.gif");
//    result.writeToFile("images/bfsborder.png");
//    PNG expected; expected.readFromFile("soln_images/bfsborder.png");
//    REQUIRE(result==expected);
//}

TEST_CASE("fill::basic dot dfs","[weight=1][part=fill]"){
    PNG img;
    img.readFromFile(GRIDTESTIMAGE);
    HSLAPixel px(40., 1.0, 0.5);

    animation anim;
    anim = filler::fillDotDFS(img, GRIDX, GRIDY, px, GRIDGRIDSPACING, DOTSIZE,
                                     GRIDTOLERANCE, GRIDFRAMEFREQ);
    PNG result = anim.write("images/demo/dfsdot.gif");
    result.writeToFile("images/demo/dfsdot.png");
//    PNG expected; expected.readFromFile("soln_images/dfsdot.png");
//    REQUIRE(result==expected);
}

TEST_CASE("fill::basic dot bfs","[weight=1][part=fill]"){
    PNG img;
    img.readFromFile(GRIDTESTIMAGE);
    HSLAPixel px(200., 1.0, 0.5);

    animation anim;
    anim = filler::fillDotBFS(img, GRIDX, GRIDY, px, GRIDGRIDSPACING, DOTSIZE,
                                     GRIDTOLERANCE, GRIDFRAMEFREQ);
    PNG result = anim.write("images/demo/bfsdot.gif");
    result.writeToFile("images/demo/bfsdot.png");
//    PNG expected; expected.readFromFile("soln_images/bfsdot.png");
//    REQUIRE(result==expected);
}

//TEST_CASE("fill::basic rainbow dfs","[weight=1][part=fill]"){

//    PNG img;
//    img.readFromFile(RAINTESTIMAGE);

//    animation anim;
//    anim = filler::fillRainDFS(img, RAINX, RAINY, RAINFREQ,
//                                         RAINTOLERANCE,
//                                         RAINFRAMEFREQ);
//    PNG result = anim.write("images/dfsrain.gif");
//    result.writeToFile("images/dfsrain.png");
//    PNG expected; expected.readFromFile("soln_images/dfsrain.png");
//    REQUIRE(result==expected);

//}
//TEST_CASE("fill::basic rainbow bfs","[weight=1][part=fill]"){

//    PNG img;
//    img.readFromFile(RAINTESTIMAGE);

//    animation anim;
//    anim = filler::fillRainBFS(img, RAINX, RAINY, RAINFREQ,
//                                         RAINTOLERANCE,
//                                         RAINFRAMEFREQ);
//    PNG result = anim.write("images/bfsrain.gif");
//    result.writeToFile("images/bfsrain.png");
//    PNG expected; expected.readFromFile("soln_images/bfsrain.png");
//    REQUIRE(result==expected);

//}

//  Demo
//TEST_CASE("fill::demo basic border dfs","[weight=1][part=fill]"){
//    PNG img;
//    img.readFromFile(DEMOTESTIMAGE);
//    HSLAPixel px(200., 1.0, 0.5);

//    animation anim;
//    anim = filler::fillBorderDFS(img, DEMOX, DEMOY, px, DEMOTOLERANCE, DEMOFRAMEFREQ);
//    PNG result = anim.write("images/demo/dfsborder.gif");
//    result.writeToFile("images/demo/dfsborder.png");
//}

//TEST_CASE("fill::demo basic border bfs","[weight=1][part=fill]"){
//    PNG img;
//    img.readFromFile(DEMOTESTIMAGE);
//    HSLAPixel px(200., 1.0, 0.5);

//    animation anim;
//    anim = filler::fillBorderBFS(img, DEMOX, DEMOY, px, DEMOTOLERANCE, DEMOFRAMEFREQ);
//    PNG result = anim.write("images/demo/bfsborder.gif");
//    result.writeToFile("images/demo/bfsborder.png");
//}


