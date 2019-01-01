import java.net.*;
import java.io.*;
import java.util.Scanner;

class FTPclient {
	private DataInputStream dis = null;
	private DataOutputStream dos = null;
	private Socket socket = null;
	
	FTPclient() {
		try {
			String input,output;
			BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
			socket = new Socket("localhost",3000);
			dis = new DataInputStream(socket.getInputStream());
			dos = new DataOutputStream(socket.getOutputStream());
			output = sc.readLine();
			dos.writeUTF(output);               // write ftp
			System.out.print(dis.readUTF());    // print ftp>
			dos.writeUTF(sc.readLine());            // write open 10.10.10.212
			System.out.print(dis.readUTF());    // print connected
			dos.writeUTF(sc.readLine());
			System.out.print(dis.readUTF());
			dos.writeUTF(sc.readLine());             //send mget
			System.out.print(dis.readUTF());
			
			dos.writeUTF(sc.readLine());             //send mput
			System.out.print(dis.readUTF());
			dos.writeUTF(sc.readLine());            //send exit
			System.out.print(dis.readUTF());
			dos.writeUTF(sc.readLine());             //send exit
			System.out.println(dis.readUTF());
			dis.close();
			dos.close();
			socket.close();
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		FTPclient ftp = new FTPclient();
	}
}
