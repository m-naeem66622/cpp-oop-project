# Hospital Management System

This Hospital Management System is a comprehensive project designed to manage various aspects of a hospital's operations, including patient, doctor, and nurse management. It is implemented in C++ and provides functionalities for reading and writing patient, doctor, and nurse data to CSV files, authenticating users, and managing medical histories.

## Features

- **Patient Management:** Add, find, authenticate, and manage patient information along with their medical history.
- **Doctor and Nurse Management:** Add, find, and authenticate doctors and nurses. Assign them to patients and manage their profiles.
- **Medical History Tracking:** Keep track of patients' medical histories, including medications, allergies, doctor assignments, and room numbers.
- **Data Persistence:** Reads from and writes to CSV files for patients, doctors, nurses, and medical histories, ensuring data persistence across sessions.
- **Authentication:** Supports authentication for patients, doctors, and nurses to access their respective information.

## Project Structure

The project is organized into several key files:

- **Header Files (.h):** Define the structure of classes and functions.
- **Implementation Files (.cpp):** Contain the implementation of the classes and functions declared in the header files.
- **CSV Files:** Store data about patients, doctors, nurses, and medical histories in a structured format.
- **Build Script [(script.ps1)](./script.ps1):** A PowerShell script to compile and build the project.

## Key Components

The project consists of the following key components:

- **Person Components** ([person.cpp](./person.cpp), [person.h](./person.h)): Base class for patients, doctors, and nurses.
- **Patient Components** ([patient.cpp](./patient.cpp), [patient.h](./patient.h)): Manage patient-specific information and medical history.
- **Doctor Components** ([doctor.cpp](./doctor.cpp), [doctor.h](./doctor.h)): Handle doctor-specific information and authentication.
- **Nurse Components** ([nurse.cpp](./nurse.cpp), [nurse.h](./nurse.h)): Manage nurse-specific information and assignments.
- **Hospital Components** ([hospital.cpp](./hospital.cpp), [hospital.h](./hospital.h)): Central component that ties together patients, doctors, and nurses.
- **User Interface** ([user_interface.cpp](./user_interface.cpp), [user_interface.h](./user_interface.h)): Provides a console-based interface for interacting with the system.
- **Utility Functions** ([util.cpp](./util.cpp), [util.h](./util.h)): Helper functions for common tasks like string formatting.
- **Data Files**: CSV files (`*.csv`) for storing persistent data (ignored in version control).

## Compilation and Execution

To compile the project, first create the `bin` directory if it doesn't exist:

```bash
mkdir -p bin
```

Then, use the provided PowerShell script [script.ps1](./script.ps1). This script compiles all necessary source files and generates an executable named main:

```bash
./script.ps1
```

To run the project, simply execute the compiled main executable

```bash
./bin/main.exe
```
