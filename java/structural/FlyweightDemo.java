package structural;

import java.util.HashMap;
import java.util.Map;

class Icon {
    Icon(String name) {
        this.name = name;
    }
    void draw() {
        System.out.println("icon ["+name+"] draw");
    }
    private String name;
}

class IconFactory {
    static IconFactory getInstance() {
        return instance;
    }

    public Icon getIcon(String name) {
        Icon icon = (Icon)icons.get(name);
        if (icon != null) {
            return icon;
        }
        icon = new Icon(name);
        icons.put(name, icon);
        return icon;
    }

    private IconFactory() {
    }

    private Map icons = new HashMap<String, Icon>();
    static IconFactory instance = new IconFactory();
}

public class FlyweightDemo {
    static public void main(String args[]) {
        Icon icon1 = IconFactory.getInstance().getIcon("sbkun");
        icon1.draw();

        Icon icon2 = IconFactory.getInstance().getIcon("sbkun");
        icon2.draw();
    }
}
