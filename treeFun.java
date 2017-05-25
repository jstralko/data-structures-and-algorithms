public class treeFun {

    public static int maxTotal = 0;

    public static Integer lastPrinted = null;

    public static void main(String[] args) {
      Node root = new Node();

      //right side
      Node one = new Node();
      one.value = -6;
      Node five = new Node();
      five.value = -4;
      Node six = new Node();
      six.value = 5;

      one.left = five;
      one.right = six;

      //left side
      Node two = new Node();
      Node three = new Node();
      three.value = 1;

      Node foo = new Node();
      foo.value = 0;
      three.left = foo;

      Node baz = new Node();
      baz.value = 0;
      foo.left = baz;

      Node four = new Node();
      four.value = 2;

      two.value = 3;
      two.left = three;
      two.right = four;

      root.left = two;
      root.right = one;
      root.value = -7;

      //int total = traverse(root);
      //System.out.println(total);
      //System.out.println(maxTotal);

      //calcuateHeight(root);

      int[] arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
      Node bstRootNode = createBSTFromArray(arr, 0, arr.length- 1);
      traverse(bstRootNode);

      Node twenty = new Node();
      twenty.value = 20;

      Node ten = new Node();
      ten.value = 10;

      Node twentyFive = new Node();
      twentyFive.value = 25;
      ten.right = twentyFive;

      Node thirty = new Node();
      thirty.value = 30;

      twenty.left = ten;
      twenty.right = thirty;

      boolean isBST = checkBST(twenty);
      //System.out.println(String.format("is BST: %b", isBST));

    }

    //Inorder traversal so we check if lastPrinted <= node.value
    //    left.data <= current < right
    public static boolean checkBST(Node node) {
      if (node == null) return true;

      if (!checkBST(node.left)) return false;

      System.out.println(
        String.format("lastPrinted %d node.value: %d",
          lastPrinted == null ? 0 : lastPrinted,
          node.value)
      );

      if (lastPrinted != null && lastPrinted >= node.value) {
        return false;
      }

      lastPrinted = node.value;
      System.out.println(node.value);

      if (!checkBST(node.right)) return false;

      return true;
    }

    public static Node createBSTFromArray(int[] arr, int start, int end) {
      if (start > end) return null;

      int mid = (start + end) / 2;

      Node root = new Node();
      root.value = arr[mid];
      root.left = createBSTFromArray(arr, start, mid-1);
      root.right = createBSTFromArray(arr, mid+1, end);
      return root;

    }

    public static int calcuateHeight(Node root) {
      if (root == null) return 0;

      int leftHeight = 0;
      int rightHeight = 0;

      if (root.left != null)
        leftHeight = calcuateHeight(root.left) + 1;

      if (root.right != null)
        rightHeight = calcuateHeight(root.right) + 1;

      if (Math.abs(rightHeight - leftHeight) > 1)
        System.out.println(String.format("%d left: %d right: %d", root.value, leftHeight, rightHeight));

      return Math.max(leftHeight, rightHeight);
    }

    public static int traverse(Node root) {
      if (root == null) return 0;

      //Preorder: print current, left, right
      //System.out.println(root.value);

      int total = 0;
      if (root.left != null)
        total += traverse(root.left);

      //In-Order: print left, current, right
      System.out.println(root.value);

      if (root.right != null)
        total += traverse(root.right);

      //Post-Order: print left, right, current
      //System.out.println(root.value);

      //keeps track of the largest subtree
      total += root.value;
      if (total > maxTotal) {
        maxTotal = total;
      }
      return total;
    }

    private static class Node {
      public Node left;
      public Node right;
      public int value;
    }
}
