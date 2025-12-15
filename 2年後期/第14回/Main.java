public class Main {
	public static void main(String[] args) {
		// スーパークラスShapeのサブクラスTriangleの各インスタンスの面積と外周を計算する
		Shape t1 = new Triangle(0.0, 0.0, 5.0, 0.0, 0.0, 5.0);
		System.out.println(t1);
		System.out.println("面積：" + t1.area());
		System.out.println("外周：" + t1.perimeter());

		Shape t2 = new Triangle(-2.0, -2.0, 5.0, 1.0, -4.0, 2.0);
		System.out.println(t2);
		System.out.println("面積：" + t2.area());
		System.out.println("外周：" + t2.perimeter());

		// スーパークラスShapeのサブクラスQuadrangleの各インスタンスの面積と外周を計算する
		Shape q1 = new Quadrangle(-1.0, -1.0, 4.0, -1.0, 4.0, 2.0, -1.0, 2.0);
		System.out.println(q1);
		System.out.println("面積：" + q1.area());
		System.out.println("外周：" + q1.perimeter());

		Shape q2 = new Quadrangle(-3.0, -2.0, 6.0, -1.0, 7.0, 2.0, -4.0, 3.0);
		System.out.println(q2);
		System.out.println("面積：" + q2.area());
		System.out.println("外周：" + q2.perimeter());

		// スーパークラスShapeのサブクラスCircleの各インスタンスの面積と外周を計算する
		Shape c1 = new Circle(0.0, 0.0, 3.0);
		System.out.println(c1);
		System.out.println("面積：" + c1.area());
		System.out.println("外周：" + c1.perimeter());

		Shape c2 = new Circle(-3.0, 4.0, 11.1);
		System.out.println(c2);
		System.out.println("面積：" + c2.area());
		System.out.println("外周：" + c2.perimeter());
	}
}