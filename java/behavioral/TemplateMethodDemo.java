//author sbkun
package behavioral;

abstract class TvOperator {
    abstract void open();
    abstract void close();
    void play() {
        open();
        System.out.println("playing...");
        close();
    }
}

class XiaomiTvOp extends TvOperator {
    @Override
    public void open() {
        System.out.println("Xiami TV open");
    }

    @Override
    public void close() {
        System.out.println("Xiaomi TV close");
    }

};

class KangjiaTvop extends TvOperator {
    @Override
    public void open() {
        System.out.println("Kangjia TV open");
    }

    @Override
    public void close() {
        System.out.println("Kangjia TV close");
    }

};

public class TemplateMethodDemo {
    public static void main(String args[]) {
        TvOperator tv1 = new XiaomiTvOp();
        TvOperator tv2 = new KangjiaTvop();
        tv1.play();
        System.out.println("\n");
        tv2.play();
    }
}
