package designpattern.observer;
import java.util.List;
import java.util.ArrayList;

interface Subject {
	void registerObserver(Observer observer);
	void removeObserver(Observer observer);
	void updateObservers(String message);
}

interface Observer{
	void update(String message);
}

class ConcreteSubject implements Subject{
	private List<Observer> observers = new ArrayList<Observer>();

	@Override
	public void registerObserver(Observer observer) {
		observers.add(observer);
	}

	@Override
	public void removeObserver(Observer observer){
		observers.remove(observer);
	}

	@Override
	public void updateObservers(String message)
	{
		for (Observer observer: observers){
			observer.update(message);
		}

	}
}

class ConcreteObserverOne implements Observer {

	@Override
	public void update(String message) {
		System.out.println(this.getClass().getName()+":"+message);
	}

}

class ConcreteObserverTwo implements Observer {

	@Override
	public void update(String message) {
		System.out.println(this.getClass().getName()+":"+message);
	}

}


public class Observer_demo {
	public static void main(String args[]) {
		Subject subject = new ConcreteSubject();
		subject.registerObserver(new ConcreteObserverOne());
		subject.registerObserver(new ConcreteObserverTwo());
		subject.updateObservers("notifyed");
	}
}
