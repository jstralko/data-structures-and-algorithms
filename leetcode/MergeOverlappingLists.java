/*
 // Given two sorted lists of non-overlapping intervals, write a method that returns a single merged list 
 // of the union of these intervals  with the same properties (sorted, non-overlapping).
 //
 // e.g. [[0,2], [4,5], [8,9]] , [[1,4.05], [10,11]] -> [[0,5], [8,9], [10,11]]
 // e.g. [[0, 100]],  [[1,2], [3,4], [5,6], [7,8]] -> [[0, 100]]
*/

public class MergeOverlappingLists {

    public static class Range {
        float start;
        float end;
    };
    
    public static class ListNode {
        Range value;
        ListNode next;

        ListNode(float start, float end) {
            Range r = new Range();
            r.start = start;
            r.end = end;
            value = r;
        }
    };

    public static void main(String[] args) {


        //Use case 1
        /*ListNode one = new ListNode(1, 3);
        one.next = new ListNode(5, 9);

        ListNode two = new ListNode(2, 8);
        two.next = new ListNode(13, 20);*/

        //Use case 2
        //[[0, 100]],  [[1,2], [3,4], [5,6], [7,8]]
        /*ListNode one = new ListNode(0, 100);
        ListNode two = new ListNode(1, 2);
        two.next = new ListNode(3, 4);
        two.next.next = new ListNode(5, 6);
        two.next.next .next = new ListNode(7, 8);*/

        //Use case 3
        //[[0,2], [4,5], [8,9]] , [[1,4.05], [10,11]]
        ListNode one = new ListNode(0, 2);
        one.next = new ListNode(4, 5);
        one.next.next = new ListNode(8, 9);
        ListNode two = new ListNode(1, 4.05f);
        two.next = new ListNode(10, 11);

        ListNode mergedList = mergeLists(one, two);
        
        while (mergedList != null) {
            Range value = mergedList.value;
            System.out.println(
                String.format("{%f, %f}", value.start, value.end)
            );

            mergedList = mergedList.next;
        }
    }

    public static ListNode addOrMergeRange(ListNode mergedList, float start, float end) {
        if (mergedList.value.end >= start && mergedList.value.start != -1) {
            mergedList.value.end = end;
        } else {
            mergedList.next = new ListNode(start, end);
            mergedList = mergedList.next;
        }

        return mergedList;
    }
    /*
    (0, 100) (220, 222)
    (3, 5) (6, 7)

    */

    /*
    one:
    (1, 3), (5, 9)
    two:
    (2, 8), (10, 20)

    Merge:
    (1, 9), (13, 20)
    */

    public static ListNode mergeLists(ListNode one, ListNode two) {
        ListNode mergedList = new ListNode(-1, -1);
        ListNode head = mergedList;

        if (one == null) {
            return two;
        }
        if (two == null) {
            return one;
        }

        while (one != null || two != null) {
            if (one == null) {
                while (two != null) {
                    mergedList = addOrMergeRange(mergedList, two.value.start, two.value.end);

                    two = two.next;
                }
                continue;
            }

            if (two == null) {
                while (one != null) {
                    mergedList = addOrMergeRange(mergedList, one.value.start, one.value.end);

                    one = one.next;
                }
                continue;
            }

            //CHECK if one is super range of two. (1, 5) -> (2,3)
            if (one.value.start <= two.value.start && one.value.end >= two.value.end) {
                mergedList = addOrMergeRange(mergedList, one.value.start, one.value.end);

                two = two.next;
            //CHECK if two is super range of one.
            } else if (two.value.start <= one.value.start && two.value.end >= one.value.end) {
                mergedList = addOrMergeRange(mergedList, two.value.start, two.value.end);

                one = one.next;
            //one and two don't overlaps one is ordered first
            } else if (one.value.end <= two.value.start) {
                mergedList = addOrMergeRange(mergedList, one.value.start, one.value.end);

                one = one.next;
            //one and two don't overlaps two is ordered first
            } else if (two.value.end <= one.value.start) {
                mergedList = addOrMergeRange(mergedList, two.value.start, two.value.end);

                two = two.next;
            //Overlap - one.end overlaps two.start. or two.end overlaps with one.start
            }else if(one.value.end >= two.value.start || two.value.end >= one.value.start) {
                float start = Math.min(one.value.start, two.value.start);
                float end = Math.max(one.value.end, two.value.end);

                mergedList = addOrMergeRange(mergedList, start, end);

                one = one.next;
                two = two.next;
            }
        }

        return head.next;
    }
}
