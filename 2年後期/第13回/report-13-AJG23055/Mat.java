//AJG23055 牧野唯希
//行列演算クラス
public class Mat {
  // コンストラクタ
  public Mat() {

  }

  // 行列 A を表示する．
  public void show(double[][] A) {
    System.out.println("---");
    for (int i = 0; i < A.length; i++) {
      for (int j = 0; j < A[0].length; j++) {
        System.out.print(A[i][j] + ", ");
      }
      System.out.println();
    }
    System.out.println("---");
  }

  public double[][] sc(double[][] A, double a) {
    double[][] out = new double[A.length][A[0].length];
    for (int i = 0; i < A.length; i++) {
      for (int j = 0; j < A[0].length; j++) {
        out[i][j] = A[i][j] * a;
      }
    }
    return out;
  }

  public double[][] T(double[][] A) {
    double[][] out = new double[A[0].length][A.length];
    for (int i = 0; i < A.length; i++) {
      for (int j = 0; j < A[0].length; j++) {
        out[j][i] = A[i][j];
      }
    }
    return out;
  }

  public double[][] add(double[][] A1, double[][] A2) {
    double[][] out = new double[A1.length][A1[0].length];
    for (int i = 0; i < A1.length; i++) {
      for (int j = 0; j < A1[0].length; j++) {
        out[i][j] = A1[i][j] + A2[i][j];
      }
    }
    return out;
  }

  public double[][] sub(double[][] A1, double[][] A2) {
    double[][] out = new double[A1.length][A1[0].length];
    for (int i = 0; i < A1.length; i++) {
      for (int j = 0; j < A1[0].length; j++) {
        out[i][j] = A1[i][j] - A2[i][j];
      }
    }
    return out;
  }

  public double[][] mul(double[][] A1, double[][] A2) {
    double[][] out = new double[A1.length][A1[0].length];
    for (int i = 0; i < A1.length; i++) {
      for (int j = 0; j < A1[0].length; j++) {
          out[i][j] = A1[i][j] * A2[i][j];
      }
    }
    return out;
  }


  public double[][] div(double[][] A1, double[][] A2) {
    double[][] out = new double[A1.length][A1[0].length];
    for (int i = 0; i < A1.length; i++) {
      for (int j = 0; j < A1[0].length; j++) {
        out[i][j] = A1[i][j] / A2[i][j];
      }
    }
    return out;
  }

  public double[][] matmul(double[][] A1, double[][] A2) {
    double[][] out = new double[A1.length][A2[0].length];
    for (int i = 0; i < A1.length; i++) {
      for (int j = 0; j < A2[0].length; j++) {
        for (int k = 0; k < A1[0].length; k++) {
          out[i][j] += A1[i][k] * A2[k][j];
        }
      }
    }
    return out;
  }
}