//author sbkun
package behavioral;

import java.util.Vector;

class Context {
    Context(String input) {
        this.input = input;
    }

    public String getInput() {
        return input;
    }

    public void setInput(String input) {
        this.input = input;
    }

    public String getOutput() {
        return output;
    }

    public void setOutput(String output) {
        this.output = output;
    }

    private String input;
    private String output;
}

abstract class Expression {
    abstract void interpret(Context context);
}

class IntToHexExpression extends Expression{
    @Override
    void interpret(Context context) {
        String arg = context.getInput();
        if (arg.contains("Hexadecimal")) {
            int intArg = Integer.parseInt(arg.substring(0, arg.indexOf(" ")));
            context.setOutput(Integer.toHexString(intArg));
        }
    }
}

class IntToBinaryExpression extends Expression{

    @Override
    void interpret(Context context) {
        String arg = context.getInput();
        if (arg.contains("Binary")) {
            int intArg = Integer.parseInt(arg.substring(0, arg.indexOf(" ")));
            context.setOutput(Integer.toBinaryString(intArg));
        }
    }
}

class InterpreterClient {
    InterpreterClient() {
        //build the parse tree
        interpreters.add(new IntToBinaryExpression());
        interpreters.add(new IntToHexExpression());
    }

    String interpret(Context context) {
        for(Expression e: interpreters) {
            e.interpret(context);
        }
        return context.getOutput();
    }

    private Vector<Expression> interpreters = new Vector<>();
}

public class InterpreterDemo {
    public static void main(String args[]) {
        String str1 = "28 in Binary";
        String str2 = "28 in Hexadecimal";

        InterpreterClient interpreterClient = new InterpreterClient();

        Context context1 = new Context(str1);
        Context context2 = new Context(str2);

        String ret1 = interpreterClient.interpret(context1);
        String ret2 = interpreterClient.interpret(context2);

        System.out.println(str1+" = "+ret1);
        System.out.println(str2+" = "+ret2);
    }
}
