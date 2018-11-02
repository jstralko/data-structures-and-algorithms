/*
	4
      2   -10
    1  1  3  0
*/

public class NodeWrapper {
  Integer max;
  Node subTreeNode;
}

public static void start() {
  NodeWrapper maxSubTreeWrapper = new NodeWrapper();
  maxSubTreeWrapper.max = 0;
  maxSubTreeWrapper.subTreeNode = null;
  setLargestSumTree(root, maxSubTreeWrapper);
}

public static Integer setLargestSumTree(Node root, NodeWrapper maxSubTreeWrapper) {
  if (root == null) return 0;

  int total = root.value;
  total += setLargestSumTree(root.left, maxSubTreeWrapper);
  total += setLargestSumTree(root.right, maxSubTreeWrapper);

  if (maxSubTreeWrapper.max < total) {
    maxSubTreeWrapper.max = total;
    maxSubTreeWrapper.subTreeNode = root;
  }

  return total;
}
