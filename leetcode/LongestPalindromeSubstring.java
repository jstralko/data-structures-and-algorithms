/*
public String longestPalindrome(String s) {
    if (s == null || s.length() < 1) return "";
    int start = 0, end = 0;
    for (int i = 0; i < s.length(); i++) {
        int len1 = expandAroundCenter(s, i, i);
        int len2 = expandAroundCenter(s, i, i + 1);
        int len = Math.max(len1, len2);
        if (len > end - start) {
            start = i - (len - 1) / 2;
            end = i + len / 2;
        }
    }
    return s.substring(start, end + 1);
}

private int expandAroundCenter(String s, int left, int right) {
    int L = left, R = right;
    while (L >= 0 && R < s.length() && s.charAt(L) == s.charAt(R)) {
        L--;
        R++;
    }
    return R - L - 1;
}
*/

public class LongestPalindromeSubstring {

    public static void main(String[] args) {
      String s = "babad";
      System.out.println(longestPalindrome(s));

      s = "aaaa";
      System.out.println(longestPalindrome(s));

      s = "aaabaaaa";
      System.out.println(longestPalindrome(s));
    }

    public static String longestPalindrome(String s) {
      String longestPalindrome = new String();

      for (int i = 0; i < s.length(); i++) {
        int l = i;
        int r = s.length() - 1;
        int rEnd = -1;

        while (l < r) {
          char lChar = s.charAt(l);
          char rChar = s.charAt(r);

          if (lChar == rChar) {
            if (rEnd == -1) {
              rEnd = r;
            }
            l++;
          } else {
            rEnd = -1;
            l = i;
          }
          r--;
        }

        String palindrome = rEnd == -1 ? s.substring(i, i + 1) : s.substring(i, rEnd+1);

        if (palindrome.length() > longestPalindrome.length()) {
          longestPalindrome = palindrome;
        }

      }

      for (int i = s.length() - 1; i > -1; i--) {
        int l = 0;
        int r = i;
        int lEnd = -1;

        while (l < r) {
          char lChar = s.charAt(l);
          char rChar = s.charAt(r);

          if (lChar == rChar) {
            if (lEnd == -1) {
              lEnd = l;
            }
            r--;
          } else {
            lEnd = -1;
            r = i;
          }
          l++;
        }

        String palindrome = lEnd == -1 ? s.substring(i, i + 1) : s.substring(lEnd, i+1);

        if (palindrome.length() > longestPalindrome.length()) {
          longestPalindrome = palindrome;
        }

      }

      return longestPalindrome;
    }
}
