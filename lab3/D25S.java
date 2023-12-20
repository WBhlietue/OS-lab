import java.util.*;
import java.io.*;
import java.net.*;
import java.time.*;

public class D25S {
    public static void main(String[] args) {
        try {
            String serverAddress = "127.0.0.1";
            int serverPort = 17;

            Socket socket = new Socket(serverAddress, serverPort);
            OutputStream output = socket.getOutputStream();

            String message = "hihi, asdasd nani nani :)\n";
            byte[] messageBytes = message.getBytes();
            output.write(messageBytes);

            InputStream in = socket.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));
            String line;
            while ((line = bin.readLine()) != null) {
                System.out.println(line);
            }

            output.close();
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
