package structural;

class HttpService {
    void service(String req, String rsp) {
        System.out.println("handle req " + req);
    }
}

class HttpServerProxy extends HttpService {
    void service(String req, String rsp) {
        if (req.indexOf("sbkun") == -1) {
            super.service(req, rsp);
        } else {
            System.out.println("not handle " + req);
        }
    }
}

public class ProxyDemo {
    public static void main(String args[]) {
        HttpServerProxy hp = new HttpServerProxy();
        String rsp = "";
        hp.service("sbkun", rsp);
        hp.service("haha", rsp);
    }
}
