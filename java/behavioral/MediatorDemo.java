package behavioral;

import java.util.HashMap;
import java.util.Map;

class ChatRoom {
    ChatRoom(String name) {
        this.name = name;
    }

    void addRoot(User user) {
        room.put(user.getName(), user);
        user.setRoom(this);
    }

    void send(String msg, String userName) {
        for(Map.Entry<String, User> entry: room.entrySet()) {
            if (!entry.getKey().equals(userName)) {
                User user = entry.getValue();
                user.recv(msg);
            }
        }
    }

    public String getName() {
        return name;
    }

    private String name;
    private Map<String, User> room = new HashMap<String, User>();
}

class User {
    User(String name) {
        this.name = name;
    }

    void send(String msg) {
        if (room != null) {
            System.out.println(name + " send " + msg + " to " + room.getName());
            room.send(msg, name);
        }
    }

    void recv(String msg) {
        if (room != null) {
            System.out.println(name + " recv " + msg + " from " + room.getName());
        }
    }

    public String getName() {
        return name;
    }

    public void setRoom(ChatRoom room) {
        this.room = room;
    }

    private String name;

    private ChatRoom room = null;
}

public class MediatorDemo {
    static public void main(String args[]) {
        ChatRoom chat1 = new ChatRoom("chat1");
        ChatRoom chat2 = new ChatRoom("chat2");

        User user1 = new User("user1");
        User user2 = new User("user2");
        User user3 = new User("user3");
        User user4 = new User("user4");
        User user5 = new User("user5");

        chat1.addRoot(user1);
        chat1.addRoot(user2);

        chat2.addRoot(user3);
        chat2.addRoot(user4);
        chat2.addRoot(user5);

        user1.send("sbkun");

        System.out.println("");

        user3.send("sbkun");
    }
}
