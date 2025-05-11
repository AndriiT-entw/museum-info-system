# 🏛️ Museum Information System

This is a C++ console-based information system for managing museum operations, including exhibitions, ticket sales, visitors, staff, and role-based access control. The system uses a MySQL database and supports admin, manager, and visitor roles.

---

## 💡 Features

- 🔐 **User authentication** with roles: `Admin`, `Manager`, and basic visitor access.
- 🎫 **Ticket management** – buy tickets, assign to visitors.
- 🧑‍🏫 **Tour and guide management** – link tours with guides and museums.
- 🖼️ **Exhibition and author linking** – manage exhibitions and their creators.
- 👥 **Sponsor and seller tracking**
- 💾 **MySQL integration** for persistent storage.
- 📊 Console-based menus adapted to user roles.

---

## 🖥️ Technologies Used

- C++ (C++11+)
- MySQL Server 8.x
- MySQL Connector/C++ 8.0+
- Visual Studio 2019/2022

---

## 📁 Folder Structure

/src
├── main.cpp
├── database/ # DB connection handling
├── Users/ # Admin and Manager menus
├── Models/ # Business logic classes
├── sql/ # SQL scripts
└── docs/ # Documentation and report (optional)


## ⚙️ Setup Instructions

### 1. 🛠️ Install Prerequisites

- MySQL Server 8.x
- MySQL Connector/C++ (add `include` and `lib` paths in Visual Studio)
- Visual Studio 2019 or later

### 2. 🧱 Set Up Database

- Create the database using:


CREATE DATABASE museum;



CREATE TABLE Museum (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255),
    Address VARCHAR(255),
    Contact_Info VARCHAR(255)
);

CREATE TABLE Hall (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Hall_Name VARCHAR(255),
    Capacity INT,
    Museum_ID INT,
    FOREIGN KEY (Museum_ID) REFERENCES Museum(ID)
);

CREATE TABLE Guide (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255),
    Contact_Info VARCHAR(255),
    Years_Experience INT,
    Museum_ID INT,
    FOREIGN KEY (Museum_ID) REFERENCES Museum(ID)
);

CREATE TABLE Tour (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255),
    Date DATE,
    Guide_ID INT,
    Museum_ID INT,
    FOREIGN KEY (Guide_ID) REFERENCES Guide(ID),
    FOREIGN KEY (Museum_ID) REFERENCES Museum(ID)

);

CREATE TABLE Visitor (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255),
    Email VARCHAR(255),
    Ticket_ID INT,
    FOREIGN KEY (Ticket_ID) REFERENCES Ticket(ID)
);

CREATE TABLE Ticket (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Ticket_Type VARCHAR(100),
    Price DOUBLE,
    Visitor_Category VARCHAR(100),
    Tour_ID INT,
    Museum_ID INT,
    Sale_Date DATE,
    FOREIGN KEY (Tour_ID) REFERENCES Tour(ID),
    FOREIGN KEY (Museum_ID) REFERENCES Museum(ID)
);

ALTER TABLE Visitor
ADD FOREIGN KEY (Ticket_ID) REFERENCES Ticket(ID);

CREATE TABLE Ticket_Sale (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Seller_ID INT,
    Ticket_ID INT,
    FOREIGN KEY (Ticket_ID) REFERENCES Ticket(ID),
    FOREIGN KEY (Seller_ID) REFERENCES Seller(ID)
);

CREATE TABLE Author (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255),
    Email VARCHAR(255),
    Agreement VARCHAR(255)
);

CREATE TABLE Exhibition (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(255),
    Start_Date DATE,
    End_Date DATE,
    Cost DECIMAL,
    Museum_ID INT,
    FOREIGN KEY (Museum_ID) REFERENCES Museum(ID)
);

CREATE TABLE Exhibition_Author (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Share DECIMAL,
    Exhibition_ID INT,
    Author_ID INT,
    FOREIGN KEY (Exhibition_ID) REFERENCES Exhibition(ID),
    FOREIGN KEY (Author_ID) REFERENCES Author(ID)
);

CREATE TABLE Sponsor (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Sponsor_Name VARCHAR(255),
    Contact_Info VARCHAR(255),
    Contribution_Amount DOUBLE,
    Contribution_Date DATE,
    Museum_ID INT,
    FOREIGN KEY (Museum_ID) REFERENCES Museum(ID)
);

CREATE TABLE Seller (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Full_Name VARCHAR(255),
    Contact_Info VARCHAR(255)
);

CREATE TABLE User (
    ID INT AUTO_INCREMENT PRIMARY KEY,
    Username VARCHAR(255),
    Role ENUM('admin', 'manager', 'user'),
    Password VARCHAR(255)
);


Build & Run (F5)

🔐 User Roles
Role	Capabilities
Admin	Manage users, exhibitions, authors...
Manager	Edit tickets, tours, and exhibitions
Visitor	View and buy tickets



📑 Documentation
See docs/KP_Report.docx for:

UML class & interaction diagrams

Conceptual model

Test cases and results

Listings and database scripts

🧪 Testing
The project includes:

✔️ White-box: unit testing of methods

✔️ Gray-box: class-level testing

✔️ Black-box: functional testing via menus


🙌 Acknowledgements
Thanks to:

MySQL documentation

Stack Overflow community

YouTube C++ guides

ChatGPT for development guidance
