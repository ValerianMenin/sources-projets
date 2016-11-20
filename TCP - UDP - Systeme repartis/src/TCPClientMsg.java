import java.io.IOException;


public class TCPClientMsg extends TCPClientBuilder implements Runnable
{
	@Override
	public void run()
	{
		try 
		{
			socket.connect(inetSocketAddress);
					
			out = socket.getOutputStream();
			in = socket.getInputStream();
			
			
			send(out, "Hello Theo"); // send 1st output
			//System.out.println(receive(in)); // get 1st input
			
			System.out.println(receive(in)); // get 2nd input
			
			in.close();
			out.close();
			socket.close();
		}
		catch(IOException e)
		{ System.out.println("IOException TCPClientMsg"); }
	}
}
