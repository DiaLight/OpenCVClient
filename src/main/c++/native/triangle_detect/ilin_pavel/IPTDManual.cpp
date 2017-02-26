//
// Created by dialight on 26.02.17.
//
#include <triangle_detect/ilin_pavel/IPTDManual.hpp>

#include <opencv/OpenCVWrap.hpp>

using namespace std;
using namespace cv;

typedef struct Jump_t {
    Point p;
    bool toWhite;
    Jump_t(const Point p, bool toWhite) : p(p), toWhite(toWhite) {}
} Jump ;
typedef struct Pixel_t {
    int x;
    int y;
    uchar val;
    Pixel_t(int x, int y, uchar val) : x(x), y(y), val(val) {}
} Pixel;

class PixelIterator {
public:
    virtual bool hasNext() = 0;
    virtual Pixel next() = 0;
};

class HorisontalPixelIterator : public PixelIterator {
    Mat &gray;
    int accuracy;

    int x;
    int y;
    uchar *ptr;
public:
    HorisontalPixelIterator(Mat &gray, int accuracy, int y) : gray(gray), accuracy(accuracy), y(y) {
        x = accuracy;
        ptr = gray.ptr(y) + x;
    }

    bool hasNext() override {
        return x < gray.cols - accuracy;
    }

    Pixel next() override {
        uchar value = *ptr;
        ptr++;
        return Pixel(x++, y, value);
    }
};

class DiagPixelIterator : public PixelIterator {
    Mat &gray;
    int accuracy;
    int accSqr;
    Point &p;
    int back;

    int i;
public:
    DiagPixelIterator(Mat &gray, int accuracy, Point &p, int back) :
            gray(gray),
            accuracy(accuracy),
            p(p),
            back(back), i(0) {
        accSqr = accuracy * 2;
    }

    bool hasNext() override { return i < accSqr; }

    Pixel next() override {
        int x = p.x + i;
        int y = p.y + (accSqr - i) * back;
        ++i;
        uchar *ptr = gray.ptr(y) + x;
        uchar value = *ptr;
        return Pixel(x, y, value);
    }
};

void findJumps(Mat &gray, vector<Jump> &out, int accuracy, PixelIterator &pi) {
    bool white;
    int diff;
    Pixel p = pi.next();
    white = !p.val;
    diff = 0;
    Point diffP;
    while(pi.hasNext()) {
        p = pi.next();
        if(white ^ !p.val) {
            if(diff == 0) {
                diffP.x = p.x;
                diffP.y = p.y;
            }
            diff++;
            if(diff >= accuracy) {
                white = !white;
                out.push_back(Jump(diffP, white));
                diff = 0;
            }
        } else if(diff) diff = 0;
    }
}

void IPTDManual::loop(Mat &frame) {
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    CVWrap::otsu(gray);

    int accuracy = 10;

    vector<Jump> points;
    HorisontalPixelIterator pi(gray, accuracy, (gray.rows / 2) - 0);
    findJumps(gray, points, accuracy, pi);

    cvtColor(gray, frame, COLOR_GRAY2BGR);

    int accSqr = accuracy * 2;
    for(auto &j : points) {

        int w = 0;
        int b = 0;
        for (int y = j.p.y - accuracy; y <= j.p.x + accuracy; ++y) {
            uchar *ptr = gray.ptr(y) + j.p.x - accuracy;
            for (int x = 0; x <= accSqr; ++x) {
                if(*ptr) w++;
                else b++;
                ptr++;
            }
        }
        if(abs((float) w / b - 1.0f) > 0.4) {
            continue;
        }

        int ver = 0;
        for (int i = 1; i <= accuracy; ++i) {
            uchar *ptr = gray.ptr(j.p.y - i) + j.p.x;
            if(*ptr) ver++;
        }
        int back = ((float) ver / accuracy > 0.5f) ^ j.toWhite ? 1 : -1;
        Point from = Point2i(j.p.x - accuracy, j.p.y - accuracy * back);
        Point to = Point2i(j.p.x + accuracy, j.p.y + accuracy * back);
        cv::line(frame, from, to, Scalar(0, 255, 0), 2);

        vector<Jump> points2;
        DiagPixelIterator dpi(gray, accSqr, j.p, back);
        findJumps(gray, points2, accuracy, dpi);
        for(auto const &k : points2) {
            cv::circle(frame, k.p, 2, Scalar(0, 0, 255), 2, LineTypes::LINE_AA);
        }

    }
}
