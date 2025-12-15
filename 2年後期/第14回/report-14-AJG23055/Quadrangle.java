//AJG23055 牧野唯希

public class Quadrangle extends Shape {
    private double x1, y1, x2, y2, x3, y3, x4, y4;

    public Quadrangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
        this.x3 = x3;
        this.y3 = y3;
        this.x4 = x4;
        this.y4 = y4;
    }

    public double area() {
        double area1 = Math.abs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2);
        double area2 = Math.abs((x1*(y3-y4) + x3*(y4-y1) + x4*(y1-y3)) / 2);
        return area1 + area2;
    }

    public double perimeter() {
        double side1 = Math.sqrt(Math.pow(x2-x1, 2) + Math.pow(y2-y1, 2));
        double side2 = Math.sqrt(Math.pow(x3-x2, 2) + Math.pow(y3-y2, 2));
        double side3 = Math.sqrt(Math.pow(x4-x3, 2) + Math.pow(y4-y3, 2));
        double side4 = Math.sqrt(Math.pow(x1-x4, 2) + Math.pow(y1-y4, 2));
        return side1 + side2 + side3 + side4;
    }

    public String toString() {
        return String.format("四角形：(%.1f, %.1f), (%.1f, %.1f), (%.1f, %.1f), (%.1f, %.1f)", x1, y1, x2, y2, x3, y3, x4, y4);
    }
}
