package behavioral;

import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;

class Stock {
    private String name;
    private double price;

    Stock(String name, double price) {
        this.name = name;
        this.price = price;
    }

    void setPrice(double price) {
        this.price = price;
    }

    String getName() {
        return this.name;
    }
    double getPrice() {
        return this.price;
    }
}

interface StockObservable {
    void registerObserver(String stockName, StockObserver observer);

    void removeObserver(String stockName, StockObserver observer);
}

class Market implements StockObservable {
    private Map<String, Stock> stocks = new HashMap<String, Stock>();
    private Map<String, List<StockObserver>> stockObservers = new HashMap<String, List<StockObserver>>();

    Market() {
        addStock("one", 1.1);
        addStock("two", 2.1);
    }

    private void addStock(String name, double price) {
        if (!stocks.containsKey(name)) {
            stocks.put(name, new Stock(name, price));
            stockObservers.put(name, new ArrayList<StockObserver>());
        }
    }

    @Override
    public void registerObserver(String stockName, StockObserver observer) {
        if (stocks.containsKey(stockName)) {
            ArrayList<StockObserver> stockObserverList = (ArrayList<StockObserver>) stockObservers.get(stockName);
            if (stockObserverList != null) {
                stockObserverList.add(observer);
            }
        }
    }

    @Override
    public void removeObserver(String stockName, StockObserver observer) {
        if (stocks.containsKey(stockName)) {
            ArrayList<StockObserver> stockObserverList = (ArrayList<StockObserver>) stockObservers.get(stockName);
            if (stockObserverList != null) {
                stockObserverList.remove(observer);
            }
        }
    }

    public void setStockPrice(String name, double price) {
        Stock stock = stocks.get(name);
        if (stock != null) {
            stock.setPrice(price);
            List<StockObserver> list = stockObservers.get(name);
            if (list != null) {
                for (StockObserver o : list) {
                    o.onPriceChanged(stock);
                }
            }
        }
    }
}

interface StockObserver {
    void onPriceChanged(Stock stock);
}

//股民
class Investor implements StockObserver {
    @Override
    public void onPriceChanged(Stock stock) {
        System.out.println(this.getClass().getSimpleName() + ":" + "know that stock's price changed->" + stock.getPrice());
    }
}

//管理员
class Admin implements StockObserver {
    @Override
    public void onPriceChanged(Stock stock) {
        System.out.println(this.getClass().getSimpleName() + ":" + "know that stock's price changed->" + stock.getPrice());
    }
}

public class ObserverDemo {
    public static void main(String args[]) {
        Market m = new Market();
        Investor i = new Investor();
        Admin a = new Admin();

        m.registerObserver("one", i);
        m.registerObserver("one", a);
        m.registerObserver("two", i);

        m.setStockPrice("one", 1.2);
        m.setStockPrice("two", 2.2);
    }
}

