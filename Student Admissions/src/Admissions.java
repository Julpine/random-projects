/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Test;

import java.util.ArrayList;

/**
 *
 * @author Julian Pineiro
 */
public class Admissions {

    ArrayList<Student> list;
    Student a;
    int index;
    boolean found;

    public Admissions() {
        list = new ArrayList<Student>();
    }

    void search(String idNum) {
        found = false;
        int i = 0;

        while (!found && i < list.size()) {
            Student b = list.get(i);
            if (b.getId().equalsIgnoreCase(idNum)) {
                a = b;
                found = true;
                index = i;
            } else {
                i++;
            }
        }
    }

    void add(Student a) {
        list.add(a);
    }

    Student delete(int i) {
        return list.remove(i);
    }

    int getIndex() {
        return index;
    }

    boolean inList() {
        return found;
    }

    Student getAccount() {
        return a;
    }

    int size() {
        return list.size();
    }

    boolean isEmpty() {
        return list.isEmpty();
    }

    ArrayList getList() {
        return list;
    }

}
