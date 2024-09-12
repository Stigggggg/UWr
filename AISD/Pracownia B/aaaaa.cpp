#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Point {
    int x, y;
};

struct Triangle {
    Point p1, p2, p3;
};

bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

double dist(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double bruteForce(vector<Point>& points, int n, Triangle& minTriangle) {
    double minDist = numeric_limits<double>::max();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                double d = dist(points[i], points[j]) + dist(points[j], points[k]) + dist(points[k], points[i]);
                if (d < minDist) {
                    minDist = d;
                    minTriangle = {points[i], points[j], points[k]};
                }
            }
        }
    }
    return minDist;
}

double stripClosest(vector<Point>& strip, double d, Triangle& minTriangle) {
    double minDist = d;
    sort(strip.begin(), strip.end(), compareY);
    int n = strip.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n && strip[k].y - strip[i].y < minDist; ++k) {
                double d = dist(strip[i], strip[j]) + dist(strip[j], strip[k]) + dist(strip[k], strip[i]);
                if (d < minDist) {
                    minDist = d;
                    minTriangle = {strip[i], strip[j], strip[k]};
                }
            }
        }
    }
    return minDist;
}

double closestUtil(vector<Point>& points, int n, Triangle& minTriangle) {
    if (n <= 3) {
        return bruteForce(points, n, minTriangle);
    }

    int mid = n / 2;
    Point midPoint = points[mid];

    vector<Point> leftPoints(points.begin(), points.begin() + mid);
    vector<Point> rightPoints(points.begin() + mid, points.end());

    Triangle leftTriangle, rightTriangle;
    double dl = closestUtil(leftPoints, mid, leftTriangle);
    double dr = closestUtil(rightPoints, n - mid, rightTriangle);

    double d = min(dl, dr);

    // Find the strip
    vector<Point> strip;
    for (int i = 0; i < n; ++i) {
        if (abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    // Check for closest points in the strip
    Triangle stripTriangle;
    double dStrip = stripClosest(strip, d, stripTriangle);

    // Choose the minimum distance among dl, dr, and dStrip
    if (dStrip < d) {
        minTriangle = stripTriangle;
        return dStrip;
    } else if (dl < dr) {
        minTriangle = leftTriangle;
        return dl;
    } else {
        minTriangle = rightTriangle;
        return dr;
    }
}

double closest(vector<Point>& points, int n, Triangle& minTriangle) {
    sort(points.begin(), points.end(), compareX);
    return closestUtil(points, n, minTriangle);
}

int main() {
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    Triangle minTriangle;
    double minDist = closest(points, n, minTriangle);

    cout << minTriangle.p1.x << " " << minTriangle.p1.y << endl;
    cout << minTriangle.p2.x << " " << minTriangle.p2.y << endl;
    cout << minTriangle.p3.x << " " << minTriangle.p3.y << endl;

    return 0;
}