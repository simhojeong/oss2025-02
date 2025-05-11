#include <iostream>
using namespace std;

class Point {
    int x, y;
public:
    Point(int x = 0, int y = 0) { this->x = x; this->y = y; }
    int getX() { return x; }
    int getY() { return y; }
protected:
    void move(int x, int y) { this->x = x; this->y = y; }
};

class ColorPoint : public Point {
    char color[20];
public:
    ColorPoint(int x = 0, int y = 0, const char* color = "BLACK") : Point(x, y) {
        setColor(color);
    }

    void setPoint(int x, int y) {
        move(x, y);
    }

    void setColor(const char* color) {
        int i = 0;
        while (color[i] != '\0' && i < 19) {
            this->color[i] = color[i];
            i++;
        }
        this->color[i] = '\0';
    }

    void show() {
        cout << color << "색의 (" << getX() << ", " << getY() << ")의 점" << endl;
    }
};

int main() {
    ColorPoint zeroPoint; // BLACK 색에 (0, 0) 위치의 점
    zeroPoint.show();

    ColorPoint cp(5, 5);
    cp.setPoint(10, 20);
    cp.setColor("BLUE");
    cp.show();

    return 0;
}