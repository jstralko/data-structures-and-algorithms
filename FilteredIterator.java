public class FilteredIterator<T> implements Iterator<T> {
    private Iterator<? extends T> iterator;
    private Filter<T> filter;
    private T nextElement;
    private boolean hasNext;

    /**
     * Creates a new FilteredIterator using wrapping the iterator and returning only elements matching the filter.
     *
     * @param iterator
     *            the iterator to wrap
     * @param filter
     *            elements must match this filter to be returned
     */
    public FilteredIterator(Iterator<? extends T> iterator, Filter<T> filter) {
        this.iterator = iterator;
        this.filter = filter;

        nextMatch();
    }

    @Override
    public boolean hasNext() {
        return hasNext;
    }

    @Override
    public T next() {
        if (!hasNext) {
            throw new NoSuchElementException();
        }

        return nextMatch();
    }

    private T nextMatch() {
        T oldMatch = nextElement;

        while (iterator.hasNext()) {
            T o = iterator.next();

            if (filter.matches(o)) {
                hasNext = true;
                nextElement = o;

                return oldMatch;
            }
        }

        hasNext = false;

        return oldMatch;
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}

public interface Filter<T> {

    /**
     * Determines whether elements should be filtered or not.
     *
     * @param element the element to be matched against the filter
     * @return {@code true} if the element matches the filter, otherwise {@code false}
     */
    public boolean matches(T element);
}
