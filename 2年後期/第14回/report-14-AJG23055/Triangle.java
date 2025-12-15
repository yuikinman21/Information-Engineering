//AJG23055 牧野唯希

public class Triangle extends Shape {
  private double x1, y1, x2, y2, x3, y3;
  
  public Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
    this.x1 = x1;
    this.y1 = y1;
    this.x2 = x2;
    this.y2 = y2;
    this.x3 = x3;
    this.y3 = y3;
  }

  public double area() {
    return Math.abs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2);
  }

  public double perimeter() {
    double side1 = Math.sqrt(Math.pow(x2-x1, 2) + Math.pow(y2-y1, 2));
    double side2 = Math.sqrt(Math.pow(x3-x2, 2) + Math.pow(y3-y2, 2));
    double side3 = Math.sqrt(Math.pow(x1-x3, 2) + Math.pow(y1-y3, 2));
    return side1 + side2 + side3;
  }

  public String toString() {
      return String.format("三角形：(%.1f, %.1f), (%.1f, %.1f), (%.1f, %.1f)", x1, y1, x2, y2, x3, y3);
  }
}