# Memory Management
The Project for the LVA [System Software](https://ssw.jku.at/Teaching/Lectures/SSW/index.html) @JKU Linz by Prof. Hanspeter Mössenböck.

The project is performed by [@BioGustav](https://github.com/BioGustav) aka. Tobias and myself (MrMinemeet aka. Alex)

## Task description:
1. Create a memory management system which utilizes a free list in first-fit configuration
2. Implement a Mark & Sweep algorithm based on Deutsch-Schorr-Waite
3. Create a small real-world application to test the implementation of task 1. and 2.

**Full Task Description:** [MemoryManagementProject.pdf](https://ssw.jku.at/Teaching/Lectures/SSW/MemoryManagementProject.pdf)

All the tasks are basically fulfilled, with some minor… lets call it "adjustments".


## How to build?
Use `cmake --build .`.

## Things that didn't make it
* Creating a `static` version of the heap. We use a single instance in a global variable instead.
* Return proper pointer, meaning that at the moment the address of the header is returned. When being precise, it should have been the beginning of the actual data part. We missed that and reworking quite a bunch of the code would be too time consuming.
* Definitly not writing more readable and nice code 😉 (but it could be worse)
