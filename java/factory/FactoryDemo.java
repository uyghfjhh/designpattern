//author sbkun
package factory;

abstract class HwPhone {
    HwPhone(String model) {
        this.model = model;
    }

    void call(String to) {
        if (!model.isEmpty()) {
            System.out.println(model + " is calling " + to);
        }
    }

    private String model;

    //手机型号
    public static final String LawMate30 = "LowMate30";
    public static final String LowHonour6 = "LowHonour6";
    public static final String LowHonour7 = "LowHonour7";

    public static final String HighMate30 = "HighMate30";
    public static final String HighHonour6 = "HighHonour6";
    public static final String HighHonour7 = "HighHonour7";
}

class LowMate30 extends HwPhone {
    LowMate30() {
        super(HwPhone.LawMate30);
    }
}

class LowHonour6 extends HwPhone {
    LowHonour6() {
        super(HwPhone.LowHonour6);
    }
}

class LowHonour7 extends HwPhone {
    LowHonour7() {
        super(HwPhone.LowHonour7);
    }
}

class SimpleFactory {
    public static HwPhone makePhone(String model) {
        if (model.equalsIgnoreCase(HwPhone.LawMate30)) {
            return new LowMate30();
        } else if (model.equalsIgnoreCase(HwPhone.LowHonour6)) {
            return new LowHonour6();
        } else if (model.equalsIgnoreCase(HwPhone.LowHonour7)) {
            return new LowHonour7();
        }
        return null;
    }
}

//工厂方法
interface PhoneFactory {
    HwPhone makePhone();
}

class LowMate30Factory implements PhoneFactory {
    @Override
    public HwPhone makePhone() {
        return new LowMate30();
    }
}

class LowHonour6Factory implements PhoneFactory {
    @Override
    public HwPhone makePhone() {
        return new LowHonour6();
    }
}

//抽象工厂
interface HonourFactory {
    //抽象工厂，负责创建荣耀系列手机
    HwPhone makeHonour6();

    HwPhone makeHonour7();
}

//具体工厂类，负责创建低配的，荣耀系列手机
class LowHonourFactory implements HonourFactory {
    @Override
    public HwPhone makeHonour6() {
        return new LowHonour6();
    }

    @Override
    public HwPhone makeHonour7() {
        return new LowHonour7();
    }
}

public class FactoryDemo {
    static void testSimpleFactory() {
        System.out.println("testSimpleFactory");
        HwPhone p1 = SimpleFactory.makePhone(HwPhone.LawMate30);
        p1.call("110");
        HwPhone p2 = SimpleFactory.makePhone(HwPhone.LowHonour6);
        p2.call("110");
    }

    static void testFactoryMethod() {
        System.out.println("testFactoryMethod");
        PhoneFactory f1 = new LowMate30Factory();
        HwPhone p1 = f1.makePhone();
        p1.call("110");

        PhoneFactory f2 = new LowHonour6Factory();
        HwPhone p2 = f2.makePhone();
        p2.call("110");
    }

    static void testAbstractFactory() {
        System.out.println("testAbstractFactory");
        HonourFactory f = new LowHonourFactory();
        HwPhone p1 = f.makeHonour6();
        HwPhone p2 = f.makeHonour7();
        p1.call("110");
        p2.call("110");
    }

    public static void main(String args[]) {
        testSimpleFactory();
        System.out.println("\n====================\n");
        testFactoryMethod();
        System.out.println("\n====================\n");
        testAbstractFactory();
    }
}
