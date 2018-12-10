import java.util.*;

public class LongestSubString {

    public static void main(String[] args) {
      String s = "jbpnbwwd";

      System.out.println(lengthOfLongestSubstring(s));

    }

    public static int lengthOfLongestSubstring(String s) {
        String max = new String();
        String cur = new String();
        Set<Integer> hash = new HashSet<Integer>();

        for (int i = 0; i < s.length(); i++) {
            for (int j = i; j < s.length(); j++) {
                char c = s.charAt(j);
                int cInt = (int)c;

                if (!hash.contains(cInt)) {
                    cur += c;
                    hash.add(cInt);
                } else if (cur.length() > max.length()) {
                    max = cur;
                    break;
                } else {
                  break;
                }
            }

            if (cur.length() > max.length()) {
                System.out.println(cur);
                max  = cur;
            }
            cur = new String();
            hash.clear();
        }

        return max.length();
    }
}
