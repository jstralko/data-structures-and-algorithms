public class SearchMatrix {

    public static void main(String[] args) {
      /*
      matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
      */

        /*int matrix[][] = {
          { 1, 3, 5, 7},
          {10, 11, 16, 20},
          {23, 30, 34, 50}
        };*/

        int matrix [][] = {{}};

        System.out.println("Return: " + searchMatrix(matrix, 60));

    }

    public static boolean searchMatrix(int[][] matrix, int target) {
      if (matrix == null || matrix[0].length == 0) {
        return false;
      }
      System.out.println("len: "+ matrix.length);
      return searchMatrix(matrix, 0, matrix.length - 1, target);
    }

    public static boolean searchMatrix(int[][] matrix, int lo, int hi, int target) {

        if (lo > hi) {
            return false;
        }

        int mid = (lo + hi) / 2;



        if (matrix[mid][0] <= target && matrix[mid][matrix[0].length -1] >= target) {
            return searchColumn(matrix, mid, 0, matrix[mid].length - 1, target);
        } else if (matrix[mid][0] > target) {
            return searchMatrix(matrix, 0, mid - 1, target);
        }

        return searchMatrix(matrix, mid + 1, hi, target);
    }

    public static boolean searchColumn(int[][] matrix, int row, int lo, int hi, int target) {
        if (lo > hi) {
            return false;
        }

        int mid = (lo + hi)/ 2;

        if (matrix[row][mid] == target) {
            return true;
        } else if (matrix[row][mid] > target) {
            return searchColumn(matrix, row, 0, mid - 1, target);
        }

        return searchColumn(matrix, row, mid + 1, hi, target);
    }
}
