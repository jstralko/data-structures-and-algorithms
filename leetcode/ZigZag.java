public class ZigZag {

    public static void main(String[] args) {
      String s = "PAYPALISHIRING";

      System.out.println(convert(s, 4));
    }

    public static String convert(String s, int numRows) {
      StringBuilder buf[] = new StringBuilder[numRows];

      for (int ii = 0; ii < numRows; ii++) {
        buf[ii] = new StringBuilder();
      }

      int i = 0;
      while (i < s.length()) {
        while (i < numRows) {
          buf[i].append(s.charAt(i));
          i++;
        }

        int j = i;
        while (j > 0) {
          buf[numRows - (i % numRows)].append(s.charAt(i));
          j--;
          i++;
        }

        System.out.println(buf[0].toString());
        System.out.println(buf[1].toString());
        System.out.println(buf[2].toString());
        System.out.println(buf[3].toString());
        //break;
      }

      return null;
    }

    /*public static String convert(String s, int numRows) {
        String zigZag = "";

        for (int i = 0; i < numRows; i++) {
          int j = i;
          int k = i + 1;

          zigZag += s.charAt(j);
          while(j < s.length()) {
            int index = ((numRows - k) + (numRows - k) + j);

            if (index == 0) {
              index = (numRows - 1) * 2;
            }
            if (index > s.length()) {
              break;
            }
            zigZag += s.charAt(index);
            System.out.println(zigZag);
            j = index;
          }
          k++;
        }
        return zigZag;
    }*/
}
