/*Hello Jerry*/

/*
You have a pool of resources, each resource in the pool has an identifier
that can be used to identify the resource.
We also have a particular resource, let’s call it X,
which can be created by combining two resources from the pool.
Once a resource is used, it cannot be used again.
Find all the pairs of resources that can be used to create X. 
Assume each resource has an identifier that can be used to identify the resource.
The identifier supports arithmetic operations.

2

1 - 3, 1 + 2,

R: 5
1 -> 2-> 3 -> 4

(1+ 4, 2 +3)
*/

class PairResource {
    public Resource r1;
    public Resource r2;
}

List<Resource> findAllPairs(List<Resource> resources, Resource x) {
    List<PairResource> pairs = new ArrayList<>();
    Map<Resource, Integer> map = new HashSet<>();

    if (resources == null)
        return pairs;

    for (Resource r : resources) {
        if (map.get(r) == null)
          map.get(r) = 0;
        map.get(r)++;
    }

    // 1,1,2,3,4,4, 4 x = 5
    for (Resource r1: resources) {

        if (map.get(x - r1) != null && map.get(x - r1) > 0) {

            if (r1 != null) {
                Resource r2 = x - r1;
                map.get(r)--;

                PairResource pair = new PairResource();
                pair.r1 = r1
                pair.r2 = r2;
                pairs.add(pair);
            }
        }
    }

    return pairs;
}
