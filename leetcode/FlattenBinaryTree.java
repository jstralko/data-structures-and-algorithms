/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode(int x) { val = x; }
 * }
 */
class Solution {
    public void flatten(TreeNode root) {
        traverse(root);
    }

    public void traverse(TreeNode root) {
        if (root == null)
            return;

        traverse(root.left);

        if (root.left != null) {
            TreeNode right = root.right;
            TreeNode left = root.left;
            root.right = left;
            root.left = null;

            traverseRightMost(root.right, right);
        }

        traverse(root.right);
    }

    public void traverseRightMost(TreeNode root, TreeNode right) {
        if (root == null) {
            return;
        }

        traverseRightMost(root.right, right);
        if (root.right == null) {
            root.right = right;
        }
    }
}
