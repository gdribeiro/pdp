public class Main {

    public static void main(String[] args) {

        for(int i=0; i < 10; i++) {
            new Thread(new SlowConsole(), "Thread " + i).start();
        }
    }
}

class SlowConsole implements Runnable {

    public void println(String msg) {
        if (msg == null) throw new NullPointerException("Invalid parameter");
        for (int i=0; i<msg.length(); i++)
        slowPutchar(msg.charAt(i));
        slowPutchar('\n');
    }

    private void slowPutchar(char c) {
        System.out.print(c);
        try
        {
            Thread.sleep(100);
        }
        catch (InterruptedException ie) {
            // Blank
        }
    }

    @Override
    public void run() {
            println("Hello! I'm " + Thread.currentThread().getName());
    }


}
