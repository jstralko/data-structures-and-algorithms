public class MergedTwoList_2 {

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
        ListNode one = new ListNode(1, 3);
        one.next = new ListNode(5, 9);

        ListNode two = new ListNode(2, 8);
        two.next = new ListNode(13, 20);

        ListNode mergedList = mergeLists(one, two);
        
        while (mergedList != null) {
            Range value = mergedList.value;
            System.out.println(
                String.format("{%f, %f}", value.start, value.end)
            );

            mergedList = mergedList.next;
        }
    }

    public static boolean canAddNode(ListNode saved, float start, float end) {
        boolean addNode = true;
        if (saved != null) {
            if (saved.value.start >= start && saved.value.end <= end) {
                saved.value.start = start;
                addNode = false;
            }
            if (saved.value.end >= start) {
                saved.value.end = end;
                addNode = false;
            }
        }

        return addNode;
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

        ListNode saved = null;

        while (one != null || two != null) {
            if (one == null) {
                while (two != null) {
                    if (mergedList.value.end >= two.value.start) {
                        mergedList.value.end = two.value.end;
                    } else {
                        ListNode n = new ListNode(two.value.start, two.value.end);
                        mergedList.next = n;
                        mergedList = mergedList.next;
                    }

                    two = two.next;
                }
                continue;
            }

            if (two == null) {
                while (one != null) {
                    if (mergedList.value.end >= one.value.start) {
                        mergedList.value.end = one.value.end;
                    } else {
                        ListNode n = new ListNode(one.value.start, one.value.end);
                        mergedList.next = n;
                        mergedList = mergedList.next;
                    }
                    one = one.next;
                }
                continue;
            }

                //saved:
                //one: 1, 3
                //two: (2, 8)

            //CHECK if one is super range of two. (1, 5) -> (2,3)
            if (one.value.start <= two.value.start && one.value.end >= two.value.end) {
                mergedList.next = new ListNode(one.value.start, one.value.end);
                saved = mergedList.next;
                mergedList = mergedList.next;
                two = two.next;
            //CHECK if two is super range of one.
            } else if (two.value.start <= one.value.start && two.value.end >= one.value.end) {
                mergedList.next = new ListNode(two.value.start, two.value.end);
                mergedList = mergedList.next;
                saved = mergedList.next;
                one = one.next;
            //one and two doesn't overlaps one is first
            } else if (one.value.end <= two.value.start) {

                boolean addNode = canAddNode(saved, one.value.start, one.value.end);
                if (addNode) {
                    mergedList.next = new ListNode(one.value.start, one.value.end);
                    saved = mergedList.next;
                    mergedList = mergedList.next;
                }

                one = one.next;
            //one and two doesn't overlaps two is first
            } else if (two.value.end <= one.value.start) {
                boolean addNode = canAddNode(saved, two.value.start, two.value.end);
                if (addNode) {
                    mergedList.next = new ListNode(two.value.start, two.value.end);
                    saved = mergedList.next;
                    mergedList = mergedList.next;
                }
                two = two.next;
            //Overlap - one.end overlaps two start. (5, 9) -> (4, 10)
            }else if(one.value.end >= two.value.start) {
                float start = one.value.start;
                float end = two.value.end;
                boolean addNode = canAddNode(saved, start, end);

                if (addNode) {
                    ListNode node = new ListNode(start, end);
                    saved = node;
                    mergedList.next = node;
                    mergedList = mergedList.next;
                }

                one = one.next;
                two = two.next;
            //Overlap - two.end overlaps with one.start
            } else if (two.value.end >= one.value.start) {
                float start = two.value.start;
                float end = one.value.end;
                boolean addNode = canAddNode(saved, start, end);

                if (addNode) {
                    ListNode node = new ListNode(start, end);
                    saved = node;
                    mergedList.next = node;
                    mergedList = mergedList.next;
                }

                one = one.next;
                two = two.next;
            }
        }

        return head.next;
    }
}