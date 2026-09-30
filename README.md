Engineering Data Structures (EECE4040) 
Topics covered: Advanced Linked Lists

Objective:

The objective of this Lab is to explore creating and using an ordered linked list.

Task 1: Create an ordered linked list class.

1.	Create a new project.  You can name this whatever you like.
2.	Design and implement an ordered linked list class as described in class.  This class should be a template.  The template is expected to have overloaded the >, < and == operators.
a.	The class should have the following methods fully implemented.
i.	Constructor
ii.	AddItem – adds an item from the list
iii.	GetItem – searches the list for the given item.  If found, it removes it from the list and returns it.  If not found, it returns a null pointer.
iv.	IsInlist – returns a bool indicating if the given item is in the list.
v.	IsEmpty – returns a bool indicating if the list is empty.
vi.	Size – returns an int indicating the number of items in the list.
vii.	SeeNext – returns the item without removing it from the list at a given location in the list.  The class will maintain the next location and will start at the first item in the list.  When it gets to the last item in the list, it will return a null pointer after it gets past the last item.  If the list is empty, this will throw an error or display an error message.  2 calls to SeeNext will return the 2 items next to each other in the list unless SeeAt or Reset is called in between the 2 calls (or the first call returns the last item in the list).
viii.	SeeAt – Finds an item at a location in the list (int passed in from user), and returns the item without removing it.  If the location passed by the user is past the end of the list, this will throw an error or display an error message.  This will set the location used by SeeNext to point at the item after the item returned.
ix.	Reset – resets the location that the SeeNext function uses to point at the first item in the list.
x.	Destructor
b.	All items passed to or from the class should be done so via a pointer rather than by value.
c.	Make sure you don’t have any memory leaks.
Complete this before moving on to task 2.


Task 2: Create a class to be used as the item stored in the list.  This class will be a student.  It should have the following members at a minimum.

1.	Priavte:
a.	FirstName
b.	LastName
c.	MNumber – This should store the M as well as any leading zeros.
d.	GPA
e.	Birthday
2.	Public:
a.	Constructor – This accepts parameters for FirstName, LastName, MNumber and Birthday.  It has an optional parameter for GPA which if missing is set to 0.0.
b.	GetName – this returns a string containing both FirstName concatenated with LastName
c.	GetMNumber
d.	GetAge – returns the age in years of the student.  
e.	Overloads of the >, < and == operators that compare the MNumber member of two student instances.
Complete this before moving on to task 3.


Task 3: Create a test program that has a menu allowing you to test each of the functions in your linked last class (Task 1).

1.	This should present the user with a choice of public member functions of your linked list class and ask which the user would like to try.
2.	When the user selects a member function, the program will prompt the user for any required information.  For example, the GetItem function only requires an MNumber as that is what is being compared but the AddItem requires the user to enter a FirstName, LastName, MNumber, Birthday and optionally a GPA.
3.	Test your program.  Include a screen shot of some of this testing in your lab report.
Complete this before moving on to task 4.
 

Task 4: Create a visualization of your list using ASCII art.

1.	Modify your Student class to include a display method that will output to the screen the contents of the class
a.	This method should write directly to the screen.
b.	This method does not need to display all members of the item, just key members (explain your choice of key members in your lab report).
c.	This method should reuse members of the class as much as possible.
2.	Modify your linked list class to add a new public method to display the list.
a.	This method should write directly to the screen.
b.	This method should walk through the list and display every item in the list on the screen.  The format of the output is up to you.
c.	To display the contents of the item in the list, it should call the display member of the item (created in step 1 of this task).
d.	This method should reuse members of the class as much as possible.
e.	This method should not change the results of SeeNext method meaning it should not have a different value for the internal variable used by SeeNext after this method completes.
3.	Modify your test program from task 3 to include an option that calls this new method.
4.	Include in the lab report a screen shot(s) of the output of a test.  


Task 5: Implement Copying and Assignment of the Ordered Linked List

Objective:
Extend the OrderedLinkedList class so that it correctly supports copying and assignment without sharing nodes or causing memory leaks.

Requirements
1.	Add a copy constructor to OrderedLinkedList.
o	It should create a completely independent copy of another ordered linked list.
o	Modifying one list should not affect the other.
2.	Add an overloaded assignment operator (=).
o	It should properly delete the existing contents of the destination list.
o	It should then make a deep copy of the source list.
3.	Make sure the nextLocation pointer is correctly initialized in the copied list.
4.	Test the following:
o	Create a list containing several students.
o	Copy the list using the copy constructor.
o	Modify the original list.
o	Verify that the copied list has not changed.
o	Assign one list to another using =.
o	Verify that both lists contain the correct students.
5.	Verify that there are no memory leaks or double deletions.


Task 6: Add Advanced Ordered-List Operations

Objective:
Expand the linked-list class by implementing additional operations that require manipulating nodes while maintaining the ordered structure.

Add the following public member functions:
1. RemoveAll
void RemoveAll();
Removes every item from the list and releases all dynamically allocated memory.
After calling this function:
IsEmpty()
should return true, and:
Size()
should return 0.
2. GetLargest
T* GetLargest();
Returns a pointer to the largest item in the list without removing it.
If the list is empty, display an appropriate error message or return nullptr.

3. GetSmallest
T* GetSmallest();
Returns a pointer to the smallest item without removing it.
4. Reverse
void Reverse();
Reverse the order of the linked list.
The list should remain a valid linked list after the operation.

5. DisplayAll
void DisplayAll();
Displays every item in the list without modifying or deleting the items.

Additional Requirements
Update the menu in main.cpp to allow the user to test all five new functions.
The program should also correctly update:
•	head
•	nextLocation
•	listSize
whenever necessary.


Task 7: Student Database with File Storage and Data Validation

Objective:
Convert the linked-list program into a small student database that can save and reload student information from a file.

Requirements
Extend the program to support the following menu options:
1. Add Student
2. Get Student
3. Search for Student
4. Display All Students
5. Display Student at Location
6. Remove All Students
7. Save Students to File
8. Load Students from File
9. Display Smallest M Number
10. Display Largest M Number
11. Reverse List
12. Exit
A. Save to File
Implement:
bool SaveToFile(string filename);
The function should save every student in the linked list to a text file.

B. Load from File
Implement:
bool LoadFromFile(string filename);

The function should:
1.	Open the specified file.
2.	Remove the current contents of the list.
3.	Read each student from the file.
4.	Dynamically create a Student.
5.	Add the student to the ordered linked list.
6.	Maintain the correct ordering automatically.

C. Validate Student Information
The program should reject invalid input such as:
•	Empty first or last name.
•	Invalid M Number format.
•	GPA below 0.0.
•	GPA above 4.0.
•	Invalid birthday.
•	Future birthday.
•	Duplicate M Number.

D. Duplicate M Numbers
Before adding a student, use IsInList() to determine whether the M Number already exists.
If it does:
Error: A student with M00012345 already exists.
Student was not added.

E. File Error Handling
The program should gracefully handle situations such as:
Error: Unable to open file.
rather than crashing.

F. Testing
Test the following scenarios:
1.	Save an empty list.
2.	Save a list containing several students.
3.	Exit the program.
4.	Restart the program.
5.	Load the saved file.
6.	Verify that all students were restored.
7.	Verify that they remain sorted by M Number.
8.	Attempt to add a duplicate student.
9.	Attempt to enter an invalid GPA.
10.	Attempt to load a nonexistent file.



Lab Submission:
1.	Include the following information in your miniproject1 submission:
a.	Screenshots of the output/results of your program in a pdf/word file
b.	Miniproject1.cpp file (Source Code)
c.	Input and output files (if any), and any special instructions to compile and run those programs (if any).



Lab Grading:
1.	2.0% - Task 1 has been correctly implemented and meets all requirements.
2.	2.0% - Task 2 has been correctly implemented and meets all requirements. 
3.	2.0% - Task 3 has been correctly implemented and meets all requirements.
4.	2.0% - Task 4 has been correctly implemented and meets all requirements.
5.	2.0% - Task 5 has been correctly implemented and meets all requirements. 
6.	2.0% - Task 6 has been correctly implemented and meets all requirements.
7.	3.0% - Task 7 has been correctly implemented and meets all requirements.
8.	5.0% - Lab report contains all required information and is well written.
If program fails to compile, 0% will be given for that Task.





