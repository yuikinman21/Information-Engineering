//AJG23055 牧野唯希

public class Circle extends Shape {
    private double x, y, radius;

    public Circle(double x, double y, double radius) {
        this.x = x;
        this.y = y;
        this.radius = radius;
    }

    public double area() {
        return Math.PI * radius * radius;
    }

    public double perimeter() {
        return 2 * Math.PI * radius;
    }

    public String toString() {
        return String.format("円：(%.1f, %.1f), 半径 = %.1f", x, y, radius);
    }
}
