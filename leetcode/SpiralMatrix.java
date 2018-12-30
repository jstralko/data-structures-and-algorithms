class SpiralMatrix {
    public List<Integer> spiralOrder(int[][] matrix) {
        List<Integer> order = new ArrayList();
        
        if (matrix == null || matrix.length == 0 || matrix[0].length == 0)
            return order;
        
        int limit = matrix[0].length * matrix.length;
        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};
        int dir = 0;
        int r = 0;
        int c = 0;
        
        while (limit > 0) {
            order.add(matrix[r][c]);
            matrix[r][c] = Integer.MIN_VALUE;
            
            r += dr[dir];
            c += dc[dir];
            
            if (isInvalid(matrix, r, c)) {
                r -= dr[dir];
                c -= dc[dir];
                
                dir = (dir + 1) % 4;
                
                r += dr[dir];
                c += dc[dir];
            }
            
            limit--;
        }
        
        return order;
    }
    
    public boolean isInvalid(int[][] matrix, int r, int c) {
        if (r >= matrix.length || r < 0 || c >= matrix[0].length || c < 0 || matrix[r][c] == Integer.MIN_VALUE)
            return true;
        
        return false;
    }
}
