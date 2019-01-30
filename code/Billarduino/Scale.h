#define CENTIMETERS 40.0

class Scale {
  public:
    Point points[2];
    bool isDefined;
    int distance = 0;

    Scale() {
    }
    void calculateDistance() {
      this->distance = points[0].distanceTo(points[1]);
    }

    double getDistance() {
      return this->distance;
    }

    void setPoints(Point pt1, Point pt2) {
      points[0] = pt1;
      points[1] = pt2;
      isDefined = true;
      calculateDistance();
    }

    double getCentToCart() {
      return distance / CENTIMETERS;
    }

    double getCartToCent() {
      return (CENTIMETERS / this->distance);
    }
};
