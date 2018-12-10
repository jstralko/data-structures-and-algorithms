class LRUCache {

    private static class ListNode {
        ListNode next;
        ListNode prev;
        Integer val;

        ListNode(int v) {
            val = v;
        }
    }

    Map<Integer, ListNode> _nodeLookup = new HashMap<Integer, ListNode>();
    Map<Integer, Integer> _cache = new HashMap<Integer, Integer>();
    ListNode _cacheListHead = null;
    ListNode _cacheListTail = null;
    Integer _cacheSize = 0;
    Integer _currentSize = 0;

    public LRUCache(int capacity) {
        _cacheSize = capacity;
    }

    public int get(int key) {
        if (_cache.containsKey(key)) {


            return _cache.get(key);
        }
        return -1;
    }

    public void put(int key, int value) {
        if (_cacheListHead == null) {
            _cacheListHead = new ListNode(key);
            _cacheListTail = _cacheListHead;
        }

        if (_currentSize <= _cacheSize) {
            ListNode node = new ListNode(key);
            _cacheListTail.next = node;
            _cacheListTail = node;
            node.prev = _cacheListTail;

            _nodeLookup.put(key, node);
            _cache.put(key, value);
            _currentSize++;
        } else {
            ListNode evit = _cacheListHead;
            _cacheListHead = _cacheListHead.next;
            _cacheListHead.prev = null;


            evit.next = null;
            _cache.remove(evit.val);
            _nodeLookup.remove(evit.val);

            _cache.put(key, value);
        }
    }
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
