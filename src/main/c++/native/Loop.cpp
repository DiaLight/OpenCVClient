//
// Created by dialight on 06.11.16.
//

#include <Loop.hpp>
#include <utils/MacroEnumString.hpp>
#include <opencv/Utils.hpp>
#include <opencv/OpenCVWrap.hpp>
#include <opencv/DrawUtils.hpp>

#define MethodsMacro(m) \
    m(RAW, "Без оработки") \
    m(MANUAL_TEST, "Тест") \
    m(PA_TRIANGLES, "Платов Алексей. Поиск треугольников.") \
    m(IP_TRIANGLES, "Ильин Павел. Поиск треугольников.") \
    m(IP_TRIANGLES2, "Ильин Павел. Поиск треугольников 2.") \
    m(LINES, "поиск линий") \
    m(CONTOURS, "контуры") \
    m(BLUR_TEST, "Тест блюра") \
    m(KENNY_TEST, "Тест метода Кенни") \
    m(HARRIS_TEST, "Тест метода Харриса") \
    m(THRESHOLD_TEST, "Тест порогового преобразования") \
    m(ADAPTIVE_THRESHOLD_TEST, "Тест адаптивного порогового преобразования")
ENUM_STRING(MethodsMacro, Methods)

void Loop::loop(Mat &frame) {
    switch(props.getSelect("method", &Methods::all, Methods::IP_TRIANGLES2)) {
        case Methods::RAW: break;
        case Methods::MANUAL_TEST: { //тест адаптивного порогового преобразования на блюре
            if(frame.type() == CV_16SC3) {

            }
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            CVWrap::gaussianBlur(gray);
            CVWrap::adaptiveThreshold(gray);
            bitwise_not(gray, gray);
            CVWrap::canny(gray); //обводит резкие линии(детектор границ Кенни)
            vector<Line4i> lines;
            CVWrap::houghLines(gray, lines);
            DrawUtils::showLines(gray, lines);
            frame = gray;
            break;
        }
        case Methods::PA_TRIANGLES:
            pa_triangle.loop(frame);
            break;
        case Methods::IP_TRIANGLES:
            ip_triangle.loop(frame);
            break;
        case Methods::IP_TRIANGLES2: {
            vector<Triangle12i> triangles;
            ip_triangle2.find(frame, triangles);
            Triangle12i *big = nullptr;
            int bigArea = 0;
            for(auto &t : triangles) {
                int curArea = t.getAABB().area();
                if(big == nullptr || curArea > bigArea) {
                    bigArea = curArea;
                    big = &t;
                }
            }
            if(big == nullptr) break;
            if(last.isEmpty()) {
                color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
                last = *big;
                edison.transmit();
                break;
            }

            const Point2i &p1 = big->getCenter();
            const Point2i &p2 = last.getCenter();
            Point2i v = p1 - p2;
            double distance = sqrt(v.x*v.x + v.y*v.y);
            if(distance > 100) {
                color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
                edison.transmit();
            }else{
                cv::line(frame, p1, p2, color, 2, LineTypes::LINE_AA);
            }
            DrawUtils::showTriangle(frame, *big, color);
            last = *big;
            break;
        }
        case Methods::LINES:{
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            CVWrap::gaussianBlur(gray, 7, 1.5);
            CVWrap::canny(gray);
            vector<Line4i> lines;
            CVWrap::houghLines(gray, lines);
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
            Utils::filterContoursBySize(contours, filtered, 20, 600);

            vector<vector<Point>> aprox;
            CVWrap::approxPolyDP(filtered, aprox);

            vector<vector<Line4i>> lineContours;
            Utils::contoursToLines(aprox, lineContours);

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
        default:break;
    }
}
