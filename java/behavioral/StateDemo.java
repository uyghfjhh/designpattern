package behavioral;

//tcp连接，持有tcp状态机
class TCPConnetion {
    TCPConnetion() {
        this.state = new TCPClosed();
        System.out.println("TCPConnetion init state " + state.getStateName());
    }

    void PassiveOpen() {
        System.out.println("TCPConnetion setup tcb");
        this.state.PassiveOpen(this);
    }

    void Close() {
        state.Close(this);
    }

    void Send(String msg) {
        state.Send(this, msg);
    }

    void Recv(String msg) {
        System.out.println("TCPConnetion Recvd [ " + msg + " ]");
        state.Recv(this, msg);
    }

    void ChangeState(TCPState s) {
        this.state = s;
    }

    private TCPState state;
};

//tcp状态机基类，负责处理特定状态下的各种事件
//每一个接口，表示对一个事件的处理
abstract class TCPState {
    protected TCPState(String name) {
        this.name = name;
    }

    //主动打开连接， 用于客户端
    void ActiveOpen(TCPConnetion c) {
    }

    //被动打开连接，用于服务端
    void PassiveOpen(TCPConnetion c) {
    }

    //关闭连接
    void Close(TCPConnetion c) {

    }

    //发出报文
    void Send(TCPConnetion c, String msg) {

    }

    //收到报文
    void Recv(TCPConnetion c, String msg) {
    }

    //获取当前状态名称
    String getStateName() {
        return name;
    }

    void ChangeState(TCPConnetion c, TCPState s) {
        System.out.println("[" + getStateName() + "] goto [" + s.getStateName() + "] \n");
        c.ChangeState(s);
    }

    private String name;
};

class TCPListen extends TCPState {
    TCPListen() {
        super("LISTEN");
    }

    @Override
    void Send(TCPConnetion c, String msg) {
        System.out.println("Send " + msg);
        ChangeState(c, new TCPSynReceived());
    }

    @Override
    void Recv(TCPConnetion c, String msg) {
        if (msg == "ACK") {
            Send(c, "SYN+ACK");
        }
    }
};

class TCPEstablished extends TCPState {
    TCPEstablished() {
        super("ESTABLISHED");
    }
};

class TCPClosed extends TCPState {
    TCPClosed() {
        super("CLOSED");
    }

    @Override
    void PassiveOpen(TCPConnetion c) {
        ChangeState(c, new TCPListen());
    }
};

class TCPSynReceived extends TCPState {
    TCPSynReceived() {
        super("SYN-RECEIVED");
    }

    @Override
    void Recv(TCPConnetion c, String msg) {
        if (msg == "ACK") {
            ChangeState(c, new TCPEstablished());
        }
    }
};

public class StateDemo {
    public static void main(String[] args) {
        TCPConnetion c = new TCPConnetion();
        c.PassiveOpen();    //tcp连接进入listen状态
        c.Recv("ACK"); //收到第一步握手的ack
        c.Recv("ACK"); //收到第三步握手的ack，连接建立成功
    }
}
