//author sbkun
package structural;

abstract class Shape {
    Shape(Color color) {
        this.color = color;
    }

    abstract void draw();

    protected Color color;
}

abstract class Color {
    abstract String dye();
}

class Red extends Color {
    @Override
    String dye() {
        return "Red";
    }
}

class Blue extends Color{
    @Override
    String dye() {
        return "Blue";
    }
}

class Circle extends Shape {
    Circle(Color color) {
        super(color);
    }

    @Override
    public void draw() {
        System.out.println("draw Circle and dye it " + color.dye());
    }
}

class Rectangle extends Shape {
    Rectangle(Color color) {
        super(color);
    }

    @Override
    public void draw() {
        System.out.println("draw Rectangele and dye it " + color.dye());
    }
}

public class BridgeDemo {
    public static void main(String args[]) {
        Shape circle = new Circle(new Blue());
        Shape rectangle = new Rectangle(new Red());
        circle.draw();
        rectangle.draw();
    }
}

