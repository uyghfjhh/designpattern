//author sbkun
package behavioral;
import java.util.LinkedList;

class Hero {
    Hero(){
        this.hp = 100;
        this.name = "mk";
    }

    Memento saveToMemento() {
        return new Memento(this.name, this.hp);
    }

    void restoreFromMemento(Memento memento) {
        this.name = memento.name;
        this.hp = memento.hp;
    }

    void beingAttacked(int damage) {
        this.hp -= damage;
    }

    @Override
    public String toString() {
        return "Hero{" +
                "name='" + name + '\'' +
                ", hp=" + hp +
                '}';
    }

    private String name;
    private int hp;

    //为了少写几个get，使用了静态内部类
    static class Memento {
        Memento(String name, int hp) {
            this.name = name;
            this.hp = hp;
        }
        private String name;
        private int hp;
    }
}

class War3 {
    void save(Hero.Memento memento) {
        mementos.add(memento);
    }

    void load(Hero hero) {
        if (!mementos.isEmpty()) {
            Hero.Memento memento = mementos.getLast();
            hero.restoreFromMemento(memento);
            mementos.removeLast();
        }
    }

    private LinkedList<Hero.Memento> mementos = new LinkedList<>();
}

public class MementoDemo {
    public static void main(String args[]) {
        War3 war3 = new War3();
        Hero hero = new Hero();
        war3.save(hero.saveToMemento());

        System.out.println(hero+"\n");

        hero.beingAttacked(40);
        System.out.println("fuck ! my hero was attacked, hp reduced 40...");
        System.out.println(hero+"\n");

        System.out.println("don't worry! hero state reload...");
        war3.load(hero);
        System.out.println(hero+"\n");
    }
}


