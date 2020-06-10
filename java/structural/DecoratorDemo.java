package structural;

class Fstream {
    void read() {
        System.out.println("base read");
    }
}

class FilterFstream extends Fstream {
    FilterFstream(Fstream f) {
        this.fstream = f;
    }

    protected Fstream fstream;
}

class BufferFstream extends FilterFstream {
    BufferFstream(Fstream f) {
        super(f);
    }

    void read() {
        System.out.println("buffer read");
        fstream.read();
    }
}

class ZipFstream extends FilterFstream {
    ZipFstream(Fstream f) {
        super(f);
    }

    void read() {
        System.out.println("zip read");
        fstream.read();
    }
}

class CipherFstream extends FilterFstream {
    CipherFstream(Fstream f) {
        super(f);
    }

    void read() {
        System.out.println("cipher read");
        fstream.read();
    }
}

public class DecoratorDemo {
    public static void main(String args[]) {
        Fstream f = new BufferFstream(new CipherFstream(new ZipFstream(new Fstream())));
        f.read();
    }
}
