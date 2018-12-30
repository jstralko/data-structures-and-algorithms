class NumberOfIslands {
    
    public int numIslands(char[][] grid) {
        int countIsland = 0;
        if (grid.length == 0) {   
            return countIsland;
        }
        
        for (int i = 0; i < grid[0].length; i++) {
            for (int j = 0; j < grid.length; j++) {
                if (grid[j][i] == '1') {
                    dfs(grid, i, j);
                    countIsland++;
                }
            }
        }
        return countIsland;
    }
    
    public void dfs(char[][] grid, int i, int j) {
        if (i < 0 || j < 0) return;
        if (i >= grid[0].length || j >= grid.length) return;
        if (grid[j][i] != '1') return;
        
        grid[j][i] = '0';
        
        dfs(grid, i, j-1); //up
        dfs(grid, i, j+1); //down
        dfs(grid, i-1, j); //left
        dfs(grid, i+1, j); //right
    }
}
