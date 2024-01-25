# Syndicate Management System

## Overview

Syndicate Management System is a console-based application implemented in C that facilitates the management of various aspects related to syndicate operations in a residential or commercial building. This system allows users to perform operations on different tables, including property owners, apartments, buildings, syndicates, charges, receipts, and invoices.

## Features

- **Table Operations:** Users can add, delete, display, and modify entries in different tables.
- **Logical Data Model:** The application follows a logical data model that considers the relationships between various entities.
- **Monthly Contributions:** Handles monthly contributions from property owners based on apartment measurements and additional values.
- **Receipt Generation:** Generates and records receipts for property owners after each monthly contribution.
- **Charge Distribution:** Manages the collection of contributions for building expenses such as water, electricity, and cleaning.
- **Flexible Data Model:** Accommodates the complexities of syndicate management as described in the provided information.

## Prerequisites

- This project is implemented in C and requires a C compiler for compilation.
- Standard C libraries are used, and no additional dependencies are needed.

## How to Use

1. **Compilation:** Compile the source code using a C compiler. For example, using GCC:

    ```bash
    gcc -o syndicat_management main.c
    ```

2. **Execution:** Run the compiled executable:

    ```bash
    ./syndicat_management
    ```

3. **Main Menu:** Choose the table you want to manage and perform various operations.

4. **Exit:** Exit the program when you are done.

## Tables

- **Tproprietaire:** Manages data related to property owners.
- **Tappartement:** Manages data related to apartments.
- **Timmeuble:** Manages data related to buildings.
- **Tsyndic:** Manages data related to syndicates.
- **Tcharge:** Manages data related to charges.
- **Trecu:** Manages data related to receipts.
- **Tfacture:** Manages data related to invoices.

![image](https://github.com/mrurespect/Syndicat-Management-Sys/assets/121578147/82ecd277-7d2e-4d50-abe0-da1d46578c87)

