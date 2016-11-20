import java.io.IOException;
import java.net.Inet6Address;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;


class TCPInfo 
{
	class SocketInfo
	{
		String lA,rA,tC;
		int lP,rP,sbS,rbS,tO,soLinger;
		boolean bounded, closed,isIPV6,noDelay;
		
		SocketInfo()
		{
			lA=rA=tC=null;
			lP=rP=sbS=rbS=tO=soLinger=-1;
			bounded=closed=isIPV6=noDelay=false;
		}
	}
	
	/** To print the sever socket's parameters. */
	void ssInfo(String event, ServerSocket ss) throws SocketException,IOException 
	{
		ssI = new SocketInfo();
		ssI.isIPV6 = isIPV6(ss.getInetAddress());
		ssI.lA = getAdressName(ss.getInetAddress());
		ssI.lP = ss.getLocalPort();
		ssI.closed = ss.isClosed();
		ssI.bounded = ss.isBound();
		ssI.tO = ss.getSoTimeout();
		ssI.rbS = ss.getReceiveBufferSize();
		print(event,ssI);
	}
	
	private SocketInfo ssI;
	
	/** To print the socket's parameters. */
	void sInfo(String event, Socket s) throws SocketException,IOException
	{
		sI = new SocketInfo();
		sI.isIPV6 = isIPV6(s.getInetAddress());
		sI.lA = getAdressName(s.getLocalAddress());
		sI.lP = s.getLocalPort();
		sI.rA = getAdressName(s.getInetAddress());
		sI.rP = s.getPort();
		sI.bounded = s.isBound();
		sI.closed = s.isClosed();
		if(!sI.closed)
		{
			sI.tO = s.getSoTimeout();
			sI.soLinger = s.getSoLinger();
			sI.sbS = s.getSendBufferSize();
			sI.rbS = s.getReceiveBufferSize();
			//sI.noDelay = s.getTcpNoDelay();
			//sI.tC = Integer.toHexString(s.getTrafficClass());
		}
		print(event,sI);
	}
	
	private SocketInfo sI;
	private static String getAdressName(InetAddress iA)
	{
		if(iA != null )
		return iA.toString();
		return null;
	}
	
	private static boolean isIPV6(InetAddress iA)
	{
		if(iA instanceof Inet6Address)
		return true;
		return false;
	}
	
	private void print(String event, SocketInfo sI) 
	{
		System.out.println (
			event+":\n"
			+"IPV6: "+sI.isIPV6+"\n"
			+"local \tadress:"+sI.lA+"\t port:"+sI.lP+"\n"
			+"remote \tadress:"+sI.rA+"\t port:"+sI.rP+"\n"
			+"bounded: "+sI.bounded+"\n"
			+"closed: "+sI.closed+"\n"
			+"timeout: "+sI.tO+"\tso linger: "+sI.soLinger+"\n"
			+"buffer \tsend:"+sI.sbS+"\treceive:"+sI.rbS+"\n"
		);
	}
}

