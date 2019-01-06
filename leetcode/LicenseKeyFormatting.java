/*
 * https://leetcode.com/problems/license-key-formatting/
 */


/*
 * Faster solution work backwards!
 *
 *     public String licenseKeyFormatting(String S, int K) {
        StringBuilder sb = new StringBuilder();

        for (int i = S.length() - 1, length = 0; i >= 0; i--) {
            char ch = S.charAt(i);
            if (ch != '-') {
                if (length == K) {
                    sb.append('-');
                    length = 0;
                }

                sb.append(Character.toUpperCase(ch));
                length++;
            }
        }

        return sb.reverse().toString();
    }
 */

class Solution {
    public String licenseKeyFormatting(String S, int K) {
        
        S = S.replace("-", "");
        
        int first = S.length() % K;
        if (first == 0) {
            first = K;
        }
        
        StringBuilder buf = new StringBuilder();
        String substring = S.substring(0, first);
        buf.append(substring.toUpperCase());
        
        int offset = first;      
        int loops = S.length() / K;
        if (first == K) {
            loops--;
        }
        
        while (loops > 0) {
            buf.append("-");
            substring = S.substring(offset, offset + K);
            System.out.println(substring);
            buf.append(substring.toUpperCase());
            
            offset = offset + K;
            loops--;
        }
        
        return buf.toString();
    }
}
