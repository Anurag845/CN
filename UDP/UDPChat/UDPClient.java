import java.io.*;
import java.net.*;
import java.util.Scanner;

class UDPClient {
	public static void main(String[] args) throws Exception {
		DatagramSocket sock = new DatagramSocket();
		Scanner sc = new Scanner(System.in);
		String data1 = "",data2 = "";
		byte[] b1;
		byte[] b2;
		
		while(!data1.equalsIgnoreCase("stop")) {
			System.out.print("Client- ");
			data1 = sc.nextLine();
			b1 = data1.getBytes();
			InetAddress ia = InetAddress.getLocalHost();
			DatagramPacket pack1 = new DatagramPacket(b1,b1.length,ia,3000);
			sock.send(pack1);
			
			b2 = new byte[1024];
			DatagramPacket pack2 = new DatagramPacket(b2,b2.length);
			sock.receive(pack2);
			data2 = new String(pack2.getData());
			
			System.out.println("Server- " + data2);
		}

 	}
}
