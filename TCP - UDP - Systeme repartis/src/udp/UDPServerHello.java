package udp;

import java.io.IOException;
import java.net.DatagramPacket;

public class UDPServerHello extends UDPServerBuilder implements Runnable
{
	private final int size = 1024;
	
	public void run() 
	{
		try 
		{
			setConnection();
			
			rep = new DatagramPacket(new byte[size],size);
			socket.receive(rep);
			System.out.println("request received");
			
			req = new DatagramPacket(new byte[size],0,size,address.getAddress(),address.getPort());
			socket.send(req);
			System.out.println("reply sent");
			
			socket.close();
		}
		catch(IOException e)
		{ 
			System.out.println("IOException UDPClient"); 
		}
	}
}
