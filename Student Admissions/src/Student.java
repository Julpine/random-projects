/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Test;

import java.util.ArrayList;
import java.util.Date;

/**
 *
 * @author Julian Pineiro
 */
public class Student {

    private Name name;
    private Address address;
    private String id;

    ArrayList<String> list;
    private Date date;
    boolean found;
    String ba;
    int index;

    public Student(Name n, Address addr, String id, ArrayList<String> list, Date d) {
        this.name = n;
        this.address = addr;
        this.id = id;
        this.list = list;
        this.date = d;
    }

    public Name getName() {
        return name;
    }

    public Address getAddress() {
        return address;
    }

    public String getId() {
        return id;
    }

    public Date getDate() {
        return date;
    }

    void removeCourse(int k) {
        list.remove(k);
    }

    void addCourse(String h) {
        list.add(h);
    }

    void search(String x) {
        found = false;
        int i = 0;

        while (!found && i < list.size()) {
            String stu = list.get(i);
            if (stu.equalsIgnoreCase(x)) {
                ba = stu;
                found = true;
                index = i;
            } else {
                i++;
            }
        }
    }

    boolean inList() {
        return found;
    }

    int getCourse() {
        return index;
    }
    
    int getCourses(){
        return list.size();
    }

}
