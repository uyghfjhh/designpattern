//author sbkun
package behavioral;

import java.util.ArrayList;
import java.util.List;

interface Hander {
    boolean handle(Requset req);
}

class HanderA implements Hander {
    @Override
    public  boolean handle(Requset req) {
        req.setMsg(req.getMsg()+"->"+name+" was handled ");
        return true;
    }

    private String name = this.getClass().getSimpleName();
}

class HanderB implements Hander {
    @Override
    public  boolean handle(Requset req) {
        req.setMsg(req.getMsg()+"->"+name+" was handled");
        return true;
    }

    private String name = this.getClass().getSimpleName();
}

class HanderChain {
    private List<Hander> handers = new ArrayList<Hander>();
    public void addHander(Hander hander) {
        handers.add(hander);
    }

    public void handle(Requset req) {
        for (Hander hander: handers) {
            if (!hander.handle(req)) {
                break;
            }

        }
    }
}

class Requset {
    private String msg;

    Requset(String msg) {
        this.msg = msg;
    }

    String getMsg() {
        return msg;
    }

    void setMsg(String msg) {
        this.msg = msg;
    }
}

public class ChainOfResponsibilityDemo {
    public static void main(String args[]) {
        HanderChain process = new HanderChain();
        process.addHander(new HanderA());
        process.addHander(new HanderB());

        Requset req =  new Requset("init");
        process.handle(req);
        System.out.println(req.getMsg());
    }

}
