/*
Kody Fong (1519213)
kbfong
PA3
Matrix.java is a program that implements all the required functions for a matrix to be used in Sparse.java
//Used Professor Tantalo's Piazza Post to carry me through the add, sub, and mult functions. I was totally lost for so long. https://piazza.com/class/jtrpcey11c221r?cid=432

*/
public class Matrix {

   private class Entry {
      int column;
      double data;
      
      //creates an Entry 
      Entry(int column1, double data1) {

         column = column1;
         data = data1;
      }
      
      
      public String toString() {

         return "(" + column + ", " + data + ")";
      }
      
      
      public boolean equals(Object x) {

         boolean isEqual = false;
         Entry entry = (Entry) x;
         if(entry.column == column && entry.data == data) 
         {
            isEqual = true;
         }
         
         return isEqual;
      }
   }

     private List[] row;
     private int size = 0;
     private int NNZ = 0;
   
   // makes a new n x n zero Matrix. pre: n >= 1
   Matrix(int n) {

      if(n < 1)
      {
         throw new RuntimeException("Matrix Error: Matrix() called with less than 1 column");
      }

      row = new List[n + 1]; 
      size = n; 
      for(int i = 1; i <= size; i++) 
      {

         row[i] = new List();
      }
   }

   //returns n, the number of rows and columns of this Matrix.
   int getSize() {

      return size;
   }
   
   //returns the number of non-zero entries in this Matrix.
   int getNNZ() {

       return NNZ;
   }
   
   //overrides Object's equals() method.
   public boolean equals(Object x) {

      boolean isEqual = false;
      Matrix matrix = (Matrix) x;
      
      
      

      if(matrix.getSize() == size && matrix.getNNZ() == NNZ)
      {
         for(int i = 1; i <= size; i++)
         {
             

            if(matrix.row[i].length() == row[i].length() ) //check if they are the same length first, then check if values are the same
            {
               if(matrix.row[i].equals(row[i])) 
               {
                  isEqual = true;
               }
               else //if the values aren't equal then return false 
               {
                  isEqual = false;
                  break;
               }
            }
            else
            {
               isEqual = false;  //the lengths are not the same therefore they aren't equal
               break;
            }
         }
      }
    
    
      else
      {
         isEqual = false; //the matrix sizes aren't the same and non zero entries aren't the same
      }
      return isEqual;
      
   }
   

   //sets this Matrix to the zero state.
   void makeZero() {

      if(size > 1)
      {
         for(int i = 1; i <= getSize(); i++)
       {

         row[i].clear();
       }
      }
      NNZ = 0;
   }

   //returns a new Matrix having the same entries as this Matrix.
   Matrix copy() {

      Matrix matrix = new Matrix(size);

      for(int i = 1; i <= getSize(); i++) 
      {
         row[i].moveFront();
         while(row[i].index() >= 0) 
         {
            Entry temp = (Entry) row[i].get();
            matrix.changeEntry(i, temp.column, temp.data);
            row[i].moveNext();
         }
      }
      return matrix;
   }
   
   // changes the ith row, jth column of this Matrix to x.  pre: 1 <= i <= getSize(), 1 <= j <= getSize()
     public void changeEntry(int i, int j, double x) {
        
        boolean xIsZero = false; //boolean to check if x is 0 or not

        if((i <= 1 && i >= getSize()) || (j <= 1 && j >= getSize()))
        {
            throw new RuntimeException( "Matrix Error: changeEntry() called on invalid positions.");
        }        

        if(x == 0)
        {
          xIsZero = true;
        }
        

        if (row[i].length() == 0) 
        {
          
            // if x == 0, do nothing
            if (xIsZero == false)
            {
                Entry E = new Entry(j, x);
                row[i].append(E); //inserts the entry into the back of the list
                NNZ++;
            
            }
        } 
        else 
        {
           
            row[i].moveFront(); //move the cursor to the front of the list

            for (int k = 1; k <= getSize(); k++)  //run through the matrix
            {
                Entry entry = (Entry) row[i].get(); 

                if (entry.column == j) 
                {
                    if (xIsZero == false)  //if x isn't zero then the entry's data becomes x
                    {
                        
                        entry.data = x;
                        break;
                    } 
                    else //x is zero so the number of non zero entries decreases and the cursor element at i is deleted from the list
                    {
                        
                        row[i].delete();
                        NNZ--;
                        break;
                    }
                }
                else if (entry.column > j) 
                {
                    if (xIsZero == true) //if x is zero just break the loop since nothing else needs to be done
                    {
                        break;
                    }
                    else
                    {
                        row[i].insertBefore(new Entry(j, x)); //if x isn't zero then insert the entry before the cursor element in the list at i
                        NNZ++;
                        break;
                    }
                }
                else //entry.column < j
                {
                    row[i].moveNext();
                    if (row[i].index() == -1) 
                    {
                        if (xIsZero == true)  //if x is zero break the loop
                        {
                            break;
                        }
                        else //if x is not zero then insert the entry into the back of the list
                        {
                            row[i].append(new Entry(j, x));
                            NNZ++;
                            break;
                        }
                    }
                }
            }
        }
    }

   // returns a new Matrix that is the scalar product of this Matrix with x.
   Matrix scalarMult(double x) {

      Matrix matrix = copy(); //creates a copy of the matrix
      for(int i = 1; i <= getSize(); i++) 
      {

         matrix.row[i].moveFront(); //move cursor to the front
         while(matrix.row[i].index() >= 0) 
         {
            Entry temp = (Entry) matrix.row[i].get();
            matrix.changeEntry(i, temp.column, (x * temp.data)); //changes the matrix entry with the entry that is multiplied by x
            matrix.row[i].moveNext();
         }
      }
      return matrix;
   }

   // returns a new Matrix that is the sum of this Matrix with M. pre: getSize() == M.getSize()
  
   Matrix add(Matrix M) {

      if (getSize() != M.getSize())
        {
            throw new RuntimeException( "Matrix Errow:  add() called on matrices of different sizes");
        }
      
        if (M == this)
        {
            return copy().scalarMult(2); //if matrices are the same then just multiply the same matrix by 2
        }

        Matrix matrix = new Matrix(getSize());

        for (int i = 1; i <= getSize(); i++)
        {
            List L = row[i];
            List R = M.row[i];
            L.moveFront(); 
            R.moveFront(); 
         
            while (L.index() >= 0 && R.index() >= 0)
            {
                Entry entry1 = (Entry) (L.get());
                Entry entry2 = (Entry) (R.get());

                if (entry1.column < entry2.column) //if the first entry's column is behind advance it
                {
                    matrix.changeEntry(i, entry1.column, entry1.data); //inserts the entry into the matrix
                    L.moveNext();
                }
                else if(entry1.column > entry2.column) //if the second entry's column is behind the first one advance it
                {
                    matrix.changeEntry(i, entry2.column, entry2.data); //inserts the entry into the matrix
                    R.moveNext();
                }
                else // the columns are the same
                {
                    if (entry1.data + entry2.data != 0) //when adding, if the values do not equal 0 then change the entry to the sum of the values
                    {
                        matrix.changeEntry(i, entry1.column, (entry1.data + entry2.data)); //insert the sum into the matrix
                        L.moveNext();
                        R.moveNext();
                    }
                    else //advance
                    {
                        L.moveNext();
                        R.moveNext();
                    }
                }
            }
          //Following the directions Prof. Tantalo said but instead of making another function to insert everything into the list
            //it's possible to just create a new list here based on when the cursors become undefined

            List S;
            if (L.index() >= 0)
            {
                S = L; //if List L's cursor is still defined, then we can just set list S equal to L
            }
            else
            {
                S = R; //if List L's cursor is not defined anymore, then we set list S  equal to R due to being off the list for List L
            }
            while (S.index() >= 0) //while the cursor is still defined add entries to the matrix
            {
                Entry entry3 = (Entry) S.get();
                matrix.changeEntry(i, entry3.column, entry3.data);
                S.moveNext();
            }
        } 
        return matrix;
   }
   
   // returns a new Matrix that is the difference of this Matrix with M.  pre: getSize() == M.getSize()
   Matrix sub(Matrix M) {

       if (getSize() != M.getSize())
        {
            throw new RuntimeException( "Matrix Error:  sub() called on matrices of different sizes");
        }
      
        Matrix matrix = new Matrix(getSize());
        
        if (M == this)
        {
            return matrix; //basically will do nothing and return an empty matrix
        }
        for (int i = 1; i <= getSize(); i++)
        {
            List L= row[i];
            List R = M.row[i];
            L.moveFront();
            R.moveFront();
           
            while (L.index() >= 0 && R.index() >= 0)
            {
                Entry entry1 = (Entry) (L.get());
                Entry entry2 = (Entry) (R.get());

                if (entry1.column < entry2.column) //if entry1 is behind, then advance it and insert it into the matrix
                {
                    matrix.changeEntry(i, entry1.column, entry1.data); 
                    L.moveNext();
                }

                else if( entry1.column > entry2.column) //if entry2 is behind then advance it and insert it into the matrix
                {
                    matrix.changeEntry(i, entry2.column, -entry2.data); 
                    R.moveNext();
                }
                else //columns are in the same spot
                {
            
                    if ((entry1.data - entry2.data) != 0) // if the difference doesn't equal zero then subtract the entries and insert them into the matrix
                    {
                        matrix.changeEntry(i, entry1.column, (entry1.data - entry2.data)); 
                        L.moveNext();
                        R.moveNext();
                    }
                    else //advance
                    {
                        
                        L.moveNext();
                        R.moveNext();
                    }
                }
            }
            
            //same thing that was done for add can be done for subtract except negative values must be handled
            List S;
            boolean isNegative; //a boolean that'll keep track of the negative sign for final calculation

            if (L.index() >= 0) //if list L hasn't fallen off the list yet then we can set list S to list L and isNegative is set to false
            {
                S = L;
                isNegative = false;

            }
            else //list L has fallen off the list so we set list S to list R and set isNegative to true
            {
                S = R;
                isNegative = true;
            }

    
            while (S.index() >= 0) //while the cursor is still defined, add entries to the matrix with a sign based on the boolean result
            {
                Entry entry3 = (Entry) (S.get());
                if(isNegative == true)
                {
                  matrix.changeEntry(i, entry3.column, (-1 * entry3.data));
                }
                else
                {
                  matrix.changeEntry(i,entry3.column, entry3.data);
                }
                
                S.moveNext();
            }
        }
        return matrix;
   }
   
   


   //returns a new Matrix that is the transpose of this Matrix.
   Matrix transpose() {

      Matrix matrix = new Matrix(getSize());
      for(int i = 1; i <= getSize(); i++) 
      {
         row[i].moveFront();
         while(row[i].index() >= 0) 
         {
            matrix.changeEntry(((Entry)row[i].get()).column, i, ((Entry)row[i].get()).data); //swaps the values of the row with the values of the columns 
            row[i].moveNext();
         }
      }
      return matrix;
   }

   // returns a new Matrix that is the product of this Matrix with M. pre: getSize() == M.getSize()

   Matrix mult(Matrix M) {

      if(getSize() != M.getSize())
      {
         throw new RuntimeException("Matrices aren't the same size");
      }

      Matrix matrix = new Matrix(getSize());
      Matrix A = M.transpose(); 
      for(int i = 1; i <= getSize(); i++)
       {
         
         for(int j = 1; j <= getSize(); j++) 
         {
            
            matrix.changeEntry(i, j, dot(row[i], A.row[j])); 
         }
      }
      return matrix;   
   }
   // computes the vector dot product of two matrix rows represented by Lists P and Q
   private static double dot(List P, List Q) {

      double dotProduct = 0.0;
      P.moveFront();
      Q.moveFront();
      while(P.index() >= 0 && Q.index() >= 0) 
      {
         Entry entry1 = (Entry) P.get();
         Entry entry2 = (Entry) Q.get();
         if(entry1.column > entry2.column)  //cursor for List Q is behind so advance it
         {
            Q.moveNext();
         } 
         else if(entry1.column < entry2.column)  //cursor for List P is behind so advance it
         {
            P.moveNext();
         } 
         else 
         {
            dotProduct += (entry1.data * entry2.data);
            P.moveNext();
            Q.moveNext();
         }
      }
      return dotProduct;
   }


   //overrides Object's toString() method.
   public String toString() {

      String out = "";
      for(int i = 1; i <= getSize(); i++) 
      {
         if(row[i].length() > 0)
            out += (i + ": " + row[i] + "\n"); 
      }
      return out;
   }

 }

   