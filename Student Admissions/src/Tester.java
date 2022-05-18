/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Test;


import java.util.Date;
import javax.swing.JOptionPane;
import java.util.ArrayList;
import java.util.Scanner;
import java.text.SimpleDateFormat;


/**
 *
 * @author Julian Pineiro
 */
public class Tester {

    public static void main(String args[]) {
        Admissions db = new Admissions(); // Enrolled Students
        Admissions drop = new Admissions(); //  Students Who Dropped
        SimpleDateFormat form = new SimpleDateFormat("MMMM d, yyyy");
        boolean done = false;

        while (!done) {
            int menu = GetData.getInt("\tStudent Registration" + "\t"
                    + "\nOptions:"
                    + "\n1. Enroll New Student\n2. Update "
                    + "An Existing Student"
                    + "\n3. Delete A Student\n4. View Student Information\n5."
                    + " Exit");

            switch (menu) {
                case 1: //Creating a Student object
                    System.out.println("Creating Student...");
                    String first = GetData.getWord("Enter First Name");
                    String last = GetData.getWord("Enter Last Name");
                    Name n = new Name(first, last);
                    System.out.printf("%-10s %s\n", "Name:", n.getLastName() + ", " + n.getFirstName());

                    String str = GetData.getWord("Enter Street Name");
                    String city = GetData.getWord("Enter City");
                    String st = GetData.getWord("Enter State");
                    String zip = GetData.getWord("Enter Zip");
                    System.out.printf("%-10s %s %-10s%s\n", "Address:", str + "\n",
                            " ", city + ", " + st + " "
                            + zip);

                    String id = GetData.getWord("enter Id");

                    System.out.printf("%-10s %s\n", "Id Number:", id);

                    String course = GetData.getWord("Enter course");
                    ArrayList<String> courses = new ArrayList<String>();
                    Scanner x = new Scanner(course);
                    int count = 0;
                    while (x.hasNext()) {

                        String token = x.next();
                        courses.add(token);
                        count++;

                    }
                    if (count > 1) {
                        JOptionPane.showMessageDialog(null, "Invalid Course");
                    } else {
                        System.out.printf("%-10s %s\n", "Courses:", courses);
                    }
                    Date today = new Date();
                    
                    System.out.printf("%-10s %s\n", "Date:",form.format(today));

                    Address addr = new Address(str, city, st, zip);
                    Student c = new Student(n, addr, id, courses, today);
                    System.out.println();

                    db.search(id);
                    if (db.inList() || id.equals("")) {

                        System.out.println("INVALID ID WAS PLACED ON STUDENT\n");
                        JOptionPane.showMessageDialog(null, "Invalid ID for student");

                    } else if (count > 1) {

                        System.out.println();
                    } else {

                        db.add(c);
                        System.out.println("STUDENT ADDED\n");
                    }

                    break;
                case 2: //Update Student
                    String idd;
                    idd = GetData.getWord("Enter the Student's ID that needs to be updated");
                    db.search(idd);
                    if (!db.inList()) {
                        JOptionPane.showMessageDialog(null, "Student not found");
                    } else {
                        int option = GetData.getInt("Would you like to (1) Add Course, (2) Delete Course");
                        switch (option) {
                            case 1: //Add Course
                                int h;
                                int count2 = 0;
                                String add = GetData.getWord("Enter course number you wish to add");

                                Scanner y = new Scanner(add);

                                while (y.hasNext()) {
                                    y.next();

                                    count2++;

                                }
                                Student b = db.getAccount();
                                b.search(add);
                                if (count2 > 1 || b.inList()) {
                                    JOptionPane.showMessageDialog(null, "Invalid Course");

                                } else if (5 > b.getCourses()) {
                                    b.addCourse(add);
                                    System.out.println("Courses for Student ID: " + b.getId());
                                    for (h = 0; h < b.list.size(); h++) {
                                        System.out.print(b.list.get(h) + ", ");

                                    }
                                    System.out.println("\n");
                                } else {
                                    JOptionPane.showMessageDialog(null, "Too many courses for student");
                                }

                                break;

                            case 2: // Drop Course
                                String delete = GetData.getWord("Enter the course number you wish to remove");
                                Student d = db.getAccount();
                                d.search(delete);
                                if (!d.inList()) {
                                    JOptionPane.showMessageDialog(null, "Course not found");
                                } else {

                                    d.removeCourse(d.getCourse());
                                    drop.add(d);
                                    for (h = 0; h < d.list.size(); h++) {
                                        System.out.print(d.list.get(h) + ", ");
                                    }
                                    System.out.println();
                                }

                                break;

                        }
                    }

                    break;

                case 3: //Delete Student
                    String ex;
                    ex = GetData.getWord("Enter the ID of the student you wish to remove");
                    db.search(ex);
                    if (!db.inList()) {
                        JOptionPane.showMessageDialog(null, "Student not found.");
                    } else {
                        db.delete(db.getIndex());
                        JOptionPane.showMessageDialog(null, "Student ID:" + ex + " has been removed.");
                    }
                    break;

                case 4: //View Student Information

                    int view = GetData.getInt("What information would you like to view?\n1. One Student\n2. All"
                            + " Students\n3. All Deleted Students\n");

                    switch (view) {
                        case 1: // View one Student
                            int j;
                            String ac = GetData.getWord("Enter Student's ID");
                            db.search(ac);
                            if (!db.inList()) {
                                JOptionPane.showMessageDialog(null, "Student not found.");
                            } else {
                                System.out.println("STUDENT");
                                Student bb = db.getAccount();
                                String s = "Student\t" + bb.getName().getFirstName() + "\t"
                                        + bb.getId();
                                System.out.printf("%-10s %s\n", "Id Number:", bb.getId());
                                System.out.printf("%-10s %s\n", "Name:", bb.getName().getLastName() + ", "
                                        + bb.getName().getFirstName());
                                System.out.printf("%-10s %s %-10s%s\n", "Address:", bb.getAddress().getStreet() + "\n",
                                        " ", bb.getAddress().getCity() + ", " + bb.getAddress().getState() + " "
                                        + bb.getAddress().getZip());
                                System.out.printf("%-10s %s\n", "Date:", form.format(bb.getDate()));
                                System.out.printf("%-10s ", "Courses:");
                                for (j = 0; j < bb.list.size(); j++) {
                                    System.out.print(bb.list.get(j) + ", ");
                                }
                                System.out.println("\n");
                            }

                            break;
                        case 2: // View all active accounts
                            ArrayList list = db.getList();

                            if (list.isEmpty()) {
                                JOptionPane.showMessageDialog(null, "List is empty");
                            } else {
                                int i = 0, size = db.size();

                                System.out.println("CURRENTLY ENROLLED");
                                while (i < size) {
                                    Student u = db.list.get(i);
                                    System.out.printf("%-10s %s\n", "Id Number:", u.getId());
                                    System.out.printf("%-10s %s\n", "Name:", u.getName().getLastName() + ", "
                                            + u.getName().getFirstName());
                                    System.out.printf("%-10s %s %-10s%s\n", "Address:", u.getAddress().getStreet() + "\n",
                                            " ", u.getAddress().getCity() + ", " + u.getAddress().getState() + " "
                                            + u.getAddress().getZip());
                                    System.out.printf("%-10s %s\n", "Date:", form.format(u.getDate()));
                                    System.out.printf("%-10s ", "Courses:");
                                    for (j = 0; j < u.list.size(); j++) {
                                        System.out.print(u.list.get(j) + ", ");

                                    }
                                    System.out.println("\n");
                                    i++;
                                }
                                break;
                            }
                            break;

                        case 3: // View all dropped courses
                            ArrayList list2 = drop.getList();

                            if (list2.isEmpty()) {
                                JOptionPane.showMessageDialog(null, "List is empty");
                            } else {
                                int i = 0, size = db.size();

                                System.out.println("STUDENTS WHO DROPPED");
                                while (i < size) {
                                    Student u = db.list.get(i);
                                    System.out.printf("%-10s %s\n", "Id Number:", u.getId());
                                    System.out.printf("%-10s %s\n", "Name:", u.getName().getLastName() + ", "
                                            + u.getName().getFirstName());
                                    System.out.printf("%-10s %s %-10s%s\n", "Address:", u.getAddress().getStreet() + "\n",
                                            " ", u.getAddress().getCity() + ", " + u.getAddress().getState() + " "
                                            + u.getAddress().getZip());
                                    System.out.printf("%-10s %s\n", "Date:", form.format(u.getDate()));
                                    System.out.printf("%-10s ", "Courses:");
                                    for (j = 0; j < u.list.size(); j++) {
                                        System.out.print(u.list.get(j) + ", ");

                                    }
                                    System.out.println("\n");
                                    i++;
                                }
                                break;

                            }
                            break;
                    }
                    break;
                case 5: //Exit
                    done = true;

                    break;
            }
        }
    }
}
