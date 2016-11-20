import java.net.*;
import java.io.*;
import java.util.*;


abstract class TCPClientBuilder extends TCPRW
{
	protected Socket socket;
	protected InetSocketAddress inetSocketAddress;
	protected InputStream in;
	protected OutputStream out;
	
	TCPClientBuilder()
	{
		socket = new Socket();
		
		inetSocketAddress = new InetSocketAddress("172.25.3.61",8080);
	}
	
}	
	
