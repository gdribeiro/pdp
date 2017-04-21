import java.util.*;
import java.util.concurrent.*;

public class Exec3
{
	static Queue<String> buffer = new LinkedList<String>();
	static int N = 10; //N deve ser estatico, ao contrario um erro de referencia é retornado
	static CyclicBarrier barrier = new CyclicBarrier(N);

 	public static void main(String[] args)
 	{

		for (int i = 0; i < N; i++)
		{
	 		new Thread(new MyThread(), String.valueOf(i)).start();
		}
	}

	static class MyThread implements Runnable
	{
		@Override
		public void run()
		{
			System.out.println("Thread " +
			Thread.currentThread().getName() + " add to Queue");

			synchronized(buffer)
			{
				buffer.add(Thread.currentThread().getName());
			}

			try
			{
				barrier.await();
			}
			catch(InterruptedException e) { }
			catch(BrokenBarrierException e) { }

			synchronized(buffer)
			{

				System.out.println("Thread " +
					Thread.currentThread().getName() + " remove " + buffer.poll() + "from Queue");
			}
	 	}
	}

}