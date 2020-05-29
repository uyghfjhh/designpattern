package designpattern.singleton;

import initializationorder.TestInitOrder;
//饿汉模式 类加载时 instance变量被实例化
class EagerSingleton {
    private static final EagerSingleton intance = new EagerSingleton();
    public static EagerSingleton getInstance() {
        return intance;
    }
    public void foo() {
        System.out.println(this.getClass().getSimpleName()+" foo");
    }
    private EagerSingleton() {}

}

//懒汉模式 instance变量，在第一次使用时才被初始化
class LazySingleton {
    private static LazySingleton instance = null;
    public static LazySingleton getInstance(){
        if (instance == null) {
            instance = new LazySingleton();
        }
        return instance;
    }
    private LazySingleton() {}
    public void foo() {
        System.out.println(this.getClass().getSimpleName()+" foo");
    }
}

//懒汉模式的线程安全问题
//将getInstance变成了串行化操作，安全但是效率低下
class LazySingleton1 {
    private static LazySingleton1 instance = null;
    public static synchronized LazySingleton1 getInstance(){
        if (instance == null) {
            instance = new LazySingleton1();
        }
        return instance;
    }
    private LazySingleton1() {}
    public void foo() {
        System.out.println(this.getClass().getSimpleName()+" foo");
    }
}

//双重检测，看似兼顾效率和安全，实则由于指令重排，并非线程安全
class LazySingleton2 {
    private static LazySingleton2 instance = null;
    public static  LazySingleton2 getInstance(){
        if (instance == null) {
            synchronized (LazySingleton2.class) {
                if (instance == null) {
                    instance = new LazySingleton2();
                }
            }
        }
        return instance;
    }
    private LazySingleton2() {}
    public void foo() {
        System.out.println(this.getClass().getSimpleName()+" foo");
    }
}

//静态内部类，线程安全，且延迟加载
class LazySingleton3 {
    private static class HolderClass {
        private static final LazySingleton3 instance = new LazySingleton3();
    }

    //LazySingleton3 被加载时，并不会加载HolderClass
    //只有当getInstance方法被调用时，加载HolderClass，并初始化instance
    public static  LazySingleton3 getInstance(){
        return HolderClass.instance;
    }
    private LazySingleton3() {}
    public void foo() {
        System.out.println(this.getClass().getSimpleName()+" foo");
    }
}


public class Singleton_demo {
    public static void main(String args[]) {
        EagerSingleton.getInstance().foo();
        LazySingleton.getInstance().foo();
    }
}
