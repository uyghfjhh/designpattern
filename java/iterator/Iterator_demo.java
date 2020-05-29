package designpattern.iterator;
import java.util.Arrays;
import java.util.Iterator;

class MyArray<T> implements Iterable<T> {
    private T array[];

    MyArray(T array[]) {
        this.array = Arrays.copyOf(array, array.length);
    }

    public Iterator<T> iterator() {
        return new Itr();
    }

    public Iterator<T> reverseIterator() {
        return new ReverseItr();
    }

    private class Itr implements Iterator<T> {
        public boolean hasNext() {
            return index < array.length;
        }

        public T next() {
            return array[index++];
        }

        private int index = 0;
    }

    private class ReverseItr implements Iterator<T> {
        public boolean hasNext() {
            return index >= 0;
        }

        public T next() {
            return array[index--];
        }

        private int index = array.length - 1;
    }
}


public class Iterator_demo {
    public static void main(String args[]) {
        MyArray<Integer> array = new MyArray<Integer>(new Integer[]{1, 2, 3, 4, 5});
        for (Iterator<Integer> it = array.reverseIterator(); it.hasNext(); ) {
            System.out.print(it.next()+" ");
        }
        System.out.print("\n");

        for (Iterator<Integer> it = array.iterator(); it.hasNext(); ) {
            System.out.print(it.next()+" ");
        }
        System.out.print("\n");
    }

}
