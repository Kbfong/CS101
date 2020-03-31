/*
Kody Fong (1519213)
kbfong
PA3
List.java is a program that implements all the required functions for a linked list that was from previous pa's. This time, the list utilizes Objects 


*/


public class List
{
	private class Node
	{
		Object data;
		Node next;
		Node prev;

		Node(Object nData) 
		{
			data = nData;
			next = null;
			prev = null;
		}

		public String toString() //overriding of the toString method 
		{
			return String.valueOf(data);
		}
		public boolean equals(Object x) //overrides equals method. Was failing the NonEmpty equals test because I forgot to implement this.
									    //Thanks to Edward Chan who answered my question on Piazza https://piazza.com/class/jtrpcey11c221r?cid=532
		{
			Node temp = (Node) x;
			boolean isEqual = false;
			if(data.equals(temp))
			{
				isEqual = true;
			}
			return isEqual;

		}
	}

	private Node front;
	private Node back;
	private Node cursor;
	private int index;
	private int length;

	List()
	{
		front = null;
		back = null;
		cursor = null;
		length = 0;
		index = -1;
	}
	// Returns the number of elements in this List.
	int length()
	{
		return length;
	}
	// If cursor is defined, returns the index of the cursor element, otherwise returns -1.
	int index(){

		
		if (cursor == null) 
		{
			return -1;
		}
		return index;
	}
	// Returns front element. Pre: length()>0
	Object front()
	{
		if (length == 0) 
		{
			throw new RuntimeException("List Error: cannot call front() on empty List");
		}
		return front.data;
	}
	// Returns back element. Pre: length()>0
	Object back()
	{
		if (length == 0) 
		{
			throw new RuntimeException("List Error: cannot call back() on empty List");
		}
		return back.data;
	}
	// Returns cursor element. Pre: length()>0, index()>=0
	Object get()
	{
		if (length == 0 ) 
		{	
			throw new RuntimeException("List Error: cannot call get() on empty List");
		}
		if (cursor == null	) 
		{
			throw new RuntimeException("List Error: cannot call get() on cursor that is off the list");
			
		}
		else
		{
			return cursor.data;
		}
	}
	//// Returns true if and only if this List and L are the same integer sequence
	public boolean equals(Object L)
	{
		List tempList = (List) L; //creates a List object 

		boolean isEqual = true;
		Node thisTempFront = front;  
		Node thatTempFront = tempList.front;        
		if (length == tempList.length) //check if the List and L are at least the same length
		 {
			while( isEqual == true && thisTempFront != null && thatTempFront != null) 
			{
				if (thisTempFront.data.equals(thatTempFront.data)) //if the data within each node is equivalent move on to the next node to check
				{

					thatTempFront = thatTempFront.next;
					thisTempFront = thisTempFront.next;

				}
				else
				{
					isEqual = false; //if the data is not the same within each node then the integer sequence is not the same and the loop ends
				}
			}
			return isEqual;
		}
		else  //the List and L are not the same length, therefore they cannot be the same integer sequence
		{
			isEqual = false;
			return isEqual;
		}
	}
	//Manipulation procedures
	// Resets this List to its original empty state.
	void clear()
	{
		front = null;
		back = null;
		cursor = null;
		length = 0;
		index = -1;
	}
	// If List is non-empty, places the cursor under the front element, otherwise does nothing.
	void moveFront()
	{
		if (length != 0)
		 {
			cursor = front;
			index = 0; //cursor will be at the front
			

		}
	}
	// If List is non-empty, places the cursor under the back element, otherwise does nothing.
	void moveBack()
	{
		if (length != 0) 
		{
			cursor = back; 
			index = length - 1; //cursor will be at the back
			
		}
	}
	// If cursor is defined and not at front, moves cursor one step toward front of this List, if cursor is defined and at front, cursor becomes undefined, if cursor is undefined does nothing.
	void movePrev()
	{
		if (cursor != null) 
		{
			if (cursor == front) 
			{
				cursor = null;
                index = -1; //added this because i kept failing the test cases on the grading script
			}
			else
			{
				cursor = cursor.prev; //moves cursor toward front of the list
                index--; //added this because i kept failing the test cases on the grading script
			}
		}
	}
	// If cursor is defined and not at back, moves cursor one step toward back of this List, if cursor is defined and at back, cursor becomes undefined, if cursor is undefined does nothing.
	void moveNext()
	{
		if (cursor != null) 
		{
			if (cursor == back) 
			{
				cursor = null;
                index = -1; //added cause i was failing the test scripts and forgot to manage the indices 
			}
			else
			{
				cursor = cursor.next; //moves cursor toward back of the list
                index++; //added cause i was failing to the test scripts and forgot to manage the indicies
			}
		}
	}
	// Insert new element into this List. If List is non-empty, insertion takes place before front element.
	void prepend(Object data)
	{
		Node temp = new Node(data);
		if (front == null) 
		{
			front = back = temp; // if the list is empty the node will be the first node in the list making it the front and back node
			length++;
                        index = 0; //added because i failed the test scripts because i wasn't managing the indicies
		}
		else
		{
			front.prev=temp; //the temp node is inserted before the front
			temp.next=front;     //the node after temp will be the front because temp was inserted before the front
			front = temp;        //the front is now the temp node
			length++;
            index++;//added because i failed the test scripts because i wasn't managing the indicies
		}
	}

	// Insert new element into this List. If List is non-empty, insertion takes place after back element.
	void append(Object data)
	{
		Node temp = new Node(data);
		if (back == null) 
		{
			front = back = temp; //if the list is empty, then the new node temp becomes the front and back of the list as its the only node within the list
			length++;
		}
		else
		{
			back.next = temp; //the next node after the back node becomes the new node temp since it was inserted into the back of the list
			temp.prev = back; //the new node temp's previous node becomes the back since temp is now the new back of the list
			back = temp; //the new back of the list now becomes the new node temp
			length++;
		}
	}
	// Insert new element before cursor. Pre: length()>0, index()>=0
	void insertBefore(Object data)
	{
		Node temp = new Node(data);
		if (length == 0) 
		{
			throw new RuntimeException("List Error: cannot call insertBefore() on empty List");
		}
		if (cursor == null) 
		{
			throw new RuntimeException("List Error: cannot call insertBefore() on cursor that is off the list");
		}
		if (cursor == front) 
		{
			prepend(data);  //if the cursor is at the front of the list, you can just call prepend since you will be inserting the element before the front element 
		}
		else
		{
			
			temp.prev = cursor.prev; //the new node temp's previous becomes the cursors previous	
            temp.next = cursor;      //the new node temp's next becomes the cursor
            cursor.prev.next = temp; //cursor's previous next element becomes temp
            cursor.prev = temp;      //cursor's previous becomes temp
            length++;
            index++;
		}
	}
	// Inserts new element after cursor. Pre: length()>0, index()>=0
	void insertAfter(Object data)
	{
		Node temp = new Node(data);
		if (length==0) 
		{
			throw new RuntimeException("List Error: cannot call insertAfter() on empty List");
		}
		if (cursor == null) 
		{
			throw new RuntimeException("List Error: cannot call insertAfter() on cursor that is off the list");
		}
		if (cursor == back) 
		{
			append(data); //if the cursor is at the back of the list then you can just all append since you will be inserting the element into the back element
		}
		else
		{
			
			temp.next = cursor.next; //the new node temp's next will be the cursor's next
			temp.prev = cursor;      //the new node temp's previous will become the cursor
			cursor.next.prev = temp;  //cursor's next previous element becomes temp
			cursor.next = temp;      //cursor's next becomes temp
			length++;
		}
	}
	// Deletes the front element. Pre: length()>0
	void deleteFront()
	{
		if (length == 0) 
		{
			throw new RuntimeException("List Error: cannot call deleteFront() on empty List");
		}
		if (cursor == front) 
		{
			cursor = null;
			index = -1; //added because i was failing the test scripts because i wasn't managing the indicies
		}
        
		front = front.next; //front element becomes the next element in the list
		length--;
        index --; //added because i was failing the test scripts because i wasn't managing the indicies
		
	}

	// Deletes the back element. Pre: length()>0
	void deleteBack()
	{
		if (length == 0) 
		{
			throw new RuntimeException("List Error: cannot call deleteBack() on empty List");
		}
		if (cursor == back) 
		{
			cursor = null;
			index = -1;
		}
        
		back = back.prev; //the back element becomes the previous element in the list
		length--;

	}

	// Deletes cursor element, making cursor undefined. Pre: length()>0, index()>=0
	void delete()
	{
		if (length == 0) 
		{
			throw new RuntimeException("List Error: cannot call delete() on empty List");
		}
		if (cursor == null) 
		{
			throw new RuntimeException("List Error: cannot call delete() on cursor that is off the list");
		}
		if (cursor == front) 
		{
			deleteFront(); //deletes the front if the cursor is at the front

		}
		else if(cursor == back)
		{
			deleteBack(); //deletes the back if the cursor is at the back
		}
		else
		{
			cursor.prev.next=cursor.next;  
			cursor.next.prev=cursor.prev;
			cursor = null; 
			index = -1;
			length--;
		}
		
	}

	// Overrides Object's toString method. Returns a String representation of this List consisting of a space separated sequence of integers, with front on left.
	public String toString()
	{
		String stringList = "";
		Node temp = front;
		while(temp != null)
		{
			stringList += String.valueOf(temp.data) + " "; //places the data from the Node into the empty string
			temp = temp.next;              //moevs onto the next Node in the list
		}
		return stringList;
	}
	
	// Returns a new List representing the same integer sequence as this List. The cursor in the new list is undefined, regardless of the state of the cursor in this List. This List is unchanged.
	//List copy()
	//{
	//	List newList = new List();
//		Node temp = front;
//		while (temp!=null) 
//		{
//			newList.append(temp.data); //calls append on the new list
//			temp = temp.next;
//		}
//		newList.cursor = null; //undefined cursor
//		return newList;
//	}


}

