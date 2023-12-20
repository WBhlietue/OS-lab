import java.util.*;
import java.io.*;
import java.net.*;
import java.time.*;
public class D26 {
    public static void main(String[] args) {
        try {
            Socket sock = new Socket("127.0.0.1", 17);
            InputStream in = sock.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));
            String line;
            while ((line = bin.readLine()) != null) {
                System.out.println(line);
            }
            sock.close();
        } catch (Exception err) {
            System.err.println(err);
        }
    }
}
