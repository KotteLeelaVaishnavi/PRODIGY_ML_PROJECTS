#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

struct Point {
    int x, y;
};

class HandGesture {
private:
    std::vector<Point> landmarks;

public:
    HandGesture(const std::vector<Point>& points) : landmarks(points) {}

    std::string recognize() {
        if (landmarks.size() != 21) {
            return "Invalid input: Expected 21 landmarks";
        }

        if (isClosedFist()) {
            return "Closed Fist";
        } else if (isOpenPalm()) {
            return "Open Palm";
        } else if (isPointingIndex()) {
            return "Pointing Index";
        } else if (isThumbsUp()) {
            return "Thumbs Up";
        } else if (isPeaceSign()) {
            return "Peace Sign";
        } else {
            return "Unknown Gesture";
        }
    }

private:
    bool isClosedFist() {
        // Check if all fingertips are close to the palm
        for (int i = 4; i <= 20; i += 4) {
            if (distance(landmarks[i], landmarks[0]) > 50) {
                return false;
            }
        }
        return true;
    }

    bool isOpenPalm() {
        // Check if all fingertips are extended
        for (int i = 4; i <= 20; i += 4) {
            if (distance(landmarks[i], landmarks[0]) < 100) {
                return false;
            }
        }
        return true;
    }

    bool isPointingIndex() {
        // Check if index finger is extended and others are closed
        return distance(landmarks[8], landmarks[0]) > 100 &&
               distance(landmarks[12], landmarks[0]) < 50 &&
               distance(landmarks[16], landmarks[0]) < 50 &&
               distance(landmarks[20], landmarks[0]) < 50;
    }

    bool isThumbsUp() {
        // Check if thumb is extended upwards and others are closed
        return landmarks[4].y < landmarks[3].y &&
               distance(landmarks[8], landmarks[0]) < 50 &&
               distance(landmarks[12], landmarks[0]) < 50 &&
               distance(landmarks[16], landmarks[0]) < 50 &&
               distance(landmarks[20], landmarks[0]) < 50;
    }

    bool isPeaceSign() {
        // Check if index and middle fingers are extended and others are closed
        return distance(landmarks[8], landmarks[0]) > 100 &&
               distance(landmarks[12], landmarks[0]) > 100 &&
               distance(landmarks[16], landmarks[0]) < 50 &&
               distance(landmarks[20], landmarks[0]) < 50;
    }

    double distance(const Point& p1, const Point& p2) {
        return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
    }
};

std::vector<Point> simulateHandLandmarks(const std::string& gesture) {
    std::vector<Point> landmarks(21);
    // Simulate landmark positions for different gestures
    if (gesture == "fist") {
        // All points close to the palm
        for (int i = 0; i < 21; ++i) {
            landmarks[i] = {i * 5, i * 5};
        }
    } else if (gesture == "open_palm") {
        // Fingertips extended
        for (int i = 0; i < 21; ++i) {
            landmarks[i] = {i * 10, i * 10};
        }
    } else if (gesture == "pointing") {
        // Index finger extended
        for (int i = 0; i < 21; ++i) {
            landmarks[i] = {i * 5, i * 5};
        }
        landmarks[8] = {80, 80}; // Extend index fingertip
    } else if (gesture == "thumbs_up") {
        // Thumb extended upwards
        for (int i = 0; i < 21; ++i) {
            landmarks[i] = {i * 5, i * 5};
        }
        landmarks[4] = {20, 0}; // Extend thumb upwards
    } else if (gesture == "peace") {
        // Index and middle fingers extended
        for (int i = 0; i < 21; ++i) {
            landmarks[i] = {i * 5, i * 5};
        }
        landmarks[8] = {80, 80}; // Extend index fingertip
        landmarks[12] = {120, 120}; // Extend middle fingertip
    }
    return landmarks;
}

int main() {
    std::vector<std::string> testGestures = {"fist", "open_palm", "pointing", "thumbs_up", "peace"};

    for (const auto& gesture : testGestures) {
        std::vector<Point> landmarks = simulateHandLandmarks(gesture);
        HandGesture handGesture(landmarks);
        std::string recognizedGesture = handGesture.recognize();
        std::cout << "Test Gesture: " << gesture << ", Recognized as: " << recognizedGesture << std::endl;
    }

    return 0;
}