import java.net.*;
import java.io.*;
import java.util.*;

//class TCPClient implements Runnable 
//{
//	private Socket socket;
//	private InetSocketAddress inetSocketAddress;
//	
//	TCPClient()
//	{
//		socket = new Socket();
//		inetSocketAddress = new InetSocketAddress("172.25.61.182",8080);
//	}
//	
//	public void run( ) 
//	{
//		try 
//		{
//			socket.connect(inetSocketAddress);
//			System.out.println("Hello World, client connected");
//			socket.getOutputStream().write(42);
//			socket.close();
//		}
//		catch(IOException e)
//		{ System.out.println("IOException TCPClient"); }
//	}
//}

class TCPClient extends TCPClientBuilder implements Runnable 
{
	public void run( ) 
	{
		TCPInfo info = new TCPInfo();
		
		try 
		{
			socket.connect(inetSocketAddress);
			System.out.println("Hello World, client connected");
			
			
			
			socket.close();
		}
		catch(IOException e)
		{ System.out.println("IOException TCPClient"); }
	}
}