//
// Created by dialight on 06.11.16.
//

#include <Loop.hpp>
#include <utils/MacroEnumString.hpp>
#include <opencv/Utils.hpp>

Loop::Loop(Tool *tool) : tool(tool) {

}

#define MethodsMacro(m) \
    m(RAW, "Без оработки") \
    m(MANUAL_TEST, "Тест") \
    m(PA_TRIANGLES, "Платов Алексей. Поиск треугольников.") \
    m(IP_TRIANGLES, "Ильин Павел. Поиск треугольников.") \
    m(LINES, "поиск линий") \
    m(CONTOURS, "контуры") \
    m(BLUR_TEST, "Тест блюра") \
    m(KENNY_TEST, "Тест метода Кенни") \
    m(HARRIS_TEST, "Тест метода Харриса") \
    m(THRESHOLD_TEST, "Тест порогового преобразования") \
    m(ADAPTIVE_THRESHOLD_TEST, "Тест адаптивного порогового преобразования")
ENUM_STRING(MethodsMacro, Methods)

#define PATriMacro(m) \
    m(SMOOTH, "Сглаживание") \
    m(GRAY, "Серые тона") \
    m(BORDER_DETECT, "Поиск границ") \
    m(FIND_LINES, "Поиск линий") \
    m(FILTER_LINES, "Фильтр линий") \
    m(FIND_TRIANGLES, "Поиск треугольников") \
    m(FINAL, "Итог")
ENUM_STRING(PATriMacro, PATriStages)

#define IPTriMacro(m) \
    m(SMOOTH, "Сглаживание") \
    m(GRAY, "Серые тона") \
    m(HARRIS, "Метод Харриса") \
    m(FILTER_CORNERS, "Фильтр точек") \
    m(ADAPTIVE_THRESHOLD, "Адаптивное пороговое преобразование") \
    m(CANNY, "Метод Кенни") \
    m(FIND_LINES, "Поиск линий") \
    m(FILTER_LINES, "Фильтр линий") \
    m(FIND_BORDERS, "Поиск границ") \
    m(FILTER_BORDERS, "Фильтр границ") \
    m(FIND_TRIANGLES, "Поиск треугольников") \
    m(FINAL, "Итог")
ENUM_STRING(IPTriMacro, IPTriStages)

Mat Loop::loop(Mat frame) {
    switch(props.getSelect("method", &Methods::all, Methods::RAW)) {
        case Methods::RAW: break;
        case Methods::MANUAL_TEST: { //тест адаптивного порогового преобразования на блюре
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            tool->gaussianBlur(gray);
            tool->adaptiveThreshold(gray);
            bitwise_not(gray, gray);
            tool->canny(gray); //обводит резкие линии(детектор границ Кенни)
            vector<Line4i> lines;
            tool->houghLines(gray, lines);
            tool->showLines(gray, lines);
            return gray;
        }
        case Methods::PA_TRIANGLES: {
            int stage = props.getSelect("PATriangle.stage", &PATriStages::all, PATriStages::BORDER_DETECT);
            // обработка изображения (сглаживание и др.)
//            pa_triangle.filterImage(frame);
            tool->gaussianBlur(frame, 7, 1.5);
            if(stage == PATriStages::SMOOTH) return frame;
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            if(stage == PATriStages::GRAY) return gray;
//            tool->canny(gray, 20, 120);
            tool->canny(gray, 90, 100); //обводит резкие линии(детектор границ Кенни)
//            tool->harris(gray);
            if(stage == PATriStages::BORDER_DETECT) return gray;
            //Устанавливаем ROI(Область интересов)
            //int x = 50, y = 30, width = 500, height = 410;
            //cvSetImageROI(dst, cvRect(x,y,width,height));
            //cvAddS(image, cvScalar(add), dst);
            //получаем отрезки
            vector<Line4i> lines;
            tool->houghLines(gray, lines);
            if(stage == PATriStages::FIND_LINES) {
                tool->showLines(gray, lines);
                return gray;
            }
            vector<Line4i> filtered;
            filterLines(lines, filtered);
            if(stage == PATriStages::FILTER_LINES) {
                tool->showLines(gray, filtered);
                return gray;
            }
            vector<PATriangle> triangles;
            pa_triangle.findTriangles(filtered, frame.cols, triangles);
            if(stage == PATriStages::FIND_TRIANGLES) {
                pa_triangle.showTriangles(gray, triangles);
                return gray;
            }
            pa_triangle.show(frame, triangles);
            return frame;
        }
        case Methods::IP_TRIANGLES:{
            int stage = props.getSelect("IPTriangle.stage", &IPTriStages::all, IPTriStages::FIND_BORDERS);

            tool->gaussianBlur(frame, 7, 1.5);
            if(stage == IPTriStages::SMOOTH) return frame;

            cvtColor(frame, gray, COLOR_BGR2GRAY);
            if(stage == IPTriStages::GRAY) return gray;

            vector<Point2i> corners;
            tool->harris(gray, corners);
            if(stage == IPTriStages::HARRIS) {
                tool->showPoints(frame, corners);
                stringstream ss;
                ss << "corners: " << corners.size();
                cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
                return frame;
            }

            vector<Point2i> fcorners;
            filterPoints(corners, fcorners);
            if(stage == IPTriStages::FILTER_CORNERS) {
                tool->showPoints(frame, fcorners);
                stringstream ss;
                ss << "filtered corners: " << fcorners.size();
                cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
                int i = 2;
                for(auto &p : fcorners) {
                    stringstream ss2;
                    ss2 << "[" << p.x << ", " << p.y << "]";
                    cv::putText(frame, ss2.str(), Point2i(10, 22 * i++), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
                }
                return frame;
            }

            tool->adaptiveThreshold(gray);
            bitwise_not(gray, gray);
            if(stage == IPTriStages::ADAPTIVE_THRESHOLD) return gray;

            tool->canny(gray);
            if(stage == IPTriStages::CANNY) return gray;

            vector<Line4i> lines;
            tool->houghLines(gray, lines);
            if(stage == IPTriStages::FIND_LINES) {
                tool->showLines(frame, lines);
                stringstream ss;
                ss << "lines: " << lines.size();
                cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
                return frame;
            }

            vector<Line4i> flines;
            filterLines(lines, flines);
            if(stage == IPTriStages::FILTER_LINES) {
                tool->showLines(frame, flines);
                stringstream ss;
                ss << "filtered lines: " << flines.size();
                cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
                int i = 2;
                for(auto &l : flines) {
                    cv::putText(frame, l.toString().c_str(), Point2i(10, 22 * i++), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
                }
                return frame;
            }

            vector<Line4i> borders;
            ip_triangle.findBorders(fcorners, flines, borders);
            if(stage == IPTriStages::FIND_BORDERS) {
                tool->showLines(frame, borders);
                stringstream ss;
                ss << "borders: " << borders.size();
                cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
                int i = 2;
                for(auto &l : borders) {
                    cv::putText(frame, l.toString().c_str(), Point2i(10, 22 * i++), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
                }
                return frame;
            }

            vector<Line4i> fborders;
            filterLines(borders, fborders);
            if(stage == IPTriStages::FILTER_BORDERS) {
                tool->showLines(frame, fborders);
                stringstream ss;
                ss << "filtered borders: " << fborders.size();
                cv::putText(frame, ss.str(), Point2i(10, 22), FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
                int i = 2;
                for(auto &l : fborders) {
                    cv::putText(frame, l.toString().c_str(), Point2i(10, 22 * i++), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(0, 0, 255), 1, LineTypes::LINE_AA);
                }
                return frame;
            }

            vector<Triangle12i> triangles;
            ip_triangle.findTriangles(fborders, triangles);
            if(stage == IPTriStages::FIND_TRIANGLES) {
                ip_triangle.showTriangles(gray, triangles);
                return gray;
            }
            ip_triangle.showTriangles(frame, triangles);
            return frame;
        }
        case Methods::LINES:{
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            tool->gaussianBlur(gray, 7, 1.5);
            tool->canny(gray);
            vector<Line4i> lines;
            tool->houghLines(gray, lines);
            tool->showLines(frame, lines);
            return frame;
        }
        case Methods::CONTOURS:
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            tool->gaussianBlur(gray);
            tool->adaptiveThreshold(gray);
//            tool->canny(gray, 60, 80);
            tool->findContours2(gray, frame);
            return frame;
        case Methods::BLUR_TEST:
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            tool->gaussianBlur(gray);
            return gray;
        case Methods::KENNY_TEST:
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            tool->gaussianBlur(gray);
            tool->canny(gray, 30, 60); //обводит резкие линии(детектор границ Кенни)
            return gray;
        case Methods::HARRIS_TEST:{
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            tool->gaussianBlur(gray);
            vector<Point2i> corners;
            tool->harris(gray, corners);
            tool->showPoints(gray, corners);
//        cv::Sobel(mat, mat, CV_32FC1 , 1, 0, 3, BORDER_DEFAULT);
//        cv::Sobel(mat, mat, CV_32FC1 , 0, 1, 3, BORDER_DEFAULT);
            return gray;
        }
        case Methods::THRESHOLD_TEST: //тест порогового преобразования на блюре
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            tool->gaussianBlur(gray, 3, 0.0);
            tool->threshold(gray);
            return gray;
        case Methods::ADAPTIVE_THRESHOLD_TEST: //тест адаптивного порогового преобразования на блюре
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            tool->gaussianBlur(gray, 3, 0.0);
            tool->adaptiveThreshold(gray);
            bitwise_not(gray, gray);
            return gray;
        default:break;
    }
    return frame;
}
