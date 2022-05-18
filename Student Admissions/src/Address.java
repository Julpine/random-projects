/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Test;

/**
 *
 * @author Julian Pineiro
 */
public class Address {

    String street;
    String city;
    String state;
    String zip;

    Address(String str, String city, String st, String zip) {
        street = str;
        this.city = city;
        state = st;
        this.zip = zip;

    }

    public String getStreet() {
        return street;
    }

    public String getCity() {
        return city;
    }

    public String getState() {
        return state;
    }

    public String getZip() {
        return zip;
    }

    void changeAddress(String street, String city, String st, String zip) {
        this.street = street;
        this.city = city;
        this.state = st;
        this.zip = zip;
    }

}
