package behavioral;

import java.util.*;

interface Item {
    public int accept(Visitor visitor);
}

class Phone implements Item {
    Phone(int price, int weight) {
        this.price = price;
        this.weight = weight;
    }

    @Override
    public int accept(Visitor visitor) {
        return visitor.visit(this);
    }

    public int getPrice() {
        return price;
    }

    public int getWeight() {
        return weight;
    }

    private int price;
    private int weight;
}

class Watch implements Item {
    Watch(int price, int weight) {
        this.price = price;
        this.weight = weight;
    }

    @Override
    public int accept(Visitor visitor) {
        return visitor.visit(this);
    }

    public int getPrice() {
        return price;
    }

    public int getWeight() {
        return weight;
    }

    private int price;
    private int weight;
}

interface Visitor {
    int visit(Phone phone);
    int visit(Watch Watch);
}

class ShopingCart implements Visitor {
    @Override
    public int visit(Phone phone) {
        //todo 这里可以使用工厂模式+策略模式 获取商品打折策略
        return phone.getPrice();
    }

    @Override
    public int visit(Watch Watch) {
        //todo 这里可以使用工厂模式+策略模式 获取商品打折策略
        return Watch.getPrice();
    }
}

public class VisitorDemo {
    public static void main(String args[]) {
        List<Item> itemList = new ArrayList<Item>();
        itemList.add(new Watch(1, 1));
        itemList.add(new Phone(2, 2));

        Visitor v = new ShopingCart();

        int totalPrice = 0;

        for (Item it : itemList) {
           totalPrice += it.accept(v);
           //v.visit(it);
        }

        System.out.println("total price: " + totalPrice);
    }
}

