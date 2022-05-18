/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package File;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class BasicFile {

    File f;
    JFileChooser select;

    BasicFile() {

    }

    public void selectFile() {
        this.select = new JFileChooser();
        int status = this.select.showOpenDialog(null);
        try {
            if (status != 0) {
                throw new IOException();
            }
            this.f = this.select.getSelectedFile();

            if (!(this.f.exists())) {
                throw new FileNotFoundException();
            }
        } catch (FileNotFoundException e) {
            JOptionPane.showMessageDialog(null, "File Not Found ", "Error", 1);
        } catch (IOException e) {
            System.exit(0);
        }
    }

    public File selected() {
        return f;

    }

    void append(File x) throws IOException {

        FileInputStream source = new FileInputStream(f);
        BufferedWriter out;
        try (BufferedReader in = new BufferedReader(new InputStreamReader(source))) {
            FileWriter fstream = new FileWriter(x, true);
            out = new BufferedWriter(fstream);
            String Line = null;
            while ((Line = in.readLine()) != null) {

                out.write(Line);
                out.newLine();
            }
        }

        out.close();

    }

    void override(File x) throws FileNotFoundException {
        DataInputStream in = null;
        DataOutputStream out = null;
        try {

            in = new DataInputStream(new FileInputStream(this.f));
            out = new DataOutputStream(new FileOutputStream(x));
            label78:
            while (true) {
                try {
                    byte data = in.readByte();
                    out.writeByte(data);
                } catch (EOFException e) {
                    JOptionPane.showMessageDialog(null, "Success!!!", "Backup Complete!", 1);

                    break label78;
                } catch (IOException e) {
                    JOptionPane.showMessageDialog(null, "File Not Found ", "Error", 1);
                }
            }
        } finally {
            try {
                in.close();
                out.close();
            } catch (IOException e) {

            }
        }
    }

    void search(String z) throws FileNotFoundException {
        Scanner scanner = new Scanner(f.getAbsoluteFile());
        int lineNum = 0;
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            lineNum++;
            boolean y = true;
            Scanner scanner2 = new Scanner(line);
            while (scanner2.hasNext() && y) {
                String m = scanner2.next();
                if (m.equalsIgnoreCase(z)) {
                    System.out.println(lineNum + ": " + line);
                    y = false;
                }
            }

        }
    }

    void copyFile() throws FileNotFoundException {
        DataInputStream in = null;
        DataOutputStream out = null;
        try {
String name;

            int i = 1;
            name = f.getName();
            
           String[] tokens = f.getName().split("\\.(?=[^\\.]+$)");
           
           int index = f.getName().indexOf(".");
        
        String ext = f.getName().substring(index);
        
            
            
            File f2 = new File(f.getParent(), name);
            System.out.println(f.getParent());
            while (f2.exists()) {
                File f3 = new File(f.getParent(), "copy" + i + ext);
                f2 = f3;
                i++;
            }
            in = new DataInputStream(new FileInputStream(this.f));
            out = new DataOutputStream(new FileOutputStream(f2));
            label5:
            while (true) {
                try {
                    byte data = in.readByte();
                    out.writeByte(data);
                } catch (EOFException e) {
                    JOptionPane.showMessageDialog(null, "Success!!!", "Backup Complete!", 1);

                    break label5;
                } catch (IOException e) {
                    JOptionPane.showMessageDialog(null, "File Not Found ", "Error", 1);
                }
            }
        } finally {
            try {
                in.close();
                out.close();
            } catch (Exception e) {

            }
        }
    }

    boolean exists() {
        return this.f.exists();
    }

    public void attributes() throws FileNotFoundException, IOException {
        String input = "";
        input += "Absolute Path:\n" + f.getAbsolutePath() + "\n\n";

        input += "Size of File:\n" + f.length() + "\n\n";

        input += "List of Files:\n";

        File list = new File(f.getParent());
        File[] files = list.listFiles();
        if (files.length == 0) {
            input += "Empty";
        } else {
            for (File aFile : files) {
                input += aFile + "\n";
            }
        }

        JTextArea textArea = new JTextArea(input);

        JScrollPane scroll = new JScrollPane(textArea, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);

        JOptionPane.showMessageDialog(null,
                scroll,
                "File Contents:",
                JOptionPane.PLAIN_MESSAGE);
    }

    public void display() throws FileNotFoundException, IOException {
        String input = "";

        try {
            BufferedReader reader = new BufferedReader(new FileReader(f.getAbsolutePath()));
            String line = null;

            while ((line = reader.readLine()) != null) {

                input += line + "\n";
            }
        } catch (FileNotFoundException e) {

        } catch (IOException e) {

        }
        JTextArea textArea = new JTextArea(input);

        JScrollPane scroll = new JScrollPane(textArea, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);

        JOptionPane.showMessageDialog(null,
                scroll,
                "File Contents:",
                JOptionPane.PLAIN_MESSAGE);

    }

}
