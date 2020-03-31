
/*
Kody Fong (1519213)
kbfong
PA3
Sparse.java is a program that runs Matrix.java.


*/
import java.util.Scanner;
import java.io.*;

public class Sparse {

    public static void main(String[] args) throws IOException {

        Matrix Matrix1 = new Matrix(1);
        Matrix Matrix2 = new Matrix(1);

        int n = 0;
        int a = 0;
        int b = 0;
        int row = 0;
        int col = 0;
        double data = 0.0;
        Scanner in;
        PrintWriter out;

        // check that there are two command arguments
        if(args.length < 2 || args.length > 2){
            System.err.println("Usage: Sparse infile outfile");
            System.exit(1);
        }

        in = new Scanner(new File(args[0]));
        out = new PrintWriter(new FileWriter(args[1]));

        
        while (in.hasNext()) {

            
            n = in.nextInt();  
            a = in.nextInt();  
            b = in.nextInt();  

            //creates matrices of size n x n
            Matrix1 = new Matrix(n);
            Matrix2 = new Matrix(n);

            
            for (int i = 1; i <=a; i++){
                row = in.nextInt();
                col = in.nextInt();
                data = in.nextDouble();

                // puts the entry into the matrix1
                Matrix1.changeEntry(row, col, data);
            }

            
            for (int i = 1; i <=b; i++){
                row = in.nextInt();
                col = in.nextInt();
                data = in.nextDouble();

                //puts the entry into the matrix2
                Matrix2.changeEntry(row, col, data);
            }

        }

        // print Matrix A
        out.println("A has " + a + " non-zero entries:");
        out.println(Matrix1);

        // print Matrix B
        out.println("B has " + b + " non-zero entries:");
        out.println(Matrix2);

        // print Matrix (1.5) x A
        out.println("(1.5)*A =");
        out.println(Matrix1.scalarMult(1.5));

        // print Matrix (A+B)
        out.println("A+B =");
        out.println(Matrix1.add(Matrix2));

        // print Matrix (A+A)
        out.println("A+A =");
        out.println(Matrix1.add(Matrix1));

        // print Matrix (B-A)
        out.println("B-A =");
        out.println(Matrix2.sub(Matrix1));

        // print Matrix (A-A)
        out.println("A-A =");
        out.println(Matrix1.sub(Matrix1));

        // print Matrix transpose(A)
        out.println("Transpose(A) =");
        out.println(Matrix1.transpose());

        // print Matrix (A*B)
        out.println("A*B =");
        out.println(Matrix1.mult(Matrix2));

        // print Matrix (B*B)
        out.println("B*B =");
        out.print(Matrix2.mult(Matrix2));

        // close files
        in.close();
        out.close();

    }

}