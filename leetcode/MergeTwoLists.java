/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */


/*

public ListNode mergeTwoLists(ListNode l1, ListNode l2){
		if(l1 == null) return l2;
		if(l2 == null) return l1;

    if(l1.val < l2.val){
			l1.next = mergeTwoLists(l1.next, l2);
			return l1;
		}

		l2.next = mergeTwoLists(l1, l2.next);
		return l2;
}
*/

public class MergeTwoLists {

    public static class ListNode {
         int val;
         ListNode next;
         ListNode(int x) { val = x; }
    }


    public static void main(String[] args) {
      /*
      Input: 1->2->4, 1->3->4
      Output: 1->1->2->3->4->4
      */

      ListNode first = new ListNode(1);
      ListNode next = new ListNode(2);
      first.next = next;

      next = new ListNode(4);
      first.next.next = next;

      ListNode second = new ListNode(1);
      next = new ListNode(3);
      second.next = next;

      next = new ListNode(4);
      second.next.next = next;

      /*while(first != null) {
        System.out.println(first.val);
        first = first.next;
      }

      while(second != null) {
        System.out.println(second.val);
        second = second.next;
      }*/

      ListNode merge = mergeTwoLists(first, second);

      while(merge != null) {
        System.out.println(merge.val);
        merge = merge.next;
      }
    }

    public static ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        ListNode mergedList = new ListNode(0);
        ListNode head = mergedList;

        while(l2 != null || l1 != null) {
            if (l1 == null) {
                mergedList.next = new ListNode(l2.val);
                l2 = l2.next;
            }
            else if (l2 == null) {
              mergedList.next = new ListNode(l1.val);
              l1 = l1.next;
            }
            else {
              if (l1.val < l2.val) {
                  mergedList.next = new ListNode(l1.val);
                  l1 = l1.next;
              } else {
                  mergedList.next = new ListNode(l2.val);
                  l2 = l2.next;
              }
            }

            mergedList = mergedList.next;
        }

        return head.next;
    }
}
