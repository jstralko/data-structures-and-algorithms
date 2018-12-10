public class FirstLastRange {

    // nums = [5,7,7,8,8,10], target = 8

    public static void main(String[] args) {
        int[] array = { 1,2,3 };
        //int[] array = { 5, 7, 7, 8, 8, 10 };

        int[] range = searchRange(array, 3);

        System.out.println("[" + range[0] + " " + range[1] + "]");
    }

    public static int[] searchRange(int[] nums, int target) {
            if (nums == null || nums.length == 0) {
              return new int[] { -1, -1 };
            }
            return searchRange(nums, 0, nums.length, target);
    }

    public static int[] searchRange(int[] nums, int lo, int size, int target) {
            int mid = (lo + size / 2);

            if (lo >= size) {
                int noRange[] = { -1, -1 };
                return noRange;
            }

            if (size == 1 && nums[mid] != target) {
                int noRange[] = { -1, -1 };
                return noRange;
            }

            if (nums[mid] == target) {
                //System.out.println("found " + lo + " " + mid + " " + size);
                return foundTarget(nums, lo, mid, size, target);
            } else if (nums[mid] > target) {
                //left
                //System.out.println("left: " + lo + " " + mid);
                return searchRange(nums, lo, mid, target);
            } else {
                //right
                //System.out.println("right " + (mid + 1) + " " + size);
                return searchRange(nums, mid + 1, size, target);
            }
    }

    public static int[] foundTarget(int[] nums, int lo, int mid, int size, int target) {
        int left = mid - 1;
        int right = mid + 1;
        boolean searchLeft = true;
        boolean searchRight = true;

        while(searchLeft || searchRight) {
            searchLeft = false;
            searchRight = false;

            if (left >=0) {
                if (nums[left] == target) {
                    left--;
                    searchLeft = true;
                }
            }
            if (right < size) {
                if (nums[right] == target) {
                    right++;
                    searchRight = true;
                }
            }
        }

        int range[] = { left + 1, right - 1 };
        return range;
    }
}
