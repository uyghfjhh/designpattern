//author sbkun
package command;

class Tv {
    void on() {
        System.out.println("TV on");
    }

    void off() {
        System.out.println("TV off");
    }

    void watch(String channel) {
        System.out.println("watch " + channel);
    }
}

interface Command {
    void execute();
}

class TvOffCommand implements Command {
    TvOffCommand(Tv tv) {
        this.tv = tv;
    }

    @Override
    public void execute() {
        tv.off();
    }

    private Tv tv;
}

class TvWatchCommand implements Command {
    TvWatchCommand(Tv tv, String channel) {
        this.tv = tv;
        this.channel = channel;
    }

    @Override
    public void execute() {
        tv.on();
        tv.watch(channel);
    }

    private Tv tv;
    private String channel;
}


public class CommandDemo {
    public static void main(String args[]) {
        Tv tv = new Tv();

        TvWatchCommand watch = new TvWatchCommand(tv, "cctv");
        TvOffCommand off = new TvOffCommand(tv);

        watch.execute();
        off.execute();
    }
}

