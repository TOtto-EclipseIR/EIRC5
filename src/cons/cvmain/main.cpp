#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>


cv::CascadeClassifier face_cascade;

void matInfo(const cv::Mat &mat)
{
    std::cout << mat.rows << "x" << mat.cols
              << " type: " << mat.type() << " CV8UC3=" << CV_8UC3 << " "
              << mat.total() << " 0x" << std::hex << &mat.data << std::dec << std::endl;
}

bool isNull(const cv::Mat &mat)
{
    return mat.rows <= 0 || mat.cols <= 0 || NULL == mat.data;
}

bool isValid(const cv::Mat &mat)
{
    if (isNull(mat)) return false;
    // TODO more
    return true;
}

int main(int argc, char *argv[])
{
    (void)argc;
    std::cout << "Hello " << argv[0] << " compiled " << __TIME__ << " " << __DATE__ << std::endl;
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;

    if (face_cascade.load("D:/bin/detectors/v4/haarcascade_frontalcatface_extended.Xml"))
    {
        std::cout << "face_cascade.load() " << "D:/bin/detectors/v4/haarcascade_frontalcatface_extended.Xml" << " loaded" << std::endl;
        std::cout << "face_cascade.empty() " << (face_cascade.empty() ? "true!" : "FALSE") << std::endl;
    }
    else
    {
        std::cerr << "face_cascade.load() " << "D:/bin/detectors/v4/haarcascade_frontalcatface_extended.Xml" << " failed"<< std::endl;
        return 1;
    }

    cv::Mat inputMat = cv::imread("D:/INDIface/INDIin/console/hide/18yoTwins.jpg", cv::IMREAD_COLOR);
    matInfo(inputMat);
    std::cout << "inputMat is " << (isValid(inputMat) ? "valid" : "INVALID") << std::endl;
    cv::imshow("inputMat", inputMat);
    cv::waitKey();

    cv::Mat detectMat;
    cv::cvtColor(inputMat, detectMat, cv::COLOR_BGR2GRAY);
    matInfo(detectMat);
    cv::imshow("detectMat", detectMat);
    cv::waitKey();

    std::vector<cv::Rect> faceRects;
    face_cascade.detectMultiScale(detectMat, faceRects, 1.01, 1); // , cv::CASCADE_DO_ROUGH_SEARCH);
    std::cout << faceRects.size() << " Face Rectangles Detected" << std::endl;

    cv::Mat outputMat = inputMat;
    for (int x = 0; x < faceRects.size(); ++x)
    {
        cv::Rect rc = faceRects[x];
        cv::circle(outputMat,
                   cv::Point(rc.x + rc.width/2,
                             rc.y + rc.height/2),
                   (rc.width + rc.height) / 2,
                   cv::Scalar(255, 255, 0),
                   3);
    }
    matInfo(outputMat);
    cv::imshow("outputMat", outputMat);
    cv::waitKey();

    return 0;
}
