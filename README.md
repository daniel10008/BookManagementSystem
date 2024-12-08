
# **Book Management System**

## **Overview**
The Book Management System is a robust C++ application designed to manage a bookstore's inventory. It offers functionalities such as adding, updating, deleting, searching, and purchasing books, along with generating sales reports and maintaining transaction records. This system also includes features like rating books, tracking search history, and saving/loading inventory data from a file.

---

## **Features**
### **Core Functionalities**
1. **Add a Book**  
   Add new books to the inventory with details like ISBN, title, author, publisher, genre, price, and stock.
   
3. **Display Book Inventory**  
   View the entire inventory in a well-formatted tabular format.

4. **Update a Book**  
   Modify details of an existing book using its ISBN.

5. **Search a Book**  
   Search for books by:
   - ISBN  
   - Title  
   - Author  

6. **Purchase a Book**  
   Update stock and calculate the total cost based on the number of books purchased.

7. **Rate a Book**  
   Provide feedback by rating books on a scale of 0.0 to 5.0. Calculate and display the average rating.

8. **Delete a Book**  
   Remove a book from the inventory using its ISBN. Requires admin authentication.

9. **Display Successful and Unsuccessful Transactions**  
   Track and display the number of successful and unsuccessful book transactions.

10. **Generate Sales Report**  
   View a detailed sales report showing books sold, revenue generated, and total sales.

11. **Show Search History**  
    Display a list of recent search queries.

12. **Save Inventory to File**  
    Save the current inventory data to a file (`inventory.txt`) for future use.

13. **Load Inventory from File**  
    Load previously saved inventory data from a file into the system.

14. **Exit**  
    Exit the program and free all allocated memory.

---

## **Technologies Used**
- **Programming Language:** C++
- **File I/O:** Used for saving and loading inventory data to/from a file.
- **Dynamic Memory Management:** Efficient allocation and deallocation of memory for book objects.
- **OOP Principles:** Encapsulation, inheritance, and polymorphism for structured code.
- **Standard Template Library (STL):** Vectors for managing inventory, and maps for search history.

---

## **Usage Instructions**
### **Prerequisites**
- A C++ compiler (e.g., GCC, Clang, or MSVC).
- A text editor or IDE (e.g., Visual Studio Code, CLion).

### **How to Run**
1. Clone this repository:
   ```bash
   git clone https://github.com/daniel10008/BookManagementSystem.git
   cd BookManagementSystem
