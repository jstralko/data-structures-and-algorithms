import java.util.Stack;
/*
       30
      / \
    15  45
   / \
  7  18

*/
public class BSTIterator {

    static Node root;

    Stack<Node> stack = null;

    public static void main(String[] args) {
      root = new Node();
      root.value = 30;

      Node seven = new Node();
      seven.value = 7;

      Node eighteen = new Node();
      eighteen.value = 18;

      Node fifteen = new Node();
      fifteen.value = 15;

      fifteen.left = seven;
      fifteen.right = eighteen;

      root.left = fifteen;

      Node fortyfive = new Node();
      fortyfive.value = 45;

      root.right = fortyfive;

      BSTIterator bstiterator = new BSTIterator();

      while (bstiterator.hasNext()) {
        Node next = bstiterator.getNext();

        System.out.println(String.format("%d ", next.value));
      }
    }

    public boolean hasNext() {
      if (stack == null) {
        stack = new Stack<Node>();
        traverseLeft(root);
      }

      return !stack.isEmpty();
    }

    public Node getNext() {

      while(!stack.isEmpty()) {
        Node n = stack.pop();

        traverseLeft(n.right);

        return n;
      }

      return null;
    }

    private void traverseLeft(Node node) {
      if (node == null) return;

      stack.push(node);
      traverseLeft(node.left);
    }

    private static class Node {
      public Node left;
      public Node right;
      public int value;
    }
}
