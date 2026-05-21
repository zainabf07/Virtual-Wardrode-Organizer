# Virtual Wardrobe Management System

## Project Overview

The Virtual Wardrobe Management System is a console-based application developed in C++ using Object-Oriented Programming (OOP) concepts and file handling. The system allows users to manage clothing items, create outfits, filter wardrobe collections, and store data permanently using text files.

This project demonstrates the practical implementation of core programming concepts such as inheritance, encapsulation, constructors, arrays of objects, and file management.

---

# Objectives

* To develop a digital wardrobe management system using C++
* To apply Object-Oriented Programming concepts in a real-world application
* To implement file handling for permanent data storage
* To provide an interactive menu-driven console application

---

# Features

* Add clothing items
* View all clothes
* Remove clothing items
* Edit clothing items
* Create outfits
* View saved outfits
* Remove outfits
* Filter clothes by:

  * Category
  * Color
  * Season
* File handling for saving and loading data
* User-friendly console interface

---

# OOP Concepts Used

## Classes and Objects

The system is built using multiple classes such as:

* ClothingItem
* Top
* Bottom
* Shoes
* Accessory
* Outfit
* UserWardrobe

## Inheritance

Derived classes inherit from the base class `ClothingItem`.

## Encapsulation

Data members are protected and accessed using getter and setter functions.

## Constructors

Parameterized constructors are used for object initialization.

## Function Overriding

Virtual functions are used to improve extensibility.

---

# Technologies Used

* C++
* File Handling
* Object-Oriented Programming
* Standard Library Functions

---

# File Handling

The project uses two text files:

## clothes.txt

Stores all clothing item information.

### Example

top|Black T Shirt|Black|Nike|Summer|Casual

bottom|Blue Jeans|Blue|Levis|Winter|Casual

---

## outfits.txt

Stores saved outfits.

### Example

top|Black T Shirt|Black|Nike|Summer|Casual

bottom|Blue Jeans|Blue|Levis|Winter|Casual

shoes|White Sneakers|White|Adidas|AllSeason|Sport

accessory|Silver Watch|Silver|Casio|AllSeason|Formal

---

# System Functionalities

## Add Clothing Item

Users can add clothing items by entering:

* Category
* Name
* Color
* Brand
* Season
* Style

---

## View All Clothes

Displays all stored clothing items in a formatted table.

---

## Remove Clothing Item

Allows users to remove clothing items using an index.

---

## Edit Clothing Item

Users can update clothing item details.

---

## Create Outfit

Users can combine:

* Top
* Bottom
* Shoes
* Accessory

to create a complete outfit.

---

## View Saved Outfits

Displays all saved outfits.

---

## Filter Clothes

Users can filter clothes by:

* Category
* Color
* Season

---

# Advantages of the System

* Easy wardrobe organization
* Permanent data storage
* Simple and user-friendly interface
* Demonstrates practical OOP implementation
* Easily expandable for future improvements

---

# Future Improvements

* Graphical User Interface (GUI)
* Database integration
* User authentication system
* Smart outfit recommendations
* Weather-based outfit suggestions
* Random outfit generator
* Color matching system

---

# Conclusion

The Virtual Wardrobe Management System successfully demonstrates the implementation of Object-Oriented Programming concepts and file handling in C++. The project provides an efficient way to digitally manage clothing items and outfits while maintaining clean code structure and modular design.

---

# Author

Zainab Fatima

---

# License

This project is licensed under the MIT License.
