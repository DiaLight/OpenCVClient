//
// Created by dialight on 29.11.16.
//

#include <triangle_detect/platov_aleksey/PATriangleDetect.hpp>

#include <utils/MacroEnumString.hpp>
#include <utils/CvUtils.hpp>
#include <opencv/OpenCVWrap.hpp>
#include <utils/DrawUtils.hpp>


#define PATriMacro(m) \
    m(SMOOTH, "Сглаживание") \
    m(GRAY, "Серые тона") \
    m(BORDER_DETECT, "Поиск границ") \
    m(FIND_LINES, "Поиск линий") \
    m(FILTER_LINES, "Фильтр линий") \
    m(FIND_TRIANGLES, "Поиск треугольников") \
    m(FINAL, "Итог")
ENUM_STRING(PATriMacro, PATriStages)

Mat PATriangleDetect::loop(Mat &frame) {
    int stage = props.getSelect("PATriangle.stage", &PATriStages::all, PATriStages::BORDER_DETECT);
    // обработка изображения (сглаживание и др.)
//            patd.filterImage(frame);
    CVWrap::gaussianBlur(frame, 7, 1.5);
    if(stage == PATriStages::SMOOTH) return frame;

    cvtColor(frame, gray, COLOR_BGR2GRAY);
    if(stage == PATriStages::GRAY) return gray;

//            CVWrap::canny(gray, 20, 120);
    CVWrap::canny(gray, 90, 100); //обводит резкие линии(детектор границ Кенни)
//            CVWrap::harris(gray);
    if(stage == PATriStages::BORDER_DETECT) return gray;

    //Устанавливаем ROI(Область интересов)
    //int x = 50, y = 30, width = 500, height = 410;
    //cvSetImageROI(dst, cvRect(x,y,width,height));
    //cvAddS(image, cvScalar(add), dst);
    //получаем отрезки
    vector<Line4i> lines;
    CVWrap::houghLines(gray, lines);
    if(stage == PATriStages::FIND_LINES) {
        DrawUtils::showLines(gray, lines);
        return gray;
    }

    vector<Line4i> filtered;
    CvUtils::filterLines(lines, filtered);
    if(stage == PATriStages::FILTER_LINES) {
        DrawUtils::showLines(gray, filtered);
        return gray;
    }

    vector<PATriangle> triangles;
    findTriangles(filtered, frame.cols, triangles);
    if(stage == PATriStages::FIND_TRIANGLES) {
        showTriangles(gray, triangles);
        return gray;
    }

    show(frame, triangles);
    return frame;
}

bool PATriangleDetect::triangleCompare(Point2i p, Point2i q, int area) {
    return abs(q.x - p.x) <= area &&
           abs(q.y - p.y) <= area;
}

Point2i PATriangleDetect::posTriangle(Line4i *t) {
    Point2i pos;
    for (int i = 0; i < 3; i++) {
        pos += t[i].p1;
        pos += t[i].p2;
    }
    pos /= 6;
    return pos;
}

void PATriangleDetect::showTriangles(Mat &frame, vector<PATriangle> const &triangles) {
    RNG rng(12345);
    for(auto const& tr : triangles) {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
        for (int j = 0; j < 3; j++) {
            Line4i const& l = tr.lines[j];
            cv::line(frame, l.p1, l.p2, color, 3, CV_AA);
        }
        cv::circle(frame, tr.cur_pos, 2, color, 1, LINE_AA);
    }
}

void PATriangleDetect::findTriangles(const vector<Line4i> &lines, int width, vector<PATriangle> &triangles) {
    int line_length = (int) lines.size();
    // Детектирование треугольников
    for (int i = 0; i < line_length; i++) {
        for (int j = i + 1; j < line_length; j++) {
            // выбор первых двух отрезков
            Line4i l1 = lines[i];
            Line4i l2 = lines[j];
            Line4i pl3 = CvUtils::testTriangle(l1, l2, area);

            if(!pl3.isEmpty()) {
                for (int k = j + 1; k < line_length; k++) {
                    Line4i l3 = lines[k];
                    if(CvUtils::linesCompare(l3, pl3)) {
                        bool bad = false;
                        PATriangle newTr(l1, l2, l3);
                        newTr.fst_pos = posTriangle(newTr.lines);
                        // сравнение с имеющимися треугольниками
                        for(auto &tr : triangles) {
                            if (triangleCompare(tr.cur_pos, newTr.fst_pos, 150)) {
                                tr.cur_pos = newTr.fst_pos;
                                bad = true;
                                break;
                            }
                        }

                        if (checkCloseBorderline(newTr.fst_pos, width)) {
                            bad = true;
                        }
                        // запоминание треугольника
                        if (!bad) {
                            newTr.cur_pos = newTr.fst_pos;
                            newTr.checked = false;

                            triangles.push_back(newTr);
                        }
                    }
                }
            }
        }
    }
}
