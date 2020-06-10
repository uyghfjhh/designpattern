package creational;

import java.util.Arrays;

class MyString implements Cloneable{
    MyString(String org) {
        this.data = org.toCharArray();
    }

    MyString() {
        this.data = new char[0];
    }

    void sort() {
        Arrays.sort(this.data);
    }

    //deep copy
    @Override
    protected Object clone() throws CloneNotSupportedException {
        MyString s = new MyString();
        s.data = Arrays.copyOf(this.data, this.data.length);
        return s;
    }

//    //shallow copy
//    @Override
//    protected Object clone() throws CloneNotSupportedException {
//        return super.clone();
//    }

    @Override
    public String toString() {
        return new String(this.data);
    }

    private char data[];
}

public class PrototypeDemo {
    public static void main(String args[]) throws CloneNotSupportedException {
        MyString str1 = new MyString("cba");
        MyString str2 = (MyString) str1.clone();
        str1.sort();
        System.out.println(str1);
        System.out.println(str2);

    }
}
