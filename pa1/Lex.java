/*
 *  Kody Fong (1519213)
 *  kbfong
 *  PA 1
 *  Lex.java is a program that utilizes list.java to sort out a List lexicographically. Utilizes insertion sort as the core sorting method for the List.
 */ 

import java.io.*;
import java.util.Scanner;

public class Lex 
{

    public static void main(String[] args) throws IOException 
    {

        Scanner in = null;
        PrintWriter out = null;  
        int numLines= 0;  
        String[] array = null;
        int value = 0;

        // check that there are two arguments
        if(args.length != 2)
        {
            System.err.println("Usage: Lex input output");
            System.exit(1);
        }

        in = new Scanner(new File(args[0])); //creates the input file
        out = new PrintWriter(new FileWriter(args[1])); //creates the outputfile

        //count numLines of input file args[0]
        while ( in.hasNextLine() ) 
        {
            numLines++;
            in.nextLine();
        }
        in.close(); //closes the input file

        array = new String[numLines]; //creates the string Array to store the lines of the file
        in = new Scanner(new File(args[0])); //reopens the file
         
        for(int i = 0; i < numLines; i ++)
        {
            array[i] = in.nextLine(); //puts all of the lines into the array
            
        }

        List newList = new List();
        newList.append(0); // initialize new list

        //utilizing insertion sort to sort the list and store the result into a string
        for (int i = 1; i < array.length; i++) 
        {
            int j = i - 1;
            newList.moveBack();  // go to end of List
            String temp = array[i]; //store the result into a string

            while (j >= 0 && temp.compareTo(array[newList.get()]) <=     0) 
            {
                newList.movePrev();
                j--;
            }
            if (newList.index() >= 0) 
            {
                newList.insertAfter(i);
            } 
            else 
            {
                newList.prepend(i);
            }
        }

        
        newList.moveFront();

        while (newList.index() >= 0) 
        {
            value = newList.get(); //gets the value from the array
            String sorted = array[value]; //the sorted array 
            out.println(sorted);          //prints out the sorted array
            newList.moveNext();
        }

       
        in.close();
        out.close();

    }

}
