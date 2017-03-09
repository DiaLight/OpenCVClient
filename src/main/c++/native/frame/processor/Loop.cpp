//
// Created by dialight on 06.11.16.
//

#include <frame/processor/Loop.hpp>
#include <utils/MacroEnumString.hpp>
#include <utils/CvUtils.hpp>
#include <opencv/OpenCVWrap.hpp>
#include <utils/DrawUtils.hpp>
#include <triangle_detect/platov_aleksey/PATriangleDetect.hpp>
#include <triangle_detect/ilin_pavel/IPTDHough.hpp>
#include <triangle_detect/ilin_pavel/IPTDContours.hpp>
#include <triangle_detect/ilin_pavel/IPTDManual.hpp>
#include <tld/TLDWrap.hpp>

#define MethodsMacro(m) \
    m(RAW, "Без оработки") \
    m(MANUAL_TEST, "Тест") \
    m(PATD, "Платов Алексей. Поиск треугольников.") \
    m(IPTD_HOUGH, "Ильин Павел. Преобразование Хафа") \
    m(IPTD_CONTOURS, "Ильин Павел. Контуры") \
    m(IPTD_MANUAL, "Ильин Павел. Вручную") \
    m(LINES, "поиск линий") \
    m(CONTOURS, "контуры") \
    m(BLUR_TEST, "Тест блюра") \
    m(KENNY_TEST, "Тест метода Кенни") \
    m(HARRIS_TEST, "Тест метода Харриса") \
    m(THRESHOLD_TEST, "Тест порогового преобразования") \
    m(ADAPTIVE_THRESHOLD_TEST, "Тест адаптивного порогового преобразования") \
    m(TLD, "Tracking learning detection")
ENUM_STRING(MethodsMacro, Methods)

static PATriangleDetect patd;
static IPTDHough iptdHough;
static IPTDContours iptdContours;
static IPTDManual iptdManual;

Loop::Loop(SimpleConfig *cfg) : cfg(cfg), tldWrap(cfg->tldPath) {

}

void Loop::init(cv::Mat &frame) {
    tldWrap.init(frame);
}

void Loop::handle(cv::Mat &frame) {
    switch(props.getSelect("::method", &Methods::all, Methods::TLD)) {
        case Methods::RAW: break;
        case Methods::MANUAL_TEST: {
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            CVWrap::gaussianBlur(gray);
            CVWrap::adaptiveThreshold(gray);
            bitwise_not(gray, gray);
            CVWrap::canny(gray); //обводит резкие линии(детектор границ Кенни)
            vector<Line4i> lines;
            CVWrap::houghLines(gray, lines);
            cvtColor(gray, frame, COLOR_GRAY2BGR);
            DrawUtils::showLines(frame, lines);
            break;
        }
        case Methods::PATD:
            frame = patd.loop(frame);
            break;
        case Methods::IPTD_HOUGH:
            iptdHough.loop(frame);
            break;
        case Methods::IPTD_CONTOURS: {
            iptdContours.loop(frame);
            break;
        }
        case Methods::IPTD_MANUAL: {
            iptdManual.loop(frame);
            break;
        }
        case Methods::LINES: {
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            CVWrap::gaussianBlur(gray, 7, 1.5);
            CVWrap::canny(gray);
            vector<Line4i> lines;
            CVWrap::houghLines(gray, lines);
            cvtColor(gray, frame, COLOR_GRAY2BGR);
            DrawUtils::showLines(frame, lines);
            break;
        }
        case Methods::CONTOURS: {
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            CVWrap::gaussianBlur(gray);
            CVWrap::adaptiveThreshold(gray);
//            CVWrap::canny(gray, 60, 80);

            vector<vector<Point>> contours;
            vector<Vec4i> hierarchy;
            CVWrap::findContours(gray, contours, hierarchy);

            vector<vector<Point>> filtered;
            CvUtils::filterContoursBySize(contours, filtered, 20, 600);

            vector<vector<Point>> aprox;
            CVWrap::approxPolyDP(filtered, aprox);

            vector<vector<Line4i>> lineContours;
            CvUtils::contoursToLines(aprox, lineContours);

            DrawUtils::showLineContours(frame, lineContours);
            break;
        }
        case Methods::BLUR_TEST:
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            CVWrap::gaussianBlur(gray);
            frame = gray;
            break;
        case Methods::KENNY_TEST:
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            CVWrap::gaussianBlur(gray);
            CVWrap::canny(gray, 30, 60);
            frame = gray;
            break;
        case Methods::HARRIS_TEST:{
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            CVWrap::gaussianBlur(gray);
            vector<Point2i> corners;
            CVWrap::harris(gray, corners);
            DrawUtils::showPoints(gray, corners);
//        cv::Sobel(mat, mat, CV_32FC1 , 1, 0, 3, BORDER_DEFAULT);
//        cv::Sobel(mat, mat, CV_32FC1 , 0, 1, 3, BORDER_DEFAULT);
            frame = gray;
            break;
        }
        case Methods::THRESHOLD_TEST: //тест порогового преобразования на блюре
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            CVWrap::gaussianBlur(gray, 3, 0.0);
            CVWrap::threshold(gray);
            frame = gray;
            break;
        case Methods::ADAPTIVE_THRESHOLD_TEST: //тест адаптивного порогового преобразования на блюре
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            CVWrap::gaussianBlur(gray, 3, 0.0);
            CVWrap::adaptiveThreshold(gray);
            bitwise_not(gray, gray);
            frame = gray;
            break;
        case Methods::TLD:
            tldWrap.handle(frame);
            break;
        default:break;
    }
}


