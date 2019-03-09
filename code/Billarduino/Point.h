class Point {
  public:
    int x;
    int y;
    Point() {
      setPosition(-1, -1);
    }

    Point(double x, double y) {
      setPosition(x, y);
    }

    bool isDefined() {
      if (this->x != -1 and this->y != -1) {
        return true;
      }
      return false;
    }

    void setPosition(double x, double y) {
      setX(x);
      setY(y);
    }

    void setX(double x) {
      this->x = x;
    }

    void setY(double y) {
      this->y = y;
    }

    double distanceTo(Point point) {
      return sqrt(pow(this->x - point.x, 2) + pow(this->y - point.y, 2));
    }

    void toString() {
      Serial.print("x: ");
      delay(100);
      Serial.print(this->x);
      delay(100);
      Serial.print(", y: ");
      delay(100);
      Serial.println(this->y);
      delay(100);
    }

};
