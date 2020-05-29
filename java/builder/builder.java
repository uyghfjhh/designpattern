package builder;

class Spice{

    private Spice(Builder builder) {
        this.ip = builder.ip;
        this.port = builder.port;
        this.user = builder.user;
        this.password = builder.password;
        this.isH264 = builder.isH264;
        this.frameRae = builder.frameRae;
        this.isSound = builder.isSound;
    }

    public void connect(){
        System.out.println("spice is connecting....");
    }

    public static class Builder {
        Builder(String ip, int port, String user, String password){
            this.ip = ip;
            this.port = port;
            this.user = user;
            this.password = password;
        }

        Spice build() {
            //校验必选项
            if (ip==null && port <=0 && port>6555 && user==null && password==null) {
                throw new IllegalArgumentException();
            }
            //校验可选项
            if (frameRae != 0 )
            {
                if (!isH264) {
                    throw  new IllegalArgumentException("Please set h264 before");
                }
                if (frameRae > DEFAULT_MAX_FRAMERATE || frameRae < DEFAULT_MIN_FRAMERATE) {
                    throw new IllegalArgumentException("FrameRate out of range");
                }
            }

            return new Spice(this);
        }

        Builder setIsH264(boolean isH264) {
            this.isH264 = isH264;
            return this;
        }

        Builder setIsSound(boolean isSound) {
            this.isSound = isSound;
            return this;
        }

        Builder setFrameRate(int rate) {
            this.frameRae = rate;
            return this;
        }

        private static final int DEFAULT_MAX_FRAMERATE = 30;
        private static final int DEFAULT_MIN_FRAMERATE = 5;

        private String ip;
        private int port;
        private String user;
        private String password;
        private boolean isH264 = false;
        private boolean isSound = false;
        private int frameRae = 0;
    }

    private String ip;
    private int port;
    private String user;
    private String password;
    private boolean isH264;
    private boolean isSound;
    private int frameRae;

}



public class builder {
    public static void main(String args[])
    {
        try {
            Spice spice =  new Spice.Builder("127.0.0.1", 9001, "sbkun", "sbkun")
                    .setIsH264(true).setFrameRate(10).setIsSound(true).build();
            spice.connect();
        }
        catch (IllegalArgumentException e){
            System.out.println(e);
        }
    }
}
