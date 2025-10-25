# Instagram-Database-CLI-Tool

# IGDB - Instagram Database CLI Tool

IGDB is a lightweight C program that manages a simple database of social media handles.  
It supports adding, updating, sorting, finding, swapping, listing, and saving user records,  
each consisting of a handle, follower count, comment, and last modified timestamp.

---

## 🚀 Features

- **Add** new social media handles with follower count and comments  
- **List** all records in a formatted table view  
- **Find** records by handle  
- **Update** follower count and comment of an existing record  
- **Sort** records alphabetically by handle  
- **Swap** two records for quick reordering  
- **Save** database contents to a CSV file  
- **Auto-load** from `database.csv` on startup  

---

## 📂 Project Structure

.
├── Makefile
├── database.c
├── database.h
├── igdb.c
└── database.csv (generated/loaded automatically)

yaml
Copy code

- **database.c** - Core database operations: create, append, lookup, load, and write to CSV  
- **database.h** - Data structures and function declarations  
- **igdb.c** - Command-line interface logic: user commands, validation, and record display  
- **Makefile** - Simplifies compilation  

---

## ⚙️ Compilation

To build the project, simply run:

```bash
make
This will produce an executable named igdb.

To clean object files:

bash
Copy code
make clean
(Add a clean rule if desired.)

🧠 Usage
Run the program in your terminal:

bash
Copy code
./igdb
Example Commands
Command	Description
list	Lists all records in a formatted table
add HANDLE FOLLOWERS	Adds a new handle entry (prompts for comment)
update HANDLE FOLLOWERS	Updates an existing entry (prompts for comment)
find HANDLE	Displays one record
sort	Sorts records alphabetically by handle
swap HANDLE1 HANDLE2	Swaps the order of two records
save	Writes database to database.csv
exit	Quits the program safely (warns if unsaved changes)
exit fr	Forces exit without saving

💾 Data Format
The database is stored as a CSV file:

pgsql
Copy code
HANDLE,FOLLOWERS,COMMENT,DATE_MODIFIED
Example:

Copy code
techguru,1024,Great engagement,1712608500
🧩 Contributors
Name	Role	Contributions
Jerry Luo	Developer	File I/O, CSV parsing, and database write operations
Louis Renard	Developer	Core database structure and memory management
Andra Yvonne Ivanciu	Developer	Add, update, list, and sort features
Alexander Dai	Developer	Find, swap, and command loop implementation

🧠 Notes
Comments cannot contain commas or newlines.

Handles are limited to 32 characters.

Comments are limited to 64 characters.

The program dynamically resizes the database as new entries are added.

📜 License
This project is released under the MIT License.
Feel free to use, modify, and distribute.

🧰 Example Session
shell
Copy code
$ ./igdb
Loaded 3 records.
> list
HANDLE               | FOLLOWERS | LAST MODIFIED   | COMMENT
---------------------|------------|------------------|------------------------------
techguru             | 1024       | 2025-04-09 14:20 | Great engagement
codecraft            | 850        | 2025-04-08 09:33 | Weekly updates

> add datawiz 1200
Comment> Posts daily insights
> save
Wrote 4 records.
> exit
