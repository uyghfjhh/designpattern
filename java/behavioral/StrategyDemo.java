package behavioral;

import java.util.HashMap;
import java.util.Map;

interface Discount {
    double calculate(double price);
}

class VipDiscount implements Discount {
    //会员8折
    @Override
    public double calculate(double price) {
        return price * 0.8;
    }
}

class GoldVip implements Discount {
    //黄金会员5折
    @Override
    public double calculate(double price) {
        return price * 0.5;
    }
}

class DiscountFactory {
    static{
        System.out.println("haha");
    }
    private static final DiscountFactory INSTANCE = new DiscountFactory();

    public static DiscountFactory getInstance() {
        return INSTANCE;
    }

    private DiscountFactory() {
        System.out.println(this.getClass().getSimpleName() + " init");
        discounts.put("vip", new VipDiscount());
        discounts.put("goldvip", new GoldVip());

    }

    Discount getDiscount(String vipType) {
        String t = vipType.toLowerCase();
        return discounts.get(t);
    }

    private Map<String, Discount> discounts = new HashMap<>();
}

class Product {
    Product(double original_price) {
        this.original_price = original_price;
    }

    public double getPrice(String vipType) {
        Discount discount = DiscountFactory.getInstance().getDiscount(vipType);
        if (discount != null) {
            return discount.calculate(original_price);
        }
        return original_price;
    }

    private double original_price;
}

public class StrategyDemo {
    public static void main(String args[]) {
        System.out.println("in main");
        Product product = new Product(100);
        System.out.println(product.getPrice("goldvip"));
        System.out.println(product.getPrice("vip"));
        System.out.println(product.getPrice("haha"));
    }

}


