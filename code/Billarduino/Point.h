class Point {
  public:
    int x;
    int y;
    Point() {
      setPosition(-1, -1);
    }

    Point(float x, float y) {
      setPosition(x, y);
    }

    bool isDefined() {
      if (this->x != -1 and this->y != -1) {
        return true;
      }
      return false;
    }

    void setPosition(float x, float y) {
      setX(x);
      setY(y);
    }

    void setX(float x) {
      this->x = x;
    }

    void setY(float y) {
      this->y = y;
    }

    double distanceTo(Point point) {
      return sqrt((this->x - point.x) ^ 2 + (this->y - point.y) ^ 2);
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
