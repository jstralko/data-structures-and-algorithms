interface Iterator<T> {
  boolean hasNext();
  T next();
}// while (it.hasNext()) { Process(it.next()); }

interface Predicate<T> {
  boolean apply(T item);
}
// Ex: return item % 2 == 0

Iterator<T> filter(Iterator<T> in, Predicate<T> pred)
// Ex:
// in: 0, 1, 2, …
// pred: item % 2 == 0 (Is-even)
// out: 0, 2, 4, …
{
	/*int count = 0;
	List<T> list = new ArrayList<T>();
	while(it.hasNext()) {
		T item = it.next();
		if (pred.apply(item)) {
			list.add(item);
			count++;
			//if (count > MAX) {
			//	break;
//}
}

}*/

//return list.iterator();


public class CustomIterator implements Iterator<T> {
	Predicate<T> pred;
	Iterator<T> in;
	T item next;

	public CustomIterator(Iterator<T> in, Predicate<T> pred) {
		this.pred = pred;
		this.iter = in;
}

	public boolean hasNext() {
		while (in.hasNext()) {
			T item = in.next();
		if (pred.apply(item) {
				next = item;
				return true;
}
}
return false;
	}

	public T next() {
		if (next != null || hasNext()) {
			T item = next;
			next = null;
		return item;
}
throws new NoSuchItemException(“..”);
}
}
}

pred: is-even
in: [2]
println(out.next())
