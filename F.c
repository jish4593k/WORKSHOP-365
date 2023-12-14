#include "opencv2/opencv.hpp"

using namespace cv;

void empty(int) {
    // This function is empty as a placeholder for the callback
}

int main() {
    namedWindow("TrackBars", WINDOW_NORMAL);
    resizeWindow("TrackBars", 640, 240);

    createTrackbar("Hue min", "TrackBars", 0, 179, empty);
    createTrackbar("Hue max", "TrackBars", 179, 179, empty);
    createTrackbar("Saturation min", "TrackBars", 0, 255, empty);
    createTrackbar("Saturation max", "TrackBars", 255, 255, empty);
    createTrackbar("Value min", "TrackBars", 0, 255, empty);
    createTrackbar("Value max", "TrackBars", 255, 255, empty);

    while (true) {
        Mat img = imread("resources/lambo.png");
        Mat imgHSV;
        cvtColor(img, imgHSV, COLOR_BGR2HSV);

        int hueMin = getTrackbarPos("Hue min", "TrackBars");
        int hueMax = getTrackbarPos("Hue max", "TrackBars");
        int saturationMin = getTrackbarPos("Saturation min", "TrackBars");
        int saturationMax = getTrackbarPos("Saturation max", "TrackBars");
        int valueMin = getTrackbarPos("Value min", "TrackBars");
        int valueMax = getTrackbarPos("Value max", "TrackBars");

        Scalar lower(hueMin, saturationMin, valueMin);
        Scalar upper(hueMax, saturationMax, valueMax);
        Mat mask;
        inRange(imgHSV, lower, upper, mask);
        Mat finalImg;
        bitwise_and(img, img, finalImg, mask);

        std::cout << hueMin << " " << hueMax << " " << saturationMin << " " << saturationMax << " " << valueMin << " " << valueMax << std::endl;

        imshow("original", img);
        imshow("HSV", imgHSV);
        imshow("Mask", mask);
        imshow("final", finalImg);

        int key = waitKey(1);
        if (key == 27)  // Break the loop if the Esc key is pressed
            break;
    }

    return 0;
}
