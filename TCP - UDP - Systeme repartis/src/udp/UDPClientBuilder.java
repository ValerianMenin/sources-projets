package udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;

public class UDPClientBuilder extends UDPInfo
{
		InetSocketAddress address;
		DatagramSocket socket;
		DatagramPacket request, reply;
		 
		UDPClientBuilder()
		{ 
			address = null; 
			socket = null; 
			request = reply = null; 
		}
		 
		protected void setConnection() throws IOException 
		{
			address = new InetSocketAddress("172.25.61.218",8080);
			
		//	socket = new DatagramSocket(address.getPort());
			socket = new DatagramSocket();
			socket.connect(address);
			
		}


}
