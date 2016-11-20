import java.io.IOException;


public class TCPClientTimeout extends TCPClientBuilder implements Runnable
{
	@Override
	public void run()
	{
		try 
		{
			System.out.println("Trying to connect ...");
			socket.connect(inetSocketAddress);
			System.out.println("Connected");

			
			out = socket.getOutputStream();
			in = socket.getInputStream();
			
			send(out, "testSend=>");
			//System.out.println("df");
			
			in.close();
		    out.close();
			socket.close();
			System.out.println("Connection ended");

		}
		catch(IOException e)
		{ System.out.println("IOException TCPClientTimeOut"); }
	}
}
