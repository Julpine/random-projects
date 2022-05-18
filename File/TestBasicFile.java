/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package File;

import java.io.FileNotFoundException;
import java.io.IOException;
import javax.swing.JOptionPane;


public class TestBasicFile {

    public static void main(String[] args)
            throws FileNotFoundException, IOException, InterruptedException {
        boolean done = false;

        String menu = "Enter option\n1. Open a File\n2. Exit";

        while (!(done)) {

            BasicFile f = new BasicFile();
            BasicFile f2 = new BasicFile();

            String s = JOptionPane.showInputDialog(menu);
            try {
                int i = Integer.parseInt(s);

                switch (i) {
                    case 1:
                        
                        boolean done2 = false;
                        f.selectFile();

                        if (f.exists()) {
                            
                        } else {
                            f.selectFile();
                        }

                        while (!(done2)) {
                            String menu2 = "Enter option\n1. Copy the File\n2. Write to an output file"
                                    + "\n3. Atrributes of File\n4. Contents of File\n5. Search the File"
                                    + "\n6. Select a new File\n7. Exit";
                            String x = JOptionPane.showInputDialog(menu2);
                            int l = Integer.parseInt(x);
                            switch (l) {
                                case 1:
                                    f.copyFile();
                                    break;
                                case 2:

                                    f2.selectFile();
                                    String menu3 = "Enter option\n1. Override File\n2. Append to File"
                                            + "\n3. Exit";
                                    String z = JOptionPane.showInputDialog(menu3);
                                    int y = Integer.parseInt(z);
                                    switch (y) {
                                        case 1:
                                            f.override(f2.selected());
                                            break;
                                        case 2:
                                            f.append(f2.selected());
                                            break;
                                        case 3:
                                            break;
                                    }
                                    break;

                                case 3:
                                    f.attributes();
                                    break;
                                case 4:
                                    final Thread t1 = new Thread(x);
                                    
                                    f.display();
                                    
                                    
                                    
                                   
                                    break;
                                case 5:
                                    String first = GetData.getWord("What do you want to search for?");
                                    f.search(first);

                                    break;
                                case 6:
                                    done2 = true;
                                    break;
                                case 7:
                                    done2 = true;
                                    done = true;
                                    break;

                            }
                        }
                        break;
                    case 2:
                        done = true;
                    
                }

            } catch (NumberFormatException | NullPointerException e) {
                System.exit(0);
            }
        }
    }

    static void displayInfo(String s, String info) {
        JOptionPane.showMessageDialog(null, s, info, 1);
    }
}
