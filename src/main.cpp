//
// Created by yang on 2020-10-12.
//

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

inline double max(double a, double b, double c) {
    if (a > b && a > c) {
        return a;
    } else if (b > c)
        return b;
    return c;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <video path> <output path>" << endl;
        exit(0);
    }

    VideoCapture cap;
    cap.open(argv[1]);
    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    vector<float> avgs;

    int totalFrames = int(cap.get(CV_CAP_PROP_FRAME_COUNT));

    while (1) {
        Mat frame;
        Mat frame_LAB;
        Mat channels[3];
        Mat grads[3];
        int nRows, nCols;
        // Capture frame-by-frame
        cap >> frame;
        nRows = frame.rows;
        nCols = frame.cols;

        int currentFrame = int(cap.get(CV_CAP_PROP_POS_FRAMES));
        cout << "\rFrame: " << currentFrame << '/' << totalFrames;
        cout.flush();
        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        cvtColor(frame, frame_LAB, COLOR_BGR2Lab);
        split(frame_LAB, channels);

        for (int i = 0; i < 3; i++) {
            Sobel(channels[i], grads[i], CV_64F, 1, 1);
        }

        Mat grad(nRows, nCols, CV_64F);
        double sum = 0;

        for (int i = 0; i < nRows; ++i) {
            double *gradL = grads[0].ptr<double>(i);
            double *gradA = grads[1].ptr<double>(i);
            double *gradB = grads[2].ptr<double>(i);
            double *gradMax = grad.ptr<double>(i);

            for (int j = 0; j < nCols; ++j) {
                gradMax[j] = max(gradL[j], gradA[j], gradB[j]);
                sum += gradMax[j];
            }
        }
        sum = sum / (nRows * nCols);
        avgs.push_back(sum);
    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    destroyAllWindows();

    ofstream out(argv[2], ios::out);
    for (float &avg: avgs) {
        out << avg << ' ';
    }
    out << endl;
    out.close();

    return 0;
}
