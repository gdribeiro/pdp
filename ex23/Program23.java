class SlowConsole implements Runnable{
	private Integer pLock;

	public SlowConsole(Integer lock)
	{
		pLock = lock;
	}
	
	public void println(String msg)
	{
		if (msg == null) throw new NullPointerException("Invalid parameter");
 		for (int i=0; i<msg.length(); i++)
 			synchronized(pLock)
 			{
 				slowPutchar(msg.charAt(i));
 			}
 		synchronized(pLock)
 		{
			slowPutchar('\n');
 		}
 	}
 	
 	private void slowPutchar(char c)
 	{
 		System.out.print(c);
 		try
 		{
 			Thread.sleep(100);
 		}
 		catch (InterruptedException ie) {}
	}

	public void run()
	{
		println("Hello! I'm " + Thread.currentThread().getName());
	}


}

public class Program23
{
	public static void main(String[] args)
	{
		Integer printLock = 0;
		for(int i=0; i < 10; i++)
			new Thread(new SlowConsole(printLock), "Thread " + i).start();
	}	
}