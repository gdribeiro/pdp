public class Main {

    public static void main(String[] args) {

        Integer printLock = 0; //Cria variavel para ser usada como lock.

        for(int i=0; i < 10; i++) {
            new Thread(new SlowConsole(printLock), "Thread " + i).start();
        }
    }
}

class SlowConsole implements Runnable{
    private Integer pLock;

    public SlowConsole(Integer lock) {
        pLock = lock; //Inicia o lock
    }

    public void println(String msg)
    {
        if (msg == null) throw new NullPointerException("Invalid parameter");
        //Adquire o lock e imprime a mensagem.
        synchronized(pLock) {
            for (int i=0; i<msg.length(); i++) {
                slowPutchar(msg.charAt(i)); }
                slowPutchar('\n');
            }
        }

        private void slowPutchar(char c)
        {
            System.out.print(c);
            try {
                Thread.sleep(100);
            }
            catch (InterruptedException ie) {

            }
        }

        public void run() {
            println("Hello! I'm " + Thread.currentThread().getName());
        }


}
