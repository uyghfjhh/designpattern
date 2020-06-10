package behavioral;

class TV
{
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
    TvOffCommand(TV tv) {
        this.tv = tv;
    }

    @Override
    public void execute() {
        tv.off();
    }

    private TV tv;
}

class TvWatchCommand implements Command {
    TvWatchCommand(TV tv, String channel) {
        this.tv = tv;
        this.channel = channel;
    }

    @Override
    public void execute() {
        tv.on();
        tv.watch(channel);
    }

    private TV tv;
    private String channel;
}


public class CommandDemo {
    public static void main(String args[]) {
        TV tv = new TV();

        TvWatchCommand watch = new TvWatchCommand(tv, "cctv");
        TvOffCommand off = new TvOffCommand(tv);

        watch.execute();
        off.execute();
    }
}
