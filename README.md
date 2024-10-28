# ATM Management System

## Overview

The **ATM Management System** is a C++ application designed to simulate an ATM interface for two major banks: ICICI and HDFC. This prototype allows users to manage their banking needs efficiently, including account creation, secure PIN setup, and essential banking transactions such as deposits, withdrawals, and balance checks.

## Features

- **Account Creation**: Users can create a new bank account through a simple interface.
- **Secure PIN Setup**: Users can set their ATM PIN via an OTP (One-Time Password) verification process to ensure account security.
- **Transaction Operations**:
  - **Deposit**: Easily deposit funds into the bank account.
  - **Withdrawal**: Withdraw cash as needed, with customizable amounts.
  - **Check Balance**: View current account balance at any time.
- **Transaction History**: File handling is implemented to track and display the history of transactions for user reference.
- **Inter-Bank Functionality**: Users from ICICI can use HDFC ATMs and vice versa, with applicable fees for inter-bank transactions.

## Technologies Used

- **Programming Language**: C++
- **OOP Concepts**:
  - **Classes and Objects**: Structuring the code with relevant entities.
  - **Inheritance**: Extending functionalities for various bank operations.
  - **Polymorphism**: Utilizing method overriding for flexible operations.
- **File Handling**: For persistent storage of user data and transaction history.

## Installation

To set up the ATM Management System on your local machine, follow these steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/ATM-Management-System.git
2. **Navigate to the project directory**:
   ```bash
   cd ATM-Management-System
3. **Compile the C++ files**:
   ```bash
   g++ main.cpp -o atm_system
4.**Run the Program**:
   ```bash
  ./atm_system
