#ifndef CONSTANTS_H
#define CONSTANTS_H


struct ARDUCAM {
    static const int PWDN_GPIO_NUM = 32;
    static const int RESET_GPIO_NUM = -1;
    static const int XCLK_GPIO_NUM = 0;
    static const int SIOD_GPIO_NUM = 26;
    static const int SIOC_GPIO_NUM = 27;
    static const int Y9_GPIO_NUM = 35;
    static const int Y8_GPIO_NUM = 34;
    static const int Y7_GPIO_NUM = 39;
    static const int Y6_GPIO_NUM = 36;
    static const int Y5_GPIO_NUM = 21;
    static const int Y4_GPIO_NUM = 19;
    static const int Y3_GPIO_NUM = 18;
    static const int Y2_GPIO_NUM = 5;
    static const int VSYNC_GPIO_NUM = 25;
    static const int HREF_GPIO_NUM = 23;
    static const int PCLK_GPIO_NUM = 22;
};

struct WIFI {
    static const char* ssidMat1;
    static const char* passwordMat1;
    static const char* ssidMat2;
    static const char* passwordMat2;
    static const char* ssidEsp12;
    static const char* passwordEsp12;

};

struct WIFI_HOTSPOT {
    static const char* ssidDiffusion;
    static const char* passwordDiffusion;
};


const char* WIFI::ssidMat1 = "Bbox-324A417C";
const char* WIFI::passwordMat1 = "Evy3PmrR3arAJPmUeG";
const char* WIFI::ssidMat2 = "Bbox-5DD39C3D";
const char* WIFI::passwordMat2 = "rV4J4MfDZsh7h1146V";
const char* WIFI::ssidEsp12 = "Matlo_Hotspot";
const char* WIFI::passwordEsp12 = "HotspotRobot!";
const char* WIFI_HOTSPOT::ssidDiffusion = "Matlo_Hotspot";
const char* WIFI_HOTSPOT::passwordDiffusion = "HotspotRobot!";


#endif //CONSTANTS_H
