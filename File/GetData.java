/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package File;

import javax.swing.JOptionPane;

/**
 *
 * @author Julian Pineiro
 */
public class GetData {

    static double getDouble(String s) {
        return Double.parseDouble(getWord(s));
    }

    static int getInt(String s) {
        return Integer.parseInt(getWord(s));
    }

    static String getWord(String s) {
        return JOptionPane.showInputDialog(s);
    }

}
