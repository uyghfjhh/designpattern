//author sbkun
package structural;

interface Target {
   void foo();
}

class Adaptee {
   void oldFoo() {
       System.out.println("call OldFoo");
   }
}

class Adapter implements Target {
    Adapter(Adaptee adaptee){
        this.adaptee = adaptee;
    }

    @Override
    public void foo() {
        System.out.println("call foo");
        adaptee.oldFoo();
    }

    private Adaptee adaptee;
}

public class AdapterDemo {
    public static void main(String args[]) {
        Adapter adapter = new Adapter(new Adaptee());
        adapter.foo();
    }
}
