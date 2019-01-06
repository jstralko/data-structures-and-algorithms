class Solution {
    public boolean isPalindrome(int x) {
        int reverse = 0;
        int saved_x = x;
        
        while(x > 0) {
            int lsd = x % 10;
            
            reverse = ((reverse * 10) + lsd);
            x /= 10;
        }
        
        if (reverse != saved_x) {
            return false;
        }
        
        return true;
    }
}
