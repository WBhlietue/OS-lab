import java.util.*;
import java.io.*;
import java.net.*;
import java.time.*;

public class D25 {
    public static void main(String[] args) {

        try {
            ServerSocket serverSocket = new ServerSocket(17);
            while (true) {
                Socket clientSocket = serverSocket.accept();
                InputStream input = clientSocket.getInputStream();
                BufferedReader reader = new BufferedReader(new InputStreamReader(input));
                String message;
                while ((message = reader.readLine()) != null) {
                    OutputStream output = clientSocket.getOutputStream();
                    PrintWriter pout = new PrintWriter(output, true);
                    pout.println("echo -> " +  message + "\n");
                }
                clientSocket.close();
            }
        } catch (Exception err) {
            System.err.println(err);
        }
    }
}
