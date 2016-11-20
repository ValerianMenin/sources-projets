package udp;

import java.net.DatagramSocket;
import java.net.Inet6Address;
import java.net.InetAddress;
import java.net.SocketException;

class UDPInfo 
{
class SocketInfo {
String lA,rA,tC;
int lP,rP,sbS,rbS,tO;
boolean isIPV6,bounded,closed,connected,rU,bC;
SocketInfo() { clear(); }
void clear() {
lA=rA=tC=null;
lP=rP=sbS=rbS=tO=-1;
isIPV6=bounded=closed=connected=bC=rU=false;
}
}
protected void socketInfo(String event, DatagramSocket s) throws SocketException {
if((s!=null)&(event!=null)) {
sI.clear();
sI.isIPV6 = isIPV6(s.getInetAddress());
sI.lA = getAdressName(s.getLocalAddress());
sI.lP = s.getLocalPort();
sI.rA = getAdressName(s.getInetAddress());
sI.rP = s.getPort();
sI.closed = s.isClosed(); 
sI.bounded = s.isBound();
sI.connected = s.isConnected();
if(!sI.closed) {
sI.tO = s.getSoTimeout();
sI.bC = s.getBroadcast();
sI.rU = s.getReuseAddress();
sI.tC = Integer.toHexString(s.getTrafficClass());
sI.sbS = s.getSendBufferSize();
sI.rbS = s.getReceiveBufferSize();
}
print(event);
}
}
private SocketInfo sI = new SocketInfo();
private String getAdressName(InetAddress iA) {
if(iA != null )
return iA.toString();
return null;
}
private boolean isIPV6(InetAddress iA) {
if(iA instanceof Inet6Address)
return true;
return false;
}
void print(String event) {
if(sI.closed)
System.out.println (
event+"\n"
+"IPV6: "+sI.isIPV6+"\n"
+"local \tadress:"+sI.lA+"\t port:"+sI.lP+"\n"
+"remote \tadress:"+sI.rA+"\t port:"+sI.rP+"\n"
+"bounded: "+sI.bounded+"\n"
+"closed: "+sI.closed+"\n"
+"connected: "+sI.connected+"\n"
);
else
System.out.println (
event+"\n"
+"IPV6: "+sI.isIPV6+"\n"
+"local \tadress:"+sI.lA+"\t port:"+sI.lP+"\n"
+"remote \tadress:"+sI.rA+"\t port:"+sI.rP+"\n"
+"bounded: "+sI.bounded+"\n"
+"closed: "+sI.closed+"\n"
+"connected: "+sI.connected+"\n"
+"timeout: "+sI.tO+"\t broadcast: "+sI.bC+"\t reuse: "+sI.rU+"\t traffic: "+sI.tC+"\n"
+"buffer \tsend:"+sI.sbS+"\treceive:"+sI.rbS+"\n"
);
}
} 