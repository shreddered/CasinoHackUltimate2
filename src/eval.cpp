#include "coin/math/eval.hpp"
#include "coin/math/fraction.hpp"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <tesseract/baseapi.h>
#include <tesseract/publictypes.h>

namespace coin::math {

EvalException::EvalException(const std::string& msg) noexcept
    : std::runtime_error{msg} {}

std::string wrap(const std::string& input) {
    std::string result{};
    for (const auto& c : input) {
        if (std::isspace(c))
            continue;
        if (c == '"')
            result += '*';
        else if (c == 'z' || c == 'Z')
            result += '2';
        else if (c == 'o' || c == 'O')
            result += '0';
        else if (c == '/')
            result += '7';
        else if (c == ']' || c == '[' || c == 'l' || c == 'I' || c == 'i')
			result += '1';
        else
            result += c;
    }
    return result;
}

std::string wrap2(const std::string& input) {
    std::string result{};
    for (const auto& c : input) {
        if (std::isspace(c))
            continue;
        if (c == '"' || c == 'o')
            result += '*';
        else if (c == '7')
            result += '/';
        else
            result += c;
    }
    return result;
}

std::string eval(const std::string& image) {
    cv::Mat img = cv::imdecode(std::vector<uint8_t>{image.begin(), image.end()}, cv::IMREAD_GRAYSCALE);
    cv::Mat dst;
    cv::threshold(img, dst, 127, 255, cv::THRESH_BINARY);
    cv::Rect num1 = cv::Rect(220 - 80, 214 - 40, 140, 90),
             den1 = cv::Rect(220 - 60, 334 - 40, 120, 90),
             num2 = cv::Rect(480 - 60, 214 - 40, 120, 90),
             den2 = cv::Rect(480 - 60, 334 - 40, 120, 90),
             oper = cv::Rect(350 - 60, 214 - 40, 120, 140);
    auto recognizeRect = [&dst](cv::Rect rect, tesseract::PageSegMode psm) {
        tesseract::TessBaseAPI tess;
        if (tess.Init(nullptr, "eng")) {
            throw EvalException{"Cannot init Tesseract API"};
        }
        cv::Mat cropped = dst(rect);
        tess.SetImage(cropped.data, cropped.size().width, cropped.size().height, cropped.channels(), cropped.step1());
        tess.SetPageSegMode(psm);
        return std::string{tess.GetUTF8Text()};
    };
    std::vector<std::string> v = {
        wrap(recognizeRect(num1, tesseract::PSM_SINGLE_WORD)),
        wrap(recognizeRect(num2, tesseract::PSM_SINGLE_WORD)),
        wrap(recognizeRect(den1, tesseract::PSM_SINGLE_WORD)),
        wrap(recognizeRect(den2, tesseract::PSM_SINGLE_WORD))
    };
    for (const auto& elem : v) {
        std::cout << elem << ' ';
    }
    std::endl(std::cout);
    try {
        Fraction<int> f1(std::stoi(v[0]), std::stoi(v[2])),
                    f2(std::stoi(v[1]), std::stoi(v[3]));
        std::string s = wrap2(recognizeRect(oper, tesseract::PSM_SINGLE_CHAR));
        switch(s.front()) {
            case '+':
                return (f1 + f2).toString();
            case '/':
                return (f1 / f2).toString();
            case '*':
                return (f1 * f2).toString();
            case '-':
                return (f1 - f2).toString();
            default:
                throw EvalException{"Unknown operator: " + s};
        }
    } catch(std::invalid_argument e) {
        throw EvalException{"stoi failed"};
    }
}

} // namespace coin::math
