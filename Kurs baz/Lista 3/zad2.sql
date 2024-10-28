--static
/*The cursor doesn't reflect any changes made in the database 
that affect either the membership of the result set 
or changes to the values in the columns of the rows that make up the result set. 
A static cursor doesn't display new rows inserted in the database after the cursor was opened, 
even if they match the search conditions of the cursor SELECT statement. 
If rows making up the result set are updated by other users, 
the new data values aren't displayed in the static cursor. 
The static cursor displays rows deleted from the database after the cursor was opened. 
No UPDATE, INSERT, or DELETE operations are reflected in a static cursor (unless the cursor is closed and reopened), not even modifications made using the same connection that opened the cursor.*/

--keyset
/*The membership and order of rows in a keyset-driven cursor are fixed 
when the cursor is opened. Keyset-driven cursors are controlled by a set of unique identifiers, or keys, known as the keyset. 
The keys are built from a set of columns that uniquely identify the rows in the result set. 
The keyset is the set of the key values from all the rows that qualified for the SELECT statement at the time the cursor was opened.*/

--dynamic
/*Dynamic cursors are the opposite of static cursors. 
Dynamic cursors reflect all changes made to the rows in their result set when scrolling through the cursor. 
The data values, order, and membership of the rows in the result set can change on each fetch. 
All UPDATE, INSERT, and DELETE statements made by all users are visible through the cursor.*/