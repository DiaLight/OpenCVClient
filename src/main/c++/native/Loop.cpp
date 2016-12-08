//
// Created by dialight on 06.11.16.
//

#include <Loop.hpp>
#include <utils/MacroEnumString.hpp>

Loop::Loop(Tool *tool) : tool(tool) {

}

#define MethodsMacro(m) \
    m(RAW, "Без оработки") \
    m(PA_TRIANGLES, "Платов Алексей. Поиск треугольников.") \
    m(LINES, "поиск линий") \
    m(CONTOURS, "контуры") \
    m(BLUR_TEST, "Тест блюра") \
    m(KENNY_TEST, "Тест метода Кенни") \
    m(HARRIS_TEST, "Тест метода Харриса") \
    m(THRESHOLD_TEST, "Тест порогового преобразования") \
    m(ADAPTIVE_THRESHOLD_TEST, "Тест адаптивного порогового преобразования")
ENUM_STRING(MethodsMacro, Methods, MethodsMap)

#define PATriMacro(m) \
    m(SMOOTH, "Сглаживание") \
    m(GRAY, "Серые тона") \
    m(BORDER_DETECT, "Поиск границ") \
    m(FIND_LINES, "Поиск линий") \
    m(FILTER_LINES, "Фильтр линий") \
    m(FIND_TRIANGLES, "Поиск треугольников") \
    m(FINAL, "Итог")
ENUM_STRING(PATriMacro, PATriStages, PATriStagesMap)

Mat Loop::loop(Mat frame) {
    switch(props.getSelect("method", &MethodsMap, Methods::PA_TRIANGLES)) {
        case Methods::RAW: break;
        case Methods::PA_TRIANGLES:{
            // обработка изображения (сглаживание и др.)
            int stage = props.getSelect("PATriangle.stage", &PATriStagesMap, PATriStages::BORDER_DETECT);
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
            pa_triangle.filterLines(lines, filtered);
            if(stage == PATriStages::FILTER_LINES) {
                tool->showLines(gray, filtered);
                return gray;
            }
            vector<Triangle> triangles;
            pa_triangle.findTriangles(filtered, frame.cols, triangles);
            if(stage == PATriStages::FIND_TRIANGLES) {
                pa_triangle.showTriangles(gray, triangles);
                return gray;
            }
            pa_triangle.show(frame, triangles);
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
        case Methods::HARRIS_TEST:
            cvtColor(frame, gray, COLOR_BGR2GRAY);
            tool->gaussianBlur(gray);
            tool->harris(gray);
            return gray;
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
