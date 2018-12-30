/*
 * Fast Log(n) solution:
 * 
 public int[] countBits(int num) {
    int[] f = new int[num + 1];
    for (int i=1; i<=num; i++) f[i] = f[i >> 1] + (i & 1);
    return f;
 }
 */



public class CountingBits {
    
    public int getNumOfOnes(int d) {
        int count = 0;
        
        for (int i = 31; i >= 0; i--) {
            if ((d & (1 << i)) != 0) {
                count++;
            }
        }
        return count;
    }
    
    public int[] countBits(int num) {
        int[] bits = new int[num+1];
        
        for (int i = 0; i <= num; i++) {
            bits[i] = getNumOfOnes(i);
        }
        
        return bits;
    }
}
