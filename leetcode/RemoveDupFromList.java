/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class RemoveDupFromList {
    private static class ListNode {
           int val;
           ListNode next;
           ListNode(int x) { val = x; }
    }


    //[1,2,2]
    public static void main(String[] args) {
      ListNode list = new ListNode(1);
      list.next = new ListNode(2);
      list.next.next = new ListNode(2);

      ListNode newList = deleteDuplicates(list);

      while(newList != null) {
        System.out.print(newList.val + " ");
        newList = newList.next;
      }
    }
    public static ListNode deleteDuplicates(ListNode head) {
      if (head == null) {
        return null;
      }

      ListNode runner = head.next;
      ListNode dummyHead = new ListNode(0);
      ListNode dummy = dummyHead;

      while (head != null) {
          if (runner == null || runner.val == head.val) {
              while (runner != null && runner.val == head.val) {
                  runner = runner.next;
              }
              head = runner;
              if (runner != null) {
                  runner = runner.next;
              }

          } else {
              dummy.next = new ListNode(head.val);
              dummy = dummy.next;
              head = head.next;
              if (runner != null) {
                runner = runner.next;
              }
          }
      }

      return dummyHead.next;
    }
}
