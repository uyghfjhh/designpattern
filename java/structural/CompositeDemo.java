//author sbkun
package structural;

import java.util.LinkedList;
import java.util.List;

interface HumResoure {
    void showDetails();
}

class Employee implements HumResoure {
    Employee(String name, int age) {
        this.name = name;
        this.age = age;
    }

    @Override
    public void showDetails() {
        System.out.println("name:" + name + " age:" + age);
    }

    private String name;
    private int age;
}

class Department implements HumResoure {
    void addEmployee(Employee e) {
        employees_.add(e);
    }

    @Override
    public void showDetails() {
        for (Employee e : employees_) {
            e.showDetails();
        }
    }

    private List<Employee> employees_ = new LinkedList<Employee>();
}

public class CompositeDemo {
    public static void main(String args[]) {
        Department d = new Department();
        d.addEmployee(new Employee("sbkun", 13));
        d.addEmployee(new Employee("kunsb", 31));
        d.showDetails();
    }
}

